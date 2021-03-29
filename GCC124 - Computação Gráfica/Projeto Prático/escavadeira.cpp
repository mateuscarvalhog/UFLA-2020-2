#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

// definicoes ascii
#define BACKSPACE 8
#define ESC      27
#define SPACE    32
#define PLUS     43
#define MINUS    45

// variaveis de manipulacao de acoes
GLfloat zoom = 0, run = 0.0;
static int xAngle = 0, yAngle = 0;
static int wheels = 0, waist = 0, shoulder = 0, elbow = 0, shovel = 25;
static bool farol = false;

// variaveis de iluminação
GLfloat darkMode[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat ligthAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPosition[] = { 2.0f, 5.0f, 5.0f, 0.0f };

/* Cria textura de tabuleiro de xadrez */
#define checkeredBorderWidth 16
#define checkeredBorderHeight 16
static GLubyte checkeredBorder[checkeredBorderHeight][checkeredBorderWidth][4];

#ifdef GL_VERSION_1_1
    static GLuint texName;
#endif

void makecheckeredBorder(void) {
   int i, j, c;
    
   for(i = 0; i < checkeredBorderHeight; i++) {
        for (j = 0; j < checkeredBorderWidth; j++) {
            c = ((((i&0x8)==0)^((j&0x8))==0))*255;
            checkeredBorder[i][j][0] = (GLubyte) c;
            checkeredBorder[i][j][1] = (GLubyte) c;
            checkeredBorder[i][j][2] = (GLubyte) c;
            checkeredBorder[i][j][3] = (GLubyte) 255;
        }
   }
}
/* ---------------------------------- */

void light() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    if(farol == true) {
        glLightfv(GL_LIGHT0, GL_AMBIENT, ligthAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    } else {
        glLightfv(GL_LIGHT0, GL_AMBIENT, darkMode);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, darkMode);
        glLightfv(GL_LIGHT0, GL_SPECULAR, darkMode);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    }
}

void init() {
    glClearColor(0, 0, 0.139, 0.0f);
    glShadeModel(GL_FLAT);


    makecheckeredBorder();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    #ifdef GL_VERSION_1_1
        glGenTextures(1, &texName);
        glBindTexture(GL_TEXTURE_2D, texName);
    #endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    #ifdef GL_VERSION_1_1
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkeredBorderWidth, checkeredBorderHeight, 
                    0, GL_RGBA, GL_UNSIGNED_BYTE, checkeredBorder);
    #else
        glTexImage2D(GL_TEXTURE_2D, 0, 4, checkeredBorderWidth, checkeredBorderHeight, 
                    0, GL_RGBA, GL_UNSIGNED_BYTE, checkeredBorder);
    #endif
}

// definindo visao
void reshape(int w, int h) {
    glViewport (0, 0, w, h); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f,  w / h, 0.01f, 200.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef (0.0f, 0.0f, -5.0f);
}

void drawPlain(float halfWidth, float halfLength) {    
    glBegin(GL_QUADS);
        glVertex3f(-halfLength, 0.0, -halfWidth);
        glVertex3f(halfLength, 0.0, -halfWidth);
        glVertex3f(halfLength, 0.0, halfWidth);
        glVertex3f(-halfLength, 0.0, halfWidth);
    glEnd();
}

void drawAsphaltBorder(float halfWidth, float halfLength, float asphaltHalfLength) {
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    #ifdef GL_VERSION_1_1
        glBindTexture(GL_TEXTURE_2D, texName);
    #endif
    
    glTranslatef(-1000, 0.0, 0.0);
    glPushMatrix();

        for(int i = 0; i < (2 * asphaltHalfLength); i += (2 * halfLength)) {
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0); glVertex3f(-halfLength, 0.0, -halfWidth);
                glTexCoord2f(1.0, 0.0); glVertex3f(halfLength, 0.0, -halfWidth);
                glTexCoord2f(1.0, 1.0); glVertex3f(halfLength, 0.0, halfWidth);
                glTexCoord2f(0.0, 1.0); glVertex3f(-halfLength, 0.0, halfWidth);
            glEnd();
            glTranslatef((2 * halfLength), 0.0, 0.0);
        }
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

// define e desenha a cena
void renderScene() {
    float asphaltHalfLength = 1000;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    light();

    GLUquadric* gluQuadric = gluNewQuadric();
    
    glPushMatrix();
        // zoom e rotacoes de visao do objeto
        glTranslatef(0.0f, 0.0f, zoom);
        glRotatef(xAngle, 1.0f, 0.0f, 0.0f); 
        glRotatef(yAngle, 0.0f, 1.0f, 0.0f);

        glPushMatrix();
            glColor3f(0.105, 0.105, 0.105);
            glTranslatef(0.0f, -1.0f, 0.0f);
            drawPlain(3, asphaltHalfLength); // asfalto

            // canteiro 1
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, 3.5f);
                drawAsphaltBorder(0.5, 0.5, asphaltHalfLength);
                
                //planicie 1
                glColor3f(0.050, 0.205, 0.050);
                glTranslatef(asphaltHalfLength, 0.0f, 1000.5f);
                drawPlain(1000, asphaltHalfLength);
            glPopMatrix();

            // canteiro 2
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, -3.5f);
                drawAsphaltBorder(0.5, 0.5, asphaltHalfLength);

                //planicie 1
                glColor3f(0.050, 0.205, 0.050);
                glTranslatef(asphaltHalfLength, 0.0f, -1000.5f);
                drawPlain(1000, asphaltHalfLength);
            glPopMatrix();
        glPopMatrix();

        glColor3f(0.545, 0.000, 0.000);

        glTranslatef(run, 0.0f, 0.0f);

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
            waist = (waist + 2) % 360;
            break;
        case 'Q':
            waist = (waist - 2) % 360;
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
        case MINUS:  // '-'
            zoom -= 0.1;
            break;
        case PLUS:   // '+'
            zoom += 0.1;
            break;
        case SPACE:
            wheels = (wheels + 10) % 360;
            run -= 0.1;
            break;
        case BACKSPACE:
            wheels = (wheels - 10) % 360;
            run += 0.1;
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
            if(xAngle > -10) {
                xAngle = xAngle - 5;
            }
            break;
        case GLUT_KEY_UP:
            if(xAngle < 90) {
                xAngle = xAngle + 5;
            }
            break;
        case GLUT_KEY_RIGHT:
            yAngle = (yAngle - 5) % 360;
            break;
        case GLUT_KEY_LEFT:
            yAngle = (yAngle + 5) % 360;
            break;
        default:
            break;
  }

  glutPostRedisplay();    // marca matriz como necessario de redesenhar
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize (700, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Escavadeira v2.0");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(renderScene);
    glutMouseFunc(mouseEvents);
    glutKeyboardFunc(keyboardEvents);
    glutSpecialFunc(specialKeysEvents);
    glutMainLoop();

    return 0;
}