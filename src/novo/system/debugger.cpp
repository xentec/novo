#include "debugger.h"

#include "novo/gfx/gl/debug.h"

#include <iostream>

using namespace novo::system;

Debugger::Debugger()
{
	/*
	#if DEBUG > 2
		using glbinding::CallbackMask;

		lastGLCalls.set_capacity(2);
		glbinding::setCallbackMask(CallbackMask::Before | CallbackMask::ParametersAndReturnValue);
		glbinding::setBeforeCallback([&](const glbinding::FunctionCall& call)
		{
			std::stringstream cerr;
			cerr << call.function.name() << "(";
			for (unsigned i = 0; i < call.parameters.size(); ++i)
			{
				cerr << call.parameters[i]->asString();
				if (i < call.parameters.size() - 1)
					cerr << ", ";
			}
			cerr << ")";
			if (call.returnValue)
				cerr << " -> " << call.returnValue->asString();

			cerr.flush();
			lastGLCalls.push_back(cerr.str());
		});
		glbinding::setCallbackMask(glbinding::CallbackMask::None);

	#endif
	*/
}


