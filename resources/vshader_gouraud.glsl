#version 330
layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 normals;

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
uniform int numl; // Numero de luces disponibles en la escena
uniform vec4 obs; //Posicion del observador (la obtenemos de la camara)

uniform mat4 model_view;
uniform mat4 projection;

out vec4 color;

void main() {
    gl_Position = projection*model_view*vPosition;
    gl_Position = gl_Position/gl_Position.w;

    // Color sin el componenete de opacidad/transparencia
    vec3 aux_color = material.ambient * ambientGlobal;

    vec3 diffuse;
    vec3 specular;
    vec3 ambient;

    vec4 N = normalize(normals); // Normalizamos la normal
    vec4 V; // Vector que indica la direccion del observador
    vec4 L; // Direccion de la luz, la calcularemos mas adelante porque dependera del tipo de luz
    vec4 H; // Vector que se encuentra entre la dirección de la luz y el observador, lo necesitaremos para la formula de Blinn Phong

    float attenuation;
    float distance;

    // Calculamos el color local para cada luz
    for (int i = 0; i < numl; i++) {
        // Luz puntual
        if (lights[i].type_g == 0) {
            L = normalize(lights[i].position_g - vPosition); //Direccion de la luz normalizada
            distance = length(L); // Distancia a la luz
            // Atenuacion en profundidad
            attenuation = (lights[i].coeficients_g.x * distance * distance + lights[i].coeficients_g.y * distance + lights[i].coeficients_g.z);

        }

        //Aplicacion del algoritmo de Bling Phong

        V = normalize(obs - vPosition); // Normalizamos la dirección del observador
        H = normalize(L + V);

        diffuse = lights[i].iD_g * material.diffuse * max(dot(L, N), 0.0);
        specular = lights[i].iS_g* material.especular * pow(max(dot(N, H), 0.0), material.shineness);
        ambient = lights[i].iA_g * material.ambient;
        // Obtenemos el color resultante al incidir esta luz y teniendo en cuenta la atenuacion
        aux_color += (diffuse + specular + ambient) / attenuation;

    }

    color = vec4(aux_color,material.alpha);

    //TESTS REALIZADOS

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
