project(simple)

# Set source files
set(SRC
        Simple.cpp
        Symbols.h
        Transitions.h
        )

add_executable(simple ${SRC})

target_link_libraries(simple YAP)
