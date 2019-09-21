#pragma once

#include "Vec2.h"
#include "CollisionEnum.h"

class RectF
{
public:
	RectF() = default;
	RectF(float leftIn, float rightIn, float topIn, float bottomIn);
	RectF(const Vec2& topLeft, const Vec2& bottomRight);
	RectF(const Vec2& topLeft, float width, float height);
	static RectF FromCenter(const Vec2& center, float halfWidth, float halfHeight);
	CollisionEnum IsOverLappingWith(const RectF& other) const;
	RectF GetExpanded(float offset) const;
	Vec2 GetCenter() const;
public:
	float left;
	float right;
	float top;
	float bottom;
};

