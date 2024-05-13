#include <iostream>
#include <Windows.h>
#include "TV.h"
#include "math.h"

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
Point::Point(int x, int y, HDC hdc) : Location(x, y)
{
	IsVisible = false;
	_hdc = hdc;
}

//���������� Point
Point::~Point() {}

//�������� �����
void Point::Show()
{
	IsVisible = true;
	SetPixel(_hdc, X, Y, RGB(255, 0, 0));//������ ������� ������
	SetPixel(_hdc, X + 1, Y, RGB(255, 0, 0));
	SetPixel(_hdc, X + 2, Y, RGB(255, 0, 0));
	SetPixel(_hdc, X + 3, Y, RGB(255, 0, 0));
	SetPixel(_hdc, X + 1, Y, RGB(255, 0, 0));
	SetPixel(_hdc, X + 1, Y + 1, RGB(255, 0, 0));
	SetPixel(_hdc, X + 1, Y + 2, RGB(255, 0, 0));
	SetPixel(_hdc, X + 1, Y + 3, RGB(255, 0, 0));
	SetPixel(_hdc, X + 2, Y, RGB(255, 0, 0));
	SetPixel(_hdc, X + 2, Y + 1, RGB(255, 0, 0));
	SetPixel(_hdc, X + 2, Y + 2, RGB(255, 0, 0));
	SetPixel(_hdc, X + 2, Y + 3, RGB(255, 0, 0));
}//end Point::Show()

//������ �����
void Point::Hide()
{
	IsVisible = false;

	SetPixel(_hdc, X, Y, RGB(242, 242, 242));//������ ����� ������ ��� ����
	SetPixel(_hdc, X + 1, Y, RGB(242, 242, 242));
	SetPixel(_hdc, X + 2, Y, RGB(242, 242, 242));
	SetPixel(_hdc, X + 3, Y, RGB(242, 242, 242));
	SetPixel(_hdc, X + 1, Y, RGB(242, 242, 242));
	SetPixel(_hdc, X + 1, Y + 1, RGB(242, 242, 242));
	SetPixel(_hdc, X + 1, Y + 2, RGB(242, 242, 242));
	SetPixel(_hdc, X + 1, Y + 3, RGB(242, 242, 242));
	SetPixel(_hdc, X + 2, Y, RGB(242, 242, 242));
	SetPixel(_hdc, X + 2, Y + 1, RGB(242, 242, 242));
	SetPixel(_hdc, X + 2, Y + 2, RGB(242, 242, 242));
	SetPixel(_hdc, X + 2, Y + 3, RGB(242, 242, 242));
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
	int x = X;
	int y = Y;
	//����� ����������� �������� ������
	if (KEY_DOWN(VK_LEFT)) //37 ������� �����
	{
		x -= step;
		MoveTo(x, y);
		Sleep(500); //�������� ������ �� 500 ����������
	}//if

	if (KEY_DOWN(VK_RIGHT)) //39 ������� ������
	{
		x += step;
		MoveTo(x, y);
		Sleep(500); //�������� ������ �� 500 ����������
	}//if

	if (KEY_DOWN(VK_DOWN)) //40 ������� ����
	{
		y += step;
		MoveTo(x, y);
		Sleep(500); //�������� ������ �� 500 ����������
	}//if

	if (KEY_DOWN(VK_UP)) //38 ������� �����
	{
		y -= step;
		MoveTo(x, y);
		Sleep(500); //�������� ������ �� 500 ����������
	}//if
}//Point::Drag(int Step)
#pragma endregion

#pragma region TV
//����������� ����������
TV::TV(int x, int y, int scrHeight, int scrWidth, int stHeight, HDC hdc) : Point(x, y, hdc)
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

