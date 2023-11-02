#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCord;

out vec3 normal;
out vec2 TexCord;
out vec3 newColor;
out vec3 position;

uniform float xOffset;
uniform float yOffset;

uniform vec3 XColor;

void main()
{ 
	gl_Position=vec4(aPos.x + xOffset, aPos.y + yOffset, aPos.z , 1.0f);
	normal=aNorm;
	TexCord=aTexCord;
	newColor=XColor;
	position=aPos;
}