#version 330
layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 normals;

struct Material {
    vec3 diffuse;
    vec3 especular;
    vec3 ambient;
    float shineness;
    float alpha;
};

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

uniform Material material;
uniform lights_g lights[3];

uniform vec3 ambientGlobal;
uniform int numl;
uniform vec4 obs;

uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;
out vec3 color_aux;

void main() {
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    // Color without alpha component
    vec3 aux_color = material.ambient * ambientGlobal;

    vec3 diffuse;
    vec3 specular;
    vec3 ambient;

    vec4 N = normalize(normals);
    vec4 V= normalize(obs - vPosition);
    vec4 L;
    vec4 H;

    float attenuation;
    float distance;

    // Calculate the local color for each light
    for (int i = 0; i < numl; i++) {
        // If the light is Puntual
        if (lights[i].type_g == 0) {
            L = normalize(lights[i].position_g - vPosition);
            //V = normalize(obs - vPosition);
            //H = normalize(L + V);
            distance = length(L);
            attenuation = (lights[i].coeficients_g.x * distance * distance + lights[i].coeficients_g.y * distance + lights[i].coeficients_g.z);
            //color = vec4(0.0,0.0,1.0,1.0);

        }

        V = normalize(obs - vPosition);
        H = normalize(L + V);

        diffuse = lights[i].iD_g * material.diffuse * max(dot(L, N), 0.0);
        specular = lights[i].iS_g* material.especular * pow(max(dot(N, H), 0.0), material.shineness);
        ambient = lights[i].iA_g * material.ambient;
        // Add it to the output color with the correspondent attenuation
        aux_color += (diffuse + specular) / attenuation + ambient;
        //aux_color += diffuse + specular  + ambient;
    }

    color = vec4(aux_color,material.alpha);

    //Prueba 1 (verde) PASS
    //color = vec4(material.diffuse,1.0);
    //Prueba 2 (rojo) PASS
    //color = vec4(material.ambient,1.0);
    //Prueba 3 (azul oscuro)
    //color = vec4(material.especular,1.0);
    //Prueba 4 (blanco) PASS
    //color = vec4(material.shineness,1.0,1.0,1.0);
    //Prueba 5 (azul claro) PASS (?)
    //color = vec4(material.alpha,1.0,1.0,1.0);

}
