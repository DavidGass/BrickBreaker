#pragma once

#include "Ball.h"
#include "Vec2.h"
#include "Colors.h"
#include "RectF.h"
#include "Graphics.h"
#include "Keyboard.h"

class Paddle
{
public:
	Paddle() = default;
	Paddle(const Vec2& posIn, float halfWidthIn, float halfHeightIn);
	void Draw(Graphics& gfx) const;
	bool BallCollision(Ball& ball);
	void WallCollision(const RectF& walls);
	void Update(const Keyboard& kbd, float deltaTime);
	void Update(const Keyboard& kbd, float deltaTime, Ball& ball, RectF& walls);
	RectF GetRect() const;
private:
	Color wingColor = Colors::Red;
	bool ballColliding = false;
	Color color = Colors::White;
	float halfWidth;
	float halfHeight;
	float wingWidth;
	static constexpr float moveSpeed = 350.0f;
	Vec2 pos;
};

