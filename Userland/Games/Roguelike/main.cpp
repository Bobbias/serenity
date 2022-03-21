/*
 * Copyright (c) 2022, Blair Stacey
 * Copyright (c) 2022, Melissa Christie
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include "Game.h"
#include "MapViewport.h"
#include "Player.h"
#include <AK/NonnullRefPtr.h>
#include <LibConfig/Client.h>
#include <LibCore/System.h>
#include <LibGUI/Application.h>
#include <LibGUI/BoxLayout.h>
#include <LibGUI/Icon.h>
#include <LibGUI/Statusbar.h>
#include <LibGUI/Window.h>
#include <LibGfx/Forward.h>
#include <LibGfx/Point.h>
#include <LibMain/Main.h>
#include <stdio.h>
#include <time.h>

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    TRY(Core::System::pledge("stdio recvfd sendfd rpath unix"));

    auto app = TRY(GUI::Application::try_create(arguments));
    auto app_icon = TRY(GUI::Icon::try_create_default_icon("app-roguelike"));

    Config::pledge_domain("Roguelike");

    TRY(Core::System::pledge("stdio recvfd sendfd rpath"));

    TRY(Core::System::unveil("/res", "r"));
    TRY(Core::System::unveil(nullptr, nullptr));

    app->set_quit_when_last_window_deleted(true);

    auto window = TRY(GUI::Window::try_create());
    window->set_title("Roguelike");
    window->set_double_buffering_enabled(false);
    auto main_widget = TRY(window->try_set_main_widget<GUI::Widget>());
    main_widget->set_fill_with_background_color(true);
    
    (void)TRY(main_widget->try_set_layout<GUI::VerticalBoxLayout>());

    auto game = Roguelike::Game::construct();
    

    auto viewport = TRY(main_widget->try_add<Roguelike::MapViewport>(game));
    viewport->set_focus(true);

    auto statusbar = TRY(main_widget->try_add<GUI::Statusbar>());

    window->set_icon(app_icon.bitmap_for_size(16));
    window->show();

    return app->exec();
}