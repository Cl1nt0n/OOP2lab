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
public:
	Point(int x, int y);	//конструктор класса
	~Point();						//деструктор
	bool CheckIsVisible();				//узнать про светимость точки
	void MoveTo(int NewX, int NewY);//переместить фигуру
	void Drag(int step);			//буксировка фигуры

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
	int _xTopRight;
	int _yTopRight;
	int _xBottomLeft;
	int _yBottomLeft;
public:
	TV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);	//конструктор
	~TV();				//деструктор

	void Drag(int step);		//перемещение фигуры
	void Show();				//показать фигуру
	void Hide();				//скрыть фигуру
	//void MoveTo(int NewX, int NewY); //переместить фигуру

	int GetXTopRight();
	int GetYTopRight();
	int GetXBottomLeft();
	int GetYBottomLeft();
};//класс TV

class BrokenTV : public TV
{
public:
	BrokenTV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);

	void Show();
	void Hide();
};

class EllipseTV : public TV
{
public:
	EllipseTV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);

	void Show();
	void Hide();
};

class BrokenEllipseTV : public EllipseTV
{
public:
	BrokenEllipseTV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);

	void Show();
	void Hide();
};

class MagicTV : public TV
{
public:
	MagicTV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);

	void Show();
	void Hide();
};

//class BrokenEllipseTV : public TV
//{
//public:
//	BrokenEllipseTV(int x, int y, int scrHeight, int scrWidth,
//		int stHeight);
//
//	void Show();
//	void Hide();
//};

class Object : public Point
{
protected:
	//координаты крайних точек хитбокса
	int _xTopRight;
	int _yTopRight;
	int _xBottomLeft;
	int _yBottomLeft;
public:
	Object();
	Object(int x, int y);

	bool Collision(TV& TV);
};

class Stone : public Object
{
protected:
	int _radius;
public:
	Stone(int x, int y, int radius);
};

class Electricity : public Object
{
protected:
	int _radius;
public:
	Electricity(int x, int y, int radius);
};

class MagicSource : public Object
{
protected:
	int _starLenght;
	int _starWidth;
public:
	MagicSource(int x, int y, int _starLenght, int _starWidth);
};
