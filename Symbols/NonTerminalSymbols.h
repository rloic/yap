#pragma once

#include "ValuedSymbol.h"

using IntegerType = long long;

using Expr = ValuedSymbol<IntegerType, 'E', Symbol::Id::E>;
using Val = ValuedSymbol<IntegerType, 'V', Symbol::Id::VAL>;
