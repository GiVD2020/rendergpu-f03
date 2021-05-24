#version 330

in vec4 fPosition;
in vec4 fNormal;

uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;
out vec3 color_aux;

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

uniform int numl;

void main(){
    vec3 N, L;

    //intensidad que usaremos para escoger los tons
    float intensity;

    for (int i = 0; i < numl; i++)
    {
        if (lights[i].type_g == 0) // Luz puntual
        {   // Calculo del coseno del angulo que forman la normal y la direccion de la luz
            N = normalize(fNormal.xyz);
            L = normalize(lights[i].position_g.xyz - fPosition.xyz);
            intensity = dot(L,N);
        } else
        {   // Calculo del coseno del angulo que forman la normal y la direccion de la luz
            N = normalize(fNormal.xyz);
            L = normalize(-lights[i].direction_g.xyz);
            intensity = dot(L,N);
        }

        //Asignamos el color mas claro cuando ambos vectores son proximos
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
            //Asignamos el color mas oscuro cuando ambos vectores son lejanos entre si
            color += vec4(0.2,0.1,0.1,1.0);
        }
    }
}
