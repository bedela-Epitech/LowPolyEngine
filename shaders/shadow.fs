#version 330 core
precision highp float;

layout(location = 0) out float fragmentdepth;

void main()
{
    // Not really needed, OpenGL does it anyway
    fragmentdepth = gl_FragCoord.z;
}