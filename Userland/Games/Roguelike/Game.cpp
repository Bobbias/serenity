/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Game.h"

namespace Roguelike {

Game::Game(){

};
void Game::resize_event(GUI::ResizeEvent&) {};
void Game::keydown_event(GUI::KeyEvent&){};
void Game::paint_event(GUI::PaintEvent&){};
void Game::timer_event(Core::TimerEvent&){};


}