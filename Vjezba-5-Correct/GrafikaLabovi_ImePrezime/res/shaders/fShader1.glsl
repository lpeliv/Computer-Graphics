#version 330 core

in vec3 normals;
in vec2 TexCord;

out vec4 fColor;

uniform sampler2D tex;

void main()
{
	fColor=vec4(0.5f, 0.75f, 0.5f, 1.0f);
}