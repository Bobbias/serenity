/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Game.h"
#include "Map.h"
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
    
    NonnullRefPtr<Roguelike::Player> player = m_game.get_player();
    Gfx::IntPoint current_location = player->get_current_location();
    Gfx::IntPoint new_location;

    NonnullRefPtr<Roguelike::Tileset> tileset = m_game.get_tileset();
    Roguelike::Map& map = m_game.get_map();

    switch (event.key()) {
    case Key_Left:
        new_location = current_location.translated(-1, 0);
        break;
    case Key_Up:
        new_location = current_location.translated(0, -1);
        break;
    case Key_Right:
        new_location = current_location.translated(1, 0);
        break;
    case Key_Down:
        new_location = current_location.translated(0, 1);
        break;
    case Key_Q:
        dbgln("Tile at: {} : {} {} : {}", current_location, tileset->get_tile_rect_at(current_location.x(), current_location.y()), tileset->get_file_path(), map[current_location]);
        break;
    default:
        break;
    }
    if (map[new_location].traversable()) {
        player->set_current_location(new_location);
        update();
    }
}

void MapViewport::timer_event(Core::TimerEvent&)
{
    TODO();
}

void MapViewport::paint_event(GUI::PaintEvent& event)
{
    Frame::paint_event(event);

    Color background_color = Color::from_rgb(0x000000);
    Color outside_map_color = Color::from_rgb(0x2E2E2E);

    GUI::Painter painter(*this);
    painter.add_clip_rect(event.rect());
    painter.add_clip_rect(frame_inner_rect());
    painter.translate(frame_thickness(), frame_thickness());

    auto map = m_game.get_map();
    auto tileset = m_game.get_tileset();
    auto tile_size = tileset->get_tile_rect(Roguelike::TileType::PlayerTile).size();

    // Note: Consider whether it's better to use the Rect<T>::shatter method instead first painting the background
    //       and then painting over it. I think this depends on whether the painter is smart enough to automatically
    //       detect this behavior or not.
    painter.fill_rect(rect(), outside_map_color);
    painter.fill_rect({{0, 0}, map->get_dimensions() * map->get_tile_size()}, background_color);


    Gfx::IntRect dest_rect;
    Tile tile;
    for (int y = 0; y < map->get_dimensions().height(); ++y) {
        for (int x = 0; x < map->get_dimensions().width(); ++x)
        {
            dest_rect = Gfx::Rect({ x * tile_size.width(), y * tile_size.height() }, tile_size);
            tile = (*map)[Gfx::IntPoint { x, y }];
            painter.draw_scaled_bitmap(dest_rect, tileset->get_bitmap(), tileset->get_tile_rect(tile));
        }
    }
    auto player_location = m_game.get_player()->get_current_location();
    dest_rect = Gfx::Rect({player_location.x() * tile_size.width(), player_location.y() * tile_size.height()}, tile_size);
    
    painter.draw_scaled_bitmap(dest_rect, tileset->get_bitmap(), tileset->get_tile_rect(Roguelike::TileType::PlayerTile));
}
}
