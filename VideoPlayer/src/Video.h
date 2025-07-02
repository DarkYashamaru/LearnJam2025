#pragma once
#include "Debug.h"

extern "C"
{
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <inttypes.h>
	#include <libavutil/error.h>
	#include <libswscale/swscale.h>
	#include <libavutil/imgutils.h>
}

class Video
{
private:
public:
	bool LoadFrame(const char* path, int* width, int* height, unsigned char** data);
};