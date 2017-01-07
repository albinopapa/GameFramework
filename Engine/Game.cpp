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
#include <ctime>

/*
#include <iostream>
#include <fstream>
using namespace std;

int main () {
  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();
  return 0;
}
*/

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
    speed(3),
    target_x(0),
    target_y(0),
    target_w(30),
    target_h(30),
    is_game_over(false),
    score(0),
    do_rand(true)
{
    srand((unsigned int)time(NULL));
    DrawRandomTarget();
    bullet_x = (float)center_x;
    bullet_y = (float)center_y;
    std::ofstream score_file;
}

void Game::Go()
{
    gfx.BeginFrame();    
    UpdateModel();
    ComposeFrame();
    gfx.EndFrame();
}

void Game::DrawRandomTarget()
{
    if (do_rand)
    {
        target_x = rand() % (800 - target_w);
        target_y = rand() % (600 - target_h);
	do_rand = false;
    }
    DrawBox(target_x, target_y, target_w, target_h, "White");
}

void Game::UpdateModel()
{
}

void Game::DrawBullet(int mx, int my)
{
    const static int delta = 1;
    float cx = mx - (float)center_x; // cx = the x edge length of triangle
    float cy = my - (float)center_y; // cy = the y edge length of triangle
    float distance = sqrt(cx * cx + cy * cy);

    // Normalize
    float nx = cx / distance;
    float ny = cy / distance;

    float start_x = (float)center_x;
    float start_y = (float)center_y;

    // Draw bullet if inside screen
    // Destroy if outside
    bullet_x += nx * speed;
    bullet_y += ny * speed;
    if (bullet_x + 3 < 800 && bullet_x > 0 &&
        bullet_y + 3 < 600 && bullet_y > 0)
    {
        DrawBox((int)bullet_x, (int)bullet_y, 3, 3, "Pink");
    }
    else
    {
        score_file.open ("score.txt", std::ofstream::app);
        score_file << score << "\n===GAME OVER===\n";
        score_file.close();
        is_game_over = true;
    }
}

void Game::DrawVector(int mx, int my)
{
    const static int delta = 1;
    float cx = mx - (float)center_x; // cx = the x edge length of triangle
    float cy = my - (float)center_y; // cy = the y edge length of triangle
    float distance = sqrt(cx * cx + cy * cy);

    // Normalize
    float nx = cx / distance;
    float ny = cy / distance;

    float start_x = (float)center_x;
    float start_y = (float)center_y;

    for (int i = 0; i < 30; ++i)
    {
        gfx.PutPixel((int)start_x, (int)start_y, 255, 0, 255);
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

void Game::DrawBox(int x, int y, int w, int h, std::string color)
{
    if (x + w > 800 ||
        y + h > 600 ||
        x < 0 ||
        y < 0)
    {
        return;// Clamp
    }

    int r, g, b;
    if (color == "Pink")
    {
        r = 255, g = 0, b = 255;
    }
    else if (color == "White")
    {
        r = 255, g = 255, b = 255;
    }
	    
    int temp_x = x;
    int temp_y = y;
    for(int i = 0; i < h; ++i, ++y)
    {
        for (int j = 0; j < w; ++j, ++x)
        {
            gfx.PutPixel(x, y, r, g, b);
        }
        x = temp_x;
    }
}

void Game::ComposeFrame()
{
    DrawCross();
    if (is_game_over)
    {
        return;
    }
    if (wnd.mouse.IsInWindow())
    {
        if (wnd.mouse.LeftIsPressed())
        {
            mx = wnd.mouse.GetPosX();
            my = wnd.mouse.GetPosY();
            DrawBox(mx - 7, my - 7, 15, 15, "White");
            DrawVector(mx, my);
            DrawBullet(mx, my);
	    // Check to see if target is hit
            if (bullet_x > target_x &&
                bullet_x < target_x + target_w &&
                bullet_y > target_y &&
                bullet_y < target_y + target_h)
            {
                ++score;
                do_rand = true;
            }

            DrawRandomTarget();
        }
    }
}
