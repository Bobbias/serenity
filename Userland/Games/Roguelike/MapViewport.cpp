/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "MapViewport.h"
#include <LibGUI/Painter.h>
#include <LibGfx/Font.h>
#include <LibGfx/FontDatabase.h>
#include <LibGfx/Palette.h>

namespace Roguelike {
MapViewport::MapViewport()
{
}

size_t MapViewport::rows() const
{
    TODO();
}

size_t MapViewport::columns() const
{
    TODO();
}

void MapViewport::resize_event(GUI::ResizeEvent&)
{
    resize();
}

void MapViewport::resize()
{
    TODO();
}

void MapViewport::keydown_event(GUI::KeyEvent& event)
{
    (void)event;
    // if (!on_move)
    //     return;

    // switch (event.key()) {
    // case KeyCode::Key_A:
    // case KeyCode::Key_Left:
    //     on_move(Game::Direction::Left);
    //     break;
    // case KeyCode::Key_D:
    // case KeyCode::Key_Right:
    //     on_move(Game::Direction::Right);
    //     break;
    // case KeyCode::Key_W:
    // case KeyCode::Key_Up:
    //     on_move(Game::Direction::Up);
    //     break;
    // case KeyCode::Key_S:
    // case KeyCode::Key_Down:
    //     on_move(Game::Direction::Down);
    //     break;
    // default:
    //     return;
    // }
}

void MapViewport::timer_event(Core::TimerEvent&)
{
    // if (slide_animation_frame < animation_duration) {
    //     slide_animation_frame++;
    //     update();
    // } else if (pop_in_animation_frame < animation_duration) {
    //     pop_in_animation_frame++;
    //     update();
    //     if (pop_in_animation_frame == animation_duration)
    //         stop_timer();
    // }
    TODO();
}

void MapViewport::paint_event(GUI::PaintEvent& event)
{
    Frame::paint_event(event);

    Color background_color = Color::from_rgb(0x000000);

    GUI::Painter painter(*this);
    painter.add_clip_rect(event.rect());
    painter.add_clip_rect(frame_inner_rect());
    painter.translate(frame_thickness(), frame_thickness());

    painter.fill_rect(rect(), background_color);
}
}