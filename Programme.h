#include<vector>
#include <windows.h>

using namespace std;

void replaceQuads(int[][5][5], int[][12], bool&, vector<int>&, int&, int[], int[], int&); // ��������� �����

void selectFigures(int [][5][5]); // ���������� ����� � �����

int** main_field(bool); // ������� ��� ������� ������� ��������� ����

void replacing(int [][5][5], int[][12], int[], int[]); // ����������� ����� � ���

void savingMatrix(int[][12], int[][12]); // ���������� �������� ����������