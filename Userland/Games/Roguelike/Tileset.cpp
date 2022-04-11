/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Tileset.h"

namespace Roguelike
{
Tileset::Tileset(String const& name, String const& path)
    : m_name(name)
    , m_path(path)
    , m_map_tileset_bitmap(Gfx::Bitmap::try_load_from_file("/res/icons/roguelike/Cooz-curses-square-16x16.png").release_value_but_fixme_should_propagate_errors())
{
}

void Tileset::set_tile_count(int new_count)
{
    m_tile_count = new_count;
}

int Tileset::get_tile_count() const
{
    return m_tile_count;
}

Gfx::IntRect Tileset::rect() {
    return m_map_tileset_bitmap->rect();
}

StringView Tileset::get_file_path() const
{
    return { m_path.characters(), m_path.length() };
}

NonnullRefPtr<Gfx::Bitmap> Tileset::get_bitmap() const
{
    return m_map_tileset_bitmap;
}

}