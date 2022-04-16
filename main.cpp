#include <iostream>
#include <fstream>
#include<windows.h>
#include <GL/freeglut.h>
#include <ctime>
#include <cstdlib>

using namespace std;


GLdouble left_m = -100.0;
GLdouble right_m = 700.0;
GLdouble bottom_m = -140.0;
GLdouble top_m = 460.0;
double ok = 1;
double j = 0.0;
double i = 0.0;
double contor = 0;
double loc_vert = 800;
int vector[3] = { 0, 160, 320 };
double height = vector[rand() % 3];
double height2 = vector[rand() % 3];
int score = 0;
double timp = 0.15;
int pct = 1000;
double rsj, rdj, rss, rds = 0;
bool changeScore = false;
int dificultate = 2;
int color;
float rMasina1, gMasina1, bMasina1;
float rMasina2, gMasina2, bMasina2;
bool inMenu = true;
bool inEndScreen = false;

bool gameover = false;

int highscore;

void delay(float secs)
{
	float end = clock() / CLOCKS_PER_SEC + secs;
	while ((clock() / CLOCKS_PER_SEC) < end);
}

void init(void)
{
	glClearColor(0.4, 0.4, 0.4, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(left_m, right_m, bottom_m, top_m, -1.0, 1.0);
}

void RenderString(float x, float y, void* font, const unsigned char* string)
{

	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);

	glutBitmapString(font, string);
	glPopAttrib();
}
void startgame(void)
{

	if ((height != j || (loc_vert > 90 || loc_vert < -90)) && (height2 != j || (loc_vert > 90 || loc_vert < -90)))
	{

		if (i < -380)
		{
			i = 0;
		}
		i = i - 2 * timp;

		loc_vert -= dificultate * timp;

		if (loc_vert < -150)
		{
			score += 100;
			unsigned seed = time(0);
			srand(seed);
			height = vector[rand() % 3];
			height2 = vector[rand() % 3];
			color = rand() % 5;
			cout << height << " " << height2 << endl;
			cout << "Score:  " << score << endl;
			changeScore = true;
			loc_vert = 800;
		}

		if (score >= pct && pct <= 15000)
		{
			timp += 0.1;
			pct += 1000;
		}

		glutPostRedisplay();
	}
	else {
		ok = 0;
	}
}

