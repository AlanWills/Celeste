local CelesteAssert = require "CelesteAssert"


local TestKeyboardVisibilityDataConverter = { }
	
	local FILE_PATH = path.combine(TestResources.TempDirectory, "Test.xml")

	TestKeyboardVisibilityDataConverter.name = "Test Keyboard Visibility Data Converter"

	-- Initialize/Cleanup
    ------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.testInitialize()
		Resources.unloadData(FILE_PATH)
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.testCleanup()
		Resources.unloadData(FILE_PATH)
	end
	
	-- Registration Tests
    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.converterRegistered()
        CelesteAssert.isTrue(LuaComponentDataConverter.hasConverter("KeyboardVisibility"))
    end

    -- Visibility Key Tests
    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.hasVisibilityKeyAttribute()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		
		CelesteAssert.hasAttribute(keyboardVisibilityDataConverter, "visibility_key")
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.visibilityKeyAttribute_IsString()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		local visibilityKeyAttribute = keyboardVisibilityDataConverter:findAttribute("visibility_key")

		CelesteAssert.attributeIsString(visibilityKeyAttribute)
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.visibilityKeyAttribute_DefaultValue_IsEmptyString()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		local visibilityKeyAttribute = keyboardVisibilityDataConverter:findAttribute("visibility_key")

		CelesteAssert.areEqual("", visibilityKeyAttribute:asString())
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.visibilityKeyAttribute_IsNotRequired()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		local visibilityKeyAttribute = keyboardVisibilityDataConverter:findAttribute("visibility_key")

		CelesteAssert.isFalse(visibilityKeyAttribute:isRequired())
    end
    
    -- Invisibility Key Tests
    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.hasInvisibilityKeyAttribute()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		
		CelesteAssert.hasAttribute(keyboardVisibilityDataConverter, "invisibility_key")
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.invisibilityKeyAttribute_IsString()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		local invisibilityKeyAttribute = keyboardVisibilityDataConverter:findAttribute("invisibility_key")

		CelesteAssert.attributeIsString(invisibilityKeyAttribute)
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.invisibilityKeyAttribute_DefaultValue_IsEmptyString()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		local invisibilityKeyAttribute = keyboardVisibilityDataConverter:findAttribute("invisibility_key")

		CelesteAssert.areEqual("", invisibilityKeyAttribute:asString())
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.invisibilityKeyAttribute_IsNotRequired()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		local invisibilityKeyAttribute = keyboardVisibilityDataConverter:findAttribute("invisibility_key")

		CelesteAssert.isFalse(invisibilityKeyAttribute:isRequired())
    end
    
    -- Input Mode Tests
    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.hasInputModeAttribute()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		
		CelesteAssert.hasAttribute(keyboardVisibilityDataConverter, "input_mode")
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.inputModeAttribute_IsString()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		local modeAttribute = keyboardVisibilityDataConverter:findAttribute("input_mode")

		CelesteAssert.attributeIsString(modeAttribute)
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.modeAttribute_DefaultValue_IsToggle()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		local modeAttribute = keyboardVisibilityDataConverter:findAttribute("input_mode")

		CelesteAssert.areEqual("Toggle", modeAttribute:asString())
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.modeAttribute_IsNotRequired()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		local modeAttribute = keyboardVisibilityDataConverter:findAttribute("input_mode")

		CelesteAssert.isFalse(modeAttribute:isRequired())
    end
    
    -- Target Tests
    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.hasTargetttribute()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		
		CelesteAssert.hasAttribute(keyboardVisibilityDataConverter, "target")
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.targetAttribute_IsString()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		local targetAttribute = keyboardVisibilityDataConverter:findAttribute("target")

		CelesteAssert.attributeIsString(targetAttribute)
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.targetAttribute_DefaultValue_IsEmptyString()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		local targetAttribute = keyboardVisibilityDataConverter:findAttribute("target")

		CelesteAssert.areEqual("", targetAttribute:asString())
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardVisibilityDataConverter.modeAttribute_IsRequired()
        local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		local targetAttribute = keyboardVisibilityDataConverter:findAttribute("target")

		CelesteAssert.isTrue(targetAttribute:isRequired())
    end
    
	-- Convert From XML Tests
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_InputtingPathToNonExistentFile_ReturnsFalse()
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isFalse(keyboardVisibilityDataConverter:convertFromXML("WubbaLubbaDubDub"))
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_InputtingPathToInvalidFile_ReturnsFalse()
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isFalse(keyboardVisibilityDataConverter:convertFromXML(KeyboardVisibilityLoadingResources.Invalid))
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_InputtingPathToValidFile_ReturnsTrue()
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isTrue(keyboardVisibilityDataConverter:convertFromXML(KeyboardVisibilityLoadingResources.Valid))
	end
	
	-- Convert Visibility Key Tests
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_NoVisibilityKeyAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("visibility_key"))

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isTrue(keyboardVisibilityDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_NoVisibilityKeyAttribute_SetsVisibilityKeyToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("visibility_key"))

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardVisibilityDataConverter:findAttribute("visibility_key"):asString())
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_VisibilityKeyAttribute_EmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("visibility_key", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("visibility_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isTrue(keyboardVisibilityDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_VisibilityKeyAttribute_EmptyString_SetsVisibilityKeyToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("visibility_key", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("visibility_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardVisibilityDataConverter:findAttribute("invisibility_key"):asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_VisibilityKeyAttribute_NonEmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("visibility_key", "A")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("A", element:findAttribute("visibility_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isTrue(keyboardVisibilityDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_VisibilityKeyAttribute_NonEmptyString_SetsVisibilityKeyToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("visibility_key", "A")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("A", element:findAttribute("visibility_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("A", keyboardVisibilityDataConverter:findAttribute("visibility_key"):asString())
	end
    
	-- Convert Invisibility Key Tests
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_NoInvisibilityKeyAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("invisibility_key"))

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isTrue(keyboardVisibilityDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_NoInvisibilityKeyAttribute_SetsInvisibilityKeyToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("invisibility_key"))

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardVisibilityDataConverter:findAttribute("invisibility_key"):asString())
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_InvisibilityKeyAttribute_EmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("invisibility_key", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("invisibility_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isTrue(keyboardVisibilityDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_InvisibilityKeyAttribute_EmptyString_SetsInvisibilityKeyToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("invisibility_key", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("invisibility_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardVisibilityDataConverter:findAttribute("invisibility_key"):asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_InvisibilityKeyAttribute_NonEmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("invisibility_key", "A")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("A", element:findAttribute("invisibility_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isTrue(keyboardVisibilityDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_InvisibilityKeyAttribute_NonEmptyString_SetsInvisibilityKeyToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("invisibility_key", "A")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("A", element:findAttribute("invisibility_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("A", keyboardVisibilityDataConverter:findAttribute("invisibility_key"):asString())
	end
    
	-- Convert Input Mode Tests
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_NoInputModeAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("input_mode"))

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isTrue(keyboardVisibilityDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_NoInputModeAttribute_SetsInputModeToToggleString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("input_mode"))

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("Toggle", keyboardVisibilityDataConverter:findAttribute("input_mode"):asString())
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_InputModeAttribute_EmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("input_mode", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("input_mode"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isTrue(keyboardVisibilityDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_InputModeAttribute_EmptyString_SetsInputModeToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("input_mode", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("input_mode"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardVisibilityDataConverter:findAttribute("input_mode"):asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_InputModeAttribute_NonEmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("input_mode", "Continuous")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("Continuous", element:findAttribute("input_mode"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isTrue(keyboardVisibilityDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_InputModeAttribute_NonEmptyString_SetsInputModeToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("input_mode", "Continuous")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("Continuous", element:findAttribute("input_mode"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("Continuous", keyboardVisibilityDataConverter:findAttribute("input_mode"):asString())
	end
    
	-- Convert Target Tests
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_NoTargetAttribute_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("target"))

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isFalse(keyboardVisibilityDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_NoTargetAttribute_SetsTarget_ToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("target"))

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardVisibilityDataConverter:findAttribute("target"):asString())
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_TargetAttribute_EmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "") -- Required
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("target"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isTrue(keyboardVisibilityDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_TargetAttribute_EmptyString_SetsTargetToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "") -- Required
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("target"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardVisibilityDataConverter:findAttribute("target"):asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_TargetAttribute_NonEmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.areEqual("Test", element:findAttribute("target"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")

		CelesteAssert.isTrue(keyboardVisibilityDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.convertFromXML_TargetAttribute_NonEmptyString_SetsTargetToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardVisibility")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.areEqual("Test", element:findAttribute("target"):asString())

		document:saveFile(FILE_PATH)
		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("Test", keyboardVisibilityDataConverter:findAttribute("target"):asString())
	end
    
	-- SetValues Tests
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.setValues_SetsVisibilityKeyToAttributeValue()
        local screen = TestKeyboardVisibilityDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local keyboardVisibility = gameObject:addComponent("KeyboardVisibility")

		CelesteAssert.isNotNil(keyboardVisibility)
	    CelesteAssert.areEqual("", keyboardVisibility:getVisibilityKey())

		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(KeyboardVisibilityLoadingResources.Valid);

        CelesteAssert.hasAttribute(keyboardVisibilityDataConverter, "visibility_key")
		CelesteAssert.areEqual("A", keyboardVisibilityDataConverter:findAttribute("visibility_key"):asString())

		keyboardVisibilityDataConverter:setValues(keyboardVisibility)

		CelesteAssert.areEqual("A", keyboardVisibility:getVisibilityKey())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.setValues_SetsInvisibilityKeyToAttributeValue()
		local screen = TestKeyboardVisibilityDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local keyboardVisibility = gameObject:addComponent("KeyboardVisibility")

		CelesteAssert.isNotNil(keyboardVisibility)
	    CelesteAssert.areEqual("", keyboardVisibility:getInvisibilityKey())

		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(KeyboardVisibilityLoadingResources.Valid);

        CelesteAssert.hasAttribute(keyboardVisibilityDataConverter, "invisibility_key")
		CelesteAssert.areEqual("B", keyboardVisibilityDataConverter:findAttribute("invisibility_key"):asString())

		keyboardVisibilityDataConverter:setValues(keyboardVisibility)

		CelesteAssert.areEqual("B", keyboardVisibility:getInvisibilityKey())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.setValues_SetsInputModeToAttributeValue()
		local screen = TestKeyboardVisibilityDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local keyboardVisibility = gameObject:addComponent("KeyboardVisibility")

		CelesteAssert.isNotNil(keyboardVisibility)
	    CelesteAssert.areEqual("Toggle", keyboardVisibility:getInputMode())

		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(KeyboardVisibilityLoadingResources.Valid);

        CelesteAssert.hasAttribute(keyboardVisibilityDataConverter, "input_mode")
		CelesteAssert.areEqual("Continuous", keyboardVisibilityDataConverter:findAttribute("input_mode"):asString())

		keyboardVisibilityDataConverter:setValues(keyboardVisibility)

		CelesteAssert.areEqual("Continuous", keyboardVisibility:getInputMode())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardVisibilityDataConverter.setValues_SetsTargetToAttributeValue()
		local screen = TestKeyboardVisibilityDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local keyboardVisibility = gameObject:addComponent("KeyboardVisibility")

		CelesteAssert.isNotNil(keyboardVisibility)
	    CelesteAssert.isNil(keyboardVisibility:getTarget())

		local keyboardVisibilityDataConverter = LuaComponentDataConverter.getConverter("KeyboardVisibility")
		keyboardVisibilityDataConverter:convertFromXML(KeyboardVisibilityLoadingResources.Valid);

        CelesteAssert.hasAttribute(keyboardVisibilityDataConverter, "target")
		CelesteAssert.areEqual("Test", keyboardVisibilityDataConverter:findAttribute("target"):asString())
        
        local target = screen:allocateGameObject()
        target:setName("Test")

		keyboardVisibilityDataConverter:setValues(keyboardVisibility)

		CelesteAssert.isNotNil(keyboardVisibility:getTarget())
        CelesteAssert.areEqual(target, keyboardVisibility:getTarget())
	end
	

return TestKeyboardVisibilityDataConverter