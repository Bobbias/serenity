/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
// todo: consider creating LibRogue to contain all general roguelike stuff.
#include "Player.h"



Player::Player()
{
}

Player::Player(u32 maximum_health)
    : m_maximum_health(maximum_health)
    , m_current_health(maximum_health)
{
}

Player::Player(u32 maximum_health, u32 current_health)
    : m_maximum_health(maximum_health)
    , m_current_health(current_health)
{
}

Player::~Player()
{
}


