#include "Graphics.h"
#include "Programme.h"
#include "OpenSave.h"

float const a = -0.95f;
float const b = -0.25f;

int matrix_empty[12][12]; // Матриця основного поля
int height_matr[12]; // Матриця для запису чисел
int width_matr[12]; // Матриця для запису чисел

void drawGameField() // Створення поля для гри
{
	float c = 0.85;
	float a1 = a, b1 = b;
	glClearColor(0.25, 0.25, 1.0, 1.0); // Колір фону
	glClear(GL_COLOR_BUFFER_BIT); // Очищення буфера кольору

	glBegin(GL_QUADS); // Створення поля
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(a, -a);
	glVertex2f(a, b);
	glVertex2f(-b, b);
	glVertex2f(-b, -a);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(a, b);
	glVertex2f(-b, b);
	glVertex2f(-b, b - 0.1f);
	glVertex2f(a, b - 0.1f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2f(-b + 0.1f, -a);
	glVertex2f(-b + 0.1f, b);
	glVertex2f(-b, b);
	glVertex2f(-b, -a);
	glEnd();

	for (int i = 0; i < 13; i++) { // Створення ліній
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(a1, -a);
		glVertex2f(a1, b - 0.1f);
		glEnd();
		a1 += 0.1;
	}

	for (int i = 0; i < 13; i++) { // Створення ліній
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(a, b1);
		glVertex2f(-b + 0.1f, b1);
		glEnd();
		b1 += 0.1;
	}

	for (int i = 0; i < 7; i++){
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(-a, c);
		glVertex2f(0.5f, c);
		glVertex2f(0.5f, c - 0.1f);
		glVertex2f(-a, c - 0.1f);
		glEnd();
		c -= 0.15;
	}

	nameKeys(); // Підписання клавіш

	Rules(); // Правила користування

	glutSwapBuffers(); // Обмін буферів

	glClear(GL_COLOR_BUFFER_BIT); // Очищення буфера кольору
}

void reshape(int height, int width) // Заборона змінювати розмір вікна
{
	glutReshapeWindow(700, 700);
}

void mouseButton(int button, int state, int x, int y) // Обробка рухів миші
{
	emptyCell(button, state, x, y, matrix_empty); // Позначення пустих клітинок червоним кольором

	int x_1 = 525;
	int y_1 = 52;
	int x_2 = 680;
	int y_2 = 86;
	int c_1 = 52;

	if ((x > 438 && x < 472 && y > 18 && y < 438) || (x > 18 && x < 438 && y > 438 && y < 472)) { // Введення чисел в комірки
		if (button == GLUT_LEFT_BUTTON) {
			glutKeyboardFunc(enterNumber);
		}
	}

	if (x > x_1 && x < x_2 && y > y_1 + c_1 * 6 && y < y_2 + c_1 * 6)  // Завершення програми
		exit(0);

	if (x > x_1 && x < x_2 && y > y_1 && y < y_2) { // Виведення результату
		if (state == GLUT_DOWN) {
			result();
		}
	}

	if (x > x_1 && x < x_2 && y > y_1 + c_1 && y < y_2 + c_1) { // Зчитування фігур з файлу
		if (state == GLUT_DOWN) {
			main_field(true);
		}
	}

	if (x > x_1 && x < x_2 && y > y_1 + c_1 * 2 && y < y_2 + c_1 * 2) {// Відкриття з файлу
		if (state == GLUT_DOWN) {
			returnOpenFile();
		}
	}

	if (x > x_1 && x < x_2 && y > y_1 + c_1 * 3 && y < y_2 + c_1 * 3) { // Збереження у файл
		if (state == GLUT_DOWN) {
			SaveFile(matrix_empty, height_matr, width_matr);
		}
	}

	if (x > x_1 && x < x_2 && y > y_1 + c_1 * 4 && y < y_2 + c_1 * 4) { // Очищення поля
		for (int i = 0; i < 12; i++) { // Очищення матриць
			for (int j = 0; j < 12; j++) {
				matrix_empty[i][j] = 0;
			}
			height_matr[i] = 0;
			width_matr[i] = 0;
		}
		drawGameField(); // Перемалювання основного поля
	}

	if (x > x_1 && x < x_2 && y > y_1 + c_1 * 5 && y < y_2 + c_1 * 5) { // Інформація про розробника
		if (state == GLUT_DOWN) {
			About();
		}
	}

}

void emptyCell(int button, int state, int x, int y, int matrix[][12]) // Позначення пустих клітинок червоним кольором
{
	int a1, b1, c1 = 34;
	float a_f, b_f, c_f = 0.1;

	if (x > 18 && x< 438 && y>18 && y < 438) { // Якщо курсор в області поля
		a1 = 18;
		b1 = 18;
		a_f = -0.95;
		b_f = 0.95;
		glutSwapBuffers();
		if (button == GLUT_LEFT_BUTTON) { // Позначення пустих клітинок червоним кольором
			for (int i = 0; i < 12; i++) {
				if (x > a1) {
					a1 += c1;
					a_f += c_f;
				}
				if (y > b1) {
					b1 += c1;
					b_f -= c_f;
				}
			}
			matrix[(int)(b1 / c1) - 1][(int)(a1 / c1) - 1] = -1;
			glBegin(GL_QUADS); // Замалювання клітинки червоним кольором
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(a_f, b_f);
			glVertex2f(a_f, b_f + 0.1f);
			glVertex2f(a_f - 0.1f, b_f + 0.1f);
			glVertex2f(a_f - 0.1f, b_f);
			glEnd();
		}
		glutSwapBuffers(); // Обмін буферів
	}
}

void enterNumber(unsigned char key, int x, int y) // Введення чисел в комірки
{
	if (key > 47 && key < 58) {
		int a, b, c = 34;
		float a_f, b_f, c_f = 0.1, d_f = 0.01f;

		if (x > 438) {
			b = 18;
			b_f = 0.95;
			a_f = 0.25;
			for (int i = 0; i < 12; i++) {
				if (y > b) {
					b += c;
					b_f -= c_f;
				}
			}
			height_matr[(int)(b / c) - 1] = key - '0'; // Запис до матриці введеного числа
		}
		else {
			a = 18;
			a_f = -0.95f;
			b_f = -0.35f;
			for (int i = 0; i < 12; i++) {
				if (x > a) {
					a += c;
					a_f += c_f;
				}
			}
			width_matr[(int)(a / c) - 1] = key - '0'; // Запис до матриці введеного числа
			a_f -= c_f;
		}
		glutSwapBuffers();
		glBegin(GL_QUADS); // Створення поля
		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex2f(a_f + d_f, b_f + d_f);
		glVertex2f(a_f + c_f - d_f, b_f + d_f);
		glVertex2f(a_f + c_f - d_f, b_f + c_f - d_f);
		glVertex2f(a_f + d_f, b_f + c_f - d_f);
		glEnd();
		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2f(a_f + 0.05f, b_f + 0.05f);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, key);
		glutSwapBuffers();
	}
}

