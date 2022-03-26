/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/FixedArray.h>
#include <AK/NonnullRefPtr.h>
#include <AK/RefCounted.h>
#include <AK/String.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/Point.h>
#include <LibGfx/Rect.h>

#pragma once

namespace Roguelike {

// using the sort of tricks mentioned here to enable helper functions and shit: https://stackoverflow.com/a/64138113
enum TileType {
    Floor,
    Wall,
    Invalid,
};

class Tile {
public:
    Tile() = default;
    constexpr Tile(TileType typ)
        : type(typ) {};

    [[nodiscard]] operator TileType() const { return type; };
    [[nodiscard]] constexpr bool operator==(Tile tile) const { return type == tile.type; }
    [[nodiscard]] constexpr bool operator!=(Tile tile) const { return type != tile.type; }
    [[nodiscard]] constexpr bool operator==(TileType tileType) const { return type == tileType; }
    [[nodiscard]] constexpr bool operator!=(TileType tileType) const { return type != tileType; }

private:
    TileType type;
};

class Tileset : public RefCounted<Tileset> {
public:
    Tileset(String const&, String const&);

    void set_tile_count(int);
    int get_tile_count();
    Gfx::IntRect get_tile_rect();
    Gfx::IntRect rect();

    StringView get_file_path() const { return { m_path.characters(), m_path.length() }; };
    Gfx::IntRect get_tile_rect_at(Gfx::IntPoint location);

private:
    String m_name;
    String m_path;
    int m_tile_count {};
    Gfx::IntRect m_tile_rect { 0, 0, 16, 16 };
    Gfx::IntSize m_atlas_shape { 16, 16 };
    NonnullRefPtr<Gfx::Bitmap> m_map_tileset_bitmap { Gfx::Bitmap::try_load_from_file("/res/icons/roguelike/Cooz-curses-square-16x16.png").release_value_but_fixme_should_propagate_errors() };
};

class Map : public RefCounted<Map>
{
public:
    Map(int, int);

    [[nodiscard]] Tile& operator[](Gfx::IntPoint location) { return m_map_tiles[convert_intpoint_to_index(location)]; };
    [[nodiscard]] Tile operator[](Gfx::IntPoint location) const { return m_map_tiles[convert_intpoint_to_index(location)]; };
    int get_tile_size() const& { return m_tile_size; };

private:
    FixedArray<Roguelike::Tile> m_map_tiles;
    const int m_tile_size { 16 };

    static int convert_intpoint_to_index(Gfx::IntPoint& location) { return location.x() + (location.x() * location.y()); };
    static int convert_intpoint_to_index(Gfx::IntPoint const& location) { return location.x() + (location.x() * location.y()); };
};
}

template<>
struct AK::Formatter<Roguelike::Tile> : Formatter<FormatString> {
    ErrorOr<void> format(FormatBuilder& builder, Roguelike::Tile const& tile)
    {
        StringView tile_name;

        switch (tile) {
        case Roguelike::TileType::Floor:
            tile_name = "Floor"sv;
            break;
        case Roguelike::TileType::Wall:
            tile_name = "Wall"sv;
            break;
        case Roguelike::TileType::Invalid:
            tile_name = "Invalid"sv;
            break;
        default:
            VERIFY_NOT_REACHED();
        }

        return Formatter<FormatString>::format(builder, "{}", tile_name);
    }
};

template<>
struct AK::Formatter<Roguelike::Tileset> : Formatter<FormatString> {
    ErrorOr<void> format(FormatBuilder& builder, Roguelike::Tileset const& tileset)
    {
        return Formatter<FormatString>::format(builder, "{}", tileset.get_file_path());
    }
};
