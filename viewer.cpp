#include "viewer.h"

#include <math.h>
#include <iostream>
#include <QTime>

using namespace std;

Viewer::Viewer(const QGLFormat &format)
  : QGLWidget(format),
    _timer(new QTimer(this)),
    _drawMode(false) {

  _grid = new Grid(10,-5.0f,5.0f);
  
  // create a camera (automatically modify model/view matrices according to user interactions)
  _cam  = new Camera(1,glm::vec3(0.0f,0.0f,0.0f));

  _timer->setInterval(10);
  connect(_timer,SIGNAL(timeout()),this,SLOT(updateGL()));
}

Viewer::~Viewer() {
  // delete everything 
  delete _timer;
  delete _cam;

  deleteVAO();
  deleteShaders();
  deleteFBO();
}

void Viewer::createShaders() {
  _vertexFilenames.push_back("shaders/first.vert");
  _fragmentFilenames.push_back("shaders/first.frag");

  _vertexFilenames.push_back("shaders/second.vert");
  _fragmentFilenames.push_back("shaders/second.frag");

  _vertexFilenames.push_back("shaders/third.vert");
  _fragmentFilenames.push_back("shaders/third.frag");

  _vertexFilenames.push_back("shaders/fourth.vert");
  _fragmentFilenames.push_back("shaders/fourth.frag");

  _vertexFilenames.push_back("shaders/fifth.vert");
  _fragmentFilenames.push_back("shaders/fifth.frag");
}

void Viewer::deleteShaders() {
    for (unsigned int i = 0; i < _shaders.size(); i++){
        delete _shaders[i];
    }
}

void Viewer::createVAO() {
  //the variable _grid should be an instance of Grid
  //the .h file should contain the following VAO/buffer ids
  //GLuint _vaoTerrain;
  //GLuint _vaoQuad;
  //GLuint _terrain[2];
  //GLuint _quad;

  const GLfloat quadData[] = {
    -1.0f,-1.0f,0.0f, 1.0f,-1.0f,0.0f, -1.0f,1.0f,0.0f, -1.0f,1.0f,0.0f, 1.0f,-1.0f,0.0f, 1.0f,1.0f,0.0f
  };

  glGenBuffers(2,_terrain);
  glGenBuffers(1,&_quad);
  glGenVertexArrays(1,&_vaoTerrain);
  glGenVertexArrays(1,&_vaoQuad);

  // create the VBO associated with the grid (the terrain)
  glBindVertexArray(_vaoTerrain);
  glBindBuffer(GL_ARRAY_BUFFER,_terrain[0]); // vertices
  glBufferData(GL_ARRAY_BUFFER,_grid->nbVertices()*3*sizeof(float),_grid->vertices(),GL_STATIC_DRAW);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_terrain[1]); // indices
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,_grid->nbFaces()*3*sizeof(int),_grid->faces(),GL_STATIC_DRAW);

  // create the VBO associated with the screen quad
  glBindVertexArray(_vaoQuad);
  glBindBuffer(GL_ARRAY_BUFFER,_quad); // vertices
  glBufferData(GL_ARRAY_BUFFER, sizeof(quadData),quadData,GL_STATIC_DRAW);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
  glEnableVertexAttribArray(0);

}

void Viewer::deleteVAO() {
  glDeleteBuffers(2,_terrain);
  glDeleteBuffers(1,&_quad);
  glDeleteVertexArrays(1,&_vaoTerrain);
  glDeleteVertexArrays(1,&_vaoQuad);
}\
\
void Viewer::createFBO(){
    glGenFramebuffers(1, &_fbo);
    glGenTextures(1, &_heightMap);
    glGenTextures(1,&_normalMap);
}

void Viewer::initFBO() {


 glBindTexture(GL_TEXTURE2D,_normalMap);
 glTex

  // create the texture for rendering depth values
  glBindTexture(GL_TEXTURE_2D,_heightMap);
  glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT24,width(),height(),0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


  // attach textures to framebuffer object
  glBindFramebuffer(GL_FRAMEBUFFER,_fbo);
  glBindTexture(GL_TEXTURE_2D,_heightMap);
  glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,_heightMap,0);
  glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void Viewer::deleteFBO() {
  // delete all FBO Ids
  glDeleteFramebuffers(1,&_fbo);
  glDeleteTextures(1,&_depthMap);
}


/*void Viewer::createVAO() {
  // create some buffers inside the GPU memory
  glGenVertexArrays(1,&_vao);
  glGenBuffers(1,_buffers);


}

void Viewer::deleteVAO() {
  // delete / free all GPU buffers
  glDeleteVertexArrays(1,&_vao);
  glDeleteBuffers(1,_buffers);
}*/

