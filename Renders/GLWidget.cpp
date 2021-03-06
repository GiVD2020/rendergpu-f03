#include "Renders/GLWidget.h"


GLWidget::GLWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {

    setFocusPolicy( Qt::StrongFocus );

}

GLWidget::GLWidget(const QGLFormat &glf, QWidget *parent) : QGLWidget(glf, parent) {

    setFocusPolicy( Qt::StrongFocus );
    scene = make_shared<Scene>();
    scene->setCamera(make_shared<Camera>(this->size().width(), this->size().height()));
    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);
}

GLWidget::~GLWidget() {
    makeCurrent();
}


void GLWidget::setScene(shared_ptr<Scene> sc) {
    scene = sc;
    scene->setCamera(make_shared<Camera>(this->size().width(), this->size().height()));
    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);
}

/* Interacci├│ amb GL i inicialitzaci├│ de shaders */

/**
 * @brief GLWidget::initializeGL()
 */
void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_RGBA);
    glEnable(GL_DOUBLE);

    initShadersGPU();
    program = type_shaders[6];
    //type_shaders[0]->link();
    type_shaders[6]->bind();
    // Creacio d'una Light per apoder modificar el seus valors amb la interficie
    auto l  = make_shared<Light>(Puntual);
    auto l1  = make_shared<Light>(Puntual);
    //realizamos los cambios pertinentes respecto al constructor base
    auto l2 = make_shared<Light>(Direccional, vec4(1,5,1,0), vec3(0.2,0.2,0.2), vec3(0.8,0.8,0.8), vec3(1,1,1), vec3(0,0,1), vec4(10,5.0,1.0), 35.0);
    auto l3 = make_shared<Light>(Spot, vec4(-10,5,-10,0), vec3(0.2,0.2,0.2), vec3(0.8,0.8,0.8), vec3(1,1,1), vec3(0,0,1), vec4(5,5.0,1.0), 25.0);
    //scene->addLight(l);
    //scene->addLight(l1);
    //scene->addLight(l2);
    scene->addLight(l3);
    scene->setAmbientToGPU(program);
    scene->lightsToGPU(program);
    scene->camera->init(this->size().width(), this->size().height(), scene->capsaMinima);
    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);

    glViewport(scene->camera->vp.pmin[0], scene->camera->vp.pmin[1], scene->camera->vp.a, scene->camera->vp.h);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief GLWidget::paintGL()
 */
void GLWidget::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    scene->camera->toGPU(program);
    scene->draw();
}

/**
 * @brief GLWidget::resizeGL()
 */
void GLWidget::resizeGL(int width, int height) {

    glViewport(scene->camera->vp.pmin[0], scene->camera->vp.pmin[1], scene->camera->vp.a, scene->camera->vp.h);

    scene->camera->vp.a = width;
    scene->camera->vp.h = height;

    scene->camera->CalculaWindow(scene->capsaMinima);

    updateGL();
}

/**
 * @brief GLWidget::initShadersGPU
 */
void GLWidget::initShadersGPU(){
    initShader("://resources/vshader1.glsl", "://resources/fshader1.glsl",0);
    initShader("://resources/vshader_gouraud.glsl", "://resources/fshader_gouraud.glsl",1);
    initShader("://resources/vshader_phong.glsl", "://resources/fshader_phong.glsl",2);
    initShader("://resources/vshader_toon.glsl", "://resources/fshader_toon.glsl",3);
    initShader("://resources/vshader_phong_texture.glsl", "://resources/fshader_phong_texture.glsl",4);
    initShader("://resources/vshader_phong_texture_indirect.glsl", "://resources/fshader_phong_texture_indirect.glsl",5);
    initShader("://resources/vshader_phong.glsl", "://resources/fshaderNacho.glsl",6);

}

QSize GLWidget::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const {
    return QSize(400, 400);
}

/**
 * @brief GLWidget::initShader()
 * Compila i linka el vertex i el fragment shader
 */
