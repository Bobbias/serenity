/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include <AK/Optional.h>
#include <AK/Random.h>
#include <AK/Vector.h>
#include <LibGUI/Application.h>
#include <LibGUI/Frame.h>
#include <LibGUI/Painter.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/Font.h>
#include <LibGfx/StandardCursor.h>

#pragma once

namespace Roguelike {

class Game final
{
public:
    Game(); // main ctor
    Game(Game const&) = default; // copy ctor

    virtual ~Game() override = default;

    enum class Direction {
        Up,
        Down,
        Left,
        Right,
    };

private:
    Roguelike::Player m_player { }

    ErrorOr<void> try_move_player_to();
    ErrorOr<void> ensure_move_player_to();
};

}