//�������� ���������
void TV::Show()
{
	if (IsVisible == true)
		return;
	IsVisible = true;

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(_hdc, pen); //������� ���� ��������

	Rectangle(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(_hdc, brush); //������� ���� ��������

	Rectangle(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

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

	SelectObject(_hdc, pen); //������� ���� ��������

	Rectangle(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(_hdc, brush); //������� ���� ��������

	Rectangle(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
}

void TV::MoveTo(int x, int y)
{
	Hide();		//������� ����� ���������
	X = x;	//�������� ���������� �����
	Y = y;
	_xTopLeft = x;
	_yTopLeft = y;
	_xBottomRight = x + _screenWidth;
	_yBottomRight = y + _screenHeight + _standHeight + 10;
	Show();		//�������� ����� �� ����� �����
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
BrokenTV::BrokenTV(int x, int y, int scrHeight, int scrWidth, int stHeight, HDC hdc) : TV(x, y, scrHeight, scrWidth, stHeight, hdc)
{
	_index = 1;
}

void BrokenTV::Show()
{
	if (IsVisible == true)
		return;
	IsVisible = true;

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(_hdc, pen); //������� ���� ��������

	Rectangle(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(_hdc, brush); //������� ���� ��������

	Rectangle(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush2 = CreateSolidBrush(RGB(0, 0, 255));
	SelectObject(_hdc, brush2); //������� ���� ��������
	Rectangle(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);

	HBRUSH brush3 = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(_hdc, brush3);
	Rectangle(_hdc, X + 5 + _screenWidth / 10, Y + 5, X + _screenWidth - 5 - _screenWidth / 10, Y + _screenHeight - 5);

	HBRUSH brush4 = CreateSolidBrush(RGB(0, 255, 0));
	SelectObject(_hdc, brush4);
	Rectangle(_hdc, X + 5 + _screenWidth / 5, Y + 5, X + _screenWidth - 5 - _screenWidth / 5, Y + _screenHeight - 5);

	HBRUSH brush5 = CreateSolidBrush(RGB(255, 0, 0));
	SelectObject(_hdc, brush5);
	Rectangle(_hdc, X + 5 + _screenWidth / 10 * 3, Y + 5, X + _screenWidth - 5 - _screenWidth / 10 * 3, Y + _screenHeight - 5);

	HBRUSH brush6 = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(_hdc, brush6);
	Rectangle(_hdc, X + _screenWidth / 2.5, Y + 5, X + _screenWidth - _screenWidth / 2, Y + _screenHeight - 5);

	HBRUSH brush7 = CreateSolidBrush(RGB(192, 192, 192));
	SelectObject(_hdc, brush7);
	Rectangle(_hdc, X + _screenWidth / 2, Y + 5, X + _screenWidth - _screenWidth / 2.5, Y + _screenHeight - 5);

	DeleteObject(brush);
	DeleteObject(brush2);
	DeleteObject(brush3);
	DeleteObject(brush4);
	DeleteObject(brush5);
	DeleteObject(brush6);
	DeleteObject(brush7);
	DeleteObject(pen);
}

void BrokenTV::Hide()
{
	if (IsVisible == false) return;

	IsVisible = false;

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));

	SelectObject(_hdc, pen); //������� ���� ��������

	Rectangle(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(_hdc, brush); //������� ���� ��������

	Rectangle(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
};
#pragma endregion

#pragma region EllipseTV
EllipseTV::EllipseTV(int x, int y, int scrHeight, int scrWidth, int stHeight, HDC hdc) : TV(x, y, scrHeight, scrWidth, stHeight, hdc)
{
	_index = 2;
}

void EllipseTV::Show()
{
	if (IsVisible == true)
		return;
	IsVisible = true;

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(_hdc, pen); //������� ���� ��������

	Ellipse(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(_hdc, brush); //������� ���� ��������

	Ellipse(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

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

	SelectObject(_hdc, pen); //������� ���� ��������

	Ellipse(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(_hdc, brush); //������� ���� ��������

	Ellipse(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
};
#pragma endregion

#pragma region MagicTV
MagicTV::MagicTV(int x, int y, int scrHeight, int scrWidth, int stHeight, HDC hdc) : TV(x, y, scrHeight, scrWidth, stHeight, hdc)
{
	_index = 3;
}

void MagicTV::Show()
{
	if (IsVisible == true)
		return;
	IsVisible = true;

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

	SelectObject(_hdc, pen); //������� ���� ��������

	Ellipse(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(255, 215, 0));

	SelectObject(_hdc, brush);

	Ellipse(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush2 = CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(_hdc, brush2); //������� ���� ��������

	Ellipse(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);

	// ������� ���� � ���� ���� - ������
	HBRUSH brush3 = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(_hdc, brush3); //������� ���� ��������

	Ellipse(_hdc, X + _screenWidth / 2 - _screenWidth / 6, Y + _screenHeight / 8, X + _screenWidth / 2 + _screenWidth / 6, Y + _screenHeight / 8 * 7);

	SelectObject(_hdc, brush2); //������� ���� ��������

	Ellipse(_hdc, X + _screenWidth / 2 - _screenWidth / 8, Y + _screenHeight / 3, X + _screenWidth / 2 - _screenWidth / 25, Y + _screenHeight / 3 + _screenHeight / 10);
	Ellipse(_hdc, X + _screenWidth / 2 + _screenWidth / 25, Y + _screenHeight / 3, X + _screenWidth / 2 + _screenWidth / 8, Y + _screenHeight / 3 + _screenHeight / 10);
	Arc(_hdc, X + _screenWidth / 2 - _screenWidth / 10,
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

	SelectObject(_hdc, pen); //������� ���� ��������

	Ellipse(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(_hdc, brush); //������� ���� ��������

	Ellipse(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
};
#pragma endregion

#pragma region BrokenEllipseTV
BrokenEllipseTV::BrokenEllipseTV(int x, int y, int scrHeight, int scrWidth, int stHeight, HDC hdc) : EllipseTV(x, y, scrHeight, scrWidth, stHeight, hdc)
{
	_index = 4;
}

void BrokenEllipseTV::Show()
{
	if (IsVisible == true)
		return;
	IsVisible = true;

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(_hdc, pen); //������� ���� ��������

	Ellipse(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(_hdc, brush); //������� ���� ��������

	Ellipse(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);

	HBRUSH brush2 = CreateSolidBrush(RGB(0, 0, 255));

	SelectObject(_hdc, brush2);

	Ellipse(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);

	HBRUSH brush3 = CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(_hdc, brush3);

	Rectangle(_hdc, X + 5 + _screenWidth / 10,
		Y + 5 + _screenHeight - sqrt(_screenWidth * _screenWidth / 4 - (4 * 9 * (_screenWidth / 10) * _screenWidth * _screenWidth) / _screenHeight / _screenHeight),
		X - 5 + 9 * _screenWidth / 10,
		Y - 5 + sqrt(_screenWidth * _screenWidth / 4 - (4 * 9 * (_screenWidth / 10) * _screenWidth * _screenWidth) / _screenHeight / _screenHeight));

	HBRUSH brush4 = CreateSolidBrush(RGB(0, 255, 0));

	SelectObject(_hdc, brush4);

	Rectangle(_hdc, X + 5 + _screenWidth / 5,
		Y + _screenHeight - sqrt(_screenWidth * _screenWidth / 4 - (4 * (_screenWidth / 5) * _screenWidth * _screenWidth) / _screenHeight / _screenHeight),
		X - 5 + 4 * _screenWidth / 5,
		Y + sqrt(_screenWidth * _screenWidth / 4 - (4 * (_screenWidth / 5) * _screenWidth * _screenWidth) / _screenHeight / _screenHeight));

	HBRUSH brush5 = CreateSolidBrush(RGB(255, 0, 0));

	SelectObject(_hdc, brush5);

	Rectangle(_hdc, X + 5 + 3 * _screenWidth / 10,
		Y + _screenHeight - sqrt(_screenWidth * _screenWidth / 4 - (4 * (3 * (_screenWidth / 10)) * _screenWidth * _screenWidth) / _screenHeight / _screenHeight) - 10,
		X - 5 + 7 * _screenWidth / 10,
		Y + sqrt(_screenWidth * _screenWidth / 4 - (4 * (3 * (_screenWidth / 10)) * _screenWidth * _screenWidth) / _screenHeight / _screenHeight) + 10);

	HBRUSH brush6 = CreateSolidBrush(RGB(255, 255, 255));

	SelectObject(_hdc, brush6);

	Rectangle(_hdc, X + 5 + 4 * _screenWidth / 10,
		Y + _screenHeight - sqrt(_screenWidth * _screenWidth / 4 - (4 * (4 * (_screenWidth / 10)) * _screenWidth * _screenWidth) / _screenHeight / _screenHeight) - 15,
		X - 5 + 6 * _screenWidth / 10,
		Y + sqrt(_screenWidth * _screenWidth / 4 - (4 * (4 * (_screenWidth / 10)) * _screenWidth * _screenWidth) / _screenHeight / _screenHeight) + 15);

	DeleteObject(pen);
	DeleteObject(brush);
	DeleteObject(brush2);
	DeleteObject(brush3);
	DeleteObject(brush4);
	DeleteObject(brush5);
}

void BrokenEllipseTV::Hide()
{
	if (IsVisible == false)
		return;

	IsVisible = false;

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(242, 242, 242));

	SelectObject(_hdc, pen); //������� ���� ��������

	Ellipse(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush = CreateSolidBrush(RGB(242, 242, 242));

	SelectObject(_hdc, brush); //������� ���� ��������

	Ellipse(_hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Ellipse(_hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);
	Rectangle(_hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(_hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	DeleteObject(pen);
	DeleteObject(brush);
}
#pragma endregion

#pragma region Object
Object::Object(HDC hdc) : Point(0, 0, hdc) {}

Object::Object(int x, int y, HDC hdc) : Point(x, y, hdc) {}

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
Stone::Stone(int x, int y, int radius, HDC hdc) : Object(x, y, hdc)
{
	_radius = radius;

	//������ ������� ���������
	_xTopLeft = x;
	_yTopLeft = y;
	_xBottomRight = x + radius;
	_yBottomRight = y + radius;
}

void Stone::Show()
{
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(100, 100, 100));
	SelectObject(_hdc, pen);	//������� ���� ��������

	// �������� ���� ������������� ������
	Ellipse(_hdc, X, Y, X + _radius, Y + _radius);

	HBRUSH brush = CreateSolidBrush(RGB(192, 192, 192));
	SelectObject(_hdc, brush);	//������� ���� ��������

	Ellipse(_hdc, X, Y, X + _radius, Y + _radius);

	// ��������� ���� ��������� �������  
	DeleteObject(pen);
	DeleteObject(brush);
}
#pragma endregion

#pragma region Electricity
Electricity::Electricity(int x, int y, int radius, HDC hdc) : Object(x, y, hdc)
{
	_radius = radius;
}
#pragma endregion

#pragma region MagicSource
MagicSource::MagicSource(int x, int y, int starLenght, int starWidth, HDC hdc) : Object(x, y, hdc)
{
	_starLenght = starLenght;
	_starWidth = starWidth;
	//������ ������� ���������
	_xTopLeft = X;
	_yTopLeft = Y;
	_xBottomRight = X + starWidth;
	_yBottomRight = Y + starLenght;
}

void MagicSource::Show()
{
	// ������� ���� � ���� ���� - �������
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(_hdc, Pen);	//������� ���� ��������

	Line(_hdc, X, Y, X + _starWidth, Y + _starLenght);
	Line(_hdc, X, Y, X - _starWidth, Y + _starLenght);
	Line(_hdc, X + _starWidth, Y + _starLenght, X - _starWidth, Y + _starLenght / 2);
	Line(_hdc, X - _starWidth, Y + _starLenght, X + _starWidth, Y + _starLenght / 2);
	Line(_hdc, X - _starWidth, Y + _starLenght / 2, X + _starWidth, Y + _starLenght / 2);

	DeleteObject(Pen);
}
#pragma endregion

//��������� ������ ����� � ������������: x1,y1 � x2,y2
BOOL Line(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL); //������� �������� ���������� x1, y1
	return LineTo(hdc, x2, y2);
}

