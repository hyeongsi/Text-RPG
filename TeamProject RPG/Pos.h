#pragma once
class Pos
{
private:
	int x;
	int y;
public:
	Pos();
	Pos(int x, int y);

	bool operator==(Pos pos);

	const int& GetX();
	void SetX(const int x);

	const int& GetY();
	void SetY(const int y);
};