void nameKeys() // Підписання клавіш
{
	char text_1[] = "EXIT";
	char text_2[] = "SHOW RESULT";
	char text_3[] = "CLEAR";
	char text_4[] = "OPEN";
	char text_5[] = "SAVE";
	char text_6[] = "FIGURES";
	char text_7[] = "ABOUT";

	glColor3f(0.0f, 0.0f, 0.0f);

	glRasterPos2f(0.64f, 0.18f); // CLEAR
	for (int i = 0; i < strlen(text_3); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_3[i]);

	glRasterPos2f(0.66f, 0.33f); // SAVE
	for (int i = 0; i < strlen(text_5); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_5[i]);

	glRasterPos2f(0.66f, 0.48f); // OPEN
	for (int i = 0; i < strlen(text_4); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_4[i]);

	glRasterPos2f(0.62f, 0.63f); // FIGURES
	for (int i = 0; i < strlen(text_6); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_6[i]);

	glRasterPos2f(0.53f, 0.78f); // SHOW RESULT
	for (int i = 0; i < strlen(text_2); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_2[i]);

	glRasterPos2f(0.63f, 0.03f); // ABOUT
	for (int i = 0; i < strlen(text_7); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_7[i]);

	glRasterPos2f(0.66f, -0.12f); // EXIT
	for (int i = 0; i < strlen(text_1); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_1[i]);

}

