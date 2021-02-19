/* LINK PARA O VÍDEO!!!

    https://drive.google.com/file/d/1IrXGTM7zMxF7wToa3jhNMy2cFMUBWbxq/view?usp=sharing

 */

#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

float rotacao = 0;

void init(void) {
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_COLOR_MATERIAL); 
	glEnable(GL_DEPTH_TEST); // habilita ZBuffer
}

void reshape(int w, int h) {
	if(h == 0)
		h = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
    glViewport(0, 0, w, h);

	// Seta o ângulo de visão
	gluPerspective(50, 1.0f * w / h, 1, 200);

	// Define a posição do observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 5,
		      0, 0, 0,
			  0.0f ,1.0f, 0.0f);

}

void desenhaCubo(GLfloat alfa) {
    glBegin ( GL_QUADS );
		// Front Face
		glColor4f(0.7f, 0.7f, 0, alfa);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glColor4f(0,0, 0.7f, alfa);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glColor4f(0.7f,0,0.7f, alfa);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glColor4f(0.7f,0.7f,0.7f, alfa);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		// Right face
		glColor4f(0,0.5f,0, alfa);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glColor4f(0.7f,0,0, alfa);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
}

void desenhaPlano(GLfloat alfa) {
    glColor4f(1, 1, 1, alfa);
    glBegin(GL_QUADS);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
	glEnd();
}

void display( void ) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glRotatef(rotacao, 0.0, 1.0, 0.0);

	glPushMatrix();
		glTranslatef(0, 0, -1);
		desenhaCubo(0.5);		
	glPopMatrix();

	glPushMatrix();
        desenhaPlano(0.3);
	glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 0.0, 2.5);
        glColor4f(1, 0, 0, 0.7);
        glutSolidSphere(1.0, 50, 50);
	glPopMatrix();

    glFlush();
	glutSwapBuffers();
}

void keyboard ( unsigned char key, int x, int y ) {
	switch(key) {
        case 27:      
            exit(0);   
            break;

        case 'r':
            if(rotacao == 0)
                rotacao = 0.01;
            else
                rotacao = 0;
            break;      
    }
}

int main( int argc, char** argv ) {
	glutInit( &argc, argv ); 
	glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA ); 
	glutInitWindowPosition(0,0);
	glutInitWindowSize( 700, 500 ); 
	glutCreateWindow( "REO 5 - CG" ); 
		
	init();
	
	glutDisplayFunc( display );  
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutIdleFunc( display );
	glutMainLoop( );          
}