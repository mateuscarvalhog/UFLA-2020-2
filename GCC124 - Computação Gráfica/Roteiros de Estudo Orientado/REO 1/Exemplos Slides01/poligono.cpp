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
    
    PONTO p1, p2, p3, p4, p5, p6, p7, p8, p9;

    p1.posX = p5.posX = p9.posX = 128;  // centro no eixo x
    p4.posY = p5.posY = p6.posY = 128;  // centro no eixo y
    
    float diagonal = sqrt(pow(20, 2) + pow(20, 2));     // descobrindo diagonal do quadrado de lado 20

    p1.posY = p6.posX = 128 + diagonal;
    p4.posX = p9.posY = 128 - diagonal;
    p2.posX = p7.posX = p7.posY = p8.posY = 128 - (diagonal / 2);
    p2.posY = p3.posY = p3.posX = p8.posX = 128 + (diagonal / 2);

    glBegin(GL_LINE_LOOP);  // quadrado externo
        glVertex2f(p1.posX, p1.posY);
        glVertex2f(p4.posX, p4.posY);
        glVertex2f(p9.posX, p9.posY);
        glVertex2f(p6.posX, p6.posY);
    glEnd();

    glBegin(GL_LINE_STRIP); // primeira linha interna
        glVertex2f(p2.posX, p2.posY);
        glVertex2f(p8.posX, p8.posY);
    glEnd();

    glBegin(GL_LINE_STRIP); // segunda linha interna
        glVertex2f(p3.posX, p3.posY);
        glVertex2f(p7.posX, p7.posY);
    glEnd();

    glFlush();
}

int main( int argc, char** argv) {
    glutInit(&argc, argv);                          // inicializa glut
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    // define buffer e cores
    glutInitWindowPosition(710, 290);               // posicao da janela na tela
    glutInitWindowSize(500, 500);                   // tamanho da janela
    glutCreateWindow("Poligono");                   // cria janela com nome indicado
    init();
    glutDisplayFunc(display);                       // chama a funcao que sera desenhada pelo glut
    glutMainLoop();                                 // mostra as janelas criadas

    return 0;
}