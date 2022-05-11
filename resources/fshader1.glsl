#version 330

in vec4 color;
in vec2 v_texcoord;
out vec4 colorOut;

uniform sampler2D texMap;

void main()
{
    //El input que recibimos son las normales
    colorOut = (color +1)/2 ; //normalizamos el vector recibido para poder representarlo
    //colorOut = vec4(1,0,0,1);
    //colorOut = vec4(texture(texMap, v_texcoord).rgb, 1.0f);
}

