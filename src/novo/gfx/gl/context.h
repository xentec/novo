#pragma once

#include "object.h"

namespace novo {
namespace gl {

using Capability = glb::GLenum;

inline void enable(Capability cap) { glb::glEnable(cap); }
inline void disable(Capability cap) { glb::glDisable(cap); }

}}
