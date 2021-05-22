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

void main() {
    // Color without alpha component
    vec3 aux_color = material.ambient * ambientGlobal;

    vec3 diffuse;
    vec3 specular;
    vec3 ambient;

    vec4 N = normalize(fNormal);
    vec4 V = normalize(obs - fPosition);
    vec4 L;
    vec4 H;

    float attenuation;
    float distance;

    /** TOON PARAMETERS **/
    float v1 = 0.1;
    float v2 = 0.2;
    float v3 = 0.3;

    vec3 color1 = material.diffuse * 0.10;
    vec3 color2 = material.diffuse * 0.25;
    vec3 color3 = material.diffuse * 0.50;

    vec3 mod_mat_diffuse = material.diffuse;

    float nDotl;
    /********************/


    // Calculate the local color for each light
    for (int i = 0; i < numl; i++) {

        // If the light is Puntual (at he moment we only have Puntual Lights)
        if (lights[i].type_g == 0) {
            L = normalize(lights[i].position_g - fPosition);
            distance = length(L);

            // Calculate attenuation
            attenuation = (lights[i].coeficients_g.x * pow(distance, 2.0) + lights[i].coeficients_g.y * distance + lights[i].coeficients_g.z);
            // Calculate attenuation
            if (attenuation <= 1.0) {
                attenuation = 1.0;
            }
            else {
                attenuation = 1.0/attenuation;
            }

        }


        // Calculate Phong direct iluminations
        H = normalize(L + V);

        specular = lights[i].iS_g * material.especular * pow(max(dot(N, H), 0.0), material.shineness);
        ambient = lights[i].iA_g * material.ambient;

        /* Toon calc */
        nDotl = dot(N, L);

        if(nDotl < v1){
            mod_mat_diffuse = color1;
        }else if(nDotl < v2){
            mod_mat_diffuse = color2;
        }else if(nDotl < v3){
            mod_mat_diffuse = color3;
        }

        mod_mat_diffuse = max(mod_mat_diffuse, mod_mat_diffuse * (1.0 - dot(V, N)));

        diffuse = lights[i].iD_g * mod_mat_diffuse * max(nDotl, 0.0);

        // Add it to the output color with the correspondent attenuation
        //aux_color += (diffuse + specular) / attenuation + ambient;
        aux_color += diffuse + specular + ambient;
    }

    color = vec4(aux_color, material.alpha);

}
