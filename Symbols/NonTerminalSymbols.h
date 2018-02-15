#pragma once

#include "Value.h"

using IntegerType = long long;

using Expr = Value<IntegerType, 'E', Symbol::Id::E>;
using Val = Value<IntegerType, 'V', Symbol::Id::VAL>;
