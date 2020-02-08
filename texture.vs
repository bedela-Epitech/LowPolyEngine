#version 130
precision highp float;

attribute vec4 aPos;
attribute vec2 textCoord;

out vec2 v_Texture;

void main()
{
    gl_Position = aPos;
    v_Texture = textCoord;
}