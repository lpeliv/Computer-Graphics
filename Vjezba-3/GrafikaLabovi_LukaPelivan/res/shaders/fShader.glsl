#version 330 core

in vec3 normals;
in vec2 TexCord;
in vec3 newColor;
in vec3 position;

out vec4 fColor;

uniform sampler2D secondTex;
uniform sampler2D tex;
uniform vec3 xColor;

void main()
{
	fColor=texture(tex, vec2(1.0 - TexCord.x, TexCord.y))*vec4(position, 1.0f);
	//fColor=vec4(xColor, 1.0);
	//fColor=vec4(newColor, 1.0f);
	//fColor=vec4(position, 1.0f);
}