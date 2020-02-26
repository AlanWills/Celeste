#pragma once

#include "Serializers.h"
#include "Input/Key.h"
#include "Input/InputEnums.h"


namespace Celeste
{
	//------------------------------------------------------------------------------------------------
	template<>
	CelesteDllExport void serialize<Input::Key>(Input::Key key, std::string& output);
}