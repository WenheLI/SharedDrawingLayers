#version 150

uniform sampler2DRect tex0;
uniform float u_time;

in vec2 texCoordVarying;
out vec4 outputColor;

void main()
{
    vec4 rTxt = texture(tex0, texCoordVarying);
    outputColor = rTxt;
}