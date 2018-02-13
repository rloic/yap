#include "Shifts.h"
#include "Shift.h"

const Shift accept(
        [](unused Automata &automata, unused Symbol::Ptr const &symbol) -> bool {
            return false;
        }
);
const Shift skip(
        [](unused Automata &automata, Symbol::Ptr const &symbol) -> bool {
            std::cout << GRAS JAU << "[Warn] " << RESET JAU << "Skipping unexpected token: " << RESET JAU << *symbol << RESET << std::endl;
            return true;
        }
);
const Shift d2(
        [](Automata &automata, Symbol::Ptr const &symbol) -> bool {
            automata.Shift(symbol, State::State2);
            return true;
        }
);
const Shift d3(
        [](Automata &automata, Symbol::Ptr const &symbol) -> bool {
            automata.Shift(symbol, State::State3);
            return true;
        }
);
const Shift d4(
        [](Automata &automata, Symbol::Ptr const &symbol) -> bool {
            automata.Shift(symbol, State::State4);
            return true;
        }
);
const Shift d5(
        [](Automata &automata, Symbol::Ptr const &symbol) -> bool {
            automata.Shift(symbol, State::State5);
            return true;
        }
);

const Shift d9(
        [](Automata &automata, Symbol::Ptr const &symbol) -> bool {
            automata.Shift(symbol, State::State9);
            return true;
        }
);