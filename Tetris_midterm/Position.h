#pragma once
struct Position
{
	int x;
	int y;

	Position(int x = 0, int y = 0) : x(x), y(y) {}
	Position(const Position& other) : Position(other.x, other.y) {} // copy constructor

	static Position up;
	static Position right;
	static Position down;
	static Position left;
	static Position zeros;
	static Position ones;

	// Position += Position
	Position& operator+=(const Position& other)
	{
		this->x = this->x + other.x;
		this->y = this->y + other.y;

		return *this;
	}
	// Position -= Position
	Position& operator-=(const Position& other)
	{
		this->x = this->x - other.x;
		this->y = this->y - other.y;

		return *this;
	}

	// Position + Position
	Position operator+(const Position& other) const
	{
		return Position{ this->x + other.x, this->y + other.y };
	}

	// Position - Position
	Position operator-(const Position& other) const
	{
		return Position{ this->x - other.x, this->y - other.y };
	}

	// Position * Integer
	Position operator*(int x) const
	{
		return Position{ this->x * x, this->y * x };
	}
	// Integer * Position
	friend Position operator*(int x, Position pos);

	// Position / Integer
	Position operator/(int x) const
	{
		return Position{ this->x / x, this->y / x };
	}
	// Integer / Position
	friend Position operator/(int x, Position pos);

	// Position == Position ?
	bool operator==(const Position& other) const
	{
		if (this->x == other.x && this->y == other.y)
		{
			return true;
		}
		else return false;
	}
	// Position != Position ?
	bool operator!=(const Position& other) const
	{
		if (this->x != other.x || this->y != other.y)
		{
			return true;
		}
		else return false;
	}
};

typedef Position Dimension;