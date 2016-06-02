#pragma once

#include "novo/global.h"
#include "debug.h"

#include <unordered_map>

namespace novo {
namespace gl {
namespace names {

static const std::unordered_map<glb::GLenum, string>
debug {
	// Source
	{debug::Source::API, "API"},
	{debug::Source::WindowSystem, "Window System"},
	{debug::Source::ShaderCompiler, "Shader Compiler"},
	{debug::Source::ThirdParty, "Third Party"},
	{debug::Source::Application, "Application"},
	{debug::Source::Other, "Other"},
	// Type
	{debug::Type::Error, "Error"},
	{debug::Type::Deprecated, "Deprecated"},
	{debug::Type::Undefined, "Undefined"},
	{debug::Type::Portability, "Portability"},
	{debug::Type::Performance, "Performance"},
	{debug::Type::Other, "Other"},
	{debug::Type::Marker, "Marker"},
	// Severity
	{debug::Severity::High, "High"},
	{debug::Severity::Medium, "Medium"},
	{debug::Severity::Low, "Low"},
	{debug::Severity::Notification, "Notify"},
};

}}}
