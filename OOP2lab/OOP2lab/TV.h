/*----------------------  Класс МЕСТОПОЛОЖЕНИЕ ------------------------*/
class Location
{
protected:		//предоставляет возможность потомкам (производному
	//классу) иметь доступ к частным данным
	int X;		//координата Х
	int Y;		//координата Y

public:			//эти методы доступны извне всем в программе
	Location(int x, int y);	//конструктор
	~Location();					//деструктор
	int GetX();						//получить Х координату точки
	int GetY();						//получить Y координату точки
};//class Location

/*-----------------------  Класс ТОЧКА ---------------------------------*/
class Point : public Location
{
protected:							//классам, производным от Point, потребуется доступ public
	bool IsVisible;					//светимость точки
	HDC _hdc;
public:
	Point(int x, int y, HDC _hdc);	//конструктор класса
	~Point();						//деструктор
	bool CheckIsVisible();				//узнать про светимость точки
	
	void Drag(int step);			//буксировка фигуры

	virtual void MoveTo(int NewX, int NewY);					//переместить фигуру
	virtual void Show();			// показать фигуру ТОЧКА
	virtual void Hide();			// скрыть фигуру ТОЧКА
};//класс Point

/*-----------------------  Класс телевизор ----------------------------------*/
class TV : public Point
{
protected:
	int _screenHeight;				// высота экрана
	int _screenWidth;				// ширина экрана
	int _standHeight;				// высота 

	int _xTopLeft;
	int _yTopLeft;
	int _xBottomRight;
	int _yBottomRight;
	int _index;
public:
	TV(int x, int y, int scrHeight, int scrWidth,
		int stHeight, HDC hdc);	//конструктор
	~TV();				//деструктор

	void Show();				//показать фигуру
	void Hide();				//скрыть фигуру
	void MoveTo(int x, int y); //переместить фигуру

	int GetXTopLeft();
	int GetYTopLeft();
	int GetXBottomRight();
	int GetYBottomRight();
	int GetIndex();
};//класс TV

class BrokenTV : public TV
{
public:
	BrokenTV(int x, int y, int scrHeight, int scrWidth,
		int stHeight, HDC _hdc);

	void Show();
	void Hide();
};

class EllipseTV : public TV
{
public:
	EllipseTV(int x, int y, int scrHeight, int scrWidth,
		int stHeight, HDC hdc);

	void Show();
	void Hide();
};

class BrokenEllipseTV : public EllipseTV
{
public:
	BrokenEllipseTV(int x, int y, int scrHeight, int scrWidth,
		int stHeight, HDC hdc);

	void Show();
	void Hide();
};

class MagicTV : public TV
{
public:
	MagicTV(int x, int y, int scrHeight, int scrWidth,
		int stHeight, HDC hdc);

	void Show();
	void Hide();
};

class Object : public Point
{
protected:
	//координаты крайних точек хитбокса
	int _xTopLeft;
	int _yTopLeft;
	int _xBottomRight;
	int _yBottomRight;
public:
	Object(HDC hdc);
	Object(int x, int y, HDC hdc);

	int GetXTopLeft();
	int GetYTopLeft();
	int GetXBottomRight();
	int GetYBottomRight();
};

class Stone : public Object
{
protected:
	int _radius;
public:
	Stone(int x, int y, int radius, HDC hdc);

	void Show();
};

class Electricity : public Object
{
protected:
	int _radius;
public:
	Electricity(int x, int y, int radius, HDC hdc);
};

class MagicSource : public Object
{
protected:
	int _starLenght;
	int _starWidth;
public:
	MagicSource(int x, int y, int _starLenght, int _starWidth, HDC hdc);

	void Show();
};

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2); //соединять линией точки с координатами: x1,y1 и x2,y2