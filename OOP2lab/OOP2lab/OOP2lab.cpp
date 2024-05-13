/*************************************************************************
*                                                                        *
*               ЛАБОРАТОРНАЯ РАБОТА №1 ПО ООП, 4 СЕМЕСТР                 *
*                                                                        *
**************************************************************************
*Project type : Visual Studio Solution                                   *
*Project name : OOP-1ыеДфи                                               *
*File name    : main.cpp	                                             *
*Language     : CPP, MSVS 2022                                           *
*Programmer   : Чиняков Игорь Павлович, М3О-210Б-22                      *
*Modified by  :                                                          *
*Created      : 20.04.2024                                               *
*Last revision: 23.04.2024                                               *
*Comment      : ПРОСТЕЙШАЯ ИЕРАРХИЯ КЛАССОВ. ИСПОЛЬЗОВАНИЕ КОНСОЛИ.      *
*				            ФИГУРА - Телевизор					         *
*************************************************************************/

#include <iostream>
#include <Windows.h>
#include "TV.h"
using namespace std;

//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define INTERACTING_SIZE 2
#define ARR_SIZE 5

HDC hdc;
HWND GetConsoleWindow(); //указатель на консольное окно

bool CheckCollision(TV& TV, Object& object);

//Основная программа
int main()
{
	setlocale(LC_ALL, "ru");
	system("color F0");

	HWND hwnd = GetConsoleWindow(); //получили дескриптор консольного окна

	int transitionMatrix[ARR_SIZE][INTERACTING_SIZE] =
	{
		{ 1, 3 },
		{ 1, 0 },
		{ 4, 3 },
		{ 4, 3 },
		{ 4, 2 }
	};
	int objectIndex = -1;

	if (hwnd != NULL)
	{
		hdc = GetWindowDC(hwnd);

		if (hdc != NULL)
		{
			TV* currentTV;

			TV* TVs[ARR_SIZE];
			TVs[0] = new TV(200, 200, 162, 288, 25, hdc);
			TVs[1] = new BrokenTV(200, 200, 162, 288, 25, hdc);
			TVs[2] = new EllipseTV(200, 200, 162, 288, 25, hdc);
			TVs[3] = new MagicTV(200, 200, 162, 288, 25, hdc);
			TVs[4] = new BrokenEllipseTV(200, 200, 162, 288, 25, hdc);
			currentTV = TVs[0];

			Object* objects[INTERACTING_SIZE];
			objects[0] = new Stone(700, 190, 50, hdc);
			objects[1] = new MagicSource(100, 50, 50, 50, hdc);

			currentTV->Show();
			for (int i = 0; i < INTERACTING_SIZE; i++)
				objects[i]->Show();

			while (!KEY_DOWN(VK_ESCAPE))
			{
				currentTV->Show();
				currentTV->Drag(100);
				for (int i = 0; i < INTERACTING_SIZE; i++)
					if (CheckCollision(*currentTV, *(objects[i])))
						objectIndex = i;

				//выход в результате столкновения
				if (objectIndex != -1)
				{
					currentTV->Hide();
					currentTV = TVs[transitionMatrix[currentTV->GetIndex()][objectIndex]]; //переход к новому объекту
					currentTV->MoveTo(200, 200); //переход машины на начальное место

					objects[objectIndex]->Show();
					objectIndex = -1;
				}
			}//while

			delete currentTV;
			delete[] TVs;
			delete[] objects;
		}
	}

	Sleep(3000);
	return 0;
}

HWND GetConsoleWindow()
{
	char str[128];
	//char title[128]="xxxxxxxxxxxxxxxxxx";
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";	//новая версия Windows
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str)); // получить заголовок окна
	SetConsoleTitle(title);						// установить новый заголовок окна
	Sleep(100);									// ждем смены заголовка окна (100 мс);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);// определяем дескриптор окна
	SetConsoleTitle((LPWSTR)str);				//возвращаем прежний заголовок

	return hwnd;//вернуть дескриптор окна
}

bool CheckCollision(TV& TV, Object& object)
{
	//определение столкновения слева
	bool left = object.GetXTopLeft() <= TV.GetXBottomRight() && object.GetXBottomRight() >= TV.GetXBottomRight()
		&& (object.GetYTopLeft() <= TV.GetYBottomRight() && object.GetYTopLeft() >= TV.GetYTopLeft()
			|| object.GetYBottomRight() >= TV.GetYTopLeft() && object.GetYBottomRight() <= TV.GetYBottomRight());

	//определение столкновений справа
	bool right = object.GetXBottomRight() >= TV.GetXTopLeft() && object.GetXTopLeft() <= TV.GetXTopLeft()
		&& (object.GetYTopLeft() <= TV.GetYBottomRight() && object.GetYTopLeft() >= TV.GetYTopLeft()
			|| object.GetYBottomRight() >= TV.GetYTopLeft() && object.GetYBottomRight() <= TV.GetYBottomRight());

	//определение столкновений сверху
	bool top = object.GetYTopLeft() <= TV.GetYTopLeft() && object.GetYBottomRight() >= TV.GetYTopLeft()
		&& (object.GetXTopLeft() <= TV.GetXBottomRight() && object.GetXTopLeft() >= TV.GetXTopLeft()
			|| object.GetXTopLeft() >= TV.GetXTopLeft() && object.GetXBottomRight() <= TV.GetXBottomRight());

	//определение столкновений снизу
	bool bottom = object.GetYBottomRight() >= TV.GetYBottomRight() && object.GetYTopLeft() <= TV.GetYBottomRight()
		&& (object.GetXTopLeft() <= TV.GetXBottomRight() && object.GetXTopLeft() >= TV.GetXTopLeft()
			|| object.GetXBottomRight() >= TV.GetXTopLeft() && object.GetXBottomRight() <= TV.GetXBottomRight());

	//определение того, находится ли препятствие "внутри" фигуры
	bool inside = object.GetXTopLeft() >= TV.GetXTopLeft() && object.GetYTopLeft() >= TV.GetYTopLeft() &&
		object.GetXBottomRight() <= TV.GetXBottomRight() && object.GetYBottomRight() <= TV.GetYBottomRight();

	return left || right || top || bottom || inside;
}
