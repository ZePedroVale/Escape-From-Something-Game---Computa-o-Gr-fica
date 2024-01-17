#include <stdio.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

// Função de texto 3D
void escreve(int width, int height, float x, float y, void* font, string texto)
{
	float xxx = (float)x;
	float yyy = (float)y;

	glRasterPos2f(xxx, yyy);
	for (int i = 0; i < texto.length(); i++)
		glutBitmapCharacter(font, texto.at(i));
}





float rAngle = 0.0;
float xr = 1, yr = 1;
float x1x = 3.5, x1y = 3.8, x2x = 4.3, x2y = 3.8, x3x = 4.3, x3y = 4.5, x4x = 3.5, x4y = 4.5; //retangulo verde
float a1a = 5.5, a1b = 5.8, a2a = 6.3, a2b = 5.8, a3a = 6.3, a3b = 6.5, a4a = 5.5, a4b = 6.5; //retangulo amarelo

void display(void);
void specialkey(unsigned char key, int x, int y);
void keyboardd(int key, int x, int y);


//função ângulo rotação
void update(int value) {
	rAngle += 1.0f;
	if (rAngle > 50) {
		rAngle -= 1;
		if (rAngle <= 70) {
			rAngle -= 85.0f;

		}
	}
	glutPostRedisplay();
	glutTimerFunc(150, update, 0);
}

