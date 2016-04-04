#include <glut.h>
#include <iostream>

using namespace std;

void drawGameField(void); // Створення поля для гри

void mouseButton(int, int, int, int); // Обробка рухів миші

void emptyCell(int, int, int, int, int[][12]); // Позначення пустих клітинок червоним кольором

void enterNumber(unsigned char, int, int); // Введення чисел в комірки

void nameKeys(); // Підписання клавіш

void result(); // Виведення результату

void reshape(int, int); // Заборона змінювати розмір вікна

int** returnEmptyCells(); // Передача матриці у функцію для розрахунків

void returnOpenFile(); // Відкриття файлу

void AboutMe(); // Створення вікна про розробника

void About(); // Інформація про розробника

void reshape_about(int, int); // Заборона змінювати розмір вікна

void Rules(); //Правила користування

void resultWindow(); // Вікно ознаки результату

void reshape_result(int, int); // Заборона змінювати розмір вікна