void GLWidget::initShader(const char* vShaderFile, const char* fShaderFile, int type_shader){
    //Create shader
    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);

    //Compile shader
    vshader->compileSourceFile(vShaderFile);
    fshader->compileSourceFile(fShaderFile);

    //Add shader
    type_shaders[type_shader] = make_shared<QGLShaderProgram>(this);
    type_shaders[type_shader]->addShader(vshader);
    type_shaders[type_shader]->addShader(fshader);
    type_shaders[type_shader]->link();
}

/** Gestio de les animacions i la gravaci├│ d'imatges ***/

void GLWidget::setCurrentFrame(){

    scene->update(currentFrame);
    updateGL();
    this->saveFrame();
    currentFrame++;

    if (currentFrame == MAXFRAMES)
        timer->stop();

}

void GLWidget::saveFrame(){
    this->grabFrameBuffer().save("screen_output_"+QVariant(currentFrame).toString()+".jpg");
}

void GLWidget::saveImage(){

    this->grabFrameBuffer().save("screen_output_"+QVariant(currentImage).toString()+".jpg");
    currentImage++;
}



/** Metodes SLOTS que serveixen al builder per a actualitzar l'escena i els objectes */

void GLWidget::updateObject(shared_ptr<Object> obj) {

    obj->toGPU(program);

    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);

    updateGL();
}

void GLWidget::updateScene(shared_ptr<Scene> sc) {
    // Control de la nova escena a la GPU

    scene = sc;
    scene->toGPU(program);

    // Podeu Utilitzar l'altre constructor de Camera
    // per inicialitzar els parametres de la camara.
    scene->setCamera(make_shared<Camera>(this->size().width(), this->size().height()));
    scene->camera->actualitzaCamera(scene->capsaMinima);

    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);

    updateGL();

}

/** Metodes que es criden des dels men├║s */

void GLWidget::saveAnimation() {
    // Comen├ža el timer de l'animaci├│
    timer = new QTimer(this);
    currentFrame=0;
    currentImage=0;
    connect(timer, SIGNAL(timeout()), this, SLOT(setCurrentFrame()));
    timer->start(1000);

}

void GLWidget::activaToonShader() {
    //A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Toon";
    program = type_shaders[3];
    program->link();
    program->bind();
    scene->toGPU(program);
    updateShader();

}

void GLWidget::activaPhongShader() {
    //Opcional: A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Phong";
    program = type_shaders[2];
    program->link();
    program->bind();
    scene->toGPU(program);
    updateShader();
}

void GLWidget::activaGouraudShader() {
    //A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Gouraud";
    program = type_shaders[1];
    program->link();
    program->bind();
    scene->toGPU(program);
    updateShader();
}

void GLWidget::activaPhongTex() {
    //A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Phong Tex";
    program = type_shaders[4];
    program->link();
    program->bind();
    scene->toGPU(program);
    updateShaderTexture();
}


void GLWidget::activaIndirecte() {
    //A implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Phong Tex Indirecte";
    program = type_shaders[5];
    program->link();
    program->bind();
    scene->toGPU(program);
    updateShaderTexture();

}

void GLWidget::activaNacho() {
    //A implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Phong Tex Indirecte";
    program = type_shaders[6];
    program->link();
    program->bind();
    scene->toGPU(program);
    updateShaderTexture();

}
void GLWidget::activaBackground() {
    //A implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Background";
}
void GLWidget::activaBumpMapping() {
    //TO DO: a implementar a la fase 2 de la practica 2
     qDebug()<<"Estic a Bump Mapping";
}

void GLWidget::activaEnvMapping() {
    //TO DO: a implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Environmental Mapping";
}

void GLWidget::activaTransparency() {
    //TO DO: a implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Transparencia";
}

//Metode  per canviar de shaders.
void GLWidget::updateShader(){
    updateGL();
;}

//Metode per canviar de shaders de textures
void GLWidget::updateShaderTexture(){
    //A implementar a la fase 1 de la practica 2
    updateGL();

}

