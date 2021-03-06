#include "Position.h"

Position Position::up{ 0, 1 };
Position Position::down{ 0, -1 };
Position Position::right{ 1, 0 };
Position Position::left{ -1, 0 };
Position Position::zeros{ 0, 0 };
Position Position::ones{ 1, 1 };

Position operator*(int x, Position pos)
{
	return Position{ x * pos.x, x * pos.y };
}

Position operator/(int x, Position pos)
{
	return Position{ x / pos.x, x / pos.y };
}