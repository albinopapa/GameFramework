/****************************************************************************************** 
 *    Chili DirectX Framework Version 16.07.20                                              *    
 *    Game.h                                                                                *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <string>
#include <iostream>
#include <fstream>

class Game
{
public:
    Game( class MainWindow& wnd );
    Game( const Game& ) = delete;
    Game& operator=( const Game& ) = delete;
    void Go();
private:
    void ComposeFrame();
    void UpdateModel();
    /********************************/
    /*  User Functions              */
    void DrawBox(int x, int y, int w, int h, std::string color);
    void DrawVector(int mx, int my);
    void DrawCross();
    void DrawBullet(int mx, int my);
    void DrawRandomTarget();
    /********************************/
private:
    MainWindow& wnd;
    Graphics gfx;
    /********************************/
    /*  User Variables              */
    int x, y, mx, my;
    int target_y, target_x;
    const int target_w, target_h;
    float bullet_x, bullet_y;
    float speed;
    const int center_x, center_y;
    bool is_game_over;
    int score;
    bool do_rand;
    std::ofstream score_file;
    /********************************/
};
