local CelesteAssert = require "CelesteAssert"
local path = require "Core.FileSystem.Path"


local TestPath = { }
	
	TestPath.name = "Test Path"

	-- Combine Tests
    ------------------------------------------------------------------------------------------------
    function TestPath.combineTwoStrings_FirstStringEmpty_ReturnsSecondString()
        CelesteAssert.areEqual("Path", path.combine("", "Path"))
    end
	
    ------------------------------------------------------------------------------------------------
    function TestPath.combineTwoStrings_SecondStringEmpty_ReturnsFirstString()
        CelesteAssert.areEqual("Test", path.combine("Test", ""))
    end

    ------------------------------------------------------------------------------------------------
    function TestPath.combineTwoStrings_ReturnsCorrectCombinedPath()
        CelesteAssert.areEqual("Test"..path.sep.."Path", path.combine("Test", "Path"))
    end

	------------------------------------------------------------------------------------------------
    function TestPath.combineTwoStrings_WithSeparatorOnFirst_ReturnsCorrectCombinedPath()
        CelesteAssert.areEqual("Test"..path.sep.."Path", path.combine("Test"..path.sep, "Path"))
    end
	
	------------------------------------------------------------------------------------------------
    function TestPath.combineTwoStrings_WithSeparatorOnSecond_ReturnsCorrectCombinedPath()
        CelesteAssert.areEqual("Test"..path.sep.."Path", path.combine("Test", path.sep.."Path"))
    end
	
	------------------------------------------------------------------------------------------------
    function TestPath.combineTwoStrings_MultiLayerStrings_ReturnsCorrectCombinedPath()
        CelesteAssert.areEqual("Test"..path.sep.."Path"..path.sep.."Combination", path.combine("Test", "Path"..path.sep.."Combination"))
    end
	
	------------------------------------------------------------------------------------------------
    function TestPath.combineMoreThanThreeStrings_MiddleStringEmpty_ReturnsFirstAndThirdCorrectCombinedPath()
        CelesteAssert.areEqual("Test"..path.sep.."Combination", path.combine("Test", "", "Combination"))
    end

	------------------------------------------------------------------------------------------------
    function TestPath.combineMoreThanThreeStrings_ReturnsCorrectCombinedPath()
        CelesteAssert.areEqual("Test"..path.sep.."Path"..path.sep.."Combination", path.combine("Test", "Path", "Combination"))
    end


return TestPath