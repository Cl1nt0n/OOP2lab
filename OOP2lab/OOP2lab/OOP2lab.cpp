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
#include <windows.h>
#include "TV.h"
using namespace std;

//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

HDC hdc;
HWND GetConsoleWindow(); //указатель на консольное окно

//Основная программа
int main()
{
	system("color F0");
	HWND hwnd = GetConsoleWindow(); //получили дескриптор консольного окна

	if (hwnd != NULL)
	{
		hdc = GetWindowDC(hwnd);

		if (hdc != NULL)
		{
			/*Point point = Point(300, 300);
			TV tv = TV(200, 200, 162, 288, 25);
			tv.Show();
			tv.Drag(300);*/

			Point point = Point(300, 300);
			TV tv = TV(200, 200, 162, 288, 25);
			BrokenTV brokenTV = BrokenTV(200, 200, 162, 288, 25);
			EllipseTV ellipseTV = EllipseTV(200, 200, 162, 288, 25);
			MagicTV magicTV = MagicTV(200, 200, 162, 288, 25);
			tv.Show();
			tv.Drag(300);

			while (1)
			{
				if (KEY_DOWN(49)) //цифра 1
				{
					break;
				}
			}

			tv.Hide();
			brokenTV.Show();
			brokenTV.Drag(300); //перемещение фигуры, выход по esc
			while (1)
			{
				if (KEY_DOWN(50)) //цифра 2
				{
					break;
				}
			}

			brokenTV.Hide();
			ellipseTV.Show();
			ellipseTV.Drag(300);
			while (1)
			{
				if (KEY_DOWN(51)) //цифра 3
				{
					break;
				}
			}

			ellipseTV.Hide();
			magicTV.Show();
			magicTV.Drag(300);
			while (1)
			{
				if (KEY_DOWN(52)) //цифра 4
				{
					break;
				}
			}
		}
	}
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
}//end GetConcolWindow()
