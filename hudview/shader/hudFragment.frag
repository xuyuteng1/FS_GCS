
#version 330 core



uniform sampler2D ourTexture;
varying vec2 fTexCoord;
in vec4 fColor;

void main(void)
{
    vec4 weakMask = texture2D(ourTexture,fTexCoord);
    vec4 mask = fColor;


    vec4 tempColor = mask + weakMask;
    gl_FragColor = tempColor;

}
