#pragma once

#include <cstddef>
#include <limits>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <cstdio>  
#include <bitset>
#include <queue>
#include <array>
#include <set>
#include <stdexcept>

using EntityID = std::size_t;
constexpr EntityID MAX_ENTITIES = 5120;

using ComponentID = std::size_t;
constexpr ComponentID MAX_COMPONENTS = 16;

using Signature = std::bitset<MAX_COMPONENTS>;


