#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "RectF.h"

class Ball
{
public:
	Ball(const Vec2& posIn, const Vec2& velIn);
	void Draw(Graphics& gfx) const;
	void Update(float deltaTime);
	void Update(const Vec2& moveVec);
	void ReSpawn(const RectF& paddleRect);
	void InitSpeed(const Vec2& initVel);
	int WallCollision(const RectF& walls);
	void ReboundX(float scale);
	void ReboundY(float scale);
	RectF GetRect() const;
	Vec2 GetVelocity() const;
	Vec2 GetPos() const;
private:
	static constexpr float radius = 7.0f;
	bool initialized = false;
	Vec2 pos;
	Vec2 vel;
};

