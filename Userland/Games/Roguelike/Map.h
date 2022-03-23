/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/RefCounted.h>
#include <AK/FixedArray.h>
#include <LibGfx/Point.h>

#pragma once

namespace Roguelike {

// using the sort of tricks mentioned here to enable helper functions and shit: https://stackoverflow.com/a/64138113
enum TileType {
    Floor,
    Wall,
};

class Tile {
public:
    Tile() = default;
    constexpr Tile(TileType typ)
        : type(typ) {};

    operator TileType() const { return type; };
    constexpr bool operator==(Tile tile) const { return type == tile.type; }
    constexpr bool operator!=(Tile tile) const { return type != tile.type; }
    constexpr bool operator==(TileType tileType) const { return type == tileType; }
    constexpr bool operator!=(TileType tileType) const { return type != tileType; }

    // consider adding a to_image function to retrieve the associated image?

private:
    TileType type;
};

class Map : RefCounted<Map>
{
public:
    Map(int, int);

    [[nodiscard]] Tile& operator[](Gfx::IntPoint location) { return m_map_tiles[convert_intpoint_to_index(location)]; };
    [[nodiscard]] Tile operator[](Gfx::IntPoint location) const { return m_map_tiles[convert_intpoint_to_index(location)]; };

private:
    FixedArray<Tile> m_map_tiles;

    static int convert_intpoint_to_index(Gfx::IntPoint& location) { return location.x() + (location.x() * location.y()); };
    static int convert_intpoint_to_index(Gfx::IntPoint const& location) { return location.x() + (location.x() * location.y()); };
};
}