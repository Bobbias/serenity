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
    
    NonnullRefPtr<Player> player = m_game.get_player();
    Gfx::IntPoint current_location = player->get_current_location();
    Gfx::IntPoint new_location;
    switch (event.key()) {
    case Key_Left:
        dbgln("Key Pressed: {}", key_code_to_string(event.key()));
        dbgln("Current loc: {}", current_location);
        new_location = Gfx::IntPoint(current_location.translated(-1, 0));
        dbgln("New loc: {}", new_location);
        player->set_current_location(new_location);
        update();
        break;
    case Key_Right:
        dbgln("Key Pressed: {}", key_code_to_string(event.key()));
        dbgln("Current loc: {}", current_location);
        new_location = Gfx::IntPoint(current_location.translated(1, 0));
        dbgln("New loc: {}", new_location);
        player->set_current_location(new_location);
        update();
        break;
    default:
        break;
    }
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

    auto dest_rect = Gfx::Rect(m_game.get_player()->get_current_location(), m_player_bitmap->rect().size());
    painter.draw_scaled_bitmap(dest_rect, *m_player_bitmap, m_player_bitmap->rect());
}
}