void startMenu(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.5, 0.99, 0.5);
	// Iarba de jos
	glBegin(GL_POLYGON);
	glVertex2i(-100, -140);// Stanga jos
	glVertex2i(700, -140); // Dreapta jos
	glVertex2i(700, -80);  // Dreapta sus
	glVertex2i(-100, -80); // Stanga sus
	glEnd();

	// Iarba de sus
	glBegin(GL_POLYGON);
	glVertex2i(-100, 400);// Stanga jos
	glVertex2i(700, 400); // Dreapta jos
	glVertex2i(700, 460); // Dreapta sus
	glVertex2i(-100, 460);// Stanga sus
	glEnd();

	glColor3f(0, 0, 0);
	glRasterPos3f(200, 425, 0);
	char message[] = "Crashing mission!";
	for (int i = 0; i < strlen(message); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,message[i]);

	glRasterPos3f(110, -115, 0);
	char message2[] = "A game about cars, crashes and you!";
	for (int i = 0; i < strlen(message2); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message2[i]);

	glColor3f(1, 1, 1);
	glRasterPos3f(160, 150, 0);
	char message3[] = "Press X to start the game";
	for (int i = 0; i < strlen(message3); i++) {
		glColor3f(0, 0, 0);
		if (message3[i] == 'X') {
			glColor3f(1, 0, 0);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message3[i]);
		}
		else glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message3[i]);
	}


	glPushMatrix();
	glTranslated(0, 50, 0);
	glPushMatrix();

	//prima masina
	glColor3f(0, 0, 0);
	glRecti(-45, -15, 45, 15);

	glColor3f(1, 1, 1);
	glRecti(-30, -15, 30, 15);

	//girofar
	glColor3f(0, 0, 1);
	glRecti(-5, -15, 5, 0);
	glColor3f(1, 0, 0);
	glRecti(-5, 0, 5, 15);

	// stopuri
	glColor3f(1, 0, 0);
	glRecti(-45, -15, -40, -5);
	glRecti(-45, 15, -40, 5);

	// faaruri
	glColor3f(0.8, 0.5, 0);
	glRectf(45, 15, 40, 5);
	glRectf(45, -15, 40, -5);

	//a doua masina 

	glPushMatrix();
	glTranslated(550, 0, 0);
	glPushMatrix();

	glColor3f(0.7, -0.5, 0);
	glRecti(-45, -15, 45, 15);

	// faruri
	glColor3f(0.8, 0.5, 0);
	glRecti(-45, -15, -40, -5);
	glRecti(-45, 15, -40, 5);
	// stopuri
	glColor3f(1, 0, 0);
	glRectf(45, 15, 40, 5);
	glRectf(45, -15, 40, -5);

	//parbrizul
	glColor3f(0.85, 0.85, 0.85);
	glRecti(-30, -12, -15, 12);

	//plafon
	glColor3f(0.75, 0.75, 0.75);
	glRecti(-10, -12, 20, 12);

	//luneta
	glColor3f(0.85, 0.85, 0.85);
	glRecti(25, -12, 35, 12);

	//a treia masina 

	glPushMatrix();
	glTranslated(0, 150, 0);
	glRotated(180, 0, 0, 0);
	glPushMatrix();

	glColor3f(0, 0, 0);
	glRecti(-45, -15, 45, 15);

	glColor3f(1, 1, 1);
	glRecti(-30, -15, 30, 15);

	//girofar
	glColor3f(0, 0, 1);
	glRecti(-5, -15, 5, 0);
	glColor3f(1, 0, 0);
	glRecti(-5, 0, 5, 15);

	// stopuri
	glColor3f(1, 0, 0);
	glRecti(-45, -15, -40, -5);
	glRecti(-45, 15, -40, 5);

	// faruri
	glColor3f(0.8, 0.5, 0);
	glRectf(45, 15, 40, 5);
	glRectf(45, -15, 40, -5);

	//a patra masina 

	glPushMatrix();
	glTranslated(550, 0, 0);
	//glRotated(90, 0, 0, 0);
	glPushMatrix();

	glColor3f(1, 1, 0);
	glRecti(-45, -15, 45, 15);

	// faruri
	glColor3f(0.8, 0.5, 0);
	glRecti(-45, -15, -40, -5);
	glRecti(-45, 15, -40, 5);
	// stopuri
	glColor3f(1, 0, 0);
	glRectf(45, 15, 40, 5);
	glRectf(45, -15, 40, -5);

	//parbrizul
	glColor3f(0.85, 0.85, 0.85);
	glRecti(-30, -12, -15, 12);

	//plafon
	glColor3f(0.75, 0.75, 0.75);
	glRecti(-10, -12, 20, 12);

	//luneta
	glColor3f(0.85, 0.85, 0.85);
	glRecti(25, -12, 35, 12);

	glutSwapBuffers();
}

