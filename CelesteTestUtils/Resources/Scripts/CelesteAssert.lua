local LuaAssert = require "LuaAssert"


local CelesteAssert = {}

	-- Lua Assert Functions
	------------------------------------------------------------------------------------------------
	function CelesteAssert.isTrue(condition, message)
		LuaAssert.assertIsTrue(condition, message or "")
	end

	------------------------------------------------------------------------------------------------
	function CelesteAssert.isFalse(condition, message)
		LuaAssert.assertIsFalse(condition, message or "")
	end
	
	------------------------------------------------------------------------------------------------
	function CelesteAssert.fail(message)
		CelesteAssert.isTrue(false, message or "")
	end
	
	------------------------------------------------------------------------------------------------
	function CelesteAssert.areEqual(expected, actual, message)
		if expected ~= actual then
            local mt = getmetatable(expected)

			if mt ~= nil and getmetatable(expected).__get ~= nil then
				-- We have a handle object for our expected, so see if our actual equals it using handle equality
				CelesteAssert.isTrue(expected:equals(actual), message or "")
			else
				-- We have non handle types
				LuaAssert.assertEquals(actual, expected, message or "")
			end
		end
	end
	
	------------------------------------------------------------------------------------------------
	function CelesteAssert.areNotEqual(expected, actual, message)
		if expected == actual then
            local mt = getmetatable(expected)

			if mt ~= nil and getmetatable(expected).__get ~= nil then
				-- We have a handle object for our expected, so see if our actual does not equal it using handle equality
				CelesteAssert.isFalse(expected:equals(actual), message or "")
			else
				-- We have non handle types
				LuaAssert.assertNotEquals(actual, expected, message or "")
			end
		end
	end
	
	------------------------------------------------------------------------------------------------
	function CelesteAssert.areAlmostEqual(expected, actual, margin)
		LuaAssert.assertAlmostEquals(actual, expected, margin or 0.0000001)
	end
	
	------------------------------------------------------------------------------------------------
	function CelesteAssert.isNotNil(object, message)
        if object == nil then
            CelesteAssert.fail(message or "");
        end

        local mt = getmetatable(object)

        if mt ~= nil and mt.__get ~= nil then
			-- We have a handle
			LuaAssert.assertNotIsNil(object:__get(), message or "")
		else
			-- We have another object
			LuaAssert.assertNotIsNil(object, message or "")
		end
	end
	
	------------------------------------------------------------------------------------------------
	function CelesteAssert.isNil(object, message)
        if object == nil then
            return
        end

        local mt = getmetatable(object)

		if mt ~= nil and mt.__get ~= nil then
			-- We have a handle
			LuaAssert.assertIsNil(object:__get(), message or "")
		else
			-- We have another object type
			LuaAssert.assertIsNil(object, message or "")
		end
	end
	

	-- Attribute Functions
	------------------------------------------------------------------------------------------------
	function CelesteAssert.hasAttribute(dataConverter, attributeName)
		CelesteAssert.isNotNil(dataConverter)
		CelesteAssert.isNotNil(dataConverter:findAttribute(attributeName))
	end

	------------------------------------------------------------------------------------------------
	function CelesteAssert.attributeIsString(attribute)
		LuaAssert.assertNotIsNil(attribute)
		LuaAssert.assertIsTrue(attribute:isString())
	end
	
	------------------------------------------------------------------------------------------------
	function CelesteAssert.attributeIsBool(attribute)
		LuaAssert.assertNotIsNil(attribute)
		LuaAssert.assertIsTrue(attribute:isBool())
	end
	
	------------------------------------------------------------------------------------------------
	function CelesteAssert.attributeIsFloat(attribute)
		LuaAssert.assertNotIsNil(attribute)
		LuaAssert.assertIsTrue(attribute:isFloat())
	end
    
	------------------------------------------------------------------------------------------------
	function CelesteAssert.attributeIsVec2(attribute)
		LuaAssert.assertNotIsNil(attribute)
		LuaAssert.assertIsTrue(attribute:isVec2())
	end

	------------------------------------------------------------------------------------------------
	function CelesteAssert.attributeIsUVec2(attribute)
		LuaAssert.assertNotIsNil(attribute)
		LuaAssert.assertIsTrue(attribute:isUVec2())
	end


return CelesteAssert