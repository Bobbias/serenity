serenity_component(
    Roguelike
    RECOMMENDED
    TARGETS Roguelike
)

set(SOURCES
    Game.cpp
    main.cpp
)

serenity_app(Roguelike ICON app-roguelike)
target_link_libraries(Roguelike LibGfx LibConfig LibGUI LibMain)
