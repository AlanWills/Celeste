local CelesteAssert = require "CelesteAssert"


local TestAnimatorDataConverter = { }

	local FILE_PATH = path.combine(TestResources.TempDirectory, "Test.xml")

    TestAnimatorDataConverter.name = "Test Animator Data Converter"
    
	-- Initialize/Cleanup
    ------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.testInitialize()
		Resources.unloadData(FILE_PATH)
	end

	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.testCleanup()
		Resources.unloadData(FILE_PATH)
	end

    ------------------------------------------------------------------------------------------------
    function TestAnimatorDataConverter.converterRegistered()
        CelesteAssert.isTrue(LuaComponentDataConverter.hasConverter("Animator"))
    end
    
	-- Sprite Sheet Dimensions Attribute Tests
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.hasSpriteSheetDimensionsAttribute()
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		
		CelesteAssert.hasAttribute(animatorDataConverter, "sprite_sheet_dimensions")
	end

	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.spriteSheetDimensionsAttribute_IsUVec2()
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		local spriteSheetDimensionsAttribute = animatorDataConverter:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.attributeIsUVec2(spriteSheetDimensionsAttribute)
	end

	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.spriteSheetDimensionsAttributeDefaultValue_IsOneOneUVec2()
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		local spriteSheetDimensionsAttribute = animatorDataConverter:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.areEqual(uvec2.new(1, 1), spriteSheetDimensionsAttribute:asUVec2())
	end
    
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.spriteSheetDimensionsAttribute_IsRequired()
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		local spriteSheetDimensionsAttribute = animatorDataConverter:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.isTrue(spriteSheetDimensionsAttribute:isRequired())
	end

    -- Looping Attribute Tests
    ------------------------------------------------------------------------------------------------
    function TestAnimatorDataConverter.hasLoopingAttribute()
        local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

        CelesteAssert.hasAttribute(animatorDataConverter, "looping")
    end

    ------------------------------------------------------------------------------------------------
    function TestAnimatorDataConverter.loopingAttribute_IsBool()
        local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
        local loopingDimensionsAttribute = animatorDataConverter:findAttribute("looping")

        CelesteAssert.attributeIsBool(loopingDimensionsAttribute)
    end
	
    ------------------------------------------------------------------------------------------------
    function TestAnimatorDataConverter.loopingAttributeDefaultValue_IsTrue()
        local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
        local loopingDimensionsAttribute = animatorDataConverter:findAttribute("looping")

        CelesteAssert.isTrue(loopingDimensionsAttribute:asBool())
    end
    
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.loopingAttribute_IsNotRequired()
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		local loopingDimensionsAttribute = animatorDataConverter:findAttribute("looping")

		CelesteAssert.isFalse(loopingDimensionsAttribute:isRequired())
	end

    -- Seconds Per Frame Attribute Tests
    ------------------------------------------------------------------------------------------------
    function TestAnimatorDataConverter.hasSecondsPerFrameAttribute()
        local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

        CelesteAssert.hasAttribute(animatorDataConverter, "seconds_per_frame")
    end

    ------------------------------------------------------------------------------------------------
    function TestAnimatorDataConverter.secondsPerFrameAttribute_IsFloat()
        local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
        local secondsPerFrameAttribute = animatorDataConverter:findAttribute("seconds_per_frame")

        CelesteAssert.attributeIsFloat(secondsPerFrameAttribute)
    end

    ------------------------------------------------------------------------------------------------
    function TestAnimatorDataConverter.secondsPerFrameAttributeDefaultValue_IsZeroPointOne()
        local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
        local secondsPerFrameAttribute = animatorDataConverter:findAttribute("seconds_per_frame")

        CelesteAssert.areAlmostEqual(0.1, secondsPerFrameAttribute:asFloat())
    end

    ------------------------------------------------------------------------------------------------
    function TestAnimatorDataConverter.secondsPerFrameAttribute_IsNotRequired()
        local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
        local secondsPerFrameAttribute = animatorDataConverter:findAttribute("seconds_per_frame")

        CelesteAssert.isFalse(secondsPerFrameAttribute:isRequired())
    end

    -- Play Immediately Attribute Tests
    ------------------------------------------------------------------------------------------------
    function TestAnimatorDataConverter.hasPlayImmediatelyAttribute()
        local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

        CelesteAssert.hasAttribute(animatorDataConverter, "play_immediately")
    end

    ------------------------------------------------------------------------------------------------
    function TestAnimatorDataConverter.playImmediatelyAttribute_IsBool()
        local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
        local playImmediatelyAttribute = animatorDataConverter:findAttribute("play_immediately")

        CelesteAssert.attributeIsBool(playImmediatelyAttribute)
    end

    ------------------------------------------------------------------------------------------------
    function TestAnimatorDataConverter.playImmediatelyAttributeDefaultValue_IsTrue()
        local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
        local playImmediatelyAttribute = animatorDataConverter:findAttribute("play_immediately")

        CelesteAssert.isTrue(playImmediatelyAttribute:asBool())
    end

    ------------------------------------------------------------------------------------------------
    function TestAnimatorDataConverter.playImmediatelyAttribute_IsNotRequired()
        local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
        local playImmediatelyAttribute = animatorDataConverter:findAttribute("play_immediately")

        CelesteAssert.isFalse(playImmediatelyAttribute:isRequired())
    end
    
	-- Convert From Xml Tests
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_InputtingPathToNonExistentFile_ReturnsFalse()
        local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

        CelesteAssert.isFalse(animatorDataConverter:convertFromXML("WubbaLubbaDubDub"))
	end
    
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_InputtingPathToInvalidFile_ReturnsFalse()
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

        CelesteAssert.isFalse(animatorDataConverter:convertFromXML(AnimatorLoadingResources.Invalid))
	end

	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_InputtingPathToValidFile_ReturnsTrue()
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

        CelesteAssert.isTrue(animatorDataConverter:convertFromXML(AnimatorLoadingResources.Valid))
	end

	-- Convert Sprite Sheet Dimensions Tests
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_NoSpriteSheetDimensionsAttribute_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("sprite_sheet_dimensions"))

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isFalse(animatorDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_NoSpriteSheetDimensionsAttribute_SetsSpriteSheetDimensionsToOne()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("sprite_sheet_dimensions"))

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		local dimensions = animatorDataConverter:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.areEqual(1, dimensions:asUVec2().x)
		CelesteAssert.areEqual(1, dimensions:asUVec2().y)
	end

	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_SpriteSheetDimensionsAttribute_WithEmptyString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isFalse(animatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_SpriteSheetDimensionsAttribute_WithEmptyString_SetsSpriteSheetDimensionsToOne()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		local dimensions = animatorDataConverter:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.areEqual(1, dimensions:asUVec2().x)
		CelesteAssert.areEqual(1, dimensions:asUVec2().y)
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_SpriteSheetDimensionsAttribute_WithInvalidString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isFalse(animatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_SpriteSheetDimensionsAttribute_WithInvalidString_SetsSpriteSheetDimensionsToOne()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		local dimensions = animatorDataConverter:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.areEqual(1, dimensions:asUVec2().x)
		CelesteAssert.areEqual(1, dimensions:asUVec2().y)
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_SpriteSheetDimensionsAttribute_WithValidString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "12, 35")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("12, 35", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isTrue(animatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_SpriteSheetDimensionsAttribute_WithValidString_SetsSpriteSheetDimensionsToCorrectValue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "12, 35")
		document:insertFirstChild(element)

		local xmlDimensionsAttr = element:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.isNotNil(xmlDimensionsAttr)
		CelesteAssert.areEqual("12, 35", xmlDimensionsAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		local dimensions = animatorDataConverter:findAttribute("sprite_sheet_dimensions")

		CelesteAssert.areEqual(12, dimensions:asUVec2().x)
		CelesteAssert.areEqual(35, dimensions:asUVec2().y)
	end

	-- Convert Looping Tests
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_NoLoopingAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("looping"))

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isTrue(animatorDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_NoLoopingAttribute_SetsLoopingToTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("looping"))

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isTrue(animatorDataConverter:findAttribute("looping"):asBool())
	end

	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_LoopingAttribute_SetToEmptyString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		element:setAttribute("looping", "")
		document:insertFirstChild(element)

		local loopingAttr = element:findAttribute("looping")

		CelesteAssert.isNotNil(loopingAttr)
		CelesteAssert.areEqual("", loopingAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isFalse(animatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_LoopingAttribute_SetToEmptyString_SetsLoopingToTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		element:setAttribute("looping", "")
		document:insertFirstChild(element)

		local loopingAttr = element:findAttribute("looping")

		CelesteAssert.isNotNil(loopingAttr)
		CelesteAssert.areEqual("", loopingAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isTrue(animatorDataConverter:findAttribute("looping"):asBool())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_LoopingAttribute_SetToInvalidString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		element:setAttribute("looping", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local loopingAttr = element:findAttribute("looping")

		CelesteAssert.isNotNil(loopingAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", loopingAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isFalse(animatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_LoopingAttribute_SetToInvalidString_SetsLoopingToTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		element:setAttribute("looping", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local loopingAttr = element:findAttribute("looping")

		CelesteAssert.isNotNil(loopingAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", loopingAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isTrue(animatorDataConverter:findAttribute("looping"):asBool())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_LoopingAttribute_SetToValidString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		element:setAttribute("looping", "False")
		document:insertFirstChild(element)

		local loopingAttr = element:findAttribute("looping")

		CelesteAssert.isNotNil(loopingAttr)
		CelesteAssert.areEqual("False", loopingAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isTrue(animatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_LoopingAttribute_SetToValidString_SetsLoopingToCorrectValue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		element:setAttribute("looping", "False")
		document:insertFirstChild(element)

		local loopingAttr = element:findAttribute("looping")

		CelesteAssert.isNotNil(loopingAttr)
		CelesteAssert.areEqual("False", loopingAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isFalse(animatorDataConverter:findAttribute("looping"):asBool())
	end

    -- Seconds Per Frame Tests
    ------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_NoSecondsPerFrameAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
        element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("seconds_per_frame"))

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isTrue(animatorDataConverter:convertFromXML(FILE_PATH))
	end

    ------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_NoSecondsPerFrameAttribute_SetsSecondsPerFrameToZeroPointOne()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("seconds_per_frame"))

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areAlmostEqual(0.1, animatorDataConverter:findAttribute("seconds_per_frame"):asFloat())
	end

    ------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_SecondsPerFrameAttribute_SetToEmptyString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
        element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
        element:setAttribute("seconds_per_frame", "")
		document:insertFirstChild(element)

        local xmlAttr = element:findAttribute("seconds_per_frame")

		CelesteAssert.isNotNil(xmlAttr)
        CelesteAssert.areEqual("", xmlAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isFalse(animatorDataConverter:convertFromXML(FILE_PATH))
	end
	
    ------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_SecondsPerFrameAttribute_SetToEmptyString_SetsSecondsPerFrameToZeroPointOne()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
        element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
        element:setAttribute("seconds_per_frame", "")
		document:insertFirstChild(element)

        local xmlAttr = element:findAttribute("seconds_per_frame")

		CelesteAssert.isNotNil(xmlAttr)
        CelesteAssert.areEqual("", xmlAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
        animatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areAlmostEqual(0.1, animatorDataConverter:findAttribute("seconds_per_frame"):asFloat())
	end
	
    ------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_SecondsPerFrameAttribute_SetToInvalidString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
        element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
        element:setAttribute("seconds_per_frame", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

        local xmlAttr = element:findAttribute("seconds_per_frame")

		CelesteAssert.isNotNil(xmlAttr)
        CelesteAssert.areEqual("WubbaLubbaDubDub", xmlAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isFalse(animatorDataConverter:convertFromXML(FILE_PATH))
	end
	
    ------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_SecondsPerFrameAttribute_SetToInvalidString_SetsSecondsPerFrameToZeroPointOne()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
        element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
        element:setAttribute("seconds_per_frame", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

        local xmlAttr = element:findAttribute("seconds_per_frame")

		CelesteAssert.isNotNil(xmlAttr)
        CelesteAssert.areEqual("WubbaLubbaDubDub", xmlAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
        animatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areAlmostEqual(0.1, animatorDataConverter:findAttribute("seconds_per_frame"):asFloat())
	end
	
    ------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_SecondsPerFrameAttribute_SetToValidString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
        element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
        element:setAttribute("seconds_per_frame", "12.4")
		document:insertFirstChild(element)

        local xmlAttr = element:findAttribute("seconds_per_frame")

		CelesteAssert.isNotNil(xmlAttr)
        CelesteAssert.areEqual("12.4", xmlAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isTrue(animatorDataConverter:convertFromXML(FILE_PATH))
	end
	
    ------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_SecondsPerFrameAttribute_SetToInvalidString_SetsSecondsPerFrameToZeroPointOne()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
        element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
        element:setAttribute("seconds_per_frame", "12.4")
		document:insertFirstChild(element)

        local xmlAttr = element:findAttribute("seconds_per_frame")

		CelesteAssert.isNotNil(xmlAttr)
        CelesteAssert.areEqual("12.4", xmlAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
        animatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areAlmostEqual(12.4, animatorDataConverter:findAttribute("seconds_per_frame"):asFloat(), 0.00001)
	end
	
	-- Convert Play Immediately Tests
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_NoPlayImmediatelyAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("play_immediately"))

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isTrue(animatorDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_NoPlayImmediatelyAttribute_SetsPlayImmediatelyToTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("play_immediately"))

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isTrue(animatorDataConverter:findAttribute("play_immediately"):asBool())
	end

	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_PlayImmediatelyAttribute_SetToEmptyString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		element:setAttribute("play_immediately", "")
		document:insertFirstChild(element)

		local loopingAttr = element:findAttribute("play_immediately")

		CelesteAssert.isNotNil(loopingAttr)
		CelesteAssert.areEqual("", loopingAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isFalse(animatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_PlayImmediatelyAttribute_SetToEmptyString_SetsPlayImmediatelyToTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		element:setAttribute("play_immediately", "")
		document:insertFirstChild(element)

		local loopingAttr = element:findAttribute("play_immediately")

		CelesteAssert.isNotNil(loopingAttr)
		CelesteAssert.areEqual("", loopingAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isTrue(animatorDataConverter:findAttribute("play_immediately"):asBool())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_PlayImmediatelyAttribute_SetToInvalidString_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		element:setAttribute("play_immediately", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local loopingAttr = element:findAttribute("play_immediately")

		CelesteAssert.isNotNil(loopingAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", loopingAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isFalse(animatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_PlayImmediatelyAttribute_SetToInvalidString_SetsPlayImmediatelyToTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		element:setAttribute("play_immediately", "WubbaLubbaDubDub")
		document:insertFirstChild(element)

		local loopingAttr = element:findAttribute("play_immediately")

		CelesteAssert.isNotNil(loopingAttr)
		CelesteAssert.areEqual("WubbaLubbaDubDub", loopingAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isTrue(animatorDataConverter:findAttribute("play_immediately"):asBool())
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_PlayImmediatelyAttribute_SetToValidString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		element:setAttribute("play_immediately", "False")
		document:insertFirstChild(element)

		local loopingAttr = element:findAttribute("play_immediately")

		CelesteAssert.isNotNil(loopingAttr)
		CelesteAssert.areEqual("False", loopingAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")

		CelesteAssert.isTrue(animatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.convertFromXML_PlayImmediatelyAttribute_SetToValidString_SetsPlayImmediatelyToCorrectValue()
		local document = XMLDocument.new()
		local element = document:newElement("Animator")
		element:setAttribute("sprite_sheet_dimensions", "1, 1") -- Required
		element:setAttribute("play_immediately", "False")
		document:insertFirstChild(element)

		local loopingAttr = element:findAttribute("play_immediately")

		CelesteAssert.isNotNil(loopingAttr)
		CelesteAssert.areEqual("False", loopingAttr:asString())

		document:saveFile(FILE_PATH)
		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.isFalse(animatorDataConverter:findAttribute("play_immediately"):asBool())
	end

	-- SetValues Tests
	------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.setValues_SetsSpriteSheetDimensionsToAttributeValue()
		local screen = TestAnimatorDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local animator = gameObject:addComponent("Animator")

		CelesteAssert.isNotNil(animator)
	    CelesteAssert.areEqual(1, animator:getSpriteSheetDimensions().x)
        CelesteAssert.areEqual(1, animator:getSpriteSheetDimensions().y)

		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(AnimatorLoadingResources.Valid);

        CelesteAssert.hasAttribute(animatorDataConverter, "sprite_sheet_dimensions")
		CelesteAssert.areEqual(4, animatorDataConverter:findAttribute("sprite_sheet_dimensions"):asUVec2().x)
        CelesteAssert.areEqual(12, animatorDataConverter:findAttribute("sprite_sheet_dimensions"):asUVec2().y)

		animatorDataConverter:setValues(animator)

		CelesteAssert.areEqual(4, animator:getSpriteSheetDimensions().x)
        CelesteAssert.areEqual(12, animator:getSpriteSheetDimensions().y)
	end

    ------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.setValues_SetsLoopingToAttributeValue()
		local screen = TestAnimatorDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local animator = gameObject:addComponent("Animator")

		CelesteAssert.isNotNil(animator)
	    CelesteAssert.isTrue(animator:isLooping())

		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(AnimatorLoadingResources.Valid);

        CelesteAssert.hasAttribute(animatorDataConverter, "looping")
		CelesteAssert.isFalse(animatorDataConverter:findAttribute("looping"):asBool())

		animatorDataConverter:setValues(animator)

		CelesteAssert.isFalse(animator:isLooping())
	end

    ------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.setValues_SetsSecondsPerFrameToAttributeValue()
		local screen = TestAnimatorDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local animator = gameObject:addComponent("Animator")

		CelesteAssert.isNotNil(animator)
	    CelesteAssert.areAlmostEqual(0.1, animator:getSecondsPerFrame())

		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(AnimatorLoadingResources.Valid);

        CelesteAssert.hasAttribute(animatorDataConverter, "seconds_per_frame")
		CelesteAssert.areAlmostEqual(0.6, animatorDataConverter:findAttribute("seconds_per_frame"):asFloat())

		animatorDataConverter:setValues(animator)

		CelesteAssert.areAlmostEqual(0.6, animator:getSecondsPerFrame())
	end

    ------------------------------------------------------------------------------------------------
	function TestAnimatorDataConverter.setValues_SetsPlayImmediatelyToAttributeValue()
		local screen = TestAnimatorDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local animator = gameObject:addComponent("Animator")

		CelesteAssert.isNotNil(animator)
	    CelesteAssert.isTrue(animator:getPlayImmediately())

		local animatorDataConverter = LuaComponentDataConverter.getConverter("Animator")
		animatorDataConverter:convertFromXML(AnimatorLoadingResources.Valid);

        CelesteAssert.hasAttribute(animatorDataConverter, "play_immediately")
		CelesteAssert.isFalse(animatorDataConverter:findAttribute("play_immediately"):asBool())

		animatorDataConverter:setValues(animator)

		CelesteAssert.isFalse(animator:getPlayImmediately())
	end
	

return TestAnimatorDataConverter