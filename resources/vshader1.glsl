#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 normals;
layout (location = 2) in vec2 vCoordTexture;

//struct de las luces
struct lights_g
{
    vec4 position_g;
    vec3 iA_g;
    vec3 iD_g;
    vec3 iS_g;
    vec3 coeficients_g;
    int type_g;
    vec4 direction_g;
    float angle_g;
};

//uniform de la luz
uniform lights_g lights[3];

//struct de la luz ambiente
struct lightAmbient
{
    vec3 lightAmbientGlobal;
};

//struct de la luz ambiente
uniform lightAmbient lightAmbientGlobal;

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
out vec2 v_texcoord;

void main()
{
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;
    //El output seran las normales porque queremos observar la visualizacion de las normales
    //De modo que el input del correspondiente fragment seran las normales
    color = normals;
    //SECCIÓ 2 FASE 1: MATERIAL:
    //Fem test amb cada una de les components del material per veure que rebem correctament totes elles.
    //TESTEJAT I FUNCIONA AMB CADA UNA D'ELLES
    //color = vec4(lights[0].iA_g,1.0);//

    //color = vec4(material.ambient,1.0);

    //color = vec4(material.diffuse,1.0);
    //color = vec4(material.especular,1.0);
    //color = vec4(material.shineness,material.shineness,material.shineness,1.0);

    //SECCIÓ 4 FASE 1: TEXTURES:
    // Pas de les coordenades de textura al fragment shader
    // El valor del color i les coordenades de textura s'interpolaran automaticament
    // en els fragments interiors a les cares dels polígons
    v_texcoord = vCoordTexture;
}
