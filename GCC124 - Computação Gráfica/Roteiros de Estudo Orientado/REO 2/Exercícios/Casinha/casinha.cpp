#include <GL/glut.h>
#include <GL/gl.h> 

// definicoes ascii
#define BACKSPACE 8
#define SPACE     32
#define ZOOM_IN   43
#define ZOOM_OUT  45

// angulos de manipulacao
GLfloat xAngle = 30.00, yAngle = -45.0, zAngle = 0.0, zoom = -3.0;

// definindo visao
void view(GLsizei width,GLsizei height) {
    glViewport(0, 0, width, height); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(30.0, width/height, 1.0, 10.0);
}

// funcao criacao da cena
void renderScene(void) {
    // setando cor de fundo e descarregando nos buffers
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ajeitando visao
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, zoom);
    glRotatef(xAngle,1.0f,0.0f,0.0f); 
    glRotatef(yAngle,0.0f,1.0f,0.0f);
    glRotatef(zAngle,0.0f,0.0f,1.0f);
    
    glEnable(GL_DEPTH_TEST);

    // desenhando
    glBegin(GL_LINES);
        // linhas dos eixos
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
    
    glBegin(GL_QUADS);
        // chao
        glColor3f(0.502f, 0.0f, 0.0f);
        glVertex3f(0.0f,0.0f,0.0f); 
        glVertex3f(0.4f,0.0f,0.0f); 
        glVertex3f(0.4f,0.0f,0.4f); 
        glVertex3f(0.0f,0.0f,0.4f); 
    glEnd();

    glColor3f(0.827f, 0.827f, 0.827f);
    glBegin(GL_POLYGON);
        // parede dos fundos 
        glVertex3f(0.0f,0.0f,0.0f); 
        glVertex3f(0.0f,0.2f,0.0f); 
        glVertex3f(0.2f,0.3f,0.0f); 
        glVertex3f(0.4f,0.2f,0.0f); 
        glVertex3f(0.4f,0.0f,0.0f); 
    glEnd();
    glBegin( GL_QUADS ); 
        // parede lateral eixo z
        glVertex3f(0.0f,0.0f,0.0f); 
        glVertex3f(0.0f,0.0f,0.4f); 
        glVertex3f(0.0f,0.2f,0.4f); 
        glVertex3f(0.0f,0.2f,0.0f);  
    glEnd();
    glBegin(GL_QUADS);
        // parede lateral dividida em pedacos
        // para deixar janela vazada
        glVertex3f(0.4f,0.0f,0.0f);
        glVertex3f(0.4f,0.2f,0.0f);
        glVertex3f(0.4f,0.2f,0.15f); 
        glVertex3f(0.4f,0.0f,0.15f);
        
        glVertex3f(0.4f,0.2f,0.15f); 
        glVertex3f(0.4f,0.15f,0.15f);
        glVertex3f(0.4f,0.15f,0.25f); 
        glVertex3f(0.4f,0.2f,0.25f);

        glVertex3f(0.4f,0.05f,0.15f); 
        glVertex3f(0.4f,0.0f,0.15f);
        glVertex3f(0.4f,0.0f,0.25f); 
        glVertex3f(0.4f,0.05f,0.25f);

        glVertex3f(0.4f,0.2f,0.25f); 
        glVertex3f(0.4f,0.0f,0.25f);
        glVertex3f(0.4f,0.0f,0.4f); 
        glVertex3f(0.4f,0.2f,0.4f);
    glEnd();

    // parede frontal dividida em pedacos
    // para deixar porta vazada
    glBegin(GL_QUADS);
        glVertex3f(0.0f,0.0f,0.4f); 
        glVertex3f(0.15f,0.0f,0.4f);
        glVertex3f(0.15f,0.2f,0.4f);
        glVertex3f(0.0f,0.2f,0.4f);

        glVertex3f(0.4f,0.0f,0.4f);
        glVertex3f(0.25f,0.0f,0.4f);
        glVertex3f(0.25f,0.2f,0.4f);
        glVertex3f(0.4f,0.2f,0.4f);
        
        glVertex3f(0.15f,0.2f,0.4f);
        glVertex3f(0.15f,0.125f,0.4f);
        glVertex3f(0.25f,0.125f,0.4f);
        glVertex3f(0.25f,0.2f,0.4f);
    glEnd();
    glBegin(GL_TRIANGLES);
        glVertex3f(0.0f,0.2f,0.4f); 
        glVertex3f(0.4f,0.2f,0.4f);
        glVertex3f(0.2f,0.3f,0.4f); 
    glEnd();

    glBegin(GL_QUAD_STRIP);
        // teto 
        glColor3f(1.0f, 0.549f, 0.0f); 
        glVertex3f(0.0f,0.2f,0.0f); 
        glVertex3f(0.0f,0.2f,0.4f); 
        glVertex3f(0.2f,0.3f,0.0f); 
        glVertex3f(0.2f,0.3f,0.4f); 
        glVertex3f(0.4f,0.2f,0.0f); 
        glVertex3f(0.4f,0.2f,0.4f); 
    glEnd();

    glFlush();          // executar desenho das matrizes
    glutSwapBuffers();  // troca de buffers definindo mudancas nas matrizes
}

// definicao dos eventos de mouse
void mouseEvents(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON){
        if(state == GLUT_UP) {
            yAngle -= 15;
        }  
    } else if(button == GLUT_RIGHT_BUTTON) {
        if(state == GLUT_UP) {
            yAngle += 15; 
        }  
    }
         
    glutPostRedisplay();    // marca matriz como necessario de redesenhar
}

// definicao dos eventos de teclados (teclas normais)
void keyboardEvents(unsigned char key, int x, int y) {
    switch(key) {
        case BACKSPACE:
            zAngle -= 15;
            break;
        case SPACE:
            zAngle += 15;
            break;
        case ZOOM_OUT:  // '-'
            zoom -= 0.5;
            break;
        case ZOOM_IN:   // '+'
            zoom += 0.5;
            break;
    }

    glutPostRedisplay();    // marca matriz como necessario de redesenhar
}

// definicao dos eventos de teclados (teclas especiais)
void specialKeysEvents(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            xAngle -= 15;
            break;
        case GLUT_KEY_UP:
            xAngle += 15;
            break;
        case GLUT_KEY_LEFT:
            yAngle -= 15;
            break;
        case GLUT_KEY_RIGHT:
            yAngle += 15;
            break;
    }

    glutPostRedisplay();    // marca matriz como necessario de redesenhar
}

int main(int argc, char* argv[]) { 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB); 
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100); 
    glutCreateWindow("Casinha"); 
    glutReshapeFunc(view);
    glutMouseFunc(mouseEvents);
    glutKeyboardFunc(keyboardEvents);
    glutSpecialFunc(specialKeysEvents);
    glutDisplayFunc(renderScene);
    glutMainLoop();
    return 0;
}