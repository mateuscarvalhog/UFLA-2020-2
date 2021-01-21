/*  author: Mateus Carvalho Goncalves
    matricula: 201810245
    REO 01 - Computacao Grafica
    DCC/UFLA
*/

#include <GL/glut.h>
#include <cmath>

const float centro_janela = 128.0;      // valor do centro da janela

struct PONTO {
    float posX;
    float posY;
} ponto;

// desenha um quadrilatero de lados na ordem dos parametros
void quadrilatero(PONTO p1, PONTO p2, PONTO p3, PONTO p4) {
    glBegin(GL_LINE_LOOP);
        glVertex2f(p1.posX, p1.posY);
        glVertex2f(p2.posX, p2.posY);
        glVertex2f(p3.posX, p3.posY);
        glVertex2f(p4.posX, p4.posY);
    glEnd();
}

// desenha um circulo pequeno de centro (x, y)
void circuloPequeno(float x, float y) {
    const double pi = 3.1415926;
    float raio = 1;
    
    glBegin(GL_LINE_LOOP);
		for(int i = 0; i < 1000; i++) {
			float angulo = i * 2 * pi / 1000;
		    glVertex2f(x + (cos(angulo) * raio), y + (sin(angulo) * raio));
		}
    glEnd();
}

// desenha reta com pontos dos parametros
void reta(PONTO p1, PONTO p2) {
    glBegin(GL_LINE_STRIP);
        glVertex2f(p1.posX, p1.posY);
        glVertex2f(p2.posX, p2.posY);
    glEnd();
}

// define o vaso
void vaso() {
    float yReferencial = 245;

    float lCaixa = 20, hCaixa = 5;
    float lTampa = 10, hTampa = 25;

    PONTO p1, p2, p3, p4, p5, p6;   // 6 pontos para dois quadrilateros que compartilham 2 vertices
    
    p1.posX = p4.posX = centro_janela - (lCaixa / 2);
    p1.posY = p2.posY = yReferencial;
    p2.posX = p3.posX = p1.posX + lCaixa;
    p3.posY = p4.posY = yReferencial - hCaixa;
    p5.posX = centro_janela - (lTampa / 2);
    p6.posX = p5.posX + lTampa;
    p5.posY = p6.posY = yReferencial - (hCaixa + hTampa);
    
    quadrilatero(p1, p2, p3, p4);
    quadrilatero(p3, p4, p5, p6);
}

// define a pia
void pia() {
    float yReferencial = 205;
    
    float lQuadrilateroExterno = 30, hQuadrilateroExterno = 20;
    float lTorneira = 10, hTorneira = 2;
    float lQuadrilateroInterno = 20, hQuadrilateroInterno = 11;

    PONTO p1, p2, p3, p4;   // pontos reutilizados para formar quadrilateros

    // quadrado externo
    p1.posX = p4.posX = centro_janela - (lQuadrilateroExterno / 2);
    p1.posY = p2.posY = yReferencial;
    p2.posX = p3.posX = p1.posX + lQuadrilateroExterno;
    p3.posY = p4.posY = yReferencial - hQuadrilateroExterno;

    quadrilatero(p1, p2, p3, p4);

    yReferencial -= 1.5;

    // torneira
    p1.posX = p4.posX = centro_janela - (lTorneira / 2);
    p1.posY = p2.posY = yReferencial;
    p2.posX = p3.posX = p1.posX + lTorneira;
    p3.posY = p4.posY = yReferencial - hTorneira;

    quadrilatero(p1, p2, p3, p4);

    yReferencial -= 3.5;

    // quadrado interno
    p1.posX = p4.posX = centro_janela - (lQuadrilateroInterno / 2);
    p1.posY = p2.posY = yReferencial;
    p2.posX = p3.posX = p1.posX + lQuadrilateroInterno;
    p3.posY = p4.posY = yReferencial - hQuadrilateroInterno;

    quadrilatero(p1, p2, p3, p4);

    // ralo
    circuloPequeno(centro_janela, yReferencial - 3.5);

}

// define armario
void armario() {
    float yReferencial = 175;
    
    float lado = 30;

    PONTO p1, p2, p3, p4;   // um quadrado

    p1.posX = p4.posX = centro_janela - (lado / 2);
    p1.posY = p2.posY = yReferencial;
    p2.posX = p3.posX = p1.posX + lado;
    p3.posY = p4.posY = yReferencial - lado;

    quadrilatero(p1, p2, p3, p4);
}

