/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Tile.h"
#include <AK/NonnullRefPtr.h>
#include <AK/RefCounted.h>
#include <AK/String.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/Point.h>
#include <LibGfx/Rect.h>

namespace Roguelike {
class Tileset : public RefCounted<Tileset> {
private:
    String m_name;
    String m_path;
    int m_tile_count {};
    const int m_tile_rect_x = 0;
    const int m_tile_rect_y = 0;
    const int m_tile_rect_width = 16;
    const int m_tile_rect_height = 16;
    Gfx::IntRect m_tile_rect { m_tile_rect_x, m_tile_rect_y, m_tile_rect_width, m_tile_rect_height };
    Gfx::IntSize m_atlas_shape { 16, 16 };
    NonnullRefPtr<Gfx::Bitmap> m_map_tileset_bitmap;

    constexpr Gfx::IntRect get_character_rect(char& character) const
    {
        switch (character) {
        case '0':
            return get_tile_rect_at(0, 3);
        case '1':
            return get_tile_rect_at(1, 3);
        case '2':
            return get_tile_rect_at(2, 3);
        case '3':
            return get_tile_rect_at(3, 3);
        case '4':
            return get_tile_rect_at(4, 3);
        case '5':
            return get_tile_rect_at(5, 3);
        case '6':
            return get_tile_rect_at(6, 3);
        case '7':
            return get_tile_rect_at(7, 3);
        case '8':
            return get_tile_rect_at(8, 3);
        case '9':
            return get_tile_rect_at(9, 3);
        case 'A':
            return get_tile_rect_at(1, 4);
        case 'B':
            return get_tile_rect_at(2, 4);
        case 'C':
            return get_tile_rect_at(3, 4);
        case 'D':
            return get_tile_rect_at(4, 4);
        case 'E':
            return get_tile_rect_at(5, 4);
        case 'F':
            return get_tile_rect_at(6, 4);
        case 'G':
            return get_tile_rect_at(7, 4);
        case 'H':
            return get_tile_rect_at(8, 4);
        case 'I':
            return get_tile_rect_at(9, 4);
        case 'J':
            return get_tile_rect_at(10, 4);
        case 'K':
            return get_tile_rect_at(11, 4);
        case 'L':
            return get_tile_rect_at(12, 4);
        case 'M':
            return get_tile_rect_at(13, 4);
        case 'N':
            return get_tile_rect_at(14, 4);
        case 'O':
            return get_tile_rect_at(15, 4);
        case 'P':
            return get_tile_rect_at(0, 5);
        case 'Q':
            return get_tile_rect_at(1, 5);
        case 'R':
            return get_tile_rect_at(2, 5);
        case 'S':
            return get_tile_rect_at(3, 5);
        case 'T':
            return get_tile_rect_at(4, 5);
        case 'U':
            return get_tile_rect_at(5, 5);
        case 'V':
            return get_tile_rect_at(6, 5);
        case 'W':
            return get_tile_rect_at(7, 5);
        case 'X':
            return get_tile_rect_at(8, 5);
        case 'Y':
            return get_tile_rect_at(9, 5);
        case 'Z':
            return get_tile_rect_at(10, 5);
        case 'a':
            return get_tile_rect_at(1, 6);
        case 'b':
            return get_tile_rect_at(2, 6);
        case 'c':
            return get_tile_rect_at(3, 6);
        case 'd':
            return get_tile_rect_at(4, 6);
        case 'e':
            return get_tile_rect_at(5, 6);
        case 'f':
            return get_tile_rect_at(6, 6);
        case 'g':
            return get_tile_rect_at(7, 6);
        case 'h':
            return get_tile_rect_at(8, 6);
        case 'i':
            return get_tile_rect_at(9, 6);
        case 'j':
            return get_tile_rect_at(10, 6);
        case 'k':
            return get_tile_rect_at(11, 6);
        case 'l':
            return get_tile_rect_at(12, 6);
        case 'm':
            return get_tile_rect_at(13, 6);
        case 'n':
            return get_tile_rect_at(14, 6);
        case 'o':
            return get_tile_rect_at(15, 6);
        case 'p':
            return get_tile_rect_at(0, 7);
        case 'q':
            return get_tile_rect_at(1, 7);
        case 'r':
            return get_tile_rect_at(2, 7);
        case 's':
            return get_tile_rect_at(3, 7);
        case 't':
            return get_tile_rect_at(4, 7);
        case 'u':
            return get_tile_rect_at(5, 7);
        case 'v':
            return get_tile_rect_at(6, 7);
        case 'w':
            return get_tile_rect_at(7, 7);
        case 'x':
            return get_tile_rect_at(8, 7);
        case 'y':
            return get_tile_rect_at(9, 7);
        case 'z':
            return get_tile_rect_at(10, 7);
        default:
            return get_tile_rect_at(0, 0);
        }
    }

public:
    Tileset(String const&, String const&);

    void set_tile_count(int);
    int get_tile_count() const;

    constexpr Gfx::IntRect get_tile_rect(Tile const& tile)
    {
        switch (tile) {
        case TileType::PlayerTile:
            return get_tile_rect_at(1, 0);
        case TileType::EnemyTile:
            return get_tile_rect_at(14, 14);
        case TileType::Floor:
            return get_tile_rect_at(0, 0);
        case TileType::Wall:
            return get_tile_rect_at(11, 13);
        case TileType::Invalid:
            return get_tile_rect_at(13, 10);
        default:
            VERIFY_NOT_REACHED();
        }
    }

    Gfx::IntRect rect();

    StringView get_file_path() const;

    constexpr Gfx::IntRect get_tile_rect_at(const int x, const int y) const
    {
        return Gfx::IntRect({ { x * m_tile_rect_width, y * m_tile_rect_height }, { m_tile_rect_width, m_tile_rect_height } });
    }

    NonnullRefPtr<Gfx::Bitmap> get_bitmap() const;

};

}