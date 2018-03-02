project(CalcWithVars)

# Set source files
set(SRC
        CalcWithVars.cpp
        Symbols.h
        Transitions.h
        NamedVariableSymbol.h
        NamedConstSymbol.h
        )

add_executable(calcWithVars ${SRC})

target_link_libraries(calcWithVars YAP)
