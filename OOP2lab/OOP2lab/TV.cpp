#include <Windows.h>
#include "TV.h"
extern HDC hdc;			// объявление контекста устройства
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//конструктор Location
Location::Location(int x, int y)
{
	//инициализация закрытых переменных своего класса
	X = x;
	Y = y;
}//Location::Location()

//деструктор Location
Location::~Location()
{
}

//получение координаты X
int Location::GetX()
{
	return X;
}//Location::GetX()	

//получение координаты Y
int Location::GetY()
{
	return Y;
}//Location::GetY()	

//конструктор Point
Point::Point(int x, int y) : Location(x, y)
{
	IsVisible = false;
}

//деструктор Point
Point::~Point()
{
}

//показать точку
void Point::Show(void)
{
	IsVisible = true;
	SetPixel(hdc, X, Y, RGB(255, 0, 0));//рисуем красным цветом
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 2, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 3, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 2, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 3, RGB(255, 0, 0));
	SetPixel(hdc, X + 2, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 2, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 2, Y + 2, RGB(255, 0, 0));
	SetPixel(hdc, X + 2, Y + 3, RGB(255, 0, 0));
}//end Point::Show()

//скрыть точку
void Point::Hide(void)
{
	IsVisible = false;

	SetPixel(hdc, X, Y, RGB(242, 242, 242));//рисуем синим цветом или фона
	SetPixel(hdc, X + 1, Y, RGB(242, 242, 242));
	SetPixel(hdc, X + 2, Y, RGB(242, 242, 242));
	SetPixel(hdc, X + 3, Y, RGB(242, 242, 242));
	SetPixel(hdc, X + 1, Y, RGB(242, 242, 242));
	SetPixel(hdc, X + 1, Y + 1, RGB(242, 242, 242));
	SetPixel(hdc, X + 1, Y + 2, RGB(242, 242, 242));
	SetPixel(hdc, X + 1, Y + 3, RGB(242, 242, 242));
	SetPixel(hdc, X + 2, Y, RGB(242, 242, 242));
	SetPixel(hdc, X + 2, Y + 1, RGB(242, 242, 242));
	SetPixel(hdc, X + 2, Y + 2, RGB(242, 242, 242));
	SetPixel(hdc, X + 2, Y + 3, RGB(242, 242, 242));
}//Point::Hide()

//проверка, видна ли точка
bool Point::CheckIsVisible()
{
	return false;
}//Point::CheckIsVisible()

//перемещение
void Point::MoveTo(int newX, int newY)
{
	Hide();		//сделать точку невидимой
	X = newX;	//поменять координаты ТОЧКИ
	Y = newY;
	Show();		//показать точку на новом месте
}//Point::MoveTo(int newX, int newY)

//сдвиг по нажатию
void Point::Drag(int Step)
{
	int figX, figY; //новые координаты фигуры

	figX = GetX(); //получаем начальные координаты фигуры
	figY = GetY();

	//бесконечный цикл буксировки фигуры
	while (1)
	{
		if (KEY_DOWN(VK_ESCAPE)) //27 esc - конец работы
			break;

		//выбор направления движения фигуры
		if (KEY_DOWN(VK_LEFT)) //37 стрелка влево
		{
			figX -= Step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_RIGHT)) //39 стрелка вправо
		{
			figX += Step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_DOWN)) //40 стрелка вниз
		{
			figY += Step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_UP)) //38 стрелка вверх
		{
			figY -= Step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if
	}//while
}//Point::Drag(int Step)

//конструктор телевизора
TV::TV(int x, int y, int scrHeight, int scrWidth, int stHeight) : Point(x, y)
{
	_screenHeight = scrHeight;
	_screenWidth = scrWidth;
	_standHeight = stHeight;
}

//деструктор телевизора
TV::~TV()
{
}

//показать телевизор
void TV::Show()
{
	if (IsVisible == true)
		return;
	IsVisible = true;

	// Зададим перо и цвет пера - чёрный
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, pen); //сделали перо активным

	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, brush); //сделали перо активным

	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
}

