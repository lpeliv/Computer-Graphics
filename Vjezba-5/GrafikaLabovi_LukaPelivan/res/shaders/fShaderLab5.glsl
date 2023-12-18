#version 330 core

out vec4 fColor;

uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 ambientColor;
uniform float ambientStrength;

void main()
{
    vec3 ambient = ambientStrength * ambientColor;
    vec3 result = ambient * objectColor;
	
	fColor=vec4(result, 1.0);
	
	//Task-1
	//fColor=vec4(lightColor * objectColor, 1.0);
	
}