#version 330 core

layout (location = 0) in vec3 position_at;
layout (location = 1) in vec2 texture_coords_at;

out vec2 texture_coords;

void main()
{
	gl_Position = vec4(position_at.xyz, 1.0);
	texture_coords = texture_coords_at;
}
