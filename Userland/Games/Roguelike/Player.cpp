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

Gfx::IntPoint const& Player::get_current_location() const
{
    return m_current_location;
}

void Player::set_current_location(Gfx::IntPoint const& new_location)
{
    m_current_location = new_location;
}

unsigned const& Player::get_current_health() const
{
    return m_current_health;
}

void Player::set_current_health(unsigned& new_health)
{
    if (new_health > m_maximum_health)
    {
        m_current_health = m_maximum_health;
    }
    else
    {
        m_current_health = new_health;
    }
}

void Player::set_maximum_health(unsigned& new_maximum)
{
    if (m_current_health > new_maximum) {
        m_maximum_health = new_maximum;
        m_current_health = m_maximum_health;
    } else {
        m_maximum_health = new_maximum;
    }
}

unsigned const& Player::get_maximum_health() const
{
    return m_maximum_health;
}


}