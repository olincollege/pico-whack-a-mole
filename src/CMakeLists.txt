# If you have a program that's just a .c file and it has a main method, define
# an executable. If it has both a .c and .h file, make it a library. Also, link
# libraries appropriately here. Targets should be added in dependency order - if
# executable bar needs library foo, then you should do
#   add_library(foo foo.c foo.h)
#   add_executable(bar bar.c)
#   target_link_libraries(bar PRIVATE foo)
# or similar. The PRIVATE/INTERFACE/PUBLIC keyword will depend on whether the
# library is used only in function bodies (PRIVATE), only in function
# signatures/types (INTERFACE), or both (PUBLIC).


# cmake_minimum_required(VERSION 3.13)
# # initialize the SDK based on PICO_SDK_PATH
# # note: this must happen before project()
# include(pico_sdk_import.cmake)

# # initialize the Raspberry Pi Pico SDK
# pico_sdk_init()


add_library(keypad_ctrl
        keypad_ctrl.cpp
        keypad_ctrl.h
        )

add_library(game_ctrl
    game_ctrl.c
    game_ctrl.h
)

target_link_libraries(keypad_ctrl
    pico_rgb_keypad
    pico_stdlib
)

add_executable(main_loop
    main_loop.c
)

target_link_libraries(main_loop
    pico_stdlib
    keypad_ctrl
    game_ctrl
)

# Generate the UF2 file
pico_add_extra_outputs(main_loop)
