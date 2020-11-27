#version 330 core

in vec2 texture_coords;
out vec4 frag_color;

uniform sampler2D texture_s1;

void main()
{
	frag_color = texture(texture_s1, texture_coords);
}