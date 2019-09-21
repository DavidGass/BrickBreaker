#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
public:
	Brick() = default;
	Brick(const RectF& rectIn, Color colorIn);
	void Draw(Graphics& gfx) const;
	CollisionEnum CheckBallCollision(const Ball& ball);
	void ExecuteBallCollision(Ball& ball, CollisionEnum collision);
	Vec2 GetCenter() const;
private:
	static constexpr float padding = 1.0f;
	RectF rect;
	Color color;
	bool destroyed = false;
};

