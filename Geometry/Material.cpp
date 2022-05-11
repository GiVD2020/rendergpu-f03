#include "Geometry/Material.h"

Material::Material(){

  //parametros del pdf que dejo anna en el campus para ver si las shaders iban bien
    ambient = vec3(0.2,0.2,0.2);
    diffuse= vec3(0.8,0.5,0.5);
    especular = vec3(1.0,1.0,1.0);
    shineness = 20.;

    //hardcodejat per quan les dades virtual/reals no vinguin amb un material especificat
    //ambient = vec3(0.0,1.0,0.0);
    //diffuse= vec3(0.0,1.0,0.0);
    //especular = vec3(0.0,0.0,1.0);
    //shineness = 1.0;

}

Material::Material(vec3 d){
    //quan nomes ens vingui el color difus
    ambient = vec3(1.0,0.0,0.0);
    diffuse = d;
    especular = vec3(0.0,0.0,1.0);
    shineness = 0;
}

Material::Material(vec3 d, vec3 s, vec3 a, float beta){
    //quan ens vinguin totes les dades
    ambient = a;
    diffuse = d;
    especular = s;
    shineness = beta;
}

/**
 * Passa el material de CPU a GPU
 * @brief Material::toGPU
 * @param program
 */
void Material::toGPU(shared_ptr<QGLShaderProgram> program){
    struct {
        GLuint ambient_Id;
        GLuint diffuse_Id;
        GLuint especular_Id;
        GLuint shineness_Id;
     }material_Id;

     // 2. obtencio dels identificadors de la GPU
    //posar en el shader amb el nom de material
    material_Id.ambient_Id = program->uniformLocation("material.ambient");
    material_Id.diffuse_Id = program->uniformLocation("material.diffuse");
    material_Id.especular_Id = program->uniformLocation("material.especular");
    material_Id.shineness_Id = program->uniformLocation("material.shineness");

    // 3. Bind de les zones de memòria que corresponen a la GPU a valors de les variables de la CPU
    glUniform3fv(material_Id.ambient_Id, 1, ambient); // ambient és una variable de tipus vec3
    glUniform3fv(material_Id.diffuse_Id, 1, diffuse);// diffuse és una variable de tipus vec3
    glUniform3fv(material_Id.especular_Id, 1, especular);// especular és una variable de tipus vec3
    glUniform1f(material_Id.shineness_Id, shineness);// shineness és una variable de tipus float

}
