#version 330 core

in vec2 texture_coords;
out vec4 frag_color;

uniform sampler2D texture_s1;
uniform sampler2D texture_s2;
uniform float coef; // 0.2

void main()
{
	//frag_color = texture(texSampler1, texture_coords);
	//frag_color = texelFetch(texSampler1, ivec2(gl_FragCoord.xy), 0);

	frag_color = mix(texture(texture_s1, texture_coords), texture(texture_s2, texture_coords), coef);
}
