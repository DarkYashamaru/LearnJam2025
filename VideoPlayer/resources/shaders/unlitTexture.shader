#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TextCoord;

void main ()
{
	gl_Position = position;
	v_TextCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextCoord;

uniform vec4 u_color;
uniform sampler2D u_Texture;

void main ()
{
	vec4 textColor = texture(u_Texture, 1.0 - v_TextCoord);
	color = textColor;
};
