/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Game.h"
#include <LibGUI/Frame.h>

namespace Roguelike
{
    class MapViewport final : public GUI::Frame {
        C_OBJECT(MapViewport);

    public:
        virtual ~MapViewport() override = default;
        

    private:
        explicit MapViewport();

        virtual void resize_event(GUI::ResizeEvent&) override;
        virtual void paint_event(GUI::PaintEvent&) override;
        virtual void keydown_event(GUI::KeyEvent&) override;
        virtual void timer_event(Core::TimerEvent&) override;

        size_t rows() const;
        size_t columns() const;

        NonnullRefPtr<Gfx::Bitmap> m_player_bitmap {Gfx::Bitmap::try_load_from_file("/res/icons/32x32/app-roguelike.png").release_value_but_fixme_should_propagate_errors()};

        void resize();

        static constexpr int frame_duration_ms = 1000 / 60;
    };
}