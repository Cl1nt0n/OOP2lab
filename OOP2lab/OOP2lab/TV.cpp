#include <Windows.h>
#include "TV.h"
extern HDC hdc;			// ���������� ��������� ����������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

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
void Point::Drag(int Step)
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
			figX -= Step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_RIGHT)) //39 ������� ������
		{
			figX += Step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_DOWN)) //40 ������� ����
		{
			figY += Step;
			MoveTo(figX, figY);
			Sleep(500); //�������� ������ �� 500 ����������
		}//if

		if (KEY_DOWN(VK_UP)) //38 ������� �����
		{
			figY -= Step;
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
}

//���������� ����������
TV::~TV()
{
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

////����������� ���������
//void TV::MoveTo(int newX, int newY)
//{
//	Hide();		//������� ����� ���������
//	X = newX;	//�������� ���������� �����
//	Y = newY;
//	Show();		//�������� ����� �� ����� �����
//}
//
////�������� ��������� �� ������� �������
//void TV::Drag(int step)
//{
//	int figX, figY; //����� ���������� ������
//
//	figX = GetX(); //�������� ��������� ���������� ������
//	figY = GetY();
//
//	//����������� ���� ���������� ������
//	while (1)
//	{
//		if (KEY_DOWN(VK_ESCAPE)) //27 esc - ����� ������
//			break;
//
//		//����� ����������� �������� ������
//		if (KEY_DOWN(VK_LEFT)) //37 ������� �����
//		{
//			figX -= step;
//			MoveTo(figX, figY);
//			Sleep(500); //�������� ������ �� 500 ����������
//		}//if
//
//		if (KEY_DOWN(VK_RIGHT)) //39 ������� ������
//		{
//			figX += step;
//			MoveTo(figX, figY);
//			Sleep(500); //�������� ������ �� 500 ����������
//		}//if
//
//		if (KEY_DOWN(VK_DOWN)) //40 ������� ����
//		{
//			figY += step;
//			MoveTo(figX, figY);
//			Sleep(500); //�������� ������ �� 500 ����������
//		}//if
//
//		if (KEY_DOWN(VK_UP)) //38 ������� �����
//		{
//			figY -= step;
//			MoveTo(figX, figY);
//			Sleep(500); //�������� ������ �� 500 ����������
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


	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));

	SelectObject(hdc, brush);

	Ellipse(hdc, X, Y, X + _screenWidth, Y + _screenHeight);
	Rectangle(hdc, X + _screenWidth / 2 - 10, Y + _screenHeight, X + _screenWidth / 2 + 10, Y + _screenHeight + _standHeight);
	Rectangle(hdc, X + _screenWidth * 0.2, Y + _screenHeight + _standHeight, X + _screenWidth * 0.8, Y + _screenHeight + _standHeight + 10);

	HBRUSH brush2 = CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(hdc, brush2); //������� ���� ��������

	Ellipse(hdc, X + 5, Y + 5, X + _screenWidth - 5, Y + _screenHeight - 5);

	// ������� ���� � ���� ���� - ������
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, pen); //������� ���� ��������

	//������ ���� ����
	Ellipse(hdc, X + _screenWidth / 2 - _faceWidth / 2, Y - _faceHeight / 2, X + _faceWidth / 2, Y + _faceHeight / 2);
	//������ ����� ����
	Ellipse(hdc, X - 3 * _faceWidth / 8, Y - _eyesWidth, X - _faceWidth / 8, Y);
	//������ ������ ����
	Ellipse(hdc, X + _faceWidth / 8, Y - _eyesWidth, X + 3 * _faceWidth / 8, Y);
	//������ �����
	MoveToEx(hdc, X - 3 * _faceWidth / 8, Y - 3 * _eyesWidth / 2, NULL);
	LineTo(hdc, X - _faceWidth / 8, Y - 3 * _eyesWidth / 2);
	MoveToEx(hdc, X + 3 * _faceWidth / 8, Y - 3 * _eyesWidth / 2, NULL);
	LineTo(hdc, X + _faceWidth / 8, Y - 3 * _eyesWidth / 2);
	//������ ���
	MoveToEx(hdc, X, Y - _eyesWidth, NULL);
	LineTo(hdc, X - _noseWidth / 2, Y + _faceHeight / 7);
	MoveToEx(hdc, X - _noseWidth / 2, Y + faceHeight / 7, NULL);
	LineTo(hdc, X + noseWidth / 2, Y + faceHeight / 7);
	//������ ��� 
	MoveToEx(hdc, X - mouthLength / 2, Y + faceHeight / 4, NULL);
	LineTo(hdc, X + mouthLength / 2, Y + faceHeight / 4);
	Arc(hdc, X - mouthLength / 2, Y + 11 * faceHeight / 48, X + mouthLength / 2, Y + 13 * faceHeight / 48,
		X - mouthLength / 2, Y + faceHeight / 4, X + mouthLength / 2, Y + faceHeight / 4);
	DeleteObject(pen);
	//������ ������
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, brush); //������� ����� ��������
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
