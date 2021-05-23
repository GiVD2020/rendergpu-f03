#version 330
layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vNormal;
layout (location = 2) in vec2 vCoordTexture;

uniform mat4 model_view;
uniform mat4 projection;

out vec4 position;
out vec4 normal;
out vec2 v_texcoord;


void main() {
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    normal = vNormal;
    position = vPosition;
    //v_texcoord = vCoordTexture;
    float u = 0.5 - atan(vPosition.z,vPosition.x) / (2.0 * 3.141);
    float v = 0.5 - asin(vPosition.y) / 3.141;
    v_texcoord = vec2(u,v);
}
