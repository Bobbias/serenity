/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibGfx/Point.h>
#include <LibGfx/Rect.h>

namespace Roguelike {
// using the sort of tricks mentioned here to enable helper functions and shit: https://stackoverflow.com/a/64138113
enum TileType {
    Wall,
    Floor,
    PlayerTile,
    EnemyTile,
    Invalid,
};

class Tile {
public:
    Tile() = default;
    constexpr Tile(TileType typ)
        : m_type(typ) {};

    [[nodiscard]] constexpr operator TileType() const { return m_type; };
    [[nodiscard]] constexpr bool operator==(Tile tile) const { return m_type == tile.m_type; }
    [[nodiscard]] constexpr bool operator!=(Tile tile) const { return m_type != tile.m_type; }
    [[nodiscard]] constexpr bool operator==(TileType tileType) const { return m_type == tileType; }
    [[nodiscard]] constexpr bool operator!=(TileType tileType) const { return m_type != tileType; }

    constexpr StringView to_stringview() const
    {
        switch (m_type) {
        case Roguelike::TileType::PlayerTile:
            return "Player"sv;
        case Roguelike::TileType::EnemyTile:
            return "Enemy"sv;
        case Roguelike::TileType::Floor:
            return "Floor"sv;
        case Roguelike::TileType::Wall:
            return "Wall"sv;
        case Roguelike::TileType::Invalid:
            return "Invalid"sv;
        default:
            VERIFY_NOT_REACHED();
        }
    }

    constexpr bool traversable() const
    {
        switch (m_type) {
        case Roguelike::TileType::PlayerTile:
            return false;
        case Roguelike::TileType::EnemyTile:
            return false;
        case Roguelike::TileType::Floor:
            return true;
        case Roguelike::TileType::Wall:
            return false;
        case Roguelike::TileType::Invalid:
            return false;
        default:
            VERIFY_NOT_REACHED();
        }
    }

private:
    TileType m_type;
};

}