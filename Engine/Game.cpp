/****************************************************************************************** 
 *    Chili DirectX Framework Version 16.07.20                                              *    
 *    Game.cpp                                                                              *
 *    Copyright 2016 PlanetChili.net <http://www.planetchili.net>                           *
 *                                                                                          *
 *    This file is part of The Chili DirectX Framework.                                     *
 *                                                                                          *
 *    The Chili DirectX Framework is free software: you can redistribute it and/or modify   *
 *    it under the terms of the GNU General Public License as published by                  *
 *    the Free Software Foundation, either version 3 of the License, or                     *
 *    (at your option) any later version.                                                   *
 *                                                                                          *
 *    The Chili DirectX Framework is distributed in the hope that it will be useful,        *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of                        *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                         *
 *    GNU General Public License for more details.                                          *
 *                                                                                          *
 *    You should have received a copy of the GNU General Public License                     *
 *    along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
    :
    wnd( wnd ),
    gfx( wnd ),
    mx(0),
    my(0),
    x(0),
    y(0),
    center_x(400),
    center_y(300),
    speed(3)
{
    bullet_x = center_x;
    bullet_y = center_y;
}

void Game::Go()
{
    gfx.BeginFrame();    
    UpdateModel();
    ComposeFrame();
    gfx.EndFrame();
}

void Game::UpdateModel()
{
}

void Game::DrawBullet(int mx, int my)
{
    const static int delta = 1;
    float cx = mx - center_x; // cx = the x edge length of triangle
    float cy = my - center_y; // cy = the y edge length of triangle
    float distance = sqrt(cx * cx + cy * cy);

    // Normalize
    float nx = cx / distance;
    float ny = cy / distance;

    float start_x = center_x;
    float start_y = center_y;

    // Draw bullet if inside screen
    // Destroy if outside
    bullet_x += nx * speed;
    bullet_y += ny * speed;
    if (bullet_x < 800 && bullet_x > 0 &&
        bullet_y < 600 && bullet_y > 0)
    {
        gfx.PutPixel(bullet_x, bullet_y, 255, 0, 255);
    }
    else
    {
        bullet_x = center_x;
        bullet_y = center_y;
    }
}

void Game::DrawVector(int mx, int my)
{
    const static int delta = 1;
    float cx = mx - center_x; // cx = the x edge length of triangle
    float cy = my - center_y; // cy = the y edge length of triangle
    float distance = sqrt(cx * cx + cy * cy);

    // Normalize
    float nx = cx / distance;
    float ny = cy / distance;

    float start_x = center_x;
    float start_y = center_y;

    for (int i = 0; i < 30; ++i)
    {
        gfx.PutPixel(start_x, start_y, 255, 0, 255);
        start_x += nx * delta;
        start_y += ny * delta;
    }
}

void Game::DrawCross()
{
    for (int x = 0; x < 800; ++x)
    {
        gfx.PutPixel(x, 300, 190, 190, 190);
    }

    for (int y = 0; y < 600; ++y)
    {
        gfx.PutPixel(400, y, 190, 190, 190);
    }
}

void Game::DrawBox(int x, int y)
{
    int temp_x = x;
    int temp_y = y;
    for(int i = 0; i < 15; ++i, ++y)
    {
        for (int j = 0; j < 15; ++j, ++x)
        {
            gfx.PutPixel(x, y, 255, 255, 255);
        }
        x = temp_x;
    }
}

void Game::ComposeFrame()
{
    DrawCross();
    if (wnd.mouse.IsInWindow())
    {
        if (wnd.mouse.LeftIsPressed())
        {
            mx = wnd.mouse.GetPosX();
            my = wnd.mouse.GetPosY();
            DrawBox(mx - 7, my - 7);
            DrawVector(mx, my);
            DrawBullet(mx, my);
        }
    }
}
