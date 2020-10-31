#version 330 core
precision highp float;

attribute vec4 aPos;
uniform mat4 mvp;

void main()
{
     gl_Position = mvp * aPos;
}