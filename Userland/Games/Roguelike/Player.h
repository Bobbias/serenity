/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/Types.h>
#include <libgfx/Point.h>

#pragma once

namespace Roguelike
{
class Player
{
private:
    IntPoint m_current_location{ 0, 0 };
    u32 m_current_health { 20 };
    u32 m_maximum_health { 20 };

public:
    explicit Player();
    explicit Player(u32);
    explicit Player(u32, u32);
    ~Player();

    u32 get_current_health() { return m_current_health; };
    u32 get_maximum_health() { return m_maximum_health; };
    IntPoint get_current_location() { return m_current_location; };

};
}
