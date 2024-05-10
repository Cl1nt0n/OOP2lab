#include <iostream>
#include <Windows.h>
#include "TV.h"

using namespace std;

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

#pragma region Location
//����������� Location
Location::Location(int x, int y)
{
	X = x;
	Y = y;
}//Location::Location()

//���������� Location
Location::~Location() {}

//��������� ���������� X
int Location::GetX()
{
	return X;
}

//��������� ���������� Y
int Location::GetY()
{
	return Y;
}
#pragma endregion

#pragma region Point

//����������� Point
Point::Point(int x, int y) : Location(x, y)
{
	IsVisible = false;
}

//���������� Point
Point::~Point() {}

//�������� �����
void Point::Show(HDC hdc)
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
void Point::Hide(HDC hdc)
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
void Point::MoveTo(int newX, int newY, HDC hdc)
{
	Hide(hdc);		//������� ����� ���������
	X = newX;	//�������� ���������� �����
	Y = newY;
	Show(hdc);		//�������� ����� �� ����� �����
}//Point::MoveTo(int newX, int newY)

//����� �� �������
void Point::Drag(int step, HDC hdc)
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
			MoveTo(figX, figY, hdc);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_RIGHT)) //39 ������� ������
		{
			figX += step;
			MoveTo(figX, figY, hdc);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_DOWN)) //40 ������� ����
		{
			figY += step;
			MoveTo(figX, figY, hdc);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_UP)) //38 ������� �����
		{
			figY -= step;
			MoveTo(figX, figY, hdc);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if
	}//while
}//Point::Drag(int Step)
#pragma endregion

#pragma region TV
//����������� ����������
TV::TV(int x, int y, int scrHeight, int scrWidth, int stHeight) : Point(x, y)
{
	_screenHeight = scrHeight;
	_screenWidth = scrWidth;
	_standHeight = stHeight;
	_xTopLeft = x;
	_yTopLeft = y;
	_xBottomRight = x + scrWidth;
	_yBottomRight = y + scrHeight + stHeight + 10;
	_index = 0;
}

//���������� ����������
TV::~TV() {}

void TV::Drag(int step, HDC hdc)
{
	int figX, figY; //����� ���������� ������

	figX = GetX(); //�������� ��������� ���������� ������
	figY = GetY();

	//����� ����������� �������� ������
	if (KEY_DOWN(VK_LEFT)) //37 ������� �����
	{
		figX -= step;
		_xTopLeft -= step;
		_xBottomRight -= step;
		MoveTo(figX, figY, hdc);
		Sleep(500); //�������� ������ �� 500 ����������
	}//if

	if (KEY_DOWN(VK_RIGHT)) //39 ������� ������
	{
		figX += step;
		_xTopLeft += step;
		_xBottomRight += step;
		MoveTo(figX, figY, hdc);
		Sleep(500); //�������� ������ �� 500 ����������
	}//if

	if (KEY_DOWN(VK_DOWN)) //40 ������� ����
	{
		figY += step;
		_yTopLeft += step;
		_yBottomRight += step;
		MoveTo(figX, figY, hdc);
		Sleep(500); //�������� ������ �� 500 ����������
	}//if

	if (KEY_DOWN(VK_UP)) //38 ������� �����
	{
		figY -= step;
		_yTopLeft -= step;
		_yBottomRight -= step;
		MoveTo(figX, figY, hdc);
		Sleep(500); //�������� ������ �� 500 ����������
	}
}

//�������� ���������
void TV::Show(HDC hdc)
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
void TV::Hide(HDC hdc)
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

int TV::GetXTopLeft()
{
	return _xTopLeft;
}

int TV::GetYTopLeft()
{
	return _yTopLeft;
}

int TV::GetXBottomRight()
{
	return _xBottomRight;
}

int TV::GetYBottomRight()
{
	return _yBottomRight;
}
int TV::GetIndex()
{
	return _index;
}
#pragma endregion

#pragma region BrokenTV
BrokenTV::BrokenTV(int x, int y, int scrHeight, int scrWidth, int stHeight) : TV(x, y, scrHeight, scrWidth, stHeight)
{
	_index = 1;
}

void BrokenTV::Show(HDC hdc)
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
	DeleteObject(brush7);
}

void BrokenTV::Hide(HDC hdc)
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
#pragma endregion

#pragma region EllipseTV
EllipseTV::EllipseTV(int x, int y, int scrHeight, int scrWidth, int stHeight) : TV(x, y, scrHeight, scrWidth, stHeight)
{
	_index = 2;
}

void EllipseTV::Show(HDC hdc)
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

void EllipseTV::Hide(HDC hdc)
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
#pragma endregion