// Menu items
enum MENU_TYPE
{
	JOGAR_DE_NOVO,
	INSTRUCOES,
	FECHAR,
};
// Função para o menu
void menu(int item)
{
	switch (item)
	{
	case JOGAR_DE_NOVO:
	{
		xr = 1, yr = 1; // fazer com que o poligno volte ao inicio
		x1x = 3.5, x1y = 3.8, x2x = 4.3, x2y = 3.8, x3x = 4.3, x3y = 4.5, x4x = 3.5, x4y = 4.5; //retangulo verde
	}break;
	case INSTRUCOES:
	{
		MessageBox(NULL, L" O objetivo do jogo é empurrar o retângulo verde para o retângulo amarelo sem tocar no vermelho, e assim entrar no portal da vitória!", L"Instruções",
			MB_OK | MB_ICONEXCLAMATION);
	}break;
	case FECHAR:
	{
		exit(1);
	}
	break;
	default:
	{       exit(1);     }
	break;
	}
	glutPostRedisplay();
	return;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	glutSwapBuffers();   // swapping image buffer for double buffering
	glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
	glClear(GL_COLOR_BUFFER_BIT); // clears the frame buffer and set values defined in glClearColor() function call 
	glMatrixMode(GL_PROJECTION);              // setup viewing projection
	glLoadIdentity();                           // start with identity matrix
	glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);   // setup a 10x10x2 viewing world

		//Função para Fazer aparecer o quadrado branco apenas quando o quadrado verde estiver nas posições do quadrado amarelo
	if (x1x >= 5.4 && x1y >= 5.7 && x3x <= 6.35 && x3y <= 6.55) {
		if ((1.7f + xr) >= 7.5 && (1.3f + xr) >= 7.51 && (1.7f + yr) <= 2.5) {
			MessageBox(NULL, L"Ganhou!", L"Mensagem",
				MB_OK | MB_ICONEXCLAMATION); //Mensagem a pois perder :) 
			xr = 1, yr = 1; // fazer com que o poligno volte ao inicio ;) 
			x1x = 3.5, x1y = 3.8, x2x = 4.3, x2y = 3.8, x3x = 4.3, x3y = 4.5, x4x = 3.5, x4y = 4.5; // fazer com que o quadrado volte ao inicio ;)
		}
	}
	// area vermelha
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.2, 0.8, 0.0);
	glVertex3f(9.8, 0.8, 0.0);
	glVertex3f(9.8, 9.8, 0.0);
	glVertex3f(0.2, 9.8, 0.0);
	glEnd();
	// area cinza
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_POLYGON);
	glVertex3f(0.5, 1.8, 0.0);
	glVertex3f(9.6, 1.8, 0.0);
	glVertex3f(9.6, 9.0, 0.0);
	glVertex3f(0.5, 9.0, 0.0);
	glEnd();




	//lado esquerdo        baixo                direito              cima Função para fazer com que o jogador peca caso toque na area vermelha
	if ((1.4 + xr) <= 0.5 || (1.4 + yr) <= 1.8 || (1.7 + xr) >= 9.6 || (1.7 + yr) >= 9.0) {  // reiniciar o jogo
		MessageBox(NULL, L"Perdeu!", L"Mensagem",
			MB_OK | MB_ICONEXCLAMATION); //Mensagem a pois perder :) 
		xr = 1, yr = 1; // fazer com que o poligno volte ao inicio ;) 
		x1x = 3.5, x1y = 3.8, x2x = 4.3, x2y = 3.8, x3x = 4.3, x3y = 4.5, x4x = 3.5, x4y = 4.5; // fazer com que o quadrado volte ao inicio ;) 
	}
	//retangulo amarelo
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(a1a, a1b, 0.0); //3.5 , 3.8
	glVertex3f(a2a, a2b, 0.0); //4.3 , 3.8
	glVertex3f(a3a, a3b, 0.0); //4.3 , 4.5
	glVertex3f(a4a, a4b, 0.0); //3.5 , 4.5
	glEnd();
	//Função para fazer aparecer a area branca
	if (x1x >= 5.4 && x1y >= 5.7 && x3x <= 6.35 && x3y <= 6.55) {
		//retangulo branco
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex3f(7.5, 1.8, 0.0); //3.5 , 3.8
		glVertex3f(8.3, 1.8, 0.0); //4.3 , 3.8
		glVertex3f(8.3, 2.5, 0.0); //4.3 , 4.5
		glVertex3f(7.5, 2.5, 0.0); //3.5 , 4.5
		glEnd();
	}
	//retangulo verde
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(x1x, x1y, 0.0); //3.5 , 3.8
	glVertex3f(x2x, x2y, 0.0); //4.3 , 3.8
	glVertex3f(x3x, x3y, 0.0); //4.3 , 4.5
	glVertex3f(x4x, x4y, 0.0); //3.5 , 4.5
	glEnd();

	//triangulo rotacao
	glPushMatrix();
	glRotatef(-rAngle, 0, 0, 1);
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(4, 6);
	glVertex2f(3, 6);
	glVertex2f(4, 5);
	glEnd();
	glPopMatrix();
	glutSwapBuffers();

	glPushMatrix();
	glRotatef(-rAngle, 0, 0, 1);
	glBegin(GL_POLYGON);            // vertices do poligno
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex2f(3.8f, 5.7f); //0
	glVertex2f(4.0f, 5.7f); //1
	glVertex2f(4.1f, 5.9f); //2
	glVertex2f(4.0f, 6.1f); //3
	glVertex2f(3.8f, 6.1f); //4
	glVertex2f(3.7f, 5.9f); //5
	glEnd();
	glPopMatrix();
	glutSwapBuffers();




	glBegin(GL_POLYGON);            // vertices do poligno jogador
	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex2f(1.4f + xr, 1.3f + yr); //0
	glVertex2f(1.6f + xr, 1.3f + yr); //1
	glVertex2f(1.7f + xr, 1.5f + yr); //2
	glVertex2f(1.6f + xr, 1.7f + yr); //3
	glVertex2f(1.4f + xr, 1.7f + yr); //4
	glVertex2f(1.3f + xr, 1.5f + yr); //5
	glEnd();

	if ((1.4 + xr) >= x1x && (1.6 + xr) <= x2x && (1.71 + yr) >= x1y && (1.71 + yr) <= x3y) {  // Lado de cima do triangulo feito
		x1y = x1y + 0.1;
		x2y = x2y + 0.1;
		x3y = x3y + 0.1;
		x4y = x4y + 0.1;
		yr = yr - 0.09; // fazer com que o poligno volte para tras
	}

	if ((1.4 + xr) >= x1x && (1.6 + xr) <= x2x && (1.32 + yr) <= x4y + 0.1 && (1.71 + yr) >= x3y) {  // Lado de baixo do triangulo
		x1y = x1y - 0.1;
		x2y = x2y - 0.1;
		x3y = x3y - 0.1;
		x4y = x4y - 0.1;
		yr = yr + 0.09; // fazer com que o poligno volte para tras
	}

	if ((1.5 + yr) >= x2y && (1.5 + yr) <= x3y && (1.29 + xr) <= x2x && (1.29 + xr) >= x1x) {  // Lado Esquerdo do Triangulo feito
		x1x = x1x - 0.1;
		x2x = x2x - 0.1;
		x3x = x3x - 0.1;
		x4x = x4x - 0.1;
		xr = xr + 0.09; // fazer com que o poligno volte para tras
	}

	if ((1.5 + yr) >= x1y && (1.5 + yr) <= x4y && (1.71 + xr) >= x1x && (1.71 + xr) <= x2x) {  // Lado direito do Triangulo feito
		x1x = x1x + 0.1;
		x2x = x2x + 0.1;
		x3x = x3x + 0.1;
		x4x = x4x + 0.1;
		xr = xr - 0.09; // fazer com que o poligno volte para tras
	}

	glColor3f(0, 1, 0);
	escreve(0, 0, 0.1, 0.3, GLUT_BITMAP_TIMES_ROMAN_24, "Aperte o botao direito do rato para instrucoes");

	glFlush();
	glMatrixMode(GL_MODELVIEW);
	glutKeyboardFunc(specialkey);
}

