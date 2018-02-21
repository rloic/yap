
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples/simple)

# Set source files
set(SRC
        ${SRCROOT}/Simple.cpp
        ${SRCROOT}/Symbols.h
        ${SRCROOT}/Transitions.h
        )

add_executable(simple ${SRC})

target_link_libraries(simple YAP)
