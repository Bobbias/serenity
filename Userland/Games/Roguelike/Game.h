/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "Player.h"
#include "Map.h"
#include <AK/Optional.h>
#include <AK/Random.h>
#include <AK/RefCounted.h>
#include <AK/Vector.h>
#include <LibGUI/Application.h>
#include <LibGUI/Frame.h>
#include <LibGUI/Painter.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/Font.h>
#include <LibGfx/Forward.h>
#include <LibGfx/Point.h>
#include <LibGfx/StandardCursor.h>

#pragma once

namespace Roguelike {

class Game final : public RefCounted<Game>
{

public:
    Game(); // main ctor
    Game(Game const&) = default; // copy ctor

    // virtual ~Game() override = default;

    enum class Direction {
        Up,
        Down,
        Left,
        Right,
    };

    enum class GameState {
        Play,
    };

    GameState get_current_game_state();
    void set_current_game_state(GameState);
    NonnullRefPtr<Roguelike::Player> get_player() { return m_player; }
    NonnullRefPtr<Roguelike::Map> get_map() { return m_map; }
    NonnullRefPtr<Roguelike::Tileset> get_tileset() { return m_tileset; }

private:
    const size_t m_map_width { 16 };
    const size_t m_map_height { 16 };
    
    NonnullRefPtr<Roguelike::Player> m_player = make_ref_counted<Roguelike::Player>();
    NonnullRefPtr<Roguelike::Map> m_map = make_ref_counted<Roguelike::Map>(m_map_width, m_map_height);
    NonnullRefPtr<Roguelike::Tileset> m_tileset = make_ref_counted<Roguelike::Tileset>("Cooz curses square 16x16", "/res/icons/roguelike/Cooz-curses-square-16x16.png");

    ErrorOr<void> try_move_player_to();
    ErrorOr<void> ensure_move_player_to();

    GameState m_current_game_state = { GameState::Play };
};
}