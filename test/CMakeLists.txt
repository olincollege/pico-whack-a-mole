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


add_executable(test_which_button
    test_which_button.c
)

target_link_libraries(test_which_button
    pico_stdlib
    keypad_ctrl
    game_ctrl
    scoring
)

add_executable(verify_button_press
verify_button_press.c
)

target_link_libraries(verify_button_press
    pico_stdlib
    keypad_ctrl
    game_ctrl
    scoring
)

# Generate the UF2 file
pico_add_extra_outputs(test_which_button)

# Generate the UF2 file
pico_add_extra_outputs(verify_button_press)
