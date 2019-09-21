#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2& posIn, const Vec2& velIn)
	:
	pos(posIn),
	vel(velIn)
{
}

void Ball::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::Update(float deltaTime)
{
	pos += vel * deltaTime;
}

void Ball::Update(const Vec2& moveVec)
{
	pos.x = moveVec.x;
}

void Ball::ReSpawn(const RectF& paddleRect)
{
	pos.x = paddleRect.GetCenter().x;
	pos.y = paddleRect.top - 7.0f;
	vel = Vec2(0, 0);
	initialized = false;
}

void Ball::InitSpeed(const Vec2& initVel)
{
	if (!initialized)
	{
		vel = initVel;
		initialized = true;
	}
}

int Ball::WallCollision(const RectF& walls)
{
	int collided = 0;
	const RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
		ReboundX(-1.0f);
		collided = 1;
	}
	else if (rect.right > walls.right)
	{
		pos.x += walls.right - rect.right;
		ReboundX(-1.0f);
		collided = 1;
	}
	if (rect.top < walls.top)
	{
		pos.y += walls.top - rect.top;
		ReboundY(-1.0f);
		collided = 1;
	}
	else if (rect.bottom > walls.bottom)
	{
		pos.y += walls.bottom - rect.bottom;
		ReboundY(-1.0f);
		collided = -1;
	}
	return collided;
}

void Ball::ReboundX(float scale)
{
	vel.x = scale * vel.x;
}

void Ball::ReboundY(float scale)
{
	vel.y = scale * vel.y;
}

RectF Ball::GetRect() const
{
	return RectF::FromCenter(pos, radius, radius);
}

Vec2 Ball::GetVelocity() const
{
	return vel;
}

Vec2 Ball::GetPos() const
{
	return pos;
}
