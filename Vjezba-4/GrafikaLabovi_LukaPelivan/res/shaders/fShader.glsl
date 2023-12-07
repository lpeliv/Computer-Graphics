#version 330 core

in vec3 normals;
in vec2 TexCoord;

out vec4 fColor;

uniform sampler2D tex;

void main()
{
	fColor=texture(tex, TexCoord);
}