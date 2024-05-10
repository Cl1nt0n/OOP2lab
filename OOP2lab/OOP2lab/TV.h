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
public:
	Point(int x, int y);	//����������� ������
	~Point();						//����������
	bool CheckIsVisible();				//������ ��� ���������� �����
	void MoveTo(int NewX, 
		int NewY, 
		HDC hdc);					//����������� ������
	void Drag(int step, HDC hdc);			//���������� ������

	virtual void Show(HDC hdc);			// �������� ������ �����
	virtual void Hide(HDC hdc);			// ������ ������ �����
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
		int stHeight);	//�����������
	~TV();				//����������

	void Drag(int step, HDC hdc);		//����������� ������
	void Show(HDC hdc);				//�������� ������
	void Hide(HDC hdc);				//������ ������
	//void MoveTo(int NewX, int NewY); //����������� ������

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
		int stHeight);

	void Show(HDC hdc);
	void Hide(HDC hdc);
};

class EllipseTV : public TV
{
public:
	EllipseTV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);

	void Show(HDC hdc);
	void Hide(HDC hdc);
};

class BrokenEllipseTV : public EllipseTV
{
public:
	BrokenEllipseTV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);

	void Show(HDC hdc);
	void Hide(HDC hdc);
};

class MagicTV : public TV
{
public:
	MagicTV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);

	void Show(HDC hdc);
	void Hide(HDC hdc);
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
	Object();
	Object(int x, int y);

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
	Stone(int x, int y, int radius);

	void Show(HDC hdc);
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

	void Show(HDC hdc);
};

BOOL Line(HDC hdc, int x1, int y1, int x2, int y2); //��������� ������ ����� � ������������: x1,y1 � x2,y2