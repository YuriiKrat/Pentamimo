#include <glut.h>
#include <iostream>

using namespace std;

void drawGameField(void); // ��������� ���� ��� ���

void mouseButton(int, int, int, int); // ������� ����� ����

void emptyCell(int, int, int, int, int[][12]); // ���������� ������ ������� �������� ��������

void enterNumber(unsigned char, int, int); // �������� ����� � ������

void nameKeys(); // ϳ�������� �����

void result(); // ��������� ����������

void reshape(int, int); // �������� �������� ����� ����

int** returnEmptyCells(); // �������� ������� � ������� ��� ����������

void returnOpenFile(); // ³������� �����

void AboutMe(); // ��������� ���� ��� ����������

void About(); // ���������� ��� ����������

void reshape_about(int, int); // �������� �������� ����� ����

void Rules(); //������� ������������

void resultWindow(); // ³��� ������ ����������

void reshape_result(int, int); // �������� �������� ����� ����