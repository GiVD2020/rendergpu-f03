#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;


//struct del material
struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 especular;
    float shineness;
};
//uniform del material de gpu
uniform Material material;

uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;
    //color = vColor;
    //SECCIÓ 2 FASE 1: MATERIAL:
    //Fem test amb cada una de les components del material per veure que rebem correctament totes elles.
    //TESTEJAT I FUNCIONA AMB CADA UNA D'ELLES
    color = vec4(material.ambient,1.0);
    //color = vec4(material.diffuse,1.0);
    //color = vec4(material.especular,1.0);
    //color = vec4(material.shineness,material.shineness,material.shineness,1.0);
}
