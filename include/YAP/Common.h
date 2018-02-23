#pragma once

#include <YAP/Console.h>

#include <iostream>
#include <cassert>
#include <stdexcept>
#include <cstdint> // For types like int32_t

#define yap_unused __attribute__((unused))

#define YAP_UNUSED(var) (void)(var)
