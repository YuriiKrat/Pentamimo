#include "Programme.h"
#include "Graphics.h"
#include <fstream>

int pentamimo[12][5][5]; // �������, �� ���������� ������

int** main_field(bool select)
{
	int matrix[12][12]; // ������� ��������� ����
	
	int height_matr[12]; // �������, �� ���������� ������� �������� �������
	int width_matr[12]; // �������, �� ���������� ������� �������� �������

	int** matr = new int*[14]; // ������� ��� ��������� ������� �������
	for (int i = 0; i < 12; i++)
		matr[i] = new int[12];
	
	if (select) {
		selectFigures(pentamimo); // ���������� �����
	}
	else {
		matr = returnEmptyCells();

		for (int i = 0; i < 14; i++) { // ����� �� ������� ������� ������� �� �����
			for (int j = 0; j < 12; j++) {
				if (i < 12)
					matrix[i][j] = matr[i][j];
				else if (i == 12)
					height_matr[j] = matr[i][j];
				else
					width_matr[j] = matr[i][j];
			}
		}

		replacing(pentamimo, matrix, height_matr, width_matr);

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++) {
				matr[i][j] = matrix[i][j];
			}
		}
	}
	
	return matr;
}

void replacing(int pentamimo[][5][5], int matrix[][12], int height_number[], int weight_number[])
{
	int cou = 0;
	bool special_flag = true;
	vector<int> figure; // ������ ��� ��������� ������������ �����
	int amount = 0; // ʳ������ ������������ �����

	replaceQuads(pentamimo, matrix, special_flag, figure, amount, height_number, weight_number, cou);
	cout << "Amount of recursions: " << cou << endl;
}