/*void Viewer::loadMeshIntoVAO() {
  // activate VAO
  glBindVertexArray(_vao);
  
  // store mesh positions into buffer 0 inside the GPU memory
  glBindBuffer(GL_ARRAY_BUFFER,_buffers[0]);
  glBufferData(GL_ARRAY_BUFFER,_mesh->nb_vertices*3*sizeof(float),_mesh->vertices,GL_STATIC_DRAW);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
  glEnableVertexAttribArray(0);

  // store mesh normals into buffer 1 inside the GPU memory
  glBindBuffer(GL_ARRAY_BUFFER,_buffers[1]);
  glBufferData(GL_ARRAY_BUFFER,_mesh->nb_vertices*3*sizeof(float),_mesh->normals,GL_STATIC_DRAW);
  glVertexAttribPointer(1,3,GL_FLOAT,GL_TRUE,0,(void *)0);
  glEnableVertexAttribArray(1);

  // store mesh indices into buffer 2 inside the GPU memory
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_buffers[2]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,_mesh->nb_faces*3*sizeof(unsigned int),_mesh->faces,GL_STATIC_DRAW);

  // deactivate the VAO for now
  glBindVertexArray(0);
}*/

void Viewer::drawVAO() {
  // activate the VAO, draw the associated triangles and desactivate the VAO
  glBindVertexArray(_vaoTerrain);
  glDrawElements(GL_TRIANGLES, 3*_grid->nbFaces(),GL_UNSIGNED_INT,(void *)0);
  glBindVertexArray(0);
  glBindVertexArray(_vaoQuad);
  //glDrawArrays(GL_TRIANGLES, 3*_grid->nbFaces(),10);
  glBindVertexArray(0);
}

void Viewer::enableShaders(unsigned int shader) {

  // current shader ID
  GLuint id = _shaders[shader]->id();

  // activate the current shader
  glUseProgram(id);


  /*// send the model-view matrix
  glUniformMatrix4fv(glGetUniformLocation(id,"mdvMat"),1,GL_FALSE,&(_cam->mdvMatrix()[0][0]));

  // send the projection matrix
  glUniformMatrix4fv(glGetUniformLocation(id,"projMat"),1,GL_FALSE,&(_cam->projMatrix()[0][0]));*/
}

void Viewer::disableShaders() {
  // desactivate all shaders 
  glUseProgram(0);
}

void Viewer::paintGL() {
  // clear the color and depth buffers 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // set viewport
  glViewport(0,0,width(),height());

  // tell the GPU to use this specified shader and send custom variables (matrices and others)
  enableShaders(_currentshader);
  
  // actually draw the scene 
  drawVAO();

  // tell the GPU to stop using this shader 
  disableShaders();
}

void Viewer::resizeGL(int width,int height) {
  _cam->initialize(width,height,false);
  glViewport(0,0,width,height);
  updateGL();
}

void Viewer::mousePressEvent(QMouseEvent *me) {
  // handle camera events
  const glm::vec2 p((float)me->x(),(float)(height()-me->y()));

  if(me->button()==Qt::LeftButton) {
    _cam->initRotation(p);
  } else if(me->button()==Qt::RightButton) {
    _cam->initMoveXY(p);
  } else if(me->button()==Qt::MidButton) {
    _cam->initMoveZ(p);
  }

  updateGL();
}

void Viewer::mouseMoveEvent(QMouseEvent *me) {
  // handle camera motion
  const glm::vec2 p((float)me->x(),(float)(height()-me->y()));
 
  _cam->move(p);
  updateGL();
}

void Viewer::keyPressEvent(QKeyEvent *ke) {

  // key a: play/stop animation
  if(ke->key()==Qt::Key_A) {
    if(_timer->isActive())
      _timer->stop();
    else
      _timer->start();
  }

  // key i: init camera
  if(ke->key()==Qt::Key_I) {
    _cam->initialize(width(),height(),true);
  }

  // key f: compute FPS
  if(ke->key()==Qt::Key_F) {
    int elapsed;
    QTime timer;
    timer.start();
    unsigned int nb = 500;
    for(unsigned int i=0;i<nb;++i) {
      paintGL();
    }
    elapsed = timer.elapsed();
    double t = (double)nb/((double)elapsed);
    cout << "FPS : " << t*1000.0 << endl;
  }

  // key r: reload shaders
  if(ke->key()==Qt::Key_R) {
    for(unsigned int i=0;i<_vertexFilenames.size();++i) {
      _shaders[i]->reload(_vertexFilenames[i].c_str(),_fragmentFilenames[i].c_str());
    }
  }

  // space: next shader
  if(ke->key()==Qt::Key_Space) {
    _currentshader = (_currentshader+1)%_shaders.size();
  }

  updateGL();
}

void Viewer::initializeGL() {
  // make this window the current one
  makeCurrent();

  glewExperimental = GL_TRUE;

  // init and chack glew
  if(glewInit()!=GLEW_OK) {
    cerr << "Warning: glewInit failed!" << endl;
  }

  // init OpenGL settings
  glClearColor(0.0,0.0,0.0,1.0);
  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glViewport(0,0,width(),height());

  // initialize camera
  _cam->initialize(width(),height(),true);

  // create and initialize shaders and VAO 
  createShaders();

  for(unsigned int i=0;i<_vertexFilenames.size();++i) {
    _shaders.push_back(new Shader());
    _shaders[i]->load(_vertexFilenames[i].c_str(),_fragmentFilenames[i].c_str());
  }

  createVAO();

  createFBO();
  initFBO();

  // starts the timer 
  _timer->start();
}

