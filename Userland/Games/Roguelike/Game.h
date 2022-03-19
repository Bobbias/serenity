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

class Game final : public GUI::Frame {
    C_OBJECT(Game);

public:
    Game(); // main ctor
    Game(Game const&) = default; // copy ctor
    Game& operator=(Game const&) = default;

    virtual ~Game() override = default;

private:
    virtual void resize_event(GUI::ResizeEvent&) override;
    virtual void paint_event(GUI::PaintEvent&) override;
    virtual void keydown_event(GUI::KeyEvent&) override;
    virtual void timer_event(Core::TimerEvent&) override;
};

}