#version 330
precision highp float;

in  vec3 ex_Color;
out vec4 out_Color;

uniform sampler2D u_Texture;
in vec2 v_Texture;

void main(void)
{
    vec4 textColor = texture(u_Texture, v_Texture);
    out_Color = textColor;
}
