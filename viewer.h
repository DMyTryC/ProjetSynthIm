#ifndef VIEWER_H
#define VIEWER_H

// GLEW lib: needs to be included first!
#include <GL/glew.h>

// OpenGL library 
#include <GL/gl.h>

// OpenGL Utility library
#include <GL/glu.h>

// OpenGL Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <QGLFormat>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <stack>

#include "camera.h"
#include "shader.h"
#include "grid.h"

class Viewer : public QGLWidget {
 public:
  Viewer(const QGLFormat &format=QGLFormat::defaultFormat());
  ~Viewer();

 protected :
  virtual void paintGL();
  virtual void initializeGL();
  virtual void resizeGL(int width,int height);
  virtual void keyPressEvent(QKeyEvent *ke);
  virtual void mousePressEvent(QMouseEvent *me);
  virtual void mouseMoveEvent(QMouseEvent *me);
    

 private:
  void createVAO();
  void deleteVAO();
  void drawVAO();

  void createFBO();
  void initFBO();
  void deleteFBO();
  void drawQuad();
  void drawGrid(unsigned int shader);

  void createShaders();
  void deleteShaders();
  void enableShaders(unsigned int shader);
  void disableShaders();

  QTimer        *_timer;    // timer that controls the animation
  bool           _drawMode; // press w for wire or fill drawing mode
  unsigned int   _currentshader; // current shader index
  glm::vec2 _deplacement;
  glm::vec4 _FOG_COLOR;
  Camera *_cam; // the camera
  Grid *_grid;  // the grid
  unsigned int _GRID_SIZE;

  std::vector<std::string> _vertexFilenames;   // all vertex filenames
  std::vector<std::string> _fragmentFilenames; // all fragment filenames

  std::vector<Shader *> _shaders; // all the shaders
  
  GLuint _vaoTerrain;
  GLuint _vaoQuad;
  GLuint _terrain[2];
  GLuint _quad;

  GLuint _fbo;
  GLuint _heightMap;
  GLuint _normalMap;
};

#endif // VIEWER_H
