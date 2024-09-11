#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <cstddef>
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
const EntityID MAX_ENTITIES = 10240;

using ComponentID = std::size_t;
const ComponentID MAX_COMPONENTS = 16;

using Signature = std::bitset<MAX_COMPONENTS>;

#endif // !DEFINITIONS_HPP


