#include "Brick.h"
#include <assert.h>
#include <math.h>

Brick::Brick(const RectF& rectIn, Color colorIn)
	:
	rect(rectIn),
	color(colorIn)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect(rect.GetExpanded(-padding), color);
	}
}

CollisionEnum Brick::CheckBallCollision(const Ball& ball)
{
	CollisionEnum collision = CollisionEnum::NO_COLLISION;
	if (!destroyed)
	{
		collision = rect.IsOverLappingWith(ball.GetRect());
	}
	return collision;
}

void Brick::ExecuteBallCollision(Ball& ball, CollisionEnum collision)
{
	assert(int(CheckBallCollision(ball)) >= 0);
	const Vec2 ballPos = ball.GetPos();
	if (collision == CollisionEnum::TOP_BOTTOM || signbit(ball.GetVelocity().x) == signbit((ballPos - GetCenter()).x))
	{
		ball.ReboundY(-1.0f);
	}
	else if (collision == CollisionEnum::CORNER)
	{
		ball.ReboundY(-1.0f);
		ball.ReboundX(-1.0f);
	}
	else if (collision == CollisionEnum::SIDE)
	{
		ball.ReboundX(-1.0f);
	}
	destroyed = true;
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}
