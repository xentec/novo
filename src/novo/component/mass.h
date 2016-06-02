#pragma once

#include "novo/component.h"

namespace novo {
namespace component {

struct Mass
{
	Mass(f64 mass = 1.0): m(mass) {}
	f64	m;
};

}}
