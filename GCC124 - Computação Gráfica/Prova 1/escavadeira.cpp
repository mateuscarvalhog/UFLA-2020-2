#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h> 

// definicoes ascii
#define ESC         27
#define ZOOM_IN     43
#define ZOOM_OUT    45

// angulos de manipulacao
GLfloat zoom = 0;
static int xAngle = 0, yAngle = 0;
static int wheels = 0, waist = 0, shoulder = 0, elbow = 0, shovel = 25;
static bool farol = false;


void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glShadeModel(GL_FLAT);
    
    
    GLfloat difuse[] = { 1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = { 3.0, 15.0, 10.0, 0.0 };

    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE); // determina que a reflexao aconteca para as faces de frente e de tras dos objetos

    glEnable(GL_COLOR_MATERIAL); // habilita as colorações

    glLightfv (GL_LIGHT0, GL_DIFFUSE, difuse);  // cria luz difusa
    glLightfv (GL_LIGHT0, GL_POSITION, position);  // define que a luz eh direcional

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}

// definindo visao
void reshape (int w, int h) {
    glViewport (0, 0, w, h); 
    
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f,  w / h, 0.01f, 200.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef (0.0f, 0.0f, -5.0f);
}

// define e desenha a cena
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLUquadric* gluQuadric = gluNewQuadric();
    
    glPushMatrix();
        // zoom e rotacoes de visao do objeto
        glTranslatef(0.0f, 0.0f, zoom);
        glRotatef(xAngle, 1.0f, 0.0f, 0.0f); 
        glRotatef(yAngle, 0.0f, 1.0f, 0.0f);

        glColor3f(0.545, 0.000, 0.000);

        // base inferior e rodas
        glPushMatrix();
            glTranslatef(0.0f, -0.60f, 0.0f);
            glPushMatrix();
                glScalef(2.0, 0.2, 1.6);
                glutSolidCube(1.0);
            glPopMatrix();

            glTranslatef(-0.5f, 0.0f, 0.8f);
            glPushMatrix();
                glRotatef(wheels, 0.0f, 0.0f, 1.0f);
                glColor3f(0.412, 0.412, 0.412);
                gluDisk(gluQuadric, 0, 0.4, 200, 100);
                gluCylinder(gluQuadric, 0.4, 0.4, 0.5, 200, 100);
                glTranslatef(0.0f, 0.0f, 0.5f);
                gluDisk(gluQuadric, 0, 0.4, 200, 100);
                glutWireSphere(0.1f, 5, 5);
            glPopMatrix();

            glTranslatef(1.0f, 0.0f, 0.0f);
            glPushMatrix();
                glRotatef(wheels, 0.0f, 0.0f, 1.0f);
                gluDisk(gluQuadric, 0, 0.4, 200, 100);
                gluCylinder(gluQuadric, 0.4, 0.4, 0.5, 200, 100);
                glTranslatef(0.0f, 0.0f, 0.5f);
                gluDisk(gluQuadric, 0, 0.4, 200, 100);
                glutWireSphere(0.1f, 5, 5);
            glPopMatrix();

            glTranslatef(0.0f, 0.0f, -2.1f);
            glPushMatrix();
                glRotatef(wheels, 0.0f, 0.0f, 1.0f);
                gluCylinder(gluQuadric, 0.4, 0.4, 0.5, 200, 100);
                gluDisk(gluQuadric, 0, 0.4, 200, 100);
                glutWireSphere(0.1f, 5, 5);
                glTranslatef(0.0f, 0.0f, 0.5f);
                gluDisk(gluQuadric, 0, 0.4, 200, 100);
            glPopMatrix();

            glTranslatef(-1.0f, 0.0f, 0.0f);
            glPushMatrix();
                glRotatef(wheels, 0.0f, 0.0f, 1.0f);
                gluCylinder(gluQuadric, 0.4, 0.4, 0.5, 200, 100);
                gluDisk(gluQuadric, 0, 0.4, 200, 100);
                glutWireSphere(0.1f, 5, 5);
                glTranslatef(0.0f, 0.0f, 0.5f);
                gluDisk(gluQuadric, 0, 0.4, 200, 100);
            glPopMatrix();

        glPopMatrix();

        glColor3f(0.545, 0.000, 0.000);

        glPushMatrix();
            // rotacao do corpo - articulacao da cintura
            glRotatef(waist, 0.0f, 1.0f, 0.0f);
            
            //cilindro de rotacao
            glPushMatrix();
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                gluCylinder(gluQuadric, 0.5, 0.5, 0.5, 200, 100);
            glPopMatrix();

            // base superior
            glPushMatrix();
                glScalef(2.0, 0.2, 1.6);
                glutSolidCube(1.0);
            glPopMatrix();

            // cabine
            glPushMatrix();
                glTranslatef(0.3f, 0.4f, -0.4f);
                glPushMatrix();
                    glScalef(0.04, 0.6, 0.6);
                    glutSolidCube(1.0);
                glPopMatrix();

                glTranslatef(-0.6f, 0.0f, -0.27f);
                glPushMatrix();
                    glScalef(0.06, 0.6, 0.06);
                    glutSolidCube(1.0);
                glPopMatrix();

                glTranslatef(0.0f, 0.0f, 0.54f);
                glPushMatrix();
                    glScalef(0.06, 0.6, 0.06);
                    glutSolidCube(1.0);
                glPopMatrix();

                glTranslatef(0.27f, 0.27f, -0.27f);
                glPushMatrix();
                    glScalef(0.6, 0.06, 0.6);
                    glutSolidCube(1.0);
                glPopMatrix();
                
                // farol
                glTranslatef(-0.20f, 0.06f, 0.0f);
                glutSolidCube(0.06);
                glTranslatef(-0.045f, 0.0f, 0.0f);
                glPushMatrix();
                    glScalef(0.03, 0.06, 0.06);
                    if(!farol)
                        glColor3f(0.827, 0.827, 0.827);
                    else
                        glColor3f(1.000, 1.000, 0.000);
                    glutSolidCube(1.0);
                glPopMatrix();

            glPopMatrix();
            
            glColor3f(0.545, 0.000, 0.000);

            glPushMatrix();
                // rotacao do braco - articulacao do ombro
                glTranslatef(0.0f, 0.1f, 0.4f);
                glRotatef(shoulder, 0.0f, 0.0f, 1.0f);
                
                // braco
                glPushMatrix();
                    glTranslatef(0.0f, 1.0f, 0.0f);
                    glScalef(0.2, 2.0, 0.2);
                    glutSolidCube(1.0);
                glPopMatrix();

                glPushMatrix();
                    // rotacao do antebraco - articulacao do cotovelo
                    glTranslatef(0.0f, 2.0f, 0.0f);
                    glRotatef(elbow, 0.0f, 0.0f, 1.0f);
                    
                    // antebraco
                    glPushMatrix();
                        glTranslatef(-1.0f, 0.0f, 0.0f);
                        glScalef(2.0, 0.2, 0.2);
                        glutSolidCube(1.0);
                    glPopMatrix();

                    glPushMatrix();
                        glTranslatef(-2.0f, 0.0f, 0.0f);
                        glRotatef(shovel, 0.0f, 0.0f, 1.0f);
                        
                        glTranslatef(-0.025f, 0.1f, 0.0f);
                        // pa
                        glPushMatrix();
                            glTranslatef(0.01f, 0.0f, 0.0f);
                            glPushMatrix();
                                glScalef(0.02, 0.26, 0.26);
                                glutSolidCube(1.0);
                            glPopMatrix();
                            
                            glTranslatef(-0.13f, -0.13f, 0.0f);
                            glPushMatrix();
                                glScalef(0.26, 0.02, 0.26);
                                glutSolidCube(1.0);
                            glPopMatrix();

                            glTranslatef(-0.12f, 0.16f, 0.0f);
                            glPushMatrix();
                                glScalef(0.02, 0.32, 0.26);
                                glutSolidCube(1.0);
                            glPopMatrix();

                            glTranslatef(0.12f, -0.03f, 0.13f);
                            glPushMatrix();
                                glScalef(0.26, 0.26, 0.02);
                                glutSolidCube(1.0);
                            glPopMatrix();

                            glTranslatef(0.0f, 0.0f, -0.26f);
                            glPushMatrix();
                                glScalef(0.26, 0.26, 0.02);
                                glutSolidCube(1.0);
                            glPopMatrix();

                        glPopMatrix();
                        
                    glPopMatrix();

                glPopMatrix();

            glPopMatrix();

        glPopMatrix();

    glPopMatrix();

    glFlush();          // executar desenho das matrizes
    glutSwapBuffers();  // troca de buffers definindo mudancas nas matrizes
}

