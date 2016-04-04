#include "Graphics.h"

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(350, 0); // Відстань від краю
	glutInitWindowSize(700, 700); // Розмір вікна
	glutCreateWindow("Pentagon"); // Створення вікна

	glutDisplayFunc(drawGameField); // Створення поля для гри

	glutReshapeFunc(reshape); // Заборона змінювати розмір вікна

	glutMouseFunc(mouseButton); // Обробка кліків миші

	glutMainLoop(); // Нескінченний цикл

	return 1;
}