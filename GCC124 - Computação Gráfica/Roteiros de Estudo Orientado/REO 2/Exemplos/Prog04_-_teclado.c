#include <windows.h> 
#include <gl\gl.h> 
#include <gl\glaux.h> 
  
GLfloat horzangle = -45.0,vertangle = 30.0,distance = -3.0; 
  
void CALLBACK RenderScene(void) { 
  glMatrixMode( GL_MODELVIEW ); 
  glLoadIdentity(); 
  glTranslatef(0.0f,0.0f,distance); 
  glRotatef(vertangle,1.0f,0.0f,0.0f); 
  glRotatef(horzangle,0.0f,1.0f,0.0f); 
  glEnable( GL_DEPTH_TEST ); 
  glClearColor(0.0f,0.0f,0.0f,0.0f); 
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
  glBegin( GL_LINES ); 
    glColor3f(0.0f,0.0f,1.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.7f,0.0f,0.0f); 
    glColor3f(1.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.5f,0.0f); 
    glColor3f(0.0f,1.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.7f); 
  glEnd(); 
  glBegin( GL_POLYGON ); 
    glColor3f(1.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.2f,0.0f); 
    glVertex3f(0.2f,0.3f,0.0f); 
    glVertex3f(0.4f,0.2f,0.0f); 
    glVertex3f(0.4f,0.0f,0.0f); 
  glEnd(); 
  glBegin( GL_QUADS ); 
    glColor3f(0.0f,0.0f,1.0f); 
    glVertex3f(0.0f,0.0f,0.0f); 
    glVertex3f(0.0f,0.0f,0.4f); 
    glVertex3f(0.0f,0.2f,0.4f); 
    glVertex3f(0.0f,0.2f,0.0f); 
  glEnd(); 
  glBegin( GL_QUAD_STRIP ); 
    glColor3f(0.0f,1.0f,0.0f); 
    glVertex3f(0.0f,0.2f,0.0f); 
    glVertex3f(0.0f,0.2f,0.4f); 
    glVertex3f(0.2f,0.3f,0.0f); 
    glVertex3f(0.2f,0.3f,0.4f); 
    glVertex3f(0.4f,0.2f,0.0f); 
    glVertex3f(0.4f,0.2f,0.4f); 
  glEnd(); 
  glColor3f(1.0f,1.0f,1.0f); 
  glBegin( GL_LINE_STRIP ); 
    glVertex3f(0.0f,0.0f,0.4f); 
    glVertex3f(0.4f,0.0f,0.4f); 
    glVertex3f(0.4f,0.0f,0.0f); 
  glEnd(); 
  glBegin( GL_LINES ); 
    glVertex3f(0.4f,0.0f,0.4f); 
    glVertex3f(0.4f,0.2f,0.4f); 
  glEnd(); 
  glFlush(); 
  auxSwapBuffers(); 
} 
  
void CALLBACK ChangeSize(GLsizei width,GLsizei height) { 
  glViewport(0,0,width,height); 
  glMatrixMode( GL_PROJECTION ); 
  glLoadIdentity(); 
  gluPerspective(30.0,width/height,1.0,10.0); 
} 
  
void CALLBACK LeftKey(void) { 
  horzangle -= 5; 
  RenderScene(); 
} 
  
void CALLBACK RightKey(void) { 
  horzangle += 5; 
  RenderScene(); 
} 
  
void CALLBACK UpKey(void) { 
  vertangle -= 5; 
  RenderScene(); 
} 
  
void CALLBACK DownKey(void) { 
  vertangle += 5; 
  RenderScene(); 
} 
  
void CALLBACK ReturnKey(void) { 
  distance += 0.5; 
  RenderScene(); 
} 
  
void CALLBACK SpaceKey(void) { 
  distance -= 0.5; 
  RenderScene(); 
} 
  
void main(void) { 
  auxInitDisplayMode( AUX_DOUBLE | AUX_DEPTH | AUX_RGBA ); 
  auxInitPosition(100,100,320,240); 
  auxInitWindow("OpenGL - Teclado"); 
  auxReshapeFunc(ChangeSize); 
  auxKeyFunc(AUX_LEFT,LeftKey); 
  auxKeyFunc(AUX_RIGHT,RightKey); 
  auxKeyFunc(AUX_DOWN,DownKey); 
  auxKeyFunc(AUX_UP,UpKey); 
  auxKeyFunc(AUX_RETURN,ReturnKey); 
  auxKeyFunc(AUX_SPACE,SpaceKey); 
  auxMainLoop(RenderScene); 
} 
