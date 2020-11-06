#pragma once
class Pos
{
private:
	int x;
	int y;
public:
	Pos();
	Pos(int x, int y);

	bool operator==(const Pos& pos) const;

	const int& GetX() const;
	void SetX(const int x);

	const int& GetY() const;
	void SetY(const int y);
};