// define espelho
void espelho() {
    float yReferencial = 135;
    
    float largura = 90, altura = 4;

    PONTO p1, p2, p3, p4;   // um retangulo

    p1.posX = p4.posX = centro_janela - (largura / 2);
    p1.posY = p2.posY = yReferencial;
    p2.posX = p3.posX = p1.posX + largura;
    p3.posY = p4.posY = yReferencial - altura;

    quadrilatero(p1, p2, p3, p4);
}

// define chuveiro
void chuveiro() {
    float yReferencial = 120;
    
    float lQuadrilateroExterno = 80, hQuadrilateroExterno = 50;
    float lQuadrilateroInterno = 70, hQuadrilateroInterno = 40;

    PONTO p1, p2, p3, p4;   // pontos reutilizados para formar quadrilateros

    // quadrado externo
    p1.posX = p4.posX = centro_janela - (lQuadrilateroExterno / 2);
    p1.posY = p2.posY = yReferencial;
    p2.posX = p3.posX = p1.posX + lQuadrilateroExterno;
    p3.posY = p4.posY = yReferencial - hQuadrilateroExterno;

    quadrilatero(p1, p2, p3, p4);

    yReferencial -= 5;

    // quadrado interno
    p1.posX = p4.posX = centro_janela - (lQuadrilateroInterno / 2);
    p1.posY = p2.posY = yReferencial;
    p2.posX = p3.posX = p1.posX + lQuadrilateroInterno;
    p3.posY = p4.posY = yReferencial - hQuadrilateroInterno;

    quadrilatero(p1, p2, p3, p4);

    PONTO aux;
    aux.posX = centro_janela - 3;
    aux.posY = yReferencial - (hQuadrilateroInterno / 2) + 1;
    reta(p1, aux);

    aux.posX = centro_janela + 3;
    reta(p2, aux);
    
    aux.posY = yReferencial - (hQuadrilateroInterno / 2) - 1;
    reta(p3, aux);

    aux.posX = centro_janela - 3;
    reta(p4, aux);

    // circulo
    circuloPequeno(centro_janela, yReferencial - (hQuadrilateroInterno / 2));
}

// define banheira
void banheira() {
    float yReferencial = 60;
    
    float lQuadrilateroExterno = 80, hQuadrilateroExterno = 45;
    float lQuadrilateroInterno = 73, hQuadrilateroInterno = 38;

    PONTO p1, p2, p3, p4;   // pontos reutilizados para formar quadrilateros

    // quadrado externo
    p1.posX = p4.posX = centro_janela - (lQuadrilateroExterno / 2);
    p1.posY = p2.posY = yReferencial;
    p2.posX = p3.posX = p1.posX + lQuadrilateroExterno;
    p3.posY = p4.posY = yReferencial - hQuadrilateroExterno;

    quadrilatero(p1, p2, p3, p4);

    yReferencial -= 3.5;

    // quadrado interno
    p1.posX = p4.posX = centro_janela - (lQuadrilateroInterno / 2);
    p1.posY = p2.posY = yReferencial;
    p2.posX = p3.posX = p1.posX + lQuadrilateroInterno;
    p3.posY = p4.posY = yReferencial - hQuadrilateroInterno;

    quadrilatero(p1, p2, p3, p4);

    // circulo
    circuloPequeno(p2.posX - 3, yReferencial - (hQuadrilateroInterno / 2));
}

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);   // cor de fundo no buffer
    glOrtho(0, 256, 0, 256, -1 ,1);     // modo de projecao (ortogonal)
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);   // limpa o buffer de acordo com glClearColor()
	glColor3f (0.0, 0.0, 0.0);      // cor do desenho

    glPointSize(3.0);               // tamanho do ponto e traco
	glLineWidth(3);

    vaso();
    pia();
    armario();
    espelho();
    chuveiro();
    banheira();

    glFlush();                      // forca a executar comandos gl no buffer o mais rapido possivel
}

int main( int argc, char** argv) {
    glutInit(&argc, argv);                                  // inicializa glut
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);            // define buffer e cores
    glutInitWindowPosition(545, 115);                       // posicao da janela na tela
    glutInitWindowSize(850, 850);                           // tamanho da janela
    glutCreateWindow("REO1_MateusCarvalho_201810245");      // cria janela com nome indicado
    init();
    glutDisplayFunc(display);                               // chama a funcao que sera desenhada pelo glut
    glutMainLoop();                                         // mostra as janelas criadas

    return 0;
}