#pragma once

#include "novo/component.h"
#include "novo/gfx/screen.h"

namespace novo {
namespace component {

struct Screen
{
	Screen(gfx::Screen* screen): screen(screen) {}

	gfx::Screen* screen;
};

}}
