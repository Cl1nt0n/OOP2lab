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

	//����������� ������ (������ ����������)
	//void Show();					//
	//void Hide();					//

	//����������� ������ (������� ����������)
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
public:
	TV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);	//�����������
	~TV();				//����������

	//void Drag(int step);		//����������� ������
	void Show();				//�������� ������
	void Hide();				//������ ������
	//void MoveTo(int NewX, int NewY); //����������� ������
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

class MagicTV : public TV
{
protected:
	int _faceWidth;
	int _faceHeight;
	int _eyesWidth;
	int _noseWidth;
	int _mouthLenght;
public:
	MagicTV(int x, int y, int scrHeight, int scrWidth,
		int stHeight);

	void Show();
	void Hide();
};

//class BrokenTV : public TV
//{
//protected:
//	bool _isBroken;
//public:
//	BrokenTV(int x, int y, int scrHeight, int scrWidth,
//		int stHeight, bool isBroken);	//�����������
//	~BrokenTV();
//
//	void Show();				//�������� ������
//	void Hide();				//������ ������
//};

//class EllipseTV : public TV
//{
//protected:
//	int _ellipseRadius;
//public:
//	EllipseTV(int x, int y, int scrHeight, int scrWidth,
//		int stHeight, bool isBroken);	//�����������
//	~EllipseTV();
//
//	virtual void Show();				//�������� ������
//	virtual void Hide();				//������ ������
//};
//
//class MagicTV : public TV
//{
//protected:
//
//public:
//
//};
//
