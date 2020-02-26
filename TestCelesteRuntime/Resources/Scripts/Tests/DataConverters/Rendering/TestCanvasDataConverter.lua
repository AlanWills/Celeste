local CelesteAssert = require "CelesteAssert"


local TestCanvasDataConverter = { }
    
  local FILE_PATH = path.combine(TestResources.TempDirectory, "Test.xml")

  TestCanvasDataConverter.name = "Test Canvas Data Converter"
    
	-- Initialize/Cleanup
  ------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.testInitialize()
		Resources.unloadData(FILE_PATH)
	end

	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.testCleanup()
		Resources.unloadData(FILE_PATH)
	end
    
  ------------------------------------------------------------------------------------------------
  function TestCanvasDataConverter.converterRegistered()
    CelesteAssert.isTrue(LuaComponentDataConverter.hasConverter("Canvas"))
  end
    
  -- Projection Mode Attribute Tests
  ------------------------------------------------------------------------------------------------
  function TestCanvasDataConverter.hasProjectionModeAttribute()
    local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")

    CelesteAssert.hasAttribute(canvasDataConverter, "projection_mode")
  end

  ------------------------------------------------------------------------------------------------
  function TestCanvasDataConverter.projectionModeAttribute_IsString()
    local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
    local projectionModeAttribute = canvasDataConverter:findAttribute("projection_mode")

    CelesteAssert.attributeIsString(projectionModeAttribute)
  end
	
  ------------------------------------------------------------------------------------------------
  function TestCanvasDataConverter.projectionModeAttributeDefaultValue_IsPerspective()
    local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
    local projectionModeAttribute = canvasDataConverter:findAttribute("projection_mode")

    CelesteAssert.areEqual("Perspective", projectionModeAttribute:asString())
  end
    
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.projectionModeAttribute_IsNotRequired()
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		local projectionModeAttribute = canvasDataConverter:findAttribute("projection_mode")

		CelesteAssert.isFalse(projectionModeAttribute:isRequired())
	end
    
	-- Dimensions Attribute Tests
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.hasDimensionsAttribute()
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		
		CelesteAssert.hasAttribute(canvasDataConverter, "dimensions")
	end

	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.dimensionsAttribute_IsVec2()
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		local dimensionsAttribute = canvasDataConverter:findAttribute("dimensions")

		CelesteAssert.attributeIsVec2(dimensionsAttribute)
	end

	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.dimensionsAttributeDefaultValue_IsVec2One()
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		local dimensionsAttribute = canvasDataConverter:findAttribute("dimensions")

		CelesteAssert.areEqual(1, dimensionsAttribute:asVec2().x)
    CelesteAssert.areEqual(1, dimensionsAttribute:asVec2().y)
	end
    
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.dimensionsAttribute_IsRequired()
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		local dimensionsAttribute = canvasDataConverter:findAttribute("dimensions")

		CelesteAssert.isTrue(dimensionsAttribute:isRequired())
	end
    
	-- Convert From Xml Tests
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_InputtingPathToNonExistentFile_ReturnsFalse()
    local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")

    CelesteAssert.isFalse(canvasDataConverter:convertFromXML("WubbaLubbaDubDub"))
	end
    
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_InputtingPathToInvalidFile_ReturnsFalse()
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")

    CelesteAssert.isFalse(canvasDataConverter:convertFromXML(CanvasLoadingResources.Invalid))
	end

	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_InputtingPathToValidFile_ReturnsTrue()
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")

    CelesteAssert.isTrue(canvasDataConverter:convertFromXML(CanvasLoadingResources.Valid))
	end

	-- Convert Projection Mode Tests
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_NoProjectionModeAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		element:setAttribute("dimensions", "1, 1") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("projection_mode"))

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")

		CelesteAssert.isTrue(canvasDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_NoProjectionModeAttribute_SetsProjectionModeToPerspective()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		element:setAttribute("dimensions", "1, 1") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("projection_mode"))

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		canvasDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("Perspective", canvasDataConverter:findAttribute("projection_mode"):asString())
	end

	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_projectionModeAttribute_SetToEmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("projection_mode", "")
		document:insertFirstChild(element)

		local projectionModeAttr = element:findAttribute("projection_mode")

		CelesteAssert.isNotNil(projectionModeAttr)
		CelesteAssert.areEqual("", projectionModeAttr:asString())

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")

		CelesteAssert.isTrue(canvasDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_projectionModeAttribute_SetToEmptyString_SetsProjectionModeToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("projection_mode", "")
		document:insertFirstChild(element)

		local projectionModeAttr = element:findAttribute("projection_mode")

		CelesteAssert.isNotNil(projectionModeAttr)
		CelesteAssert.areEqual("", projectionModeAttr:asString())

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		canvasDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", canvasDataConverter:findAttribute("projection_mode"):asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_projectionModeAttribute_SetToNonEmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("projection_mode", "Perspective")
		document:insertFirstChild(element)

		local projectionModeAttr = element:findAttribute("projection_mode")

		CelesteAssert.isNotNil(projectionModeAttr)
		CelesteAssert.areEqual("Perspective", projectionModeAttr:asString())

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")

		CelesteAssert.isTrue(canvasDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_projectionModeAttribute_SetToNonEmptyString_SetsProjectionModeToCorrectValue()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("projection_mode", "Orthographic")
		document:insertFirstChild(element)

		local projectionModeAttr = element:findAttribute("projection_mode")

		CelesteAssert.isNotNil(projectionModeAttr)
		CelesteAssert.areEqual("Orthographic", projectionModeAttr:asString())

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		canvasDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("Orthographic", canvasDataConverter:findAttribute("projection_mode"):asString())
	end
    
	-- Convert Dimensions Tests
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_NoDimensionsAttribute_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("dimensions"))

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")

		CelesteAssert.isFalse(canvasDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_NoDimensionsAttribute_SetsDimensionsTo_Vec2One()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("dimensions"))

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		canvasDataConverter:convertFromXML(FILE_PATH)

		local dimensions = canvasDataConverter:findAttribute("dimensions")

		CelesteAssert.areEqual(1, dimensions:asVec2().x)
    CelesteAssert.areEqual(1, dimensions:asVec2().y)
	end

	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_DimensionsAttribute_WithEmptyString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		element:setAttribute("dimensions", "")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")

		CelesteAssert.isFalse(canvasDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_DimensionsAttribute_WithEmptyString_SetsDimensionsTo_Vec2One()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		element:setAttribute("dimensions", "")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		canvasDataConverter:convertFromXML(FILE_PATH)

		local dimensions = canvasDataConverter:findAttribute("dimensions")

		CelesteAssert.areEqual(1, dimensions:asVec2().x)
    CelesteAssert.areEqual(1, dimensions:asVec2().y)
	end
	
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_DimensionsAttribute_WithInvalidString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		element:setAttribute("dimensions", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")

		CelesteAssert.isFalse(canvasDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_DimensionsAttribute_WithInvalidString_SetsDimensionsTo_Vec2One()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		element:setAttribute("dimensions", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		canvasDataConverter:convertFromXML(FILE_PATH)

		local dimensions = canvasDataConverter:findAttribute("dimensions")

		CelesteAssert.areEqual(1, dimensions:asVec2().x)
    CelesteAssert.areEqual(1, dimensions:asVec2().y)
	end
	
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_DimensionsAttribute_WithValidString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		element:setAttribute("dimensions", "12, 35")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("12, 35", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")

		CelesteAssert.isTrue(canvasDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.convertFromXML_DimensionsAttribute_WithValidString_SetsDimensionsToCorrectValue()
		local document = XMLDocument.new()
		local element = document:newElement("Canvas")
		element:setAttribute("dimensions", "12, 35.2")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("12, 35.2", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		canvasDataConverter:convertFromXML(FILE_PATH)

		local dimensions = canvasDataConverter:findAttribute("dimensions")

		CelesteAssert.areEqual(vec2.new(12, 35.2), dimensions:asVec2())
	end

	-- SetValues Tests
  ------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.setValues_SetsProjectionModeToAttributeValue()
		local screen = TestCanvasDataConverter.Screen
    local gameObject = screen:allocateGameObject()
		local canvas = gameObject:addComponent("Canvas")

		CelesteAssert.isNotNil(canvas)
	  CelesteAssert.areEqual("Perspective", canvas:getProjectionMode())

		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		canvasDataConverter:convertFromXML(CanvasLoadingResources.Valid);

    CelesteAssert.hasAttribute(canvasDataConverter, "projection_mode")
		CelesteAssert.areEqual("Orthographic", canvasDataConverter:findAttribute("projection_mode"):asString())

		canvasDataConverter:setValues(canvas)

		CelesteAssert.areEqual("Orthographic", canvas:getProjectionMode())
	end

	------------------------------------------------------------------------------------------------
	function TestCanvasDataConverter.setValues_SetsDimensionsToAttributeValue()
		local screen = TestCanvasDataConverter.Screen
    local gameObject = screen:allocateGameObject()
		local canvas = gameObject:addComponent("Canvas")

		CelesteAssert.isNotNil(canvas)
	  CelesteAssert.areNotEqual(12, canvas:getDimensions().x)
    CelesteAssert.areNotEqual(34, canvas:getDimensions().y)

		local canvasDataConverter = LuaComponentDataConverter.getConverter("Canvas")
		canvasDataConverter:convertFromXML(CanvasLoadingResources.Valid);

    CelesteAssert.hasAttribute(canvasDataConverter, "dimensions")
		CelesteAssert.areEqual(12, canvasDataConverter:findAttribute("dimensions"):asVec2().x)
    CelesteAssert.areEqual(34, canvasDataConverter:findAttribute("dimensions"):asVec2().y)

		canvasDataConverter:setValues(canvas)

		CelesteAssert.areEqual(vec2.new(12, 34), canvas:getDimensions())
	end


return TestCanvasDataConverter