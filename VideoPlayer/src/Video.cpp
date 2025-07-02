#include "Video.h"

bool Video::LoadFrame(const char* path, int* width, int* height, unsigned char** data)
{
	//Open the file using libavformat
	AVFormatContext* avFormatContext = avformat_alloc_context();

	if (avformat_open_input(&avFormatContext, path, NULL, NULL) != 0)
	{
		Debug::LogError("Couldn't open video file");
		return false;
	}

	//find the first valid video stream in file

	int videoStreamIndex = -1;
	AVCodecParameters* avCodecParams = nullptr;
	const AVCodec* codec = nullptr;

	for (int i = 0; i < avFormatContext->nb_streams; i++)
	{
		avCodecParams = avFormatContext->streams[i]->codecpar;
		codec = avcodec_find_decoder(avCodecParams->codec_id);
		if (!codec)
			continue;

		if (avCodecParams->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoStreamIndex = i;
			break;
		}
	}

	if (videoStreamIndex == -1)
	{
		Debug::LogError("Couldn't find valid video stream in file");
		return false;
	}

	AVCodecContext* codecContext = nullptr;
	codecContext = avcodec_alloc_context3(codec);
	
	if (avcodec_parameters_to_context(codecContext, avCodecParams) < 0)
	{
		Debug::LogError("Couldn't initialize avcodec parameters to context");
		return false;
	}

	if (avcodec_open2(codecContext, codec, NULL) < 0)
	{
		Debug::LogError("Couldn't open codec");
		return false;
	}

	AVFrame* avFrame = av_frame_alloc();
	AVPacket* avPacket = av_packet_alloc();

	while (av_read_frame(avFormatContext, avPacket) >= 0)
	{
		if (avPacket->stream_index != videoStreamIndex)
			continue;

		int response = avcodec_send_packet(codecContext, avPacket);
		if (response < 0)
		{
			Debug::LogError("Failed to decode packet");
			return false;
		}

		response = avcodec_receive_frame(codecContext, avFrame);
		if (response == AVERROR(EAGAIN) || response == AVERROR_EOF)
		{
			Debug::Log("Failed to receive frame, continuing");
			continue;
		}
		else if (response < 0)
		{
			Debug::LogError("Error while trying to receive frame");
			return false;
		}

		av_packet_unref(avPacket);
		break;
	}

	//Buffer to store the final image
	unsigned char* frameData = new unsigned char[avFrame->width * avFrame->height * 4];

	// Create another AVFrame to store the final RGBA data
	AVFrame* rgbaFrame = av_frame_alloc();
	rgbaFrame->format = AV_PIX_FMT_RGBA;
	rgbaFrame->width = avFrame->width;
	rgbaFrame->height = avFrame->height;

	av_image_fill_arrays(rgbaFrame->data, rgbaFrame->linesize, frameData, AV_PIX_FMT_RGBA, avFrame->width, avFrame->height, 1);

	// set up SwsContext for RGBA conversion
	SwsContext* swsContext = sws_getContext(
		avFrame->width, avFrame->height, codecContext->pix_fmt, // source format
		avFrame->width, avFrame->height, AV_PIX_FMT_RGBA,		// target format
		SWS_BILINEAR, nullptr, nullptr, nullptr
	);

	// perform the conversion to RGBA
	sws_scale(
		swsContext,
		avFrame->data, avFrame->linesize,
		0, avFrame->height,
		rgbaFrame->data, rgbaFrame->linesize
	);

	* width = avFrame->width;
	*height = avFrame->height;
	*data = frameData;

	sws_freeContext(swsContext);
	av_frame_free(&rgbaFrame);
	av_frame_free(&avFrame);
	av_packet_free(&avPacket);
	avformat_close_input(&avFormatContext);
	avformat_free_context(avFormatContext);
	avcodec_free_context(&codecContext);

	return true;
}