void result() // Виведення результату
{
	int** matrix = new int*[12]; // Матриця основного поля
	for (int i = 0; i < 12; i++)
		matrix[i] = new int[12];

	matrix = main_field(false); // Заповнення матриці основного поля


	float x = 0.1f;
	glutSwapBuffers();
	for (int i = 0; i < 12; i++) { // Замальовка основного поля
		for (int j = 0; j < 12; j++) {
			if (matrix[i][j] == 1) {
				glBegin(GL_QUADS);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex2f(a + (float)(j*x), -a - (float)(i*x));
				glVertex2f(a + (float)(j*x), -a - (float)((i + 1)*x));
				glVertex2f(a + (float)((j + 1)*x), -a - (float)((i + 1)*x));
				glVertex2f(a + (float)((j + 1)*x), -a - (float)(i*x));
				glEnd();
			}
		}
	}
	glutSwapBuffers();

	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(450, 300); // Відстань від краю
	glutInitWindowSize(250, 100); // Розмір вікна
	glutCreateWindow("Result window"); // Створення вікна

	glutDisplayFunc(resultWindow); // Вікно ознаки результату
	glutReshapeFunc(reshape_result); // Заборона змінювати розмір вікна
}

int** returnEmptyCells() // Передача матриці у функцію для розрахунків
{
	int** matr = new int*[14];
	for (int i = 0; i < 14; i++)
		matr[i] = new int[12];

	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 12; j++)
			matr[i][j] = 0;
	}

	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 12; j++) {
			if (i < 12)
				matr[i][j] = matrix_empty[i][j];
			else if (i == 12)
				matr[i][j] = height_matr[j];
			else
				matr[i][j] = width_matr[j];
		}
	}

	return matr;
}

void returnOpenFile() // Перемалювання основного поля після відкриття файлу
{
	int** matr = new int*[14];
	for (int i = 0; i < 14; i++)
		matr[i] = new int[12];

	OpenFile(matr);

	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 12; j++) {
			if (i < 12)
				matrix_empty[i][j] = matr[i][j];
			else if (i == 12)
				height_matr[j] = matr[i][j];
			else
				width_matr[j] = matr[i][j];
		}
	}

	float x = 0.1f;
	glutSwapBuffers(); // Обмін буферів
	for (int i = 0; i < 12; i++) { // Позначення порожніх клітинок
		for (int j = 0; j < 12; j++) {
			if (matr[i][j] == -1) {
				glBegin(GL_QUADS);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex2f(a + (float)(j*x), -a - (float)(i*x));
				glVertex2f(a + (float)(j*x), -a - (float)((i + 1)*x));
				glVertex2f(a + (float)((j + 1)*x), -a - (float)((i + 1)*x));
				glVertex2f(a + (float)((j + 1)*x), -a - (float)(i*x));
				glEnd();
			}
		}
	}
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(a + 0.05f, b + 0.05f);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 1);
	float a_f = a, b_f = b - 0.05f;
	for (int i = 0; i < 12; i++) { // Запис цифр по горизонталі
		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2f(a_f + 0.05f, b_f);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 48 + matr[13][i]);
		a_f += 0.1;
	}
	a_f = -b;
	b_f = -a - 0.05f;
	for (int i = 0; i < 12; i++) { // Запис цифр по вертикалі
		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2f(a_f + 0.05f, b_f);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 48 + matr[12][i]);
		b_f -= 0.1;
	}
	glutSwapBuffers(); // Обмін буферів
}

void About() // Створення вікна про розробника
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(450, 300); // Відстань від краю
	glutInitWindowSize(400, 300); // Розмір вікна
	glutCreateWindow("About author"); // Створення вікна

	glutDisplayFunc(AboutMe); // Створення поля для гри
	glutReshapeFunc(reshape_about); // Заборона змінювати розмір вікна
}

