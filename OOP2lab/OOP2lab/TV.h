/*----------------------  ����� �������������� ------------------------*/
class Location
{
protected:		//������������� ����������� �������� (������������
	//������) ����� ������ � ������� ������
	int X;		//���������� �
	int Y;		//���������� Y

public:			//��� ������ �������� ����� ���� � ���������
	Location(int x, int y);	//�����������
	~Location();					//����������
	int GetX();						//�������� � ���������� �����
	int GetY();						//�������� Y ���������� �����
};//class Location

/*-----------------------  ����� ����� ---------------------------------*/
class Point : public Location
{
protected:							//�������, ����������� �� Point, ����������� ������ public
	bool IsVisible;					//���������� �����
	HDC _hdc;
public:
	Point(int x, int y, HDC _hdc);	//����������� ������
	~Point();						//����������
	bool CheckIsVisible();				//������ ��� ���������� �����
	
	void Drag(int step);			//���������� ������

	virtual void MoveTo(int NewX, int NewY);					//����������� ������
	virtual void Show();			// �������� ������ �����
	virtual void Hide();			// ������ ������ �����
};//����� Point

/*-----------------------  ����� ��������� ----------------------------------*/
class TV : public Point
{
protected:
	int _screenHeight;				// ������ ������
	int _screenWidth;				// ������ ������
	int _standHeight;				// ������ 

	int _xTopLeft;
	int _yTopLeft;
	int _xBottomRight;
	int _yBottomRight;
	int _index;
public:
	TV(int x, int y, int scrHeight, int scrWidth,
		int stHeight, HDC hdc);	//�����������
	~TV();				//����������

	void Show();				//�������� ������
	void Hide();				//������ ������
	void MoveTo(int x, int y); //����������� ������

	int GetXTopLeft();
	int GetYTopLeft();
	int GetXBottomRight();
	int GetYBottomRight();
	int GetIndex();
};//����� TV

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
	//���������� ������� ����� ��������
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

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2); //��������� ������ ����� � ������������: x1,y1 � x2,y2