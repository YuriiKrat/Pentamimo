#include "Graphics.h"

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(350, 0); // ³������ �� ����
	glutInitWindowSize(700, 700); // ����� ����
	glutCreateWindow("Pentagon"); // ��������� ����

	glutDisplayFunc(drawGameField); // ��������� ���� ��� ���

	glutReshapeFunc(reshape); // �������� �������� ����� ����

	glutMouseFunc(mouseButton); // ������� ���� ����

	glutMainLoop(); // ����������� ����

	return 1;
}