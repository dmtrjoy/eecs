#ifndef EECS_SYSTEM_HPP
#define EECS_SYSTEM_HPP

#include "world.hpp"

namespace eecs {

using system = void (*)(world&);

} // namespace eecs

#endif
