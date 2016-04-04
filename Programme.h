#include<vector>
#include <windows.h>

using namespace std;

void replaceQuads(int[][5][5], int[][12], bool&, vector<int>&, int&, int[], int[], int&); // Розміщення фігур

void selectFigures(int [][5][5]); // Зчитування фігур з файлу

int** main_field(bool); // Функція для обробки матриці осеовного поля

void replacing(int [][5][5], int[][12], int[], int[]); // Розстановка фігур у полі

void savingMatrix(int[][12], int[][12]); // Збереження проміжних результатів