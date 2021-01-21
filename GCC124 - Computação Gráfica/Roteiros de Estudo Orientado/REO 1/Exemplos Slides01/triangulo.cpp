#include <GL/glut.h>
#include <cmath>

struct PONTO {
    float posX;
    float posY;
} ponto;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);    // cor de fundo no buffer
    glOrtho (0, 256, 0, 256, -1 ,1);     // modo de projecao (ortogonal)
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);   // limpa o buffer de acordo com glClearColor()
	glColor3f (0.0, 0.0, 0.0);      // cor do desenho

    glPointSize(3.0);               // tamanho do ponto e traco
	glLineWidth(3);

    float metadeLado = 50 / sqrt(3);

    PONTO p1, p2, p3;
    p1.posX = 128;
    p1.posY = 156;
    p2.posX = p1.posX - metadeLado;
    p2.posY = 103;
    p3.posX = p1.posX + metadeLado;
    p3.posY = 103;

    glBegin(GL_LINE_LOOP);      //indica inicio de um desenho com loop
        glVertex2f(p1.posX, p1.posY);
        glVertex2f(p2.posX, p2.posY);   //triangulo equilatero
		glVertex2f(p3.posX, p3.posY);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                          // inicializa glut
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // define buffer e cores
    glutInitWindowPosition(710, 290);               // posicao da janela na tela
    glutInitWindowSize(500, 500);                   // tamanho da janela
    glutCreateWindow("Triangulo");                  // cria janela com nome indicado
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}