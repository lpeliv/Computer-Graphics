#version 330 core
out vec4 FragColor;

uniform vec3 ambientLight;
uniform float ambientLightFactor;
uniform vec3 lightColor;

void main()
{
    FragColor = vec4(objectColor * ambientLight * ambientLightFactor);
}