//скрыть телевизор
void TV::Hide()
{
	if (IsVisible == false) 
		return;

	IsVisible = false;

	// Зададим перо и цвет пера - чёрный
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));

	SelectObject(hdc, pen); //сделали перо активным

	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(hdc, brush); //сделали перо активным

	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
}

////переместить телевизор
//void TV::MoveTo(int newX, int newY)
//{
//	Hide();		//сделать точку невидимой
//	X = newX;	//поменять координаты ТОЧКИ
//	Y = newY;
//	Show();		//показать точку на новом месте
//}
//
////сдвинуть телевизор по нажатию клавишу
//void TV::Drag(int step)
//{
//	int figX, figY; //новые координаты фигуры
//
//	figX = GetX(); //получаем начальные координаты фигуры
//	figY = GetY();
//
//	//бесконечный цикл буксировки фигуры
//	while (1)
//	{
//		if (KEY_DOWN(VK_ESCAPE)) //27 esc - конец работы
//			break;
//
//		//выбор направления движения фигуры
//		if (KEY_DOWN(VK_LEFT)) //37 стрелка влево
//		{
//			figX -= step;
//			MoveTo(figX, figY);
//			Sleep(500); //задержка экрана на 500 милисекунд
//		}//if
//
//		if (KEY_DOWN(VK_RIGHT)) //39 стрелка вправо
//		{
//			figX += step;
//			MoveTo(figX, figY);
//			Sleep(500); //задержка экрана на 500 милисекунд
//		}//if
//
//		if (KEY_DOWN(VK_DOWN)) //40 стрелка вниз
//		{
//			figY += step;
//			MoveTo(figX, figY);
//			Sleep(500); //задержка экрана на 500 милисекунд
//		}//if
//
//		if (KEY_DOWN(VK_UP)) //38 стрелка вверх
//		{
//			figY -= step;
//			MoveTo(figX, figY);
//			Sleep(500); //задержка экрана на 500 милисекунд
//		}//if
//	}//while
//}

BrokenTV::BrokenTV(int x, int y, int scrHeight, int scrWidth, int stHeight) : TV(x, y, scrHeight, scrWidth, stHeight)
{

}

void BrokenTV::Show()
{
	if (IsVisible == true)
		return;
	IsVisible = true;

	// Зададим перо и цвет пера - чёрный
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, pen); //сделали перо активным

	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);


	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, brush); //сделали перо активным
	
	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush2 = CreateSolidBrush(RGB(0, 0, 255));

	SelectObject(hdc, brush2); //сделали перо активным
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);

	HBRUSH brush3 = CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(hdc, brush3);
	Rectangle(hdc, X + 5 + _screenWidth / 10, Y + 5, X + _screenWidth - 5 - _screenWidth / 10, Y + _screenHeight - 5);

	HBRUSH brush4 = CreateSolidBrush(RGB(0, 255, 0));

	SelectObject(hdc, brush4);
	Rectangle(hdc, X + 5 + _screenWidth / 5, Y + 5, X + _screenWidth - 5 - _screenWidth / 5, Y + _screenHeight - 5);

	HBRUSH brush5 = CreateSolidBrush(RGB(255, 0, 0));

	SelectObject(hdc, brush5);
	Rectangle(hdc, X + 5 + _screenWidth / 10 * 3, Y + 5, X + _screenWidth - 5 - _screenWidth / 10 * 3, Y + _screenHeight - 5);

	HBRUSH brush6 = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, brush6);
	Rectangle(hdc, X + _screenWidth / 2.5, Y + 5, X + _screenWidth - _screenWidth / 2, Y + _screenHeight - 5);

	HBRUSH brush7 = CreateSolidBrush(RGB(255, 255, 0));

	SelectObject(hdc, brush7);
	Rectangle(hdc, X + _screenWidth / 2, Y + 5, X + _screenWidth - _screenWidth / 2.5, Y + _screenHeight - 5);

	DeleteObject(pen);
	DeleteObject(brush);
	DeleteObject(brush2);
	DeleteObject(brush3);
	DeleteObject(brush4);
	DeleteObject(brush5);
	DeleteObject(brush6);
}

