#include "Reductions.h"
#include "Reduction.h"
#include "../Symbols/NonTerminalSymbols.h"

// E -> E + E
const Reduction r2(
        [](Automata &automata, unused Symbol::Ptr const &symbol) -> bool {
            Symbol::Ptr s1 = automata.PopSymbol();
            automata.PopSymbol();
            Symbol::Ptr s3 = automata.PopSymbol();

            Expr const *e1 = dynamic_cast<Expr *>(s1.get());
            Expr const *e3 = dynamic_cast<Expr *>(s3.get());
            assert(s1->id() == Symbol::Id::E && e1);
            assert(s3->id() == Symbol::Id::E && e3);

            auto result = Expr::Create(e1->GetValue() + e3->GetValue());

            automata.Reduce(3, result);
            return true;
        }
);

// E -> E * E
const Reduction r3(
        [](Automata &automata, unused Symbol::Ptr const &symbol) -> bool {
            Symbol::Ptr s1 = automata.PopSymbol();
            automata.PopSymbol();
            Symbol::Ptr s3 = automata.PopSymbol();

            Expr const *e1 = dynamic_cast<Expr *>(s1.get());
            Expr const *e3 = dynamic_cast<Expr *>(s3.get());
            assert(s1->id() == Symbol::Id::E && e1);
            assert(s3->id() == Symbol::Id::E && e3);

            auto result = Expr::Create(e1->GetValue() * e3->GetValue());

            automata.Reduce(3, result);
            return true;
        }
);


// E -> ( E )
const Reduction r4(
        [](Automata &automata, unused Symbol::Ptr const &symbol) -> bool {
            automata.PopSymbol();
            Symbol::Ptr s2 = automata.PopSymbol();
            automata.PopSymbol();

            Expr const *e2 = dynamic_cast<Expr *>(s2.get());
            assert(s2->id() == Symbol::Id::E && e2);

            automata.Reduce(3, Expr::Create(e2->GetValue()));
            return true;
        }
);

// E -> val
const Reduction r5(
        [](Automata &automata, unused Symbol::Ptr const &symbol) -> bool {
            Symbol::Ptr s = automata.PopSymbol();
            auto *val = dynamic_cast<Val *>(s.get());
            assert(s->id() == Symbol::Id::VAL && val);
            automata.Reduce(1, Expr::Create(val->GetValue()));
            return true;
        }
);
