local CelesteAssert = require "CelesteAssert"
local GameObject = require "Objects.GameObject"


local TestGameObject = { }
	
	TestGameObject.name = "Test GameObject"

	-- Find Component Tests
    ------------------------------------------------------------------------------------------------
    function TestGameObject.findComponent_InputtingNilGameObject_ReturnsNil()
        CelesteAssert.isNil(GameObject.findComponent(nil, "SpriteRenderer")
    end
	
    ------------------------------------------------------------------------------------------------
    function TestGameObject.findComponent_InputtingEmptyComponentName_ReturnsNil()
        CelesteAssert.fail()
    end
    
    ------------------------------------------------------------------------------------------------
    function TestGameObject.findComponent_InputtingNonExistentComponentName_ReturnsNil()
        CelesteAssert.fail()
    end
    
    ------------------------------------------------------------------------------------------------
    function TestGameObject.findComponent_InputtingExistentComponentName_ReturnsCorrectCastedHandle()
        CelesteAssert.fail()
    end
    
    ------------------------------------------------------------------------------------------------
    function TestGameObject.findComponent_InputtingExistentComponentName_ReturnsFirstMatchingComponentHandle()
        CelesteAssert.fail()
    end
    
	-- Find Child Game Object Tests
    ------------------------------------------------------------------------------------------------
    function TestGameObject.findChildGameObject_InputtingNilGameObject_ReturnsNil()
        CelesteAssert.fail()
    end

    ------------------------------------------------------------------------------------------------
    function TestGameObject.findChildGameObject_InputtingEmptyChildName_ReturnsNil()
        CelesteAssert.fail()
    end
	
    ------------------------------------------------------------------------------------------------
    function TestGameObject.findChildGameObject_InputtingNonExistentChildName_ReturnsNil()
        CelesteAssert.fail()
    end
		
    ------------------------------------------------------------------------------------------------
    function TestGameObject.findChildGameObject_InputtingExistentChildName_ReturnsCorrectGameObjectHandle()
        CelesteAssert.fail()
    end
	
    ------------------------------------------------------------------------------------------------
    function TestGameObject.findChildGameObject_InputtingExistentChildName_ReturnsFirstMatchingGameObjectHandle()
        CelesteAssert.fail()
    end
	

return TestPath