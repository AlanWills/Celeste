local CelesteAssert = require "CelesteAssert"


local TestEllipseColliderDataConverter = { }
    
    local FILE_PATH = path.combine(TestResources.TempDirectory, "Test.xml")

    TestEllipseColliderDataConverter.name = "Test Ellipse Collider Data Converter"
    
	-- Initialize/Cleanup
    ------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.testInitialize()
		Resources.unloadData(FILE_PATH)
	end

	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.testCleanup()
		Resources.unloadData(FILE_PATH)
	end
    
    ------------------------------------------------------------------------------------------------
    function TestEllipseColliderDataConverter.converterRegistered()
        CelesteAssert.isTrue(LuaComponentDataConverter.hasConverter("EllipseCollider"))
    end
    
	-- Dimensions Attribute Tests
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.hasDimensionsAttribute()
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		
		CelesteAssert.hasAttribute(ellipseColliderDataConverter, "dimensions")
	end

	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.dimensionsAttribute_IsVec2()
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		local dimensionsAttribute = ellipseColliderDataConverter:findAttribute("dimensions")

		CelesteAssert.attributeIsVec2(dimensionsAttribute)
	end

	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.dimensionsAttributeDefaultValue_IsZeroVec2()
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		local dimensionsAttribute = ellipseColliderDataConverter:findAttribute("dimensions")

		CelesteAssert.areEqual(vec2.new(0, 0), dimensionsAttribute:asVec2())
	end
    
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.dimensionsAttribute_IsRequired()
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		local dimensionsAttribute = ellipseColliderDataConverter:findAttribute("dimensions")

		CelesteAssert.isTrue(dimensionsAttribute:isRequired())
	end

    -- Is Trigger Attribute Tests
    ------------------------------------------------------------------------------------------------
    function TestEllipseColliderDataConverter.hasIsTriggerAttribute()
        local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

        CelesteAssert.hasAttribute(ellipseColliderDataConverter, "is_trigger")
    end

    ------------------------------------------------------------------------------------------------
    function TestEllipseColliderDataConverter.isTriggerAttribute_IsBool()
        local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
        local isTriggerAttribute = ellipseColliderDataConverter:findAttribute("is_trigger")

        CelesteAssert.attributeIsBool(isTriggerAttribute)
    end
	
    ------------------------------------------------------------------------------------------------
    function TestEllipseColliderDataConverter.isTriggerAttributeDefaultValue_IsFalse()
        local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
        local isTriggerAttribute = ellipseColliderDataConverter:findAttribute("is_trigger")

        CelesteAssert.isFalse(isTriggerAttribute:asBool())
    end
    
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.isTriggerAttribute_IsNotRequired()
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		local isTriggerAttribute = ellipseColliderDataConverter:findAttribute("is_trigger")

		CelesteAssert.isFalse(isTriggerAttribute:isRequired())
	end
    
	-- Offset Attribute Tests
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.hasOffsetAttribute()
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		
		CelesteAssert.hasAttribute(ellipseColliderDataConverter, "offset")
	end

	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.offsetAttribute_IsVec2()
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		local offsetAttribute = ellipseColliderDataConverter:findAttribute("offset")

		CelesteAssert.attributeIsVec2(offsetAttribute)
	end

	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.offsetAttributeDefaultValue_IsZeroVec2()
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		local offsetAttribute = ellipseColliderDataConverter:findAttribute("offset")

		CelesteAssert.areEqual(vec2.new(0, 0), offsetAttribute:asVec2())
	end
    
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.dimensionsAttribute_IsNotRequired()
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		local offsetAttribute = ellipseColliderDataConverter:findAttribute("offset")

		CelesteAssert.isFalse(offsetAttribute:isRequired())
	end
    
	-- Convert From Xml Tests
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_InputtingPathToNonExistentFile_ReturnsFalse()
        local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

        CelesteAssert.isFalse(ellipseColliderDataConverter:convertFromXML("WubbaLubbaDubDub"))
	end
    
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_InputtingPathToInvalidFile_ReturnsFalse()
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

        CelesteAssert.isFalse(ellipseColliderDataConverter:convertFromXML(EllipseColliderLoadingResources.Invalid))
	end

	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_InputtingPathToValidFile_ReturnsTrue()
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

        CelesteAssert.isTrue(ellipseColliderDataConverter:convertFromXML(EllipseColliderLoadingResources.Valid))
	end

	-- Convert Dimensions Tests
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_NoDimensionsAttribute_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("dimensions"))

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

		CelesteAssert.isFalse(ellipseColliderDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_NoDimensionsAttribute_SetsDimensionsToZero()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("dimensions"))

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(FILE_PATH)

		local dimensions = ellipseColliderDataConverter:findAttribute("dimensions")

		CelesteAssert.areEqual(vec2.new(), dimensions:asVec2())
	end

	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_DimensionsAttribute_WithEmptyString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

		CelesteAssert.isFalse(ellipseColliderDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_DimensionsAttribute_WithEmptyString_SetsDimensionsToZero()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(FILE_PATH)

		local dimensions = ellipseColliderDataConverter:findAttribute("dimensions")

		CelesteAssert.areEqual(vec2.new(), dimensions:asVec2())
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_DimensionsAttribute_WithInvalidString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

		CelesteAssert.isFalse(ellipseColliderDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_DimensionsAttribute_WithInvalidString_SetsDimensionsToZero()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(FILE_PATH)

		local dimensions = ellipseColliderDataConverter:findAttribute("dimensions")

		CelesteAssert.areEqual(vec2.new(), dimensions:asVec2())
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_DimensionsAttribute_WithValidString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "12, 35")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("12, 35", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

		CelesteAssert.isTrue(ellipseColliderDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_DimensionsAttribute_WithValidString_SetsDimensionsToCorrectValue()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "12, 35.2")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("12, 35.2", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(FILE_PATH)

		local dimensions = ellipseColliderDataConverter:findAttribute("dimensions")

		CelesteAssert.areEqual(vec2.new(12, 35.2), dimensions:asVec2())
	end

	-- Convert Is Trigger Tests
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_NoIsTriggerAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "1, 1") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("is_trigger"))

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

		CelesteAssert.isTrue(ellipseColliderDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_NoIsTriggerAttribute_SetsIsTriggerToFalse()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "1, 1") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("is_trigger"))

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isFalse(ellipseColliderDataConverter:findAttribute("is_trigger"):asBool())
	end

	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_IsTriggerAttribute_SetToEmptyString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("is_trigger", "")
		document:insertFirstChild(element)

		local isTriggerAttr = element:findAttribute("is_trigger")

		CelesteAssert.isNotNil(isTriggerAttr)
		CelesteAssert.areEqual("", isTriggerAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

		CelesteAssert.isFalse(ellipseColliderDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_IsTriggerAttribute_SetToEmptyString_SetsIsTriggerToFalse()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("is_trigger", "")
		document:insertFirstChild(element)

		local isTriggerAttr = element:findAttribute("is_trigger")

		CelesteAssert.isNotNil(isTriggerAttr)
		CelesteAssert.areEqual("", isTriggerAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isFalse(ellipseColliderDataConverter:findAttribute("is_trigger"):asBool())
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_IsTriggerAttribute_SetToInvalidString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("is_trigger", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local isTriggerAttr = element:findAttribute("is_trigger")

		CelesteAssert.isNotNil(isTriggerAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", isTriggerAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

		CelesteAssert.isFalse(ellipseColliderDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_IsTriggerAttribute_SetToInvalidString_SetsIsTriggerToFalse()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("is_trigger", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local isTriggerAttr = element:findAttribute("is_trigger")

		CelesteAssert.isNotNil(isTriggerAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", isTriggerAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isFalse(ellipseColliderDataConverter:findAttribute("is_trigger"):asBool())
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_IsTriggerAttribute_SetToValidString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("is_trigger", "True")
		document:insertFirstChild(element)

		local isTriggerAttr = element:findAttribute("is_trigger")

		CelesteAssert.isNotNil(isTriggerAttr)
		CelesteAssert.areEqual("True", isTriggerAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

		CelesteAssert.isTrue(ellipseColliderDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_IsTriggerAttribute_SetToValidString_SetsIsTriggerToCorrectValue()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("is_trigger", "True")
		document:insertFirstChild(element)

		local isTriggerAttr = element:findAttribute("is_trigger")

		CelesteAssert.isNotNil(isTriggerAttr)
		CelesteAssert.areEqual("True", isTriggerAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isTrue(ellipseColliderDataConverter:findAttribute("is_trigger"):asBool())
	end
    
	-- Convert Offset Tests
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_NoOffsetAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
        element:setAttribute("dimensions", "1, 1") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("offset"))

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

		CelesteAssert.isTrue(ellipseColliderDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_NoOffsetAttribute_SetsOffsetToZero()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
        element:setAttribute("dimensions", "1, 1") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("offset"))

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(FILE_PATH)

		local offset = ellipseColliderDataConverter:findAttribute("offset")

		CelesteAssert.areEqual(vec2.new(), offset:asVec2())
	end

	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_OffsetAttribute_WithEmptyString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "1, 1") -- Required
        element:setAttribute("offset", "")
		document:insertFirstChild(element)

		local offsetAttr = element:findAttribute("offset")

		CelesteAssert.isNotNil(offsetAttr)
		CelesteAssert.areEqual("", offsetAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

		CelesteAssert.isFalse(ellipseColliderDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_OffsetAttribute_WithEmptyString_SetsOffsetToZero()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
		element:setAttribute("dimensions", "1, 1") -- Required
        element:setAttribute("offset", "") -- Required
		document:insertFirstChild(element)

		local offsetAttr = element:findAttribute("offset")

		CelesteAssert.isNotNil(offsetAttr)
		CelesteAssert.areEqual("", offsetAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(FILE_PATH)

		local offset = ellipseColliderDataConverter:findAttribute("offset")

		CelesteAssert.areEqual(vec2.new(), offset:asVec2())
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_OffsetAttribute_WithInvalidString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
        element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("offset", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local offsetAttr = element:findAttribute("offset")

		CelesteAssert.isNotNil(offsetAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", offsetAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

		CelesteAssert.isFalse(ellipseColliderDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_OffsetAttribute_WithInvalidString_SetsOffsetToZero()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
        element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("offset", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local offsetAttr = element:findAttribute("offset")

		CelesteAssert.isNotNil(offsetAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", offsetAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(FILE_PATH)

		local offset = ellipseColliderDataConverter:findAttribute("offset")

		CelesteAssert.areEqual(vec2.new(), offset:asVec2())
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_OffsetAttribute_WithValidString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
        element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("offset", "12, 35")
		document:insertFirstChild(element)

		local offsetAttr = element:findAttribute("offset")

		CelesteAssert.isNotNil(offsetAttr)
		CelesteAssert.areEqual("12, 35", offsetAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")

		CelesteAssert.isTrue(ellipseColliderDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.convertFromXML_OffsetAttribute_WithValidString_SetsOffsetToCorrectValue()
		local document = XMLDocument.new()
		local element = document:newElement("EllipseCollider")
        element:setAttribute("dimensions", "1, 1") -- Required
		element:setAttribute("offset", "12, 35")
		document:insertFirstChild(element)

		local offsetAttr = element:findAttribute("offset")

		CelesteAssert.isNotNil(offsetAttr)
		CelesteAssert.areEqual("12, 35", offsetAttr:asString())

		document:saveFile(FILE_PATH)
		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(FILE_PATH)

		local offset = ellipseColliderDataConverter:findAttribute("offset")

		CelesteAssert.areEqual(vec2.new(12, 35), offset:asVec2())
	end
    
	-- SetValues Tests
	------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.setValues_SetsDimensionsToAttributeValue()
		local screen = TestEllipseColliderDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local collider = gameObject:addComponent("EllipseCollider")

		CelesteAssert.isNotNil(collider)
	    CelesteAssert.areEqual(vec2.new(), collider:getDimensions())

		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(EllipseColliderLoadingResources.Valid);

        CelesteAssert.hasAttribute(ellipseColliderDataConverter, "dimensions")
		CelesteAssert.areEqual(12, ellipseColliderDataConverter:findAttribute("dimensions"):asVec2().x)
        CelesteAssert.areEqual(34, ellipseColliderDataConverter:findAttribute("dimensions"):asVec2().y)

		ellipseColliderDataConverter:setValues(collider)

		CelesteAssert.areEqual(vec2.new(12, 34), collider:getDimensions())
	end

    ------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.setValues_SetsIsTriggerToAttributeValue()
		local screen = TestEllipseColliderDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local collider = gameObject:addComponent("EllipseCollider")

		CelesteAssert.isNotNil(collider)
	    CelesteAssert.isFalse(collider:getIsTrigger())

		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(EllipseColliderLoadingResources.Valid);

        CelesteAssert.hasAttribute(ellipseColliderDataConverter, "is_trigger")
		CelesteAssert.isTrue(ellipseColliderDataConverter:findAttribute("is_trigger"):asBool())

		ellipseColliderDataConverter:setValues(collider)

		CelesteAssert.isTrue(collider:getIsTrigger())
	end

    ------------------------------------------------------------------------------------------------
	function TestEllipseColliderDataConverter.setValues_SetsOffsetToAttributeValue()
		
		local screen = TestEllipseColliderDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local collider = gameObject:addComponent("EllipseCollider")

		CelesteAssert.isNotNil(collider)
	    CelesteAssert.areEqual(vec2.new(), collider:getOffset())

		local ellipseColliderDataConverter = LuaComponentDataConverter.getConverter("EllipseCollider")
		ellipseColliderDataConverter:convertFromXML(EllipseColliderLoadingResources.Valid);

        CelesteAssert.hasAttribute(ellipseColliderDataConverter, "offset")
		CelesteAssert.areEqual(2, ellipseColliderDataConverter:findAttribute("offset"):asVec2().x)
        CelesteAssert.areEqual(-5, ellipseColliderDataConverter:findAttribute("offset"):asVec2().y)

		ellipseColliderDataConverter:setValues(collider)
		CelesteAssert.areEqual(vec2.new(2, -5), collider:getOffset())
	end
	

return TestEllipseColliderDataConverter