void AboutMe() // Інформація про розробника
{
	float c = 0.85;
	float a1 = a, b1 = b;
	glClearColor(0.0, 0.5, 0.0, 1.0); // Колір фону
	glClear(GL_COLOR_BUFFER_BIT); // Очищення буфера кольору

	char text_1[] = "YURII KRAT";
	char text_2[] = "Kyiv Politechnic Institute";
	char text_3[] = "FICT, group IP-42";
	char text_4[] = "Email: yuriikrat97@gmail.com";
	char text_5[] = "Tel. (096)07-377-50";

	glColor3f(1.0f, 1.0f, 1.0f);

	glRasterPos2f(-0.6f, 0.4f);
	for (int i = 0; i < strlen(text_1); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_1[i]);

	glRasterPos2f(-0.6f, 0.2f);
	for (int i = 0; i < strlen(text_2); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_2[i]);

	glRasterPos2f(-0.6f, 0.0f);
	for (int i = 0; i < strlen(text_3); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_3[i]);

	glRasterPos2f(-0.6f, -0.2f);
	for (int i = 0; i < strlen(text_4); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_4[i]);

	glRasterPos2f(-0.6f, -0.4f);
	for (int i = 0; i < strlen(text_5); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_5[i]);
	glutSwapBuffers();

	glClear(GL_COLOR_BUFFER_BIT); // Очищення буфера кольору
}

void reshape_about(int height, int width) // Заборона змінювати розмір вікна
{
	glutReshapeWindow(400, 300);
}

void Rules() // Правила користування
{
	float interval = 0.08f;
	char text_1[] = "How to use?";
	char text_2[] = "You must download figures in the program. For this click on \"FIGURES\" and select text";
	char text_3[] = "file with figures. If you want to mark empty cells, click on needed cell. Then click";
	char text_4[] = "on orange cells and enter numbers. You can also save and open file with conditions.";
	char text_5[] = "Click on \"SAVE\" or \"OPEN\" respectively. If you have choosen figures and conditions,";
	char text_6[] = "click on \"SHOW RESULT\" for result. For cleaning field click on \"CLEAR\". Click on";
	char text_7[] = "\"ABOUT\" if you want see information about author. Click on \"EXIT\" for exit. ";

	glColor3f(1.0f, 1.0f, 1.0f);

	glRasterPos2f(b, b - 2 * interval);
	for (int i = 0; i < strlen(text_1); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text_1[i]);

	glRasterPos2f(a, b - 3 * interval);
	for (int i = 0; i < strlen(text_2); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text_2[i]);

	glRasterPos2f(a, b - 4 * interval);
	for (int i = 0; i < strlen(text_3); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text_3[i]);

	glRasterPos2f(a, b - 5 * interval);
	for (int i = 0; i < strlen(text_4); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text_4[i]);

	glRasterPos2f(a, b - 6 * interval);
	for (int i = 0; i < strlen(text_5); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text_5[i]);

	glRasterPos2f(a, b - 7 * interval);
	for (int i = 0; i < strlen(text_6); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text_6[i]);

	glRasterPos2f(a, b - 8 * interval);
	for (int i = 0; i < strlen(text_7); i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text_7[i]);

}

void resultWindow() // Вікно ознаки результату
{
	glClearColor(0.0, 0.5, 0.0, 1.0); // Колір фону
	glClear(GL_COLOR_BUFFER_BIT); // Очищення буфера кольору

	char text_1[] = "Done!!! It's a result!!!";

	glColor3f(1.0f, 1.0f, 1.0f);

	glRasterPos2f(-0.6f, 0.0f);
	for (int i = 0; i < strlen(text_1); i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text_1[i]);

	glutSwapBuffers(); // Обмін буферів

	glClear(GL_COLOR_BUFFER_BIT); // Очищення буфера кольору
}

void reshape_result(int height, int width) // Заборона змінювати розмір вікна
{
	glutReshapeWindow(250, 100);
}