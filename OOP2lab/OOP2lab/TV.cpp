#include <iostream>
#include <Windows.h>
#include "TV.h"

using namespace std;

extern HDC hdc;			// объявление контекста устройства
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define INTERACTING_SIZE 5
#define ARR_SIZE 5

extern Object destructiveObjects[1];
//extern Object interactingObjects[1];

extern int objectIndex;

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

Object::Object() : Point(0, 0)
{
	
}

Object::Object(int x, int y) : Point(x, y)
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
void Point::Drag(int step)
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
			figX -= step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_RIGHT)) //39 стрелка вправо
		{
			figX += step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_DOWN)) //40 стрелка вниз
		{
			figY += step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_UP)) //38 стрелка вверх
		{
			figY -= step;
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
	_xTopRight = x + scrWidth;
	_yTopRight = y + scrHeight + stHeight + 10;
	_xBottomLeft = x;
	_yBottomLeft = y;
}

//деструктор телевизора
TV::~TV()
{
}

void TV::Drag(int step)
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
			figX -= step;
			_xTopRight -= step;
			_xBottomLeft -= step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_RIGHT)) //39 стрелка вправо
		{
			figX += step;
			_xTopRight += step;
			_xBottomLeft += step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_DOWN)) //40 стрелка вниз
		{
			figY += step;
			_yTopRight += step;
			_yBottomLeft += step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		if (KEY_DOWN(VK_UP)) //38 стрелка вверх
		{
			figY -= step;
			_yTopRight -= step;
			_yBottomLeft -= step;
			MoveTo(figX, figY);
			Sleep(500); //задержка экрана на 500 милисекунд
		}//if

		//после каждого перемещения все объекты проверяются на столкновение
		for (int i = 0; i < DESTRUCTIVE_SIZE; i++)
		{
			if (destructiveObjects[i].Collision(*this))
			{
				cout << "Произошло столкновение!\n";
				Hide();
				BrokenTV brokenTV = BrokenTV(X, Y, _screenHeight, _screenWidth, _standHeight);
				brokenTV.Show();

				return;
			}
		}
	}//while
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

int TV::GetXTopRight()
{
	return _xTopRight;
}

int TV::GetYTopRight()
{
	return _yTopRight;
}

int TV::GetXBottomLeft()
{
	return _xBottomLeft;
}

int TV::GetYBottomLeft()
{
	return _yBottomLeft;
}

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

	HBRUSH brush = CreateSolidBrush(RGB(255, 215, 0));

	SelectObject(hdc, brush);

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush2 = CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(hdc, brush2); //сделали перо активным

	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);

	// Зададим перо и цвет пера - чёрный
	HBRUSH brush3 = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, brush3); //сделали перо активным

	Ellipse(hdc, X + _screenWidth / 2 - _screenWidth / 6, Y + _screenHeight / 8, X + _screenWidth / 2 + _screenWidth / 6, Y + _screenHeight / 8 * 7);

	SelectObject(hdc, brush2); //сделали перо активным

	Ellipse(hdc, X + _screenWidth / 2 - _screenWidth / 8, Y + _screenHeight / 3, X + _screenWidth / 2 - _screenWidth / 25, Y + _screenHeight / 3 + _screenHeight / 10);
	Ellipse(hdc, X + _screenWidth / 2 + _screenWidth / 25, Y + _screenHeight / 3, X + _screenWidth / 2 + _screenWidth / 8, Y + _screenHeight / 3 + _screenHeight / 10);
	Arc(hdc, X + _screenWidth / 2 - _screenWidth / 10, 
		Y + _screenHeight / 2 + _screenHeight / 10, 
		X + _screenWidth / 2 + _screenWidth / 10, 
		Y + _screenHeight / 2 + _screenHeight / 5, 
		X + _screenWidth / 2 - _screenWidth / 10, 
		Y + _screenHeight / 2 + _screenHeight / 5, 
		X + _screenWidth / 2 + _screenWidth / 10, Y + _screenHeight / 2 + _screenHeight / 6);
	

	DeleteObject(pen);
	DeleteObject(brush);
	DeleteObject(brush2);
	DeleteObject(brush3);
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

//BrokenEllipseTV::BrokenEllipseTV(int x, int y, int scrHeight, int scrWidth, int stHeight) : TV(x, y, scrHeight, scrWidth, stHeight)
//{
//}
//
//void BrokenEllipseTV::Show()
//{
//}

bool Object::Collision(TV& TV)
{
	//определение столкновения слева
	bool left = _xBottomLeft <= TV.GetXTopRight() && _xTopRight >= TV.GetXTopRight()
		&& (_yBottomLeft <= TV.GetYTopRight() && _yBottomLeft >= TV.GetYBottomLeft()
			|| _yTopRight >= TV.GetYBottomLeft() && _yTopRight <= TV.GetYTopRight());
	//определение столкновений справа
	bool right = _xTopRight >= TV.GetXBottomLeft() && _xBottomLeft <= TV.GetXBottomLeft()
		&& (_yBottomLeft <= TV.GetYTopRight() && _yBottomLeft >= TV.GetYBottomLeft()
			|| _yTopRight >= TV.GetYBottomLeft() && _yTopRight <= TV.GetYTopRight());
	//определение столкновений сверху
	bool top = _yBottomLeft <= TV.GetYBottomLeft() && _yTopRight >= TV.GetYBottomLeft()
		&& (_xBottomLeft <= TV.GetXTopRight() && _xBottomLeft >= TV.GetXBottomLeft()
			|| _xBottomLeft >= TV.GetXBottomLeft() && _xTopRight <= TV.GetXTopRight());
	//определение столкновений снизу
	bool bottom = _yTopRight >= TV.GetYTopRight() && _yBottomLeft <= TV.GetYTopRight()
		&& (_xBottomLeft <= TV.GetXTopRight() && _xBottomLeft >= TV.GetXBottomLeft()
			|| _xTopRight >= TV.GetXBottomLeft() && _xTopRight <= TV.GetXTopRight());

	//определение того, находится ли препятствие "внутри" фигуры
	bool inside = _xBottomLeft >= TV.GetXBottomLeft() && _yBottomLeft >= TV.GetYBottomLeft() &&
		_xTopRight <= TV.GetXTopRight() && _yTopRight <= TV.GetYTopRight();

	//если хоть одно есть, то столкновение есть
	return left || right || top || bottom || inside;
}

Stone::Stone(int x, int y, int radius) : Object(x, y)
{
	_radius = radius;

	//расчет крайних координат
	_xTopRight = x - radius;
	_yTopRight = y - radius;
	_xBottomLeft = x + radius;
	_yBottomLeft = y + radius;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(100, 100, 100));
	SelectObject(hdc, Pen);	//сделаем перо активным

	// Нарисуем круг установленным цветом
	Ellipse(hdc, X - radius, Y - radius, X + radius, Y + radius);

	// Уничтожим нами созданные объекты  
	DeleteObject(Pen);
};

Electricity::Electricity(int x, int y, int radius) : Object(x, y)
{
	_radius = radius;
}

BrokenEllipseTV::BrokenEllipseTV(int x, int y, int scrHeight, int scrWidth, int stHeight) : EllipseTV(x, y, scrHeight, scrWidth, stHeight)
{

}

MagicSource::MagicSource(int x, int y, int _starLenght, int _starWidth) : Object(x, y)
{

}
