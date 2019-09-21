#include "Paddle.h"

Paddle::Paddle(const Vec2& posIn, float halfWidthIn, float halfHeightIn)
	:
	pos(posIn),
	halfWidth(halfWidthIn),
	halfHeight(halfHeightIn),
	wingWidth(halfWidthIn / 2.5f)
{
}

void Paddle::Draw(Graphics& gfx) const
{
	RectF rect = GetRect();
	gfx.DrawRect(rect, wingColor);
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect(rect, color);
}

bool Paddle::BallCollision(Ball& ball)
{
	CollisionEnum collision = GetRect().IsOverLappingWith(ball.GetRect());
	if (ball.GetVelocity().y > 0 && int(collision) >= 0)
	{
		if (!ballColliding)
		{
			if (ball.GetVelocity().y > 0 && int(collision) >= 0)
			{
				const Vec2 ballPos = ball.GetPos();
				//float scale = ();
				if (collision == CollisionEnum::TOP_BOTTOM || signbit(ball.GetVelocity().x) == signbit((ballPos - pos).x))
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
				return true;
			}
			return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		ballColliding = false;
		return false;
	}
}

void Paddle::WallCollision(const RectF& walls)
{
	const RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	else if (pos.x + halfWidth > walls.right)
	{
		pos.x += walls.right - rect.right;
	}
}

void Paddle::Update(const Keyboard& kbd, float deltaTime)
{
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos += Vec2(moveSpeed, 0.0f) * deltaTime;
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos -= Vec2(moveSpeed, 0.0f) * deltaTime;
	}
}

void Paddle::Update(const Keyboard& kbd, float deltaTime, Ball& ball, RectF& walls)
{
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos += Vec2(moveSpeed, 0.0f) * deltaTime;
		WallCollision(walls);
		ball.Update(pos);
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos -= Vec2(moveSpeed, 0.0f) * deltaTime;
		WallCollision(walls);
		ball.Update(pos);
	}
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}
