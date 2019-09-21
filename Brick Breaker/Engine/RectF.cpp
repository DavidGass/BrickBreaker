#include "RectF.h"
#include <algorithm>

RectF::RectF(float leftIn, float rightIn, float topIn, float bottomIn)
	:
	left(leftIn),
	right(rightIn),
	top(topIn),
	bottom(bottomIn)
{
}

RectF::RectF(const Vec2& topLeft, const Vec2& bottomRight)
	:
	RectF(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

RectF::RectF(const Vec2& topLeft, float width, float height)
	:
	RectF(topLeft, topLeft + Vec2(width, height))
{
}

RectF RectF::FromCenter(const Vec2& center, float halfWidth, float halfHeight)
{
	const Vec2 half(halfWidth, halfHeight);
	return RectF(center - half, center + half);
}

CollisionEnum RectF::IsOverLappingWith(const RectF& other) const
{
	Vec2 otherCenter = other.GetCenter();
	CollisionEnum collision = CollisionEnum::NO_COLLISION;
	if (right > other.left && left < other.right && bottom > other.top && top < other.bottom)
	{
		if ((right > other.right && left < other.left && top < other.top && bottom < other.bottom)
		 || (right > other.right && left < other.left && top > other.top && bottom > other.bottom))
		{
			collision = CollisionEnum::TOP_BOTTOM;
		}
		else if ((right > other.right && left > other.left && top < other.top && bottom > other.bottom)
			  || (right < other.right && left < other.left && top < other.top && bottom > other.bottom))
		{
			collision = CollisionEnum::SIDE;
		}
		else if ((right < other.right && left < other.left && top < other.top && bottom < other.bottom)
			  || (right > other.right && left > other.left && top < other.top && bottom < other.bottom)
			  || (right > other.right && left > other.left && top > other.top && bottom > other.bottom)
			  || (right < other.right && left < other.left && top > other.top && bottom > other.bottom))
		{
			float toRight = otherCenter.x - right;
			float toLeft = otherCenter.x - left;
			float toTop = otherCenter.y - top;
			float toBottom = otherCenter.y - bottom;
			if (toRight < 0)
			{
				toRight *= -1;
			}
			if (toLeft < 0)
			{
				toLeft *= -1;
			}
			if (toTop < 0)
			{
				toTop *= -1;
			}
			if (toBottom < 0)
			{
				toBottom *= -1;
			}
			const float closest = std::min(std::min(toRight, toLeft), std::min(toTop, toBottom));
			if ((closest == toRight || closest == toLeft) && (closest == toBottom || closest == toTop))
			{
				collision = CollisionEnum::CORNER;
			}
			else if (otherCenter.x >= left && otherCenter.x <= right)
			{
				collision = CollisionEnum::TOP_BOTTOM;
			}
			else
			{
				collision = CollisionEnum::SIDE;
			}
		}
	}
	return collision;
}

RectF RectF::GetExpanded(float offset) const
{
	return RectF(left - offset, right + offset, top - offset, bottom + offset);
}

Vec2 RectF::GetCenter() const
{
	return Vec2((left + right) / 2.0f, (top + bottom) / 2.0f);
}



