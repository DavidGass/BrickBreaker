/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"
#include <algorithm>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	walls(borderPadding, float(Graphics::ScreenWidth) - borderPadding, borderPadding, float(Graphics::ScreenHeight) - borderPadding),
	paddle(Vec2((walls.right + walls.left) / 4.0f, walls.bottom - 25.0f), 50.0f, 5.0f),
	ball(Vec2(paddle.GetRect().GetCenter().x, paddle.GetRect().top - 7.0f), Vec2(0.0f, 0.0f)),
	soundPad(L"Sounds\\arkpad.wav"),
	soundBrick(L"Sounds\\arkbrick.wav")
{
	const Color colors[4] = { Colors::Red, Colors::Green, Colors::Blue, Colors::Cyan };
	const Vec2 topLeft(40.0f, 40.0f);
	int i = 0;
	for (int y = 0; y < nBricksDown; y++)
	{
		const Color c = colors[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			bricks[i] = Brick(RectF(topLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), c);
			i++;
		}
	}

	for (int i = 0; i < lives; i++)
	{
		float x = walls.left + i * (4.0f + 2 * lifePaddleHalfWidth) + 4.0f + lifePaddleHalfWidth;
		float y = walls.bottom - 2 * lifePaddleHalfHeight;
		lifePaddles[i] = Paddle(Vec2(x, y), lifePaddleHalfWidth, lifePaddleHalfHeight);
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = timer.Mark();
	while (elapsedTime > 0.0f)
	{
		const float deltaTime = std::min(0.0025f, elapsedTime);
		UpdateModel(deltaTime);
		elapsedTime -= deltaTime;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float deltaTime)
{
	if (!gameOver)
	{
		if (gameStarted && !gamePaused)
		{
			ball.Update(deltaTime);
			paddle.Update(wnd.kbd, deltaTime);
			CollisionEnum collisionType = CollisionEnum::NO_COLLISION;
			float closestDistance;
			int bestBrick;
			for (int i = 0; i < nBricks; i++)
			{
				const CollisionEnum newCollision = bricks[i].CheckBallCollision(ball);
				if (int(newCollision) >= 0)
				{
					const float newCollisionDistance = (ball.GetPos() - bricks[i].GetCenter()).GetLengthSq();
					if (int(collisionType) >= 0)
					{
						if (newCollisionDistance < closestDistance)
						{
							closestDistance = newCollisionDistance;
							bestBrick = i;
							collisionType = newCollision;
						}
					}
					else 
					{
						closestDistance = newCollisionDistance;
						bestBrick = i;
						collisionType = newCollision;
					}
				}
			}
			if (int(collisionType) >= 0)
			{
				bricks[bestBrick].ExecuteBallCollision(ball, collisionType);
				soundBrick.Play();
			}
			if (paddle.BallCollision(ball))
			{
				soundPad.Play();
			}
			paddle.WallCollision(walls);
			int ballCollided = ball.WallCollision(walls);
			if (ballCollided > 0)
			{
				soundPad.Play();
			}
			else if (ballCollided < 0)
			{
				lives--;
				if (lives < 0)
				{
					gameOver = true;
				}
				else
				{
					ball.ReSpawn(paddle.GetRect());
					gamePaused = true;
				}
			}
		}
		else
		{
			if (wnd.kbd.KeyIsPressed(VK_SPACE))
			{
				ball.InitSpeed(Vec2(200, -300));
				gameStarted = true;
				gamePaused = false;
			}
			else
			{
				paddle.Update(wnd.kbd, deltaTime, ball, walls);
				paddle.WallCollision(walls);
			}
		}
	}
}

void Game::ComposeFrame()
{
	if (!gameStarted)
	{
		SpriteCodex::GameStart(Vec2(Graphics::ScreenWidth / 2 - 327, Graphics::ScreenHeight / 2 - 35), gfx);
	}
	else if (gameOver)
	{
		SpriteCodex::GameOver(Vec2(Graphics::ScreenWidth / 2 - 250, Graphics::ScreenHeight / 2 - 45), gfx);
	}
	paddle.Draw(gfx);
	ball.Draw(gfx);
	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}
	gfx.DrawBorder(walls, 4.0f, Colors::Blue);
	for (int i = 0; i < lives; i++)
	{
		lifePaddles[i].Draw(gfx);
	}
}
