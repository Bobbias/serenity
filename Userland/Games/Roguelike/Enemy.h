/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/RefCounted.h>
#include <LibGfx/Point.h>

namespace Roguelike {

enum class EnemyType {
    Goblin,
    Orc,
};

class Enemy : public RefCounted<Enemy> {
private:
    Gfx::IntPoint m_current_location { 0, 0 };
    unsigned m_maximum_health { 20 };
    unsigned m_current_health { 20 };

public:
    Enemy();
    virtual ~Enemy() = default;

    unsigned const& get_current_health() const;
    void set_current_health(unsigned&);
    unsigned const& get_maximum_health() const;
    void set_maximum_health(unsigned&);

    Gfx::IntPoint& get_current_location() const;
    void set_current_location(Gfx::IntPoint const&);
};

}