void BrokenTV::Hide()
{
	if (IsVisible == false) return;

	IsVisible = false;

	// Зададим перо и цвет пера - чёрный
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));

	SelectObject(hdc, pen); //сделали перо активным

	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(hdc, brush); //сделали перо активным

	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
};

EllipseTV::EllipseTV(int x, int y, int scrHeight, int scrWidth, int stHeight) : TV(x, y, scrHeight, scrWidth, stHeight)
{
}

void EllipseTV::Show()
{
	if (IsVisible == true)
		return;
	IsVisible = true;

	// Зададим перо и цвет пера - чёрный
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, pen); //сделали перо активным

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, brush); //сделали перо активным

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
}

void EllipseTV::Hide()
{
	if (IsVisible == false)
		return;

	IsVisible = false;

	// Зададим перо и цвет пера - чёрный
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));

	SelectObject(hdc, pen); //сделали перо активным

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(hdc, brush); //сделали перо активным

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
};

MagicTV::MagicTV(int x, int y, int scrHeight, int scrWidth, int stHeight) : TV(x, y, scrHeight, scrWidth, stHeight)
{

}

void MagicTV::Show()
{
	if (IsVisible == true)
		return;
	IsVisible = true;

	// Зададим перо и цвет пера - чёрный
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	SelectObject(hdc, pen); //сделали перо активным

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);


	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));

	SelectObject(hdc, brush);

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush2 = CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(hdc, brush2); //сделали перо активным

	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);

	// Зададим перо и цвет пера - чёрный
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, pen); //сделали перо активным

	//Рисуем овал лица
	Ellipse(hdc, X + _screenWidth / 2 - _faceWidth / 2, Y - _faceHeight / 2, X + _faceWidth / 2, Y + _faceHeight / 2);
	//Рисуем левый глаз
	Ellipse(hdc, X - 3 * _faceWidth / 8, Y - _eyesWidth, X - _faceWidth / 8, Y);
	//Рисуем правый глаз
	Ellipse(hdc, X + _faceWidth / 8, Y - _eyesWidth, X + 3 * _faceWidth / 8, Y);
	//Рисуем брови
	MoveToEx(hdc, X - 3 * _faceWidth / 8, Y - 3 * _eyesWidth / 2, NULL);
	LineTo(hdc, X - _faceWidth / 8, Y - 3 * _eyesWidth / 2);
	MoveToEx(hdc, X + 3 * _faceWidth / 8, Y - 3 * _eyesWidth / 2, NULL);
	LineTo(hdc, X + _faceWidth / 8, Y - 3 * _eyesWidth / 2);
	//Рисуем нос
	MoveToEx(hdc, X, Y - _eyesWidth, NULL);
	LineTo(hdc, X - _noseWidth / 2, Y + _faceHeight / 7);
	MoveToEx(hdc, X - _noseWidth / 2, Y + faceHeight / 7, NULL);
	LineTo(hdc, X + noseWidth / 2, Y + faceHeight / 7);
	//Рисуем рот 
	MoveToEx(hdc, X - mouthLength / 2, Y + faceHeight / 4, NULL);
	LineTo(hdc, X + mouthLength / 2, Y + faceHeight / 4);
	Arc(hdc, X - mouthLength / 2, Y + 11 * faceHeight / 48, X + mouthLength / 2, Y + 13 * faceHeight / 48,
		X - mouthLength / 2, Y + faceHeight / 4, X + mouthLength / 2, Y + faceHeight / 4);
	DeleteObject(pen);
	//Рисуем зрачки
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, brush); //сделали кисть активной
	Ellipse(hdc, X - 5 * faceWidth / 16, Y - eyesWidth, X - 3 * faceWidth / 16, Y);
	Ellipse(hdc, X + 3 * faceWidth / 16, Y - eyesWidth, X + 5 * faceWidth / 16, Y);


	DeleteObject(brush);

	DeleteObject(pen);
	DeleteObject(brush);
	DeleteObject(brush2);
}

void MagicTV::Hide()
{
	if (IsVisible == false)
		return;

	IsVisible = false;

	// Зададим перо и цвет пера - чёрный
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));

	SelectObject(hdc, pen); //сделали перо активным

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(hdc, brush); //сделали перо активным

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
};
