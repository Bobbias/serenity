/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Enemy.h"

namespace Roguelike {
void Enemy::set_current_location(Gfx::IntPoint const& new_location)
{
    m_current_location = new_location;
}

unsigned const& Enemy::get_current_health() const
{
    return m_current_health;
}

void Enemy::set_current_health(unsigned& new_health)
{
    if (new_health > m_maximum_health) {
        m_current_health = m_maximum_health;
    } else {
        m_current_health = new_health;
    }
}

void Enemy::set_maximum_health(unsigned& new_maximum)
{
    if (m_current_health > new_maximum) {
        m_maximum_health = new_maximum;
        m_current_health = m_maximum_health;
    } else {
        m_maximum_health = new_maximum;
    }
}

unsigned const& Enemy::get_maximum_health() const
{
    return m_maximum_health;
}
}