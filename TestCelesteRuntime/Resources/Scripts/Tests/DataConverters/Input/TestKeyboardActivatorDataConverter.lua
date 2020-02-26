local CelesteAssert = require "CelesteAssert"


local TestKeyboardActivatorDataConverter = { }
	
	local FILE_PATH = path.combine(TestResources.TempDirectory, "Test.xml")

	TestKeyboardActivatorDataConverter.name = "Test Keyboard Activator Data Converter"

	-- Initialize/Cleanup
    ------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.testInitialize()
		Resources.unloadData(FILE_PATH)
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.testCleanup()
		Resources.unloadData(FILE_PATH)
	end
	
	-- Registration Tests
    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.converterRegistered()
        CelesteAssert.isTrue(LuaComponentDataConverter.hasConverter("KeyboardActivator"))
    end

    -- Activation Key Tests
    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.hasActivationKeyAttribute()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		
		CelesteAssert.hasAttribute(keyboardActivatorDataConverter, "activation_key")
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.activationKeyAttribute_IsString()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		local activationKeyAttribute = keyboardActivatorDataConverter:findAttribute("activation_key")

		CelesteAssert.attributeIsString(activationKeyAttribute)
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.activationKeyAttribute_DefaultValue_IsEmptyString()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		local activationKeyAttribute = keyboardActivatorDataConverter:findAttribute("activation_key")

		CelesteAssert.areEqual("", activationKeyAttribute:asString())
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.activationKeyAttribute_IsNotRequired()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		local activationKeyAttribute = keyboardActivatorDataConverter:findAttribute("activation_key")

		CelesteAssert.isFalse(activationKeyAttribute:isRequired())
    end
    
    -- Deactivation Key Tests
    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.hasDeactivationKeyAttribute()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		
		CelesteAssert.hasAttribute(keyboardActivatorDataConverter, "deactivation_key")
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.deactivationKeyAttribute_IsString()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		local deactivationKeyAttribute = keyboardActivatorDataConverter:findAttribute("deactivation_key")

		CelesteAssert.attributeIsString(deactivationKeyAttribute)
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.deactivationKeyAttribute_DefaultValue_IsEmptyString()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		local deactivationKeyAttribute = keyboardActivatorDataConverter:findAttribute("deactivation_key")

		CelesteAssert.areEqual("", deactivationKeyAttribute:asString())
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.deactivationKeyAttribute_IsNotRequired()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		local deactivationKeyAttribute = keyboardActivatorDataConverter:findAttribute("deactivation_key")

		CelesteAssert.isFalse(deactivationKeyAttribute:isRequired())
    end
    
    -- Input Mode Tests
    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.hasInputModeAttribute()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		
		CelesteAssert.hasAttribute(keyboardActivatorDataConverter, "input_mode")
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.inputModeAttribute_IsString()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		local modeAttribute = keyboardActivatorDataConverter:findAttribute("input_mode")

		CelesteAssert.attributeIsString(modeAttribute)
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.modeAttribute_DefaultValue_IsToggle()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		local modeAttribute = keyboardActivatorDataConverter:findAttribute("input_mode")

		CelesteAssert.areEqual("Toggle", modeAttribute:asString())
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.modeAttribute_IsNotRequired()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		local modeAttribute = keyboardActivatorDataConverter:findAttribute("input_mode")

		CelesteAssert.isFalse(modeAttribute:isRequired())
    end
    
    -- Target Tests
    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.hasTargetttribute()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		
		CelesteAssert.hasAttribute(keyboardActivatorDataConverter, "target")
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.targetAttribute_IsString()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		local targetAttribute = keyboardActivatorDataConverter:findAttribute("target")

		CelesteAssert.attributeIsString(targetAttribute)
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.targetAttribute_DefaultValue_IsEmptyString()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		local targetAttribute = keyboardActivatorDataConverter:findAttribute("target")

		CelesteAssert.areEqual("", targetAttribute:asString())
    end

    ------------------------------------------------------------------------------------------------
    function TestKeyboardActivatorDataConverter.modeAttribute_IsRequired()
        local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		local targetAttribute = keyboardActivatorDataConverter:findAttribute("target")

		CelesteAssert.isTrue(targetAttribute:isRequired())
    end
    
	-- Convert From XML Tests
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_InputtingPathToNonExistentFile_ReturnsFalse()
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isFalse(keyboardActivatorDataConverter:convertFromXML("WubbaLubbaDubDub"))
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_InputtingPathToInvalidFile_ReturnsFalse()
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isFalse(keyboardActivatorDataConverter:convertFromXML(KeyboardActivatorLoadingResources.Invalid))
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_InputtingPathToValidFile_ReturnsTrue()
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isTrue(keyboardActivatorDataConverter:convertFromXML(KeyboardActivatorLoadingResources.Valid))
	end
	
	-- Convert Activation Key Tests
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_NoActivationKeyAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("activation_key"))

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isTrue(keyboardActivatorDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_NoActivationKeyAttribute_SetsActivationKeyToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("activation_key"))

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardActivatorDataConverter:findAttribute("activation_key"):asString())
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_ActivationKeyAttribute_EmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("activation_key", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("activation_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isTrue(keyboardActivatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_ActivationKeyAttribute_EmptyString_SetsActivationKeyToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("activation_key", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("activation_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardActivatorDataConverter:findAttribute("activation_key"):asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_ActivationKeyAttribute_NonEmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("activation_key", "A")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("A", element:findAttribute("activation_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isTrue(keyboardActivatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_ActivationKeyAttribute_NonEmptyString_SetsActivationKeyToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("activation_key", "A")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("A", element:findAttribute("activation_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("A", keyboardActivatorDataConverter:findAttribute("activation_key"):asString())
	end
    
	-- Convert Deactivation Key Tests
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_NoDeactivationKeyAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("deactivation_key"))

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isTrue(keyboardActivatorDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_NoDeactivationKeyAttribute_SetsDeactivationKeyToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("deactivation_key"))

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardActivatorDataConverter:findAttribute("deactivation_key"):asString())
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_DeactivationKeyAttribute_EmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("deactivation_key", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("deactivation_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isTrue(keyboardActivatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_DeactivationKeyAttribute_EmptyString_SetsDeactivationKeyToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("deactivation_key", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("deactivation_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardActivatorDataConverter:findAttribute("deactivation_key"):asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_DeactivationKeyAttribute_NonEmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("deactivation_key", "A")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("A", element:findAttribute("deactivation_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isTrue(keyboardActivatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_DeactivationKeyAttribute_NonEmptyString_SetsDeactivationKeyToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("deactivation_key", "A")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("A", element:findAttribute("deactivation_key"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("A", keyboardActivatorDataConverter:findAttribute("deactivation_key"):asString())
	end
    
	-- Convert Input Mode Tests
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_NoInputModeAttribute_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("input_mode"))

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isTrue(keyboardActivatorDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_NoInputModeAttribute_SetsInputModeToToggleString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("input_mode"))

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("Toggle", keyboardActivatorDataConverter:findAttribute("input_mode"):asString())
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_InputModeAttribute_EmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("input_mode", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("input_mode"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isTrue(keyboardActivatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_InputModeAttribute_EmptyString_SetsInputModeToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("input_mode", "")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("input_mode"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardActivatorDataConverter:findAttribute("input_mode"):asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_InputModeAttribute_NonEmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("input_mode", "Continuous")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("Continuous", element:findAttribute("input_mode"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isTrue(keyboardActivatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_InputModeAttribute_NonEmptyString_SetsInputModeToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		element:setAttribute("input_mode", "Continuous")
		document:insertFirstChild(element)

		CelesteAssert.areEqual("Continuous", element:findAttribute("input_mode"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("Continuous", keyboardActivatorDataConverter:findAttribute("input_mode"):asString())
	end
    
	-- Convert Target Tests
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_NoTargetAttribute_ReturnsFalse()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("target"))

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isFalse(keyboardActivatorDataConverter:convertFromXML(FILE_PATH))
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_NoTargetAttribute_SetsTarget_ToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
		document:insertFirstChild(element)

		CelesteAssert.isNil(element:findAttribute("target"))

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardActivatorDataConverter:findAttribute("target"):asString())
	end

	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_TargetAttribute_EmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "") -- Required
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("target"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isTrue(keyboardActivatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_TargetAttribute_EmptyString_SetsTargetToEmptyString()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "") -- Required
		document:insertFirstChild(element)

		CelesteAssert.areEqual("", element:findAttribute("target"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("", keyboardActivatorDataConverter:findAttribute("target"):asString())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_TargetAttribute_NonEmptyString_ReturnsTrue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.areEqual("Test", element:findAttribute("target"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")

		CelesteAssert.isTrue(keyboardActivatorDataConverter:convertFromXML(FILE_PATH))
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.convertFromXML_TargetAttribute_NonEmptyString_SetsTargetToAttributeValue()
		local document = XMLDocument.new()
		local element = document:newElement("KeyboardActivator")
        element:setAttribute("target", "Test") -- Required
		document:insertFirstChild(element)

		CelesteAssert.areEqual("Test", element:findAttribute("target"):asString())

		document:saveFile(FILE_PATH)
		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(FILE_PATH)

		CelesteAssert.areEqual("Test", keyboardActivatorDataConverter:findAttribute("target"):asString())
	end
    
	-- SetValues Tests
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.setValues_SetsActivationKeyToAttributeValue()
        local screen = TestKeyboardActivatorDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local keyboardActivator = gameObject:addComponent("KeyboardActivator")

		CelesteAssert.isNotNil(keyboardActivator)
	    CelesteAssert.areEqual("", keyboardActivator:getActivationKey())

		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(KeyboardActivatorLoadingResources.Valid);

        CelesteAssert.hasAttribute(keyboardActivatorDataConverter, "activation_key")
		CelesteAssert.areEqual("A", keyboardActivatorDataConverter:findAttribute("activation_key"):asString())

		keyboardActivatorDataConverter:setValues(keyboardActivator)

		CelesteAssert.areEqual("A", keyboardActivator:getActivationKey())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.setValues_SetsDeactivationKeyToAttributeValue()
		local screen = TestKeyboardActivatorDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local keyboardActivator = gameObject:addComponent("KeyboardActivator")

		CelesteAssert.isNotNil(keyboardActivator)
	    CelesteAssert.areEqual("", keyboardActivator:getDeactivationKey())

		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(KeyboardActivatorLoadingResources.Valid);

        CelesteAssert.hasAttribute(keyboardActivatorDataConverter, "deactivation_key")
		CelesteAssert.areEqual("B", keyboardActivatorDataConverter:findAttribute("deactivation_key"):asString())

		keyboardActivatorDataConverter:setValues(keyboardActivator)

		CelesteAssert.areEqual("B", keyboardActivator:getDeactivationKey())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.setValues_SetsInputModeToAttributeValue()
		local screen = TestKeyboardActivatorDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local keyboardActivator = gameObject:addComponent("KeyboardActivator")

		CelesteAssert.isNotNil(keyboardActivator)
	    CelesteAssert.areEqual("Toggle", keyboardActivator:getInputMode())

		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(KeyboardActivatorLoadingResources.Valid);

        CelesteAssert.hasAttribute(keyboardActivatorDataConverter, "input_mode")
		CelesteAssert.areEqual("Continuous", keyboardActivatorDataConverter:findAttribute("input_mode"):asString())

		keyboardActivatorDataConverter:setValues(keyboardActivator)

		CelesteAssert.areEqual("Continuous", keyboardActivator:getInputMode())
	end
	
	------------------------------------------------------------------------------------------------
	function TestKeyboardActivatorDataConverter.setValues_SetsTargetToAttributeValue()
		local screen = TestKeyboardActivatorDataConverter.Screen
        local gameObject = screen:allocateGameObject()
		local keyboardActivator = gameObject:addComponent("KeyboardActivator")

		CelesteAssert.isNotNil(keyboardActivator)
	    CelesteAssert.isNil(keyboardActivator:getTarget())

		local keyboardActivatorDataConverter = LuaComponentDataConverter.getConverter("KeyboardActivator")
		keyboardActivatorDataConverter:convertFromXML(KeyboardActivatorLoadingResources.Valid);

        CelesteAssert.hasAttribute(keyboardActivatorDataConverter, "target")
		CelesteAssert.areEqual("Test", keyboardActivatorDataConverter:findAttribute("target"):asString())
        
        local target = screen:allocateGameObject()
        target:setName("Test")

		keyboardActivatorDataConverter:setValues(keyboardActivator)

		CelesteAssert.isNotNil(keyboardActivator:getTarget())
        CelesteAssert.areEqual(target, keyboardActivator:getTarget())
	end
	

return TestKeyboardActivatorDataConverter