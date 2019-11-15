#version 130
precision highp float;
attribute vec3 aPos;
attribute  vec3 in_Color;
attribute  vec3 normal;
varying  vec3 ex_Color;

uniform vec3 lightDir;
uniform float ambiantCoeff;
uniform vec3 cameraDir;
uniform vec3 lightColor;

uniform mat4 view;
uniform mat4 projection;

float diff = max(dot(normal, lightDir), 0.0);
vec3 reflectDir = reflect(-lightDir, normal);
float spec = pow(max(dot(cameraDir, reflectDir), 0.0), 32);
float specularStrength = 0.5;


vec3 ambiant = ambiantCoeff * lightColor;
vec3 diffuse = diff * lightColor;
vec3 specular = specularStrength * spec * lightColor;

void main()
{
    ex_Color = (ambiant + diffuse + specular) * in_Color;
    gl_Position = projection * view * vec4(aPos, 1.0f);
}