void endScreen(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.5, 0.99, 0.5);
	// Iarba de jos
	glBegin(GL_POLYGON);
	glVertex2i(-100, -140);// Stanga jos
	glVertex2i(700, -140); // Dreapta jos
	glVertex2i(700, -80);  // Dreapta sus
	glVertex2i(-100, -80); // Stanga sus
	glEnd();

	// Iarba de sus
	glBegin(GL_POLYGON);
	glVertex2i(-100, 400);// Stanga jos
	glVertex2i(700, 400); // Dreapta jos
	glVertex2i(700, 460); // Dreapta sus
	glVertex2i(-100, 460);// Stanga sus
	glEnd();

	glColor3f(0, 0, 0);
	glRasterPos3f(200, 425, 0);
	char message[] = "Crashing mission!";
	for (int i = 0; i < strlen(message); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message[i]);

	glRasterPos3f(110, -115, 0);
	char message2[] = "A game about cars, crashes and you!";
	for (int i = 0; i < strlen(message2); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message2[i]);

	glColor3f(1, 1, 1);
	glRasterPos3f(180, 200, 0);
	char message4[] = "You crashed, too bad";
	for (int i = 0; i < strlen(message4); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message4[i]);

	glColor3f(1, 1, 1);
	glRasterPos3f(160, 120, 0);
	char message3[] = "Press C to close the game";
	for (int i = 0; i < strlen(message3); i++) {
		glColor3f(0, 0, 0);
		if (message3[i] == 'X') {
			glColor3f(1, 0, 0);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message3[i]);
		}
		else glutBitmapCharacter(GLUT_BITMAP_9_BY_15, message3[i]);
	}


	glPushMatrix();
	glTranslated(0, 50, 0);
	glPushMatrix();

	//prima masina
	glColor3f(0, 0, 0);
	glRecti(-45, -15, 45, 15);

	glColor3f(1, 1, 1);
	glRecti(-30, -15, 30, 15);

	//girofar
	glColor3f(0, 0, 1);
	glRecti(-5, -15, 5, 0);
	glColor3f(1, 0, 0);
	glRecti(-5, 0, 5, 15);

	// stopuri
	glColor3f(1, 0, 0);
	glRecti(-45, -15, -40, -5);
	glRecti(-45, 15, -40, 5);

	// faaruri
	glColor3f(0.8, 0.5, 0);
	glRectf(45, 15, 40, 5);
	glRectf(45, -15, 40, -5);

	//a doua masina 

	glPushMatrix();
	glTranslated(550, 0, 0);
	glPushMatrix();

	glColor3f(0.7, -0.5, 0);
	glRecti(-45, -15, 45, 15);

	// faruri
	glColor3f(0.8, 0.5, 0);
	glRecti(-45, -15, -40, -5);
	glRecti(-45, 15, -40, 5);
	// stopuri
	glColor3f(1, 0, 0);
	glRectf(45, 15, 40, 5);
	glRectf(45, -15, 40, -5);

	//parbrizul
	glColor3f(0.85, 0.85, 0.85);
	glRecti(-30, -12, -15, 12);

	//plafon
	glColor3f(0.75, 0.75, 0.75);
	glRecti(-10, -12, 20, 12);

	//luneta
	glColor3f(0.85, 0.85, 0.85);
	glRecti(25, -12, 35, 12);

	//a treia masina 

	glPushMatrix();
	glTranslated(0, 150, 0);
	glRotated(180, 0, 0, 0);
	glPushMatrix();

	glColor3f(0, 0, 0);
	glRecti(-45, -15, 45, 15);

	glColor3f(1, 1, 1);
	glRecti(-30, -15, 30, 15);

	//girofar
	glColor3f(0, 0, 1);
	glRecti(-5, -15, 5, 0);
	glColor3f(1, 0, 0);
	glRecti(-5, 0, 5, 15);

	// stopuri
	glColor3f(1, 0, 0);
	glRecti(-45, -15, -40, -5);
	glRecti(-45, 15, -40, 5);

	// faruri
	glColor3f(0.8, 0.5, 0);
	glRectf(45, 15, 40, 5);
	glRectf(45, -15, 40, -5);

	//a patra masina 

	glPushMatrix();
	glTranslated(550, 0, 0);
	//glRotated(90, 0, 0, 0);
	glPushMatrix();

	glColor3f(1, 1, 0);
	glRecti(-45, -15, 45, 15);

	// faruri
	glColor3f(0.8, 0.5, 0);
	glRecti(-45, -15, -40, -5);
	glRecti(-45, 15, -40, 5);
	// stopuri
	glColor3f(1, 0, 0);
	glRectf(45, 15, 40, 5);
	glRectf(45, -15, 40, -5);

	//parbrizul
	glColor3f(0.85, 0.85, 0.85);
	glRecti(-30, -12, -15, 12);

	//plafon
	glColor3f(0.75, 0.75, 0.75);
	glRecti(-10, -12, 20, 12);

	//luneta
	glColor3f(0.85, 0.85, 0.85);
	glRecti(25, -12, 35, 12);

	glutSwapBuffers();
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);


	glColor3f(0.5, 0.99, 0.5);

	// Iarba de jos
	glBegin(GL_POLYGON);
	glVertex2i(-100, -140);// Stanga jos
	glVertex2i(700, -140); // Dreapta jos
	glVertex2i(700, -80);  // Dreapta sus
	glVertex2i(-100, -80); // Stanga sus
	glEnd();

	// Iarba de sus
	glBegin(GL_POLYGON);
	glVertex2i(-100, 400);// Stanga jos
	glVertex2i(700, 400); // Dreapta jos
	glVertex2i(700, 460); // Dreapta sus
	glVertex2i(-100, 460);// Stanga sus
	glEnd();

	char* text = new char[200];
	text = (char*)"Depaseste masinile!";

	//char* scorText = new char[20];
	char scorText[10 + sizeof(char)];
	char highscoreText[10 + sizeof(char)];

	sprintf_s(scorText, "%d", score);
	sprintf_s(highscoreText, "%d", highscore);
	//cout << scorText;
	//strcat(text, scorText);

	RenderString(200.0f, 425.0f, GLUT_BITMAP_9_BY_15, (const unsigned char*)text);

	RenderString(140.0f, -115.0f, GLUT_BITMAP_9_BY_15, (const unsigned char*)"Scor: ");
	RenderString(200.0f, -115.0f, GLUT_BITMAP_9_BY_15, (const unsigned char*)scorText);

	RenderString(300.0f, -115.0f, GLUT_BITMAP_9_BY_15, (const unsigned char*)"Highscore: ");
	RenderString(420.0f, -115.0f, GLUT_BITMAP_9_BY_15, (const unsigned char*)highscoreText);
	// Delimitare sosea
	glLineWidth(5);
	glColor3f(1, 1, 0);

	// Delimitam soseaua de iarba partea de jos
	glBegin(GL_LINES);
	glVertex2i(-100, -80);
	glVertex2i(1500, -80);
	glEnd();

	// Delimitam soseaua de iarba partea de sus
	glBegin(GL_LINES);
	glVertex2i(-100, 400);
	glVertex2i(1500, 400);
	glEnd();

	// Liniile intrerupte
	glPushMatrix();
	glTranslated(i, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex2i(-100, 80);
	glVertex2i(1500, 80);
	glEnd();

	glBegin(GL_LINES);
	glVertex2i(-100, 240);
	glVertex2i(1500, 240);
	glEnd();
	glPopMatrix();



	//desenam masina

	glPushMatrix();
	glTranslated(0.0, j, 0.0);



	glColor3f(0, 0, 0);
	glRecti(-45, -15, 45, 15);

	glColor3f(1, 1, 1);
	glRecti(-30, -15, 30, 15);

	//girofar
	glColor3f(0, 0, 1);
	glRecti(-5, -15, 5, 0);
	glColor3f(1, 0, 0);
	glRecti(-5, 0, 5, 15);

	// stopuri
	glColor3f(1, 0, 0);
	glRecti(-45, -15, -40, -5);
	glRecti(-45, 15, -40, 5);

	// faruri
	glColor3f(0.8, 0.5, 0);
	glRectf(45, 15, 40, 5);
	glRectf(45, -15, 40, -5);

	//glPushMatrix();

	if (ok == 0)
	{
		rsj = 8;
		rss = -8;
		rdj = -8;
		rds = 8;
	}


	glPopMatrix();
	glPopMatrix();

	if (highscore < score) {
		highscore = score;
	}
	if (score == 500) {
		dificultate = 3;
	}
	if (score == 1000) {
		dificultate = 3.5;
	}


	if (ok == 0) {


		delay(3);

		inEndScreen = true;
		glutDisplayFunc(endScreen);
		if (gameover == false) {
			ofstream g("Highscore.txt");
			g << highscore;
			g.close();
			gameover = true;
		}
	}

	if (contor == 1 && (j != 160 && j != 320))
		j = j + 1;
	else if (contor == -1 && (j != 160 && j != 0))
		j = j - 1;
	else {
		contor = 0;

	}

	//desenam a doua masina (adversara)

	//culoare random



	switch (color) {
	case 0:
		rMasina1 = 0;
		gMasina1 = 0.4;
		bMasina1 = 0;

		rMasina2 = 0.4;
		gMasina2 = 0;
		bMasina2 = 0;
		break;
	case 1:
		rMasina1 = 0.4;
		gMasina1 = 0;
		bMasina1 = 0;

		rMasina2 = 0;
		gMasina2 = 0.4;
		bMasina2 = 0;
		break;
	case 2:
		rMasina1 = 0.39;
		gMasina1 = 0.79;
		bMasina1 = 0;

		rMasina2 = 0;
		gMasina2 = 0;
		bMasina2 = 0.39;
		break;
	case 3:
		rMasina1 = 0;
		gMasina1 = 0;
		bMasina1 = 0.39;

		rMasina2 = 0.39;
		gMasina2 = 0.79;
		bMasina2 = 0;
		break;
	case 4:
		rMasina1 = 0.79;
		gMasina1 = 1;
		bMasina1 = 0.49;

		rMasina2 = 0.99;
		gMasina2 = 1;
		bMasina2 = 0.5;
		break;

	}

	glPushMatrix();
	glTranslated(loc_vert, height, 0.0);


	glColor3f(rMasina1, gMasina1, bMasina1);
	glRecti(-45, -15, 45, 15);

	// faruri
	glColor3f(0.8, 0.5, 0);
	glRecti(-45, -15, -40, -5);
	glRecti(-45, 15, -40, 5);
	// stopuri
	glColor3f(1, 0, 0);
	glRectf(45, 15, 40, 5);
	glRectf(45, -15, 40, -5);

	//parbrizul
	glColor3f(0.85, 0.85, 0.85);
	glRecti(-30, -12, -15, 12);

	//plafon
	glColor3f(0.75, 0.75, 0.75);
	glRecti(-10, -12, 20, 12);

	//luneta
	glColor3f(0.85, 0.85, 0.85);
	glRecti(25, -12, 35, 12);


	glPopMatrix();

	glPushMatrix();
	glTranslated(loc_vert, height2, 0.0);

	glColor3f(rMasina2, gMasina2, bMasina2);
	glRecti(-45, -15, 45, 15);

	// faruri
	glColor3f(0.8, 0.5, 0);
	glRecti(-45, -15, -40, -5);
	glRecti(-45, 15, -40, 5);

	// stopuri
	glColor3f(1, 0, 0);
	glRectf(45, 15, 40, 5);
	glRectf(45, -15, 40, -5);

	//parbrizul
	glColor3f(0.85, 0.85, 0.85);
	glRecti(-30, -12, -15, 12);

	//plafon
	glColor3f(0.75, 0.75, 0.75);
	glRecti(-10, -12, 20, 12);

	//luneta
	glColor3f(0.85, 0.85, 0.85);
	glRecti(25, -12, 35, 12);

	glPopMatrix();

	startgame();
	glutPostRedisplay();
	glutSwapBuffers();
	glFlush();
}

void keys(unsigned char key, int x, int y) {
	switch (key) {
	case 'x':
		if (inMenu) {
			inMenu = false;
			glutDisplayFunc(drawScene);
		}
		break;
	case 'c':
		if (inEndScreen)
			exit(0);
		break;
	}
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0, 700.0, -140.0, 460.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void miscasus(void)
{
	if (ok != 0)
	{
		if (j < 320)
		{
			contor = 1;
			j += 1;
		}

		glutPostRedisplay();
	}
}

void miscajos(void)
{
	if (ok != 0)
	{
		if (j > 0)
		{
			contor = -1;
			j -= 1;

		}

		glutPostRedisplay();
	}
}

void keyboard(int key, int x, int y)
{


	switch (key) {
	case GLUT_KEY_UP:
		if (!inMenu)
			miscasus();
		break;
	case GLUT_KEY_DOWN:
		if (!inMenu)
			miscajos();
		break;

	}

}

int main(int argc, char** argv)
{
	ifstream f("Highscore.txt");
	f >> highscore;
	f.close();
	cout << highscore;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Crash Mission");
	init();


	glutDisplayFunc(startMenu);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);
	glutKeyboardFunc(keys);
	glutMainLoop();
}
