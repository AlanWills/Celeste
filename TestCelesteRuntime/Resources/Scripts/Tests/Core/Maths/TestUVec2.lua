local CelesteAssert = require "CelesteAssert"


local TestUVec2 = { }
	
  TestUVec2.name = "Test UVec2"

  -- Constructor Tests
  ------------------------------------------------------------------------------------------------
  function TestUVec2.constructor_NoArguments_SetsXToZero()
    local vector = uvec2.new()

    CelesteAssert.areEqual(0, vector.x);
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.constructor_NoArguments_SetsYToZero()
    local vector = uvec2.new()

    CelesteAssert.areEqual(0, vector.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.constructor_SingleUIntArgument_SetsXToUIntValue()
    local vector = uvec2.new(112)

    CelesteAssert.areAlmostEqual(112, vector.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.constructor_SingleUIntArgument_SetsYToUIntValue()
    local vector = uvec2.new(112)

    CelesteAssert.areAlmostEqual(112, vector.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.constructor_UVec2Argument_SetsXToUIntValue()
    local vector = uvec2.new(32, 112)
    local vector2 = uvec2.new(vector)

    CelesteAssert.areAlmostEqual(32, vector2.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.constructor_UVec2Argument_SetsYToUIntValue()
    local vector = uvec2.new(32, 112)
    local vector2 = uvec2.new(vector)

    CelesteAssert.areAlmostEqual(112, vector2.y);
  end
	
  -- Addition Tests
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_AddingTwoZeroUVec2s_SetsXToZero()
    local lhs = uvec2.new()
    local rhs = uvec2.new()
    local result = lhs + rhs

    CelesteAssert.areAlmostEqual(0, result.x);
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_AddingTwoZeroUVec2s_SetsYToZero()
    local lhs = uvec2.new()
    local rhs = uvec2.new()
    local result = lhs + rhs

    CelesteAssert.areAlmostEqual(0, result.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_AddingLhsNonZeroUVec2_ToRhsZeroUVec2_SetsXToCorrectValue()
    local lhs = uvec2.new(12, 1)
    local rhs = uvec2.new()
    local result = lhs + rhs

    CelesteAssert.areAlmostEqual(12, result.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_AddingLhsNonZeroUVec2_ToRhsZeroUVec2_SetsYToCorrectValue()
    local lhs = uvec2.new(12, 1)
    local rhs = uvec2.new()
    local result = lhs + rhs

    CelesteAssert.areAlmostEqual(1, result.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_AddingLhsNonZeroUVec2_ToRhsNonZeroUVec2_SetsXToCorrectValue()
    local lhs = uvec2.new(12, 1)
    local rhs = uvec2.new(32, 145)
    local result = lhs + rhs

    CelesteAssert.areAlmostEqual(44, result.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_AddingLhsNonZeroUVec2_ToRhsNonZeroUVec2_SetsYToCorrectValue()
    local lhs = uvec2.new(12, 1)
    local rhs = uvec2.new(32, 145)
    local result = lhs + rhs

    CelesteAssert.areAlmostEqual(146, result.y);
  end
	
  -- Subtraction Tests
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_SubtractingTwoZeroUVec2s_SetsXToZero()
    local lhs = uvec2.new()
    local rhs = uvec2.new()
    local result = lhs - rhs

    CelesteAssert.areAlmostEqual(0, result.x);
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_SubtractingTwoZeroUVec2s_SetsYToZero()
    local lhs = uvec2.new()
    local rhs = uvec2.new()
    local result = lhs - rhs

    CelesteAssert.areAlmostEqual(0, result.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_SubtractingLhsNonZeroUVec2_FromRhsZeroUVec2_SetsXToCorrectValue()
    local lhs = uvec2.new(12, 1)
    local rhs = uvec2.new()
    local result = lhs - rhs

    CelesteAssert.areAlmostEqual(12, result.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_SubtractingLhsNonZeroUVec2_FromRhsZeroUVec2_SetsYToCorrectValue()
    local lhs = uvec2.new(12, 1)
    local rhs = uvec2.new()
    local result = lhs - rhs

    CelesteAssert.areAlmostEqual(1, result.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_SubtractingLhsNonZeroUVec2_FromRhsNonZeroUVec2_SetsXToCorrectValue()
    local lhs = uvec2.new(120, 1000)
    local rhs = uvec2.new(32, 145)
    local result = lhs - rhs

    CelesteAssert.areAlmostEqual(88, result.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_SubtractingLhsNonZeroUVec2_FromRhsNonZeroUVec2_SetsYToCorrectValue()
    local lhs = uvec2.new(120, 1000)
    local rhs = uvec2.new(32, 145)
    local result = lhs - rhs

    CelesteAssert.areAlmostEqual(855, result.y);
  end
	
  -- Multiplication Tests
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_MultiplyingTwoZeroUVec2s_SetsXToZero()
    local lhs = uvec2.new()
    local rhs = uvec2.new()
    local result = lhs * rhs

    CelesteAssert.areAlmostEqual(0, result.x);
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_MultiplyingTwoZeroUVec2s_SetsYToZero()
    local lhs = uvec2.new()
    local rhs = uvec2.new()
    local result = lhs * rhs

    CelesteAssert.areAlmostEqual(0, result.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_MultiplyingLhsNonZeroUVec2_FromRhsZeroUVec2_SetsXToZero()
    local lhs = uvec2.new(12, 1)
    local rhs = uvec2.new()
    local result = lhs * rhs

    CelesteAssert.areAlmostEqual(0, result.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_MultiplyingLhsNonZeroUVec2_FromRhsZeroUVec2_SetsYToZero()
    local lhs = uvec2.new(12, 1)
    local rhs = uvec2.new()
    local result = lhs * rhs

    CelesteAssert.areAlmostEqual(0, result.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_MultiplyingLhsNonZeroUVec2_FromRhsNonZeroUVec2_SetsXToCorrectValue()
    local lhs = uvec2.new(12, 1)
    local rhs = uvec2.new(32, 145)
    local result = lhs * rhs

    CelesteAssert.areAlmostEqual(384, result.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_MultiplyingLhsNonZeroUVec2_FromRhsNonZeroUVec2_SetsYToCorrectValue()
    local lhs = uvec2.new(12, 10)
    local rhs = uvec2.new(32, 145)
    local result = lhs * rhs

    CelesteAssert.areAlmostEqual(1450, result.y);
  end
	
  -- Division Tests
  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_DividingZeroXComponentUVec2_ByNonZeroXComponentUVec2_SetsXToZero()
    local lhs = uvec2.new(0, 1)
    local rhs = uvec2.new(32, 145)
    local result = lhs / rhs

    CelesteAssert.areAlmostEqual(0, result.x);
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_DividingZeroYComponentUVec2_ByNonZeroYComponentUVec2_SetsYToZero()
    local lhs = uvec2.new(1, 0)
    local rhs = uvec2.new(32, 145)
    local result = lhs / rhs

    CelesteAssert.areAlmostEqual(0, result.y);
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_DividingNonZeroXComponentUVec2_ByNonZeroXComponentUVec2_SetsXToCorrectValue()
    local lhs = uvec2.new(30, 1)
    local rhs = uvec2.new(5, 145)
    local result = lhs / rhs

    CelesteAssert.areAlmostEqual(6, result.x);
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.addition_DividingNonZeroYComponentUVec2_ByNonZeroYComponentUVec2_SetsYToCorrectValue()
    local lhs = uvec2.new(1, 110)
    local rhs = uvec2.new(32, 10)
    local result = lhs / rhs

    CelesteAssert.areAlmostEqual(11, result.y);
  end
	
  -- Equality Operator Tests
  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_TwoUVec2ComponentsEqual_ReturnsTrue()
    local lhs = uvec2.new(1, 1)
    local rhs = uvec2.new(1, 1)

    CelesteAssert.areEqual(lhs.x, rhs.x);
    CelesteAssert.areEqual(lhs.y, rhs.y);
    CelesteAssert.isTrue(lhs == rhs)
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_XComponentsDifferent_ReturnsFalse()
    local lhs = uvec2.new(1, 1)
    local rhs = uvec2.new(122321, 1)

    CelesteAssert.areNotEqual(lhs.x, rhs.x);
    CelesteAssert.areEqual(lhs.y, rhs.y);
    CelesteAssert.isFalse(lhs == rhs)
  end
  
  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_YComponentsDifferent_ReturnsFalse()
    local lhs = uvec2.new(1, 1)
    local rhs = uvec2.new(1, 123132)

    CelesteAssert.areEqual(lhs.x, rhs.x);
    CelesteAssert.areNotEqual(lhs.y, rhs.y);
    CelesteAssert.isFalse(lhs == rhs)
  end
  
  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_XAndYComponentsDifferent_ReturnsFalse()
    local lhs = uvec2.new(1, 1)
    local rhs = uvec2.new(12321, 123132)

    CelesteAssert.areNotEqual(lhs.x, rhs.x);
    CelesteAssert.areNotEqual(lhs.y, rhs.y);
    CelesteAssert.isFalse(lhs == rhs)
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_IsReflexive()
    local lhs = uvec2.new(1, 1)

    CelesteAssert.isTrue(lhs == lhs);
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_IsSymmetric()
    local lhs = uvec2.new(1, 1)
    local rhs = uvec2.new(1, 1)

    CelesteAssert.isTrue(lhs == rhs);
    CelesteAssert.isTrue(rhs == lhs);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_IsTransitive()
    local a = uvec2.new(1, 1)
    local b = uvec2.new(1, 1)

    CelesteAssert.isTrue(a == b);

    local c = uvec2.new(1, 1)

    CelesteAssert.isTrue(b == c);
    CelesteAssert.isTrue(a == c);
  end

  -- Inequality Operator Tests
  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_TwoVec2ComponentsEqual_ReturnsFalse()
    local lhs = uvec2.new(1, 1)
    local rhs = uvec2.new(1, 1)

    CelesteAssert.areEqual(lhs.x, rhs.x)
    CelesteAssert.areEqual(lhs.y, rhs.y)
    CelesteAssert.isFalse(lhs ~= rhs)
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_XComponentsDifferent_ReturnsTrue()
    local lhs = uvec2.new(1, 1)
    local rhs = uvec2.new(122321, 1)

    CelesteAssert.areNotEqual(lhs.x, rhs.x);
    CelesteAssert.areEqual(lhs.y, rhs.y);
    CelesteAssert.isTrue(lhs ~= rhs)
  end
  
  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_YComponentsDifferent_ReturnsTrue()
    local lhs = uvec2.new(1, 1)
    local rhs = uvec2.new(1, 123132)

    CelesteAssert.areEqual(lhs.x, rhs.x);
    CelesteAssert.areNotEqual(lhs.y, rhs.y);
    CelesteAssert.isTrue(lhs ~= rhs)
  end
  
  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_XAndYComponentsDifferent_ReturnsTrue()
    local lhs = uvec2.new(1, 1)
    local rhs = uvec2.new(12321, 123132)

    CelesteAssert.areNotEqual(lhs.x, rhs.x);
    CelesteAssert.areNotEqual(lhs.y, rhs.y);
    CelesteAssert.isTrue(lhs ~= rhs)
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_IsNotReflexive()
    local lhs = uvec2.new(1, 1)

    CelesteAssert.isFalse(lhs ~= lhs);
  end

  ------------------------------------------------------------------------------------------------
  function TestUVec2.equalityOperator_IsSymmetric()
    local lhs = uvec2.new(1, 1)
    local rhs = uvec2.new(12, 13)

    CelesteAssert.isTrue(lhs ~= rhs);
    CelesteAssert.isTrue(rhs ~= lhs);
  end
	

return TestUVec2