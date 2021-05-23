#version 330

in vec4 fPosition;
in vec4 fNormal;

uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;
out vec3 color_aux;

struct Material {

    vec3 diffuse;
    vec3 especular;
    vec3 ambient;
    float shineness;
    float alpha;
}; uniform Material material;

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
}; uniform lights_g lights[3];

uniform vec3 ambientGlobal;
uniform int numl;
uniform vec4 obs;

void main(){
    vec3 N, L;
    float intensity;

    for (int i = 0; i < numl; i++)
    {
        if (lights[i].type_g == 0) // Luz puntual
        {
            N = normalize(fNormal.xyz);
            L = normalize(lights[i].position_g.xyz - fPosition.xyz);
            intensity = dot(L,N);
        } else
        {
            N = normalize(fNormal.xyz);
            L = -lights[i].direction_g.xyz;
            intensity = dot(L,N);
        }

        if(intensity > 0.95){
            color += vec4(1.0,0.5,0.5,1.0);
        }
        else if(intensity > 0.5){
            color += vec4(0.6,0.3,0.3,1.0);
        }
        else if(intensity > 0.25){
            color += vec4(0.4,0.2,0.2,1.0);
        }
        else {
            color += vec4(0.2,0.1,0.1,1.0);
        }
    }
}
