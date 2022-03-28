/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "Map.h"

namespace Roguelike
{
Tileset::Tileset(String const& name, String const& path)
    : m_name(name)
    , m_path(path)
{
}

Gfx::IntRect Tileset::rect()
{
    return m_map_tileset_bitmap->rect();
}

Gfx::IntRect Tileset::get_tile_rect_at(Gfx::IntPoint location)
{
    auto new_location = m_tile_rect.translated(location.x() * m_tile_rect.width(), location.y() * m_tile_rect.height());
    return new_location;
}

Map::Map(int width, int height)
    : m_map_tiles(FixedArray<Tile>::try_create(width * height).release_value_but_fixme_should_propagate_errors())
    , m_dimensions({ width, height })
{  
};
}