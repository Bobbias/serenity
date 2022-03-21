/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Game.h"
#include "MapViewport.h"
#include <AK/NonnullRefPtr.h>
#include <LibGUI/Painter.h>
#include <LibGfx/Font.h>
#include <LibGfx/FontDatabase.h>
#include <LibGfx/Palette.h>

namespace Roguelike {
MapViewport::MapViewport(Game& game)
    : m_game(game)
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
    // TODO();
}

void MapViewport::keydown_event(GUI::KeyEvent& event)
{
    (void)event;
}

void MapViewport::timer_event(Core::TimerEvent&)
{
    TODO();
}

void MapViewport::paint_event(GUI::PaintEvent& event)
{
    Frame::paint_event(event);

    Color background_color = Color::from_rgb(0xFF0000);

    GUI::Painter painter(*this);
    painter.add_clip_rect(event.rect());
    painter.add_clip_rect(frame_inner_rect());
    painter.translate(frame_thickness(), frame_thickness());

    painter.fill_rect(rect(), background_color);
    painter.draw_text(event.rect(), "Hello World!"sv, Gfx::TextAlignment::Center, Color::from_rgb(0xFFFFFF));


    
    painter.draw_scaled_bitmap(m_player_bitmap->rect(), *m_player_bitmap, m_player_bitmap->rect());

}
}