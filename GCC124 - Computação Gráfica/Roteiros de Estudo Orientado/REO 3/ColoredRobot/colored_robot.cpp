/*
* Copyright (c) 1993-1997, Silicon Graphics, Inc.
* ALL RIGHTS RESERVED 
* Permission to use, copy, modify, and distribute this software for 
* any purpose and without fee is hereby granted, provided that the above
* copyright notice appear in all copies and that both the copyright notice
* and this permission notice appear in supporting documentation, and that 
* the name of Silicon Graphics, Inc. not be used in advertising
* or publicity pertaining to distribution of the software without specific,
* written prior permission. 
*
* THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
* AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
* INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
* FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
* GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
* SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
* KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
* LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
* THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
* ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
* POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
* 
* US Government Users Restricted Rights 
* Use, duplication, or disclosure by the Government is subject to
* restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
* (c)(1)(ii) of the Rights in Technical Data and Computer Software
* clause at DFARS 252.227-7013 and/or in similar or successor
* clauses in the FAR or the DOD or NASA FAR Supplement.
* Unpublished-- rights reserved under the copyright laws of the
* United States.  Contractor/manufacturer is Silicon Graphics,
* Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
*
* OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
*/

/*
* robot.c
* This program shows how to composite modeling transformations
* to draw translated and rotated hierarchical models.
* Interaction:  pressing the s and e keys (shoulder and elbow)
* alters the rotation of the robot arm.
*/
#include <GL/glut.h>
#include <cstdlib>

#define ESC 27

static int shoulder = 0, elbow = 0, pulse = 0,
           spinPulse = 0, uFinger1 = 0, uFinger2 = 0,
           bFinger1 = 0, bFinger2 = 0;

void init() {
    GLfloat mat_shininess[] = {50.0};
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
 
	GLfloat light_position[] = {0.0, 0.0, 0.0, 0.0};
    GLfloat light_color[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_color);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   	GLfloat color[] = {0.184, 0.310, 0.310};
    glMaterialfv(GL_FRONT, GL_SPECULAR, color);
   	glMaterialfv(GL_FRONT, GL_AMBIENT, color);

    // body
    glPushMatrix();
    glTranslatef(-1.5, 0.0, 0.0);
    glScalef(1.0, 3.0, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // head
    glPushMatrix();
    glTranslatef(-1.5, 1.9, 0.0);
    glutSolidCube(0.8);
    glPopMatrix();

    // arm and shoulder articulation
    glPushMatrix();
    glTranslatef(-1.0, 0.7, 0.0);
    glRotatef((GLfloat) shoulder, 0.0, 0.0, 1.0);
    glTranslatef(0.75, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.5, 0.3, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    // forearm and elbow articulation
    glTranslatef(0.75, 0.0, 0.0);
    glRotatef((GLfloat) elbow, 0.0, 0.0, 1.0);
    glTranslatef(0.75, 0.0, 0.0);
    glPushMatrix();
    glScalef (1.5, 0.3, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    // hand and pulse articulation
    glTranslatef(0.75, 0.0, 0.0);
    glRotatef((GLfloat) pulse, 0.0, 0.0, 1.0);
    glRotatef((GLfloat) spinPulse, 1.0, 0.0, 0.0);
    glTranslatef((1.0 * 0.3) / 2, 0.0, 0.0);
    glPushMatrix();
    glScalef (0.3, 0.3, 0.3);
    glutSolidCube(1.0);
    glPopMatrix();

    // bottom finger
    // first articulation
    glPushMatrix();

    GLfloat color1[] = { 0.0, 1.0, 0.0, 0.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, color1);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color1);

    glTranslatef((1.0 * 0.3) / 2, -(1.0 * 0.3) / 2, 0.0);
    glRotatef((GLfloat) bFinger1, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glPushMatrix();
    glScalef (1.0, 0.1, 0.1);
    glutSolidCube(0.5);
    glPopMatrix();

    // second articulation
    glPushMatrix();
    glTranslatef(0.25, 0.0, 0.0);
    glRotatef((GLfloat) bFinger2, 0.0, 0.0, 1.0);
    glTranslatef(0.125, 0.0, 0.0);
    glScalef (0.5, 0.1, 0.1);
    glutSolidCube(0.5);
    glPopMatrix();
    glPopMatrix();

    // upper finger
    // first articulation
    glPushMatrix();

    GLfloat color2[] = { 0.0, 0.0, 1.0, 0.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, color2);
	glMaterialfv(GL_FRONT, GL_AMBIENT, color2);

    glTranslatef((1.0 * 0.3) / 2, (1.0 * 0.3) / 2, 0.0);
    glRotatef((GLfloat) uFinger1, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glPushMatrix();
    glScalef (1.0, 0.1, 0.1);
    glutSolidCube(0.5);
    glPopMatrix();

    // second articulation
    glPushMatrix();
    glTranslatef(0.25, 0.0, 0.0);
    glRotatef((GLfloat) uFinger2, 0.0, 0.0, 1.0);
    glTranslatef(0.125, 0.0, 0.0);
    glScalef (0.5, 0.1, 0.1);
    glutSolidCube(0.5);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0, 0.0, -5.0);
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 's':
            shoulder = (shoulder + 5) % 360;
            break;
        case 'S':
            shoulder = (shoulder - 5) % 360;
            break;
        case 'e':
            elbow = (elbow + 5) % 360;
            break;
        case 'E':
            elbow = (elbow - 5) % 360;
            break;
        case 'p':
            pulse = (pulse + 5) % 360;
            break;
        case 'P':
            pulse = (pulse - 5) % 360;
            break;
        case 'o':
            spinPulse = (spinPulse + 15) % 360;
            break;
        case 'O':
            spinPulse = (spinPulse - 15) % 360;
            break;
        case 'f':
            uFinger1 = (uFinger1 + 5) % 360;
            bFinger1 = (bFinger1 - 5) % 360;
            break;
        case 'F':
            uFinger1 = (uFinger1 - 5) % 360;
            bFinger1 = (bFinger1 + 5) % 360;
            break;
        case 'g':
            uFinger2 = (uFinger2 + 5) % 360;
            bFinger2 = (bFinger2 - 5) % 360;
            break;
        case 'G':
            uFinger2 = (uFinger2 - 5) % 360;
            bFinger2 = (bFinger2 + 5) % 360;
            break;
        case ESC:
            exit(0);
            break;
        default:
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Frank Puxa Frango");
    init();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}