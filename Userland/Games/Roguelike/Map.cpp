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
    : m_map_tiles(FixedArray<Tile>::try_create(width * height).release_value_but_fixme_should_propagate_errors())
    , m_dimensions({ width, height })
{
    unsigned room_number = 0;
    while (room_number < 10) {
        int x = get_random_uniform(m_dimensions.width() - 6);
        int y = get_random_uniform(m_dimensions.height() - 5);

        bool intersects = false;
        Gfx::IntRect room { { x, y }, { 6, 5 } };
        for (auto existing_room : m_rooms)
        {
            if(room.intersects(existing_room))
            {
                intersects = true;
                #ifdef __RL_DEBUG
                dbgln("Intersecting rooms: {} {}", existing_room, room);
                #endif
            }
        }

        if(intersects){
            continue;
        }

        m_rooms.append(room);
        ++room_number;
    }
    for (auto room : m_rooms) {
        create_room(room);
    }

    for (unsigned i = 0; i < (m_rooms.size() - 1); ++i)
    {
        connect_rooms(m_rooms[i], m_rooms[i+1]);
    }
};
}