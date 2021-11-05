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

};

typedef Position Dimension;
/*
Position::operator+(const Position& other)
{
	return Position{ this->x + other.x, this->y + other.y };
}

string  str;
str = "hello world";
string third;
// chaining // 자기 자신을 리턴하여 복사 할 수 있게 해주는 것
... = third = str = "hello world"; // 자기 자신을 return해서 복사해준다

Position p1{ 1,2 };
Position p1{ 2,3 };

// extern ostream cout;
cout << p1 << endl << hello;
// chaining
((cout.operator<<(p1).operator<<(endl)).operator<<("hello");

template<typename T>
ostream& operator<<(ostream& cout, const T& pos)
{
	//~~~~~~~~~~~~
	return cout;
}

ostream& operator<< (ostream& cout, const Position& pos) // cout을 반환
{
	cout << "(" << pos.x << ", " << pos.y << ")";
	return cout;
}

class ostream {
	static ostream cout;
public:
	ostream& operator<< (const Position& pos) // cout을 반환
	{
		this << "(" << pos.x << "," << pos.y << ")";
		return this;
	}
};
ostream ostream::cout;

void operator+=(Position& p1, const Position& p2)
{
	p1.x = p1.x + p2.x;
	p1.y = p1.y + p2.y;
}

p1 += p2;

auto p4 = p1 + p2; // 객체가 하나 만들어지고 p4에 복사를 한다. 복사 생성자 호출된다.
auto temp = operator+(p1, p2); // 전역 함수인 경우에는 friend를 만들어줘야한다.
auto temp = p1.operator+(p2); // 맴버 함수인 경우에는 friend를 안만들어도 된다. 두개 다있어도 되지만 컴파일러는 전역함수를 default로 설정한다.


Position p4;
{
	auto temp = operator(p1, p2);
	auto temp = p1.operator+(p2); // Position의 맴버 함수로 만들어서 사용
	p4 = temp;
}

Position operator+(const Position& p1, const Position& p2) // Position& 가 안되는 이유, return 값이 지역 변수이기 때문에 사라진다. Position으로 하면 temporary object를 만든다.
{
	Position pos;
	pos.x = p1.x + p2.x;
	pos.y = p1.y + p2.y;

	return pos
}
*/