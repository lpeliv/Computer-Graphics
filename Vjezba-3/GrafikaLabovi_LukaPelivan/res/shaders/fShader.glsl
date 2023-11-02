#version 330 core

in vec3 normals;
in vec2 TexCord;
in vec3 newColor;
in vec3 position;

out vec4 realColor;
out vec4 fColor;

out vec4 fFragColor;
out vec3 outputColor;
out vec4 FragColor;

uniform sampler2D secondTex;
uniform sampler2D tex;



uniform vec3 xColor;

void main()
{
	realColor=texture(secondTex, vec2(1.0 - TexCord.x, TexCord.y));
	fColor=texture(tex, vec2(1.0 - TexCord.x, TexCord.y));
	outputColor=xColor;
	FragColor=vec4(newColor, 1.0f);
	fFragColor=vec4(position, 1.0f);
	
}