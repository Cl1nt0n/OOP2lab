#include <iostream>
#include <Windows.h>
#include "TV.h"

using namespace std;

extern HDC hdc;			// ���������� ��������� ����������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define INTERACTING_SIZE 5
#define ARR_SIZE 5

extern Object destructiveObjects[1];
//extern Object interactingObjects[1];

extern int objectIndex;

//����������� Location
Location::Location(int x, int y)
{
	//������������� �������� ���������� ������ ������
	X = x;
	Y = y;
}//Location::Location()

//���������� Location
Location::~Location()
{
}

Object::Object() : Point(0, 0)
{
	
}

Object::Object(int x, int y) : Point(x, y)
{
	
}

//��������� ���������� X
int Location::GetX()
{
	return X;
}//Location::GetX()	

//��������� ���������� Y
int Location::GetY()
{
	return Y;
}//Location::GetY()	

//����������� Point
Point::Point(int x, int y) : Location(x, y)
{
	IsVisible = false;
}

//���������� Point
Point::~Point()
{
}

//�������� �����
void Point::Show(void)
{
	IsVisible = true;
	SetPixel(hdc, X, Y, RGB(255, 0, 0));//������ ������� ������
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

//������ �����
void Point::Hide(void)
{
	IsVisible = false;

	SetPixel(hdc, X, Y, RGB(242, 242, 242));//������ ����� ������ ��� ����
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

//��������, ����� �� �����
bool Point::CheckIsVisible()
{
	return false;
}//Point::CheckIsVisible()

//�����������
void Point::MoveTo(int newX, int newY)
{
	Hide();		//������� ����� ���������
	X = newX;	//�������� ���������� �����
	Y = newY;
	Show();		//�������� ����� �� ����� �����
}//Point::MoveTo(int newX, int newY)

//����� �� �������
void Point::Drag(int step)
{
	int figX, figY; //����� ���������� ������

	figX = GetX(); //�������� ��������� ���������� ������
	figY = GetY();

	//����������� ���� ���������� ������
	while (1)
	{
		if (KEY_DOWN(VK_ESCAPE)) //27 esc - ����� ������
			break;

		//����� ����������� �������� ������
		if (KEY_DOWN(VK_LEFT)) //37 ������� �����
		{
			figX -= step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_RIGHT)) //39 ������� ������
		{
			figX += step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_DOWN)) //40 ������� ����
		{
			figY += step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_UP)) //38 ������� �����
		{
			figY -= step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if
	}//while
}//Point::Drag(int Step)

//����������� ����������
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

//���������� ����������
TV::~TV()
{
}

void TV::Drag(int step)
{
	int figX, figY; //����� ���������� ������

	figX = GetX(); //�������� ��������� ���������� ������
	figY = GetY();

	//����������� ���� ���������� ������
	while (1)
	{
		if (KEY_DOWN(VK_ESCAPE)) //27 esc - ����� ������
			break;

		//����� ����������� �������� ������
		if (KEY_DOWN(VK_LEFT)) //37 ������� �����
		{
			figX -= step;
			_xTopRight -= step;
			_xBottomLeft -= step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_RIGHT)) //39 ������� ������
		{
			figX += step;
			_xTopRight += step;
			_xBottomLeft += step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_DOWN)) //40 ������� ����
		{
			figY += step;
			_yTopRight += step;
			_yBottomLeft += step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_UP)) //38 ������� �����
		{
			figY -= step;
			_yTopRight -= step;
			_yBottomLeft -= step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		//����� ������� ����������� ��� ������� ����������� �� ������������
		for (int i = 0; i < DESTRUCTIVE_SIZE; i++)
		{
			if (destructiveObjects[i].Collision(*this))
			{
				cout << "��������� ������������!\n";
				Hide();
				BrokenTV brokenTV = BrokenTV(X, Y, _screenHeight, _screenWidth, _standHeight);
				brokenTV.Show();

				return;
			}
		}
	}//while
}

//�������� ���������
void TV::Show()
{
	if (IsVisible == true)
		return;
	IsVisible = true;

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, pen); //������� ���� ��������

	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, brush); //������� ���� ��������

	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
}

