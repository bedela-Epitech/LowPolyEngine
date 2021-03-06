#version 330 core
precision highp float;

attribute vec4 aPos;
uniform mat4 lightmvp;

void main()
{
     gl_Position = lightmvp * aPos;
}