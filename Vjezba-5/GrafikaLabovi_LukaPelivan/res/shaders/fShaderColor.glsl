#version 330 core

out vec4 fColor;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	fColor=vec4(lightColor * objectColor, 1.0);
	//fColor=vec4(1.0);
}