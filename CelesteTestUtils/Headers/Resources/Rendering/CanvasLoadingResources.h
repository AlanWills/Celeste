#pragma once

#include "Resources/TestResources.h"


namespace CelesteTestUtils
{
  #define TEST_CANVAS_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, CanvasData, ResourceRelativePath)

	class CanvasLoadingResources
	{
		DECLARE_TEST_RESOURCE_CLASS(CanvasLoadingResources)
		DECLARE_TEST_RESOURCE_DIRECTORY(CanvasData, "Canvas Data")

		TEST_CANVAS_DATA(Invalid, "Invalid.xml");
		TEST_CANVAS_DATA(Valid, "Valid.xml");
	};
}