void replaceQuads(int pentamimo[][5][5], int matrix[][12], bool &special_flag, vector<int>&figure, int &amount, int height_number[], int weight_number[], int& amount_recurs)
{
	int width_end = 0, width_start = 4; // ���������� ��� ������ ������
	int height_end = 0, height_start = 4; // ���������� ��� ������ ������
	bool flag = true; // ������ �������� ������� �������� ��� ������������
	bool pentam; // ������ ������������ ������
	bool replay = true; // ������ ������� ����� ������
	int dopMatrix[12][12]; // ������� ��� ���������� �����
	int m1, n1;
	int k; // Գ����
	int count, cou = 0;
	int figure_arr[5][5]; // ������� ��� �������� ������

	savingMatrix(matrix, dopMatrix); // ���������� ������� �������

	for (k = 0; k < 12; k++) {
		pentam = true;
		for (int y = 0; y < figure.size(); y++) { // �������� ����� �� ����������
			if (k == figure[y]) {
				pentam = false;
				break;
			}
		}
		if (pentam) { // ���� ������ �� �� �����������
			for (int i = 0; i < 5; i++) { // ���������� ������ ������
				for (int j = 0; j < 5; j++) {
					if (pentamimo[k][i][j] == 1) {
						if (j > width_end) width_end = j;
						if (j < width_start) width_start = j;
					}

				}
			}

			for (int j = 0; j < 5; j++) { // ���������� ������ ������
				for (int i = 0; i < 5; i++) {
					if (pentamimo[k][i][j] == 1) {
						if (i > height_end) height_end = i;
						if (i < height_start) height_start = i;
					}

				}
			}

			for (int m = 0; m < 12; m++) { // ����� ��������� ������� �� ������
				m1 = m;
				for (int n = 0; n < 12; n++) { // ����� ������� � �����
					if (replay) { // ���� ������ �� �� �����������
						flag = true;
						for (int i = height_start; i < height_end + 1; i++) { // �������� ��������� ������������ ������� 
							if (m1 > 11) { // ����� �� ���
								flag = false;
								break;
							}
							n1 = n;
							for (int j = width_start; j < width_end + 1; j++) {
								if (n1 > 11) { // ����� �� ���
									flag = false;
									break;
								}
								if (matrix[m1][n1] == 0 || (matrix[i][j] != 0 && pentamimo[k][i][j] == 0));// �������� ���������� �������
								else {
									flag = false;
									break;
								}
								n1++;
							}
							m1++;
						}
						m1 = m;
						n1 = n;

						if (flag) { // ���� �������� ���� ��� ������ ��������
							for (int a = height_start; a < height_end + 1; a++) {
								n1 = n;
								for (int b = width_start; b < width_end + 1; b++) { // ����� �� ������� 1 �� -1
									if (pentamimo[k][a][b] == 1) {
										matrix[m1][n1] = pentamimo[k][a][b];
										if (m1 - 1 >= 0 && n1 - 1 >= 0 && matrix[m1 - 1][n1 - 1] == 0)
											matrix[m1 - 1][n1 - 1] = -1;
										if (m1 - 1 >= 0 && n1 + 1 < 12 && matrix[m1 - 1][n1 + 1] == 0)
											matrix[m1 - 1][n1 + 1] = -1;
										if (n1 - 1 >= 0 && matrix[m1][n1 - 1] == 0)
											matrix[m1][n1 - 1] = -1;
										if (n1 + 1 < 12 && matrix[m1][n1 + 1] == 0)
											matrix[m1][n1 + 1] = -1;
										if (m1 + 1 < 12 && n1 - 1 >= 0 && matrix[m1 + 1][n1 - 1] == 0)
											matrix[m1 + 1][n1 - 1] = -1;
										if (m1 + 1 < 12 && n1 + 1 < 12 && matrix[m1 + 1][n1 + 1] == 0)
											matrix[m1 + 1][n1 + 1] = -1;
										if (m1 + 1 >= 0 && matrix[m1 + 1][n1] == 0)
											matrix[m1 + 1][n1] = -1;
										if (m1 - 1 >= 0 && matrix[m1 - 1][n1] == 0)
											matrix[m1 - 1][n1] = -1;
									}
									n1++;
								}
								m1++;
							}
							figure.push_back(k); // Գ���� ��� ������������
							amount++; // ��������� ������������ �����

							for (int s = 0; s < 12; s++) { // �������� ������� �������� �������
								count = 0;
								for (int w = 0; w < 12; w++) {
									if (matrix[w][s] == 1)
										count++;
								}
								if (count>weight_number[s]) { // ������������ �����
									special_flag = false;
									break;
								}
							}

							for (int s = 0; s < 12; s++) { // �������� ������� �������� �������
								count = 0;
								for (int w = 0; w < 12; w++) {
									if (matrix[s][w] == 1)
										count++;
								}
								if (count>height_number[s]) { // ������������ �����
									special_flag = false;
									break;
								}
							}

							if (special_flag) { // �������
								amount_recurs++;
								replaceQuads(pentamimo, matrix, special_flag, figure, amount, height_number, weight_number, amount_recurs);
								replay = false;
							}
							if (!special_flag) { // ��������� ������ � ����
								replay = true;
								figure.pop_back();
								amount--;
								special_flag = true;
								savingMatrix(dopMatrix, matrix);
							}
							m1 = m;
						}
					}
				}
				if (m == 11 && !flag) { // ������� ������
					cou++;
					if (cou < 4) {
						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								figure_arr[j][4 - i] = pentamimo[k][i][j];
							}
						}

						for (int i = 0; i < 5; i++) {
							for (int j = 0; j < 5; j++) {
								pentamimo[k][i][j] = figure_arr[i][j];
							}
						}
						k--;
					}
				}
			}
		}
		if (k == 11 && !flag && amount < 12) { // ���� �������� �� ������
			special_flag = false;
		}
	}

}

void savingMatrix(int matrix[][12], int dopMatrix[][12]) // ������� ��� ���������� �������� ����������
{
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			dopMatrix[i][j] = matrix[i][j];
		}
	}
}

void selectFigures(int pentamimo[][5][5]) // ���������� ����� � �����
{
	OPENFILENAME ofn;

	char szFileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = (LPCWSTR)L"Text Files (*.txt)\0*.txt\0";
	ofn.lpstrFile = (LPWSTR)szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = (LPCWSTR)L"txt";

	if (GetOpenFileName(&ofn)) // ���������� ������
	{
		int n;
		ifstream figure(ofn.lpstrFile);
		for (int k = 0; k < 12; k++) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					figure >> n;
					pentamimo[k][i][j] = n;
				}
			}
		}
		figure.close();
	}
}