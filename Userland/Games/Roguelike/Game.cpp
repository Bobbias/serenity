/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Player.h"
#include "Game.h"

namespace Roguelike {

Game::Game() {

};

NonnullRefPtr<Roguelike::Player> Game::get_player() { return m_player; }

Game::GameState Game::get_current_game_state() { return m_current_game_state; };

void Game::set_current_game_state(Game::GameState new_state)
{
    m_current_game_state = new_state;
};
}