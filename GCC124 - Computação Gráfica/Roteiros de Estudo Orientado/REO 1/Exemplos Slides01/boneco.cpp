#include <GL/glut.h>
#include <cmath>

const float xyReferencial = 128.0;

struct PONTO {
    float posX;
    float posY;
} ponto;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);    // cor de fundo no buffer
    glOrtho(0, 256, 0, 256, -1 ,1);     // modo de projecao (ortogonal)
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);   // limpa o buffer de acordo com glClearColor()
	glColor3f (0.0, 0.0, 0.0);      // cor do desenho

    glPointSize(3.0);               // tamanho do ponto e traco
	glLineWidth(3);

    const int nPontos = 1000;
    const double pi = 3.1415926;
    int raio = 50;
    glBegin(GL_LINE_LOOP);
		for(int i = 0; i < nPontos; i++) {
			float angulo = i * 2 * pi / nPontos;
		    glVertex2f(128 + (cos(angulo) * raio), 128 + (sin(angulo) * raio));
		}
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