/** M├Ętodes que es criden des de les finestres de dialeg */

void GLWidget::setRotation(float angle, float x, float y, float z)
{
    // Rotaci├│ en coordenades de mon que es far├á sobre l'escena carregada

}
void GLWidget::setTranslation(float x, float y, float z)
{
    // Translaci├│ en coordenades de mon que es far├á sobre l'escena carregada

}

void GLWidget::setScale(float s)
{
    // Escala en coordenades de mon que es  far├á sobre l'escena carregada
}


void GLWidget::setPerspective(float verticalAngle, float nearPlane, float farPlane)
{
    scene->camera->setFrustum(verticalAngle, nearPlane, farPlane);

    updateGL();
}

void GLWidget::setLookAt(const QVector3D &eye, const QVector3D &center, const QVector3D& up)
{
    vec4 lookfrom(eye[0], eye[1], eye[2], 1.0);
    vec4 lookat(center[0], center[1], center[2], 1.0);
    vec4 vup(up[0], up[1], up[2], 1.0);
    scene->camera->setObservador(lookfrom, lookat, vup);

    updateGL();
}

void GLWidget::setLighting(const QVector3D &lightPos, const QVector3D &Ia, const QVector3D &Id,
                           const QVector3D &Is, const QVector3D &coefs)
{
    vec4 lightPosition(lightPos[0],lightPos[1], lightPos[2], 1.0) ;
    vec3 intensityA( Ia[0], Ia[1], Ia[2]);
    vec3 intensityD( Id[0], Id[1], Id[2]);
    vec3 intensityS( Is[0], Is[1], Is[2]);

    scene->lights[0]->setIa(intensityA);
    scene->lights[0]->setId(intensityD);
    scene->lights[0]->setIs(intensityS);
    scene->lights[0]->setLightPosition(lightPosition);
    updateGL();
}

void GLWidget::setTextureFile(const QString &file)
{
    shared_ptr<QOpenGLTexture> texture;

    texture = make_shared<QOpenGLTexture>(QImage(file).mirrored());

    // TO DO: A modificar en la fase 1 de la practica 2
    // Per ara es posa la textura al primer objecte de l'escena
    scene->objects[0]->setTexture(texture);

}

/**  M├Ętodes d'interacci├│ amb el ratol├ş */

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        if(lastPos.y()!= event->y() && lastPos.x()!= event->x()) {
           setXRotation(dy);
           setYRotation(dx);
        } else if(lastPos.y()!= event->y()) {// rotar la camera
            setXRotation(dy);
        } else if (lastPos.x()!= event->x()) {
            setYRotation(dx);
        }

    } else if (event->buttons() & Qt::RightButton) {
       // Zoom: canviar la mida de la window
        if(lastPos.y()> event->y())
             Zoom(-1);
        else
             Zoom(1);
    }

    lastPos = event->pos();
}


void GLWidget::setXRotation(int angle)
{
    if (angle >0) {
        scene->camera->angX += 5;
    } else if (angle<0)
        scene->camera->angX -= 5;
    qNormalizeAngle(scene->camera->angX);

    scene->camera->rotaCamera();

    emit ObsCameraChanged(scene->camera);

    updateGL();
}

void GLWidget::setYRotation(int angle)
{
    if (angle >0) {
        scene->camera->angY += 5;
    } else if (angle<0)
        scene->camera->angY-= 5;
    qNormalizeAngle(scene->camera->angY);

    scene->camera->rotaCamera();

    emit ObsCameraChanged(scene->camera);

    updateGL();
}

void GLWidget::qNormalizeAngle(double &angle)
{
    while (angle < 0)
        angle += 360*16;
    while (angle > 360)
        angle -= 360*16;
}

void GLWidget::Zoom (int positiu) {
    scene->camera->AmpliaWindow(positiu*(0.005));

    emit FrustumCameraChanged(scene->camera);

    updateGL();
}

