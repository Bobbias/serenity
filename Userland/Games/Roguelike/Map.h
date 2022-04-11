/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Player.h"
#include "Tile.h"
#include "Tileset.h"
#include <AK/FixedArray.h>
#include <AK/NonnullRefPtr.h>
#include <AK/Random.h>
#include <AK/RefCounted.h>
#include <AK/String.h>
#include <AK/Vector.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/Point.h>
#include <LibGfx/Rect.h>

#pragma once

#define __RL_DEBUG

namespace Roguelike {

enum class MapGenerator {
    SimpleRooms,
    SingleRoom,
};

class Map : public RefCounted<Map>
{
public:
    // Fixme: Map currently does not have a generic way to implement multiple dungeon generation algorithms.
    Map(int, int);

    [[nodiscard]] Tile& operator[](Gfx::IntPoint location) { return m_map_tiles[convert_intpoint_to_index(location)]; }
    [[nodiscard]] Tile operator[](Gfx::IntPoint location) const { return m_map_tiles[convert_intpoint_to_index(location)]; }

    int get_tile_size() const& { return m_tile_size; }
    Gfx::IntSize get_dimensions() const { return m_dimensions; }
    FixedArray<Roguelike::Tile>& get_tiles() { return m_map_tiles; }
    Vector<Gfx::IntRect>& get_rooms() { return m_rooms; }

private:
    FixedArray<Roguelike::Tile> m_map_tiles;
    const int m_tile_size { 16 };
    const Gfx::IntSize m_dimensions;

    const int max_rooms = 10;
    const int min_room_size = 5;
    const int max_room_size = 9;

    Vector<Gfx::IntRect> m_rooms {};

    void create_room(Gfx::IntRect room_rect)
    {
        #ifdef __RL_DEBUG
        dbgln("x{}, y{}, w{}, h{}", room_rect.x(), room_rect.y(), room_rect.width(), room_rect.height());
        #endif
        for (int y = room_rect.y() + 1; y < (room_rect.y() + room_rect.height() - 1); ++y) {
            for (int x = room_rect.x() + 1; x < (room_rect.x() + room_rect.width() - 1); ++x) {
                #ifdef __RL_DEBUG
                dbgln("{}, {} FLOOR", x, y);
                #endif
                VERIFY((size_t)(x + (m_dimensions.width() * y)) < m_map_tiles.size());
                m_map_tiles[x + (m_dimensions.width() * y)] = TileType::Floor;
            }
        }
    }

    void create_vertical_hall(Gfx::IntPoint point1, Gfx::IntPoint point2)
    {
        int y = min(point1.y(), point2.y());
        int end = max(point1.y(), point2.y());
        for (; y <= end; ++y) {
            m_map_tiles[point1.x() + (m_dimensions.width() * y)] = TileType::Floor;
        }
    }
    void create_horizontal_hall(Gfx::IntPoint point1, Gfx::IntPoint point2)
    {
        int x = min(point1.x(), point2.x());
        int end = max(point1.x(), point2.x());
        for (; x <= end; ++x) {
            m_map_tiles[x + (m_dimensions.width() * point1.y())] = TileType::Floor;
        }
    }
    void connect_rooms(Gfx::IntRect room1, Gfx::IntRect room2)
    {
        auto center1 = room1.center();
        auto center2 = room2.center();
        create_horizontal_hall(center1, { center2.x(), center1.y() });
        create_vertical_hall(center2, { center2.x(), center1.y() });
    }

    int convert_intpoint_to_index(Gfx::IntPoint& location) { return location.x() + (m_dimensions.width() * location.y()); }
    int convert_intpoint_to_index(Gfx::IntPoint const& location) const { return location.x() + (m_dimensions.width() * location.y()); }
};
}

template<>
struct AK::Formatter<Roguelike::Tile> : Formatter<FormatString> {
    ErrorOr<void> format(FormatBuilder& builder, Roguelike::Tile const& tile)
    {
        return Formatter<FormatString>::format(builder, "{}", tile.to_stringview());
    }
};

template<>
struct AK::Formatter<Roguelike::Tileset> : Formatter<FormatString> {
    ErrorOr<void> format(FormatBuilder& builder, Roguelike::Tileset const& tileset)
    {
        return Formatter<FormatString>::format(builder, "{}", tileset.get_file_path());
    }
};

template<>
struct AK::Formatter<Roguelike::Map> : Formatter<FormatString> {
    ErrorOr<void> format(FormatBuilder& builder, Roguelike::Map const& map)
    {
        return Formatter<FormatString>::format(builder, "{}", map.get_dimensions());
    }
};