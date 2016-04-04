#include "OpenSave.h"
#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

void OpenFile(int **matrix) // Відкриття файлу
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
	
	if (GetOpenFileName(&ofn)) // Зчитування фігури
	{
		int n;
		ifstream figure(ofn.lpstrFile);
		for (int i = 0; i < 14; i++) {
			for (int j = 0; j < 12; j++) {
				figure >> n;
				matrix[i][j] = n;
			}
		}
		figure.close();
	}
}

void SaveFile(int matrix_empty[][12], int height_matr[], int width_matr[]) // Збереження файлу
{
	OPENFILENAME ofn;

	char szFileName[MAX_PATH] = "";

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = (LPCWSTR)L"Text Files (*.txt)\0*.txt\0";
	ofn.lpstrFile = (LPWSTR)szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = (LPCWSTR)L"txt";

	if (GetSaveFileName(&ofn)) // Запис у файл
	{
		int n;
		ofstream figure(ofn.lpstrFile);
		for (int i = 0; i < 14; i++) {
			for (int j = 0; j < 12; j++) {
				if (i < 12) {
					n = matrix_empty[i][j];
					figure << n << " ";
				}
				else if (i == 12) {
					n = height_matr[j];
					figure << n << " ";
				}
				else {
					n = width_matr[j];
					figure << n << " ";
				}
			}
			figure << endl;
		}
		figure.close();
	}
}