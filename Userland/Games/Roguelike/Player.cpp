/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
// todo: consider creating LibRogue to contain all general roguelike stuff.
#include "Player.h"


namespace Roguelike{

Player::Player()
{

}

void Player::set_current_location(Gfx::IntPoint const& new_location)
{
    m_current_location = new_location;
}

}