// definicao dos eventos de mouse
void mouseEvents(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON){
        if(state == GLUT_UP) {
            if(!farol)
                farol = true;
            else
                farol = false;
        }  
    }
         
    glutPostRedisplay();    // marca matriz como necessario de redesenhar
}

// definicao dos eventos de teclados (teclas normais)
void keyboardEvents (unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            wheels = (wheels + 10) % 360;
            break;
        case 'A':
            wheels = (wheels - 10) % 360;
            break;
        case 'q':
            waist = (waist + 1) % 360;
            break;
        case 'Q':
            waist = (waist - 1) % 360;
            break;
        case 'w':
            if(shoulder <= 75)    
                shoulder += 1;
            break;
        case 'W':
            if(shoulder >= 0)    
                shoulder -= 1;
            break;
        case 'e':
            if(elbow <= 0)    
                elbow += 1;
            break;
        case 'E':
            if(elbow >= -75)    
                elbow -= 1;
            break;
        case 'r':
            if(shovel <= 55)    
                shovel += 1;
            break;
        case 'R':
            if(shovel >= -5)
                shovel -= 1;
            break;
        case ZOOM_OUT:  // '-'
            zoom -= 0.2;
            break;
        case ZOOM_IN:   // '+'
            zoom += 0.2;
            break;
        case ESC:
            exit(0);
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

// definicao dos eventos de teclado (teclas especiais)
void specialKeysEvents(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            xAngle = (xAngle - 10) % 360;
            break;
        case GLUT_KEY_UP:
            xAngle = (xAngle + 10) % 360;
            break;
        case GLUT_KEY_LEFT:
            yAngle = (yAngle - 10) % 360;
            break;
        case GLUT_KEY_RIGHT:
            yAngle = (yAngle + 10) % 360;
            break;
        default:
            break;
    }

    glutPostRedisplay();    // marca matriz como necessario de redesenhar
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (700, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Escavadeira");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(renderScene);
    glutMouseFunc(mouseEvents);
    glutKeyboardFunc(keyboardEvents);
    glutSpecialFunc(specialKeysEvents);
    glutMainLoop();

    return 0;
}