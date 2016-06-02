#pragma once

#include "novo/component.h"

namespace novo {
namespace component {

struct Controllable
{
	enum class Mode
	{
		SPACE,
		FPS
	};

	Controllable(Mode mode = Mode::FPS):
		mode(mode)
	{}

	Mode mode;
};
}}
