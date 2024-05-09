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
	void MoveTo(int NewX, int NewY);//����������� ������
	void Drag(int step);			//���������� ������

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
	int _xTopRight;
	int _yTopRight;
	int _xBottomLeft;
	int _yBottomLeft;
public:
	TV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);	//�����������
	~TV();				//����������

	void Drag(int step);		//����������� ������
	void Show();				//�������� ������
	void Hide();				//������ ������
	//void MoveTo(int NewX, int NewY); //����������� ������

	int GetXTopRight();
	int GetYTopRight();
	int GetXBottomLeft();
	int GetYBottomLeft();
};//����� TV

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
	//���������� ������� ����� ��������
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
