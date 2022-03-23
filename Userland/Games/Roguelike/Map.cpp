/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "Map.h"

namespace Roguelike
{
Map::Map(int width, int height)
    : m_map_tiles(FixedArray<Tile>::try_create(width * height).release_value_but_fixme_should_propagate_errors()) {};
}