void keyboardd(int key, int x, int y) {
	switch (key) {

	case GLUT_KEY_UP:
		yr = yr + 0.1;
		break;
	case GLUT_KEY_DOWN:
		yr = yr - 0.1;
		break;
	case GLUT_KEY_LEFT:
		xr = xr - 0.1;
		break;
	case GLUT_KEY_RIGHT:
		xr = xr + 0.1;
		break;

	case 27:                                         // tecla Esc (encerra o programa)
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void specialkey(unsigned char key, int x, int y) {
	switch (key) {
		if (key == 27 || key == 'q') {  // 27 = esc
			xr = xr + 0.01;
			break;
		}
	case GLUT_KEY_UP:
		glMatrixMode(GL_PROJECTION);
		xr = xr + 0.1;
		break;
	case GLUT_KEY_DOWN:
		glMatrixMode(GL_PROJECTION);
		xr = xr - 0.1;
		break;
	case GLUT_KEY_LEFT:
		glMatrixMode(GL_PROJECTION);
		yr = yr + 0.1;
		break;
	case GLUT_KEY_RIGHT:
		glMatrixMode(GL_PROJECTION);
		yr = yr - 0.1;
		break;
	case 27:                                         // tecla Esc (encerra o programa)
		exit(0);
		break;
		glutPostRedisplay();		// redraw the image now
	}
}

int main(int argc, char** argv)
{
	printf("Do Something\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	//	printf(xr);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(200, 0);
	glutCreateWindow("Do Something");
	glutDisplayFunc(display);
	glutKeyboardFunc(specialkey);                             // funcoes de teclado
	glutSpecialFunc(keyboardd);                             // funcoes de teclado
	glutTimerFunc(25, update, 0);
	// Create a menu
	glutCreateMenu(menu);
	// Add menu items
	glutAddMenuEntry("Jogar de Novo", JOGAR_DE_NOVO);
	glutAddMenuEntry("Instruções", INSTRUCOES);
	glutAddMenuEntry("Fechar", FECHAR);
	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}