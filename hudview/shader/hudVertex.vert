
#version 330 core


attribute vec4 vPosition;
in vec4 vColor;
out vec4 fColor;
attribute vec2 vTexCoord;
varying vec2 fTexCoord;

void main(void)
{
    gl_Position = vec4(vec3(vPosition.x,vPosition.y,vPosition.z),1.0f);
    fColor = vColor;
    fTexCoord = vTexCoord;
}