#pragma region MagicTV
MagicTV::MagicTV(int x, int y, int scrHeight, int scrWidth, int stHeight) : TV(x, y, scrHeight, scrWidth, stHeight)
{
	_index = 3;
}

void MagicTV::Show(HDC hdc)
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

void MagicTV::Hide(HDC hdc)
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
#pragma endregion

#pragma region BrokenEllipseTV
BrokenEllipseTV::BrokenEllipseTV(int x, int y, int scrHeight, int scrWidth, int stHeight) : EllipseTV(x, y, scrHeight, scrWidth, stHeight)
{
	_index = 4;
}

void BrokenEllipseTV::Show(HDC hdc)
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

	HBRUSH brush2 = CreateSolidBrush(RGB(0, 0, 255));

	SelectObject(hdc, brush2);

	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);

	HBRUSH brush3 = CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(hdc, brush3);

	Ellipse(hdc, X + _screenWidth / 3, Y + 5, X + _screenWidth / 3 * 2 - 5, Y + _screenHeight - 5);

	HBRUSH brush4 = CreateSolidBrush(RGB(0, 255, 0));

	SelectObject(hdc, brush4);

	Ellipse(hdc, X + _screenWidth / 3 * 2, Y + 5, X + _screenWidth / 3 - 5, Y + _screenHeight - 5);

	HBRUSH brush5 = CreateSolidBrush(RGB(255, 255, 255));

	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
	DeleteObject(brush2);
	DeleteObject(brush3);
	DeleteObject(brush4);
	DeleteObject(brush5);
}

void BrokenEllipseTV::Hide(HDC hdc)
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
}
#pragma endregion

#pragma region Object
Object::Object() : Point(0, 0) {}

Object::Object(int x, int y) : Point(x, y) {}

int Object::GetXTopLeft()
{
	return _xTopLeft;
}

int Object::GetYTopLeft()
{
	return _yTopLeft;
}

int Object::GetXBottomRight()
{
	return _xBottomRight;
}

int Object::GetYBottomRight()
{
	return _yBottomRight;
}
#pragma endregion

#pragma region Stone
Stone::Stone(int x, int y, int radius) : Object(x, y)
{
	_radius = radius;

	//������ ������� ���������
	_xTopLeft = x;
	_yTopLeft = y;
	_xBottomRight = x + radius;
	_yBottomRight = y + radius;
}

void Stone::Show(HDC hdc)
{
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(100, 100, 100));
	SelectObject(hdc, pen);	//������� ���� ��������

	// �������� ���� ������������� ������
	Ellipse(hdc, X, Y, X + _radius, Y + _radius);

	HPEN brush = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));

	Ellipse(hdc, X, Y, X + _radius, Y + _radius);

	// ��������� ���� ��������� �������  
	DeleteObject(pen);
	DeleteObject(brush);
}

//void Stone::Show(HDC hdc)
//{
//	HPEN pen = CreatePen(PS_SOLID, 2, RGB(100, 100, 100));
//	SelectObject(hdc, pen);	//������� ���� ��������
//
//	// �������� ���� ������������� ������
//	Ellipse(hdc, X, Y, X + _radius, Y + _radius);
//
//	HPEN brush = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
//
//	Ellipse(hdc, X, Y, X + _radius, Y + _radius);
//
//	// ��������� ���� ��������� �������  
//	DeleteObject(pen);
//	DeleteObject(brush);
//};
#pragma endregion

#pragma region Electricity
Electricity::Electricity(int x, int y, int radius) : Object(x, y)
{
	_radius = radius;
}
#pragma endregion

#pragma region MagicSource
MagicSource::MagicSource(int x, int y, int starLenght, int starWidth) : Object(x, y)
{
	_starLenght = starLenght;
	_starWidth = starWidth;
	//������ ������� ���������
	_xTopLeft = X;
	_yTopLeft = Y;
	_xBottomRight = X + starWidth;
	_yBottomRight = Y + starLenght;
}

void MagicSource::Show(HDC hdc)
{
	// ������� ���� � ���� ���� - �������
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, Pen);	//������� ���� ��������

	Line(hdc, X, Y, X + _starWidth, Y + _starLenght);
	Line(hdc, X, Y, X - _starWidth, Y + _starLenght);
	Line(hdc, X + _starWidth, Y + _starLenght, X - _starWidth, Y + _starLenght / 2);
	Line(hdc, X - _starWidth, Y + _starLenght, X + _starWidth, Y + _starLenght / 2);
	Line(hdc, X - _starWidth, Y + _starLenght / 2, X + _starWidth, Y + _starLenght / 2);

	DeleteObject(Pen);
}
#pragma endregion

//��������� ������ ����� � ������������: x1,y1 � x2,y2
BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL); //������� �������� ���������� x1, y1
	return LineTo(hdc, x2, y2);
}

