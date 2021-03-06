#include "FittedPlane.h"

FittedPlane::FittedPlane(float xmin,float xmax, float zmin, float zmax): Object(6)
{
    this->xmin = xmin;
    this->xmax = xmax;
    this->zmin = zmin;
    this->zmax = zmax;

    this->xorig = xmin;
    this->yorig = 0;
    this->zorig = zmin;


    vertexs.push_back(point4(xmin,0,zmin,1));
    vertexs.push_back(point4(xmin,0,zmax,1));
    vertexs.push_back(point4(xmax,0,zmin,1));
    vertexs.push_back(point4(xmax,0,zmax,1));


    vertex_colors[0] =    color4( 0.0, 0.0, 0.0, 1.0 );  // black
    vertex_colors[1] =    color4( 1.0, 0.0, 0.0, 1.0 );  // red
    vertex_colors[2] =    color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
    vertex_colors[3] =    color4( 0.0, 1.0, 0.0, 1.0 );  // green

}

void FittedPlane::quad( int a, int b, int c, int d )
{
    colors[Index] = vertex_colors[a]; points[Index] = vertexs[a];
    textureVertexCoords[Index] = vec2(0,0);
    Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertexs[b];
    textureVertexCoords[Index] = vec2(1,0);
    Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertexs[c];
    textureVertexCoords[Index] = vec2(1,1);
    Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertexs[a];
    textureVertexCoords[Index] = vec2(0,0);
    Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertexs[c];
    textureVertexCoords[Index] = vec2(1,1);
    Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertexs[d];
    textureVertexCoords[Index] = vec2(0,1);
    Index++;
}



// Realitzacio de la geometria del cub en el vertex array
void FittedPlane::make()
{
    qDebug() << "Estic en el make del cub\n";
    // generacio de la geometria dels triangles per a visualitzar-lo
    Index = 0;
    quad( 1, 0, 2, 3 );
    initTexture();
}


void FittedPlane::initTexture(){
    qDebug() << "Initializing textures...";

    // Carregar la textura
    glActiveTexture(GL_TEXTURE0);
    //passar el path de la textura que volem usar
    //QOpenGLTexture *textura = new QOpenGLTexture(QImage("://resources/textures/earth3.png"));
    //Codi necessari per passar de punter a shared_ptr
    //shared_ptr<QOpenGLTexture> punter_Texture(textura);
    //texture =  punter_Texture;
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->bind(0);
}



void FittedPlane::aplicaTG(mat4 m)
{
    point4  transformed_points[NumVertices];

    for ( int i = 0; i < NumVertices; ++i ) {
        transformed_points[i] = m * points[i];
    }

    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    // Actualitzacio del vertex array per a preparar per pintar
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(transformed_points),
                     transformed_points );
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}
