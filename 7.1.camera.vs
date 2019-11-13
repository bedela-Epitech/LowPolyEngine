#version 130
precision highp float;
attribute vec3 aPos;
attribute  vec3 in_Color;
varying  vec3 ex_Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    ex_Color = in_Color;
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}