//������ ���������
void TV::Hide()
{
	if (IsVisible == false) 
		return;

	IsVisible = false;

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));

	SelectObject(hdc, pen); //������� ���� ��������

	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(hdc, brush); //������� ���� ��������

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

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, pen); //������� ���� ��������

	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);


	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, brush); //������� ���� ��������
	
	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush2 = CreateSolidBrush(RGB(0, 0, 255));

	SelectObject(hdc, brush2); //������� ���� ��������
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

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));

	SelectObject(hdc, pen); //������� ���� ��������

	Rectangle(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(hdc, brush); //������� ���� ��������

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

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, pen); //������� ���� ��������

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, brush); //������� ���� ��������

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

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));

	SelectObject(hdc, pen); //������� ���� ��������

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(hdc, brush); //������� ���� ��������

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

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	SelectObject(hdc, pen); //������� ���� ��������

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

	SelectObject(hdc, brush2); //������� ���� ��������

	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);

	// ������� ���� � ���� ���� - ������
	HBRUSH brush3 = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(hdc, brush3); //������� ���� ��������

	Ellipse(hdc, X + _screenWidth / 2 - _screenWidth / 6, Y + _screenHeight / 8, X + _screenWidth / 2 + _screenWidth / 6, Y + _screenHeight / 8 * 7);

	SelectObject(hdc, brush2); //������� ���� ��������

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

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));

	SelectObject(hdc, pen); //������� ���� ��������

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(hdc, brush); //������� ���� ��������

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
	//����������� ������������ �����
	bool left = _xBottomLeft <= TV.GetXTopRight() && _xTopRight >= TV.GetXTopRight()
		&& (_yBottomLeft <= TV.GetYTopRight() && _yBottomLeft >= TV.GetYBottomLeft()
			|| _yTopRight >= TV.GetYBottomLeft() && _yTopRight <= TV.GetYTopRight());
	//����������� ������������ ������
	bool right = _xTopRight >= TV.GetXBottomLeft() && _xBottomLeft <= TV.GetXBottomLeft()
		&& (_yBottomLeft <= TV.GetYTopRight() && _yBottomLeft >= TV.GetYBottomLeft()
			|| _yTopRight >= TV.GetYBottomLeft() && _yTopRight <= TV.GetYTopRight());
	//����������� ������������ ������
	bool top = _yBottomLeft <= TV.GetYBottomLeft() && _yTopRight >= TV.GetYBottomLeft()
		&& (_xBottomLeft <= TV.GetXTopRight() && _xBottomLeft >= TV.GetXBottomLeft()
			|| _xBottomLeft >= TV.GetXBottomLeft() && _xTopRight <= TV.GetXTopRight());
	//����������� ������������ �����
	bool bottom = _yTopRight >= TV.GetYTopRight() && _yBottomLeft <= TV.GetYTopRight()
		&& (_xBottomLeft <= TV.GetXTopRight() && _xBottomLeft >= TV.GetXBottomLeft()
			|| _xTopRight >= TV.GetXBottomLeft() && _xTopRight <= TV.GetXTopRight());

	//����������� ����, ��������� �� ����������� "������" ������
	bool inside = _xBottomLeft >= TV.GetXBottomLeft() && _yBottomLeft >= TV.GetYBottomLeft() &&
		_xTopRight <= TV.GetXTopRight() && _yTopRight <= TV.GetYTopRight();

	//���� ���� ���� ����, �� ������������ ����
	return left || right || top || bottom || inside;
}

Stone::Stone(int x, int y, int radius) : Object(x, y)
{
	_radius = radius;

	//������ ������� ���������
	_xTopRight = x - radius;
	_yTopRight = y - radius;
	_xBottomLeft = x + radius;
	_yBottomLeft = y + radius;

	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(100, 100, 100));
	SelectObject(hdc, Pen);	//������� ���� ��������

	// �������� ���� ������������� ������
	Ellipse(hdc, X - radius, Y - radius, X + radius, Y + radius);

	// ��������� ���� ��������� �������  
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
