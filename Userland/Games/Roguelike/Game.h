/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "Player.h"
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
    NonnullRefPtr<Roguelike::Player> get_player();

private:
    NonnullRefPtr<Roguelike::Player> m_player = make_ref_counted<Player>();

    ErrorOr<void> try_move_player_to();
    ErrorOr<void> ensure_move_player_to();

    GameState m_current_game_state = { GameState::Play };
};
}