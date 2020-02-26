local CelesteAssert = require "CelesteAssert"


local TestVec2 = { }
	
  TestVec2.name = "Test Vec2"

  -- Constructor Tests
  ------------------------------------------------------------------------------------------------
  function TestVec2.constructor_NoArguments_SetsXToZero()
    local vector = vec2.new()

    CelesteAssert.areEqual(0, vector.x);
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.constructor_NoArguments_SetsYToZero()
    local vector = vec2.new()

    CelesteAssert.areEqual(0, vector.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.constructor_SingleFloatArgument_SetsXToFloatValue()
    local vector = vec2.new(-1.12)

    CelesteAssert.areAlmostEqual(-1.12, vector.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.constructor_SingleFloatArgument_SetsYToFloatValue()
    local vector = vec2.new(-1.12)

    CelesteAssert.areAlmostEqual(-1.12, vector.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.constructor_Vec2Argument_SetsXToFloatValue()
    local vector = vec2.new(3.2, -1.12)
    local vector2 = vec2.new(vector)

    CelesteAssert.areAlmostEqual(3.2, vector2.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.constructor_Vec2Argument_SetsYToFloatValue()
    local vector = vec2.new(3.2, -1.12)
    local vector2 = vec2.new(vector)

    CelesteAssert.areAlmostEqual(-1.12, vector2.y);
  end
	
  -- Addition Tests
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_AddingTwoZeroVec2s_SetsXToZero()
    local lhs = vec2.new()
    local rhs = vec2.new()
    local result = lhs + rhs

    CelesteAssert.areAlmostEqual(0, result.x);
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_AddingTwoZeroVec2s_SetsYToZero()
    local lhs = vec2.new()
    local rhs = vec2.new()
    local result = lhs + rhs

    CelesteAssert.areAlmostEqual(0, result.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_AddingLhsNonZeroVec2_ToRhsZeroVec2_SetsXToCorrectValue()
    local lhs = vec2.new(12, -0.1)
    local rhs = vec2.new()
    local result = lhs + rhs

    CelesteAssert.areAlmostEqual(12, result.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_AddingLhsNonZeroVec2_ToRhsZeroVec2_SetsYToCorrectValue()
    local lhs = vec2.new(12, -0.1)
    local rhs = vec2.new()
    local result = lhs + rhs

    CelesteAssert.areAlmostEqual(-0.1, result.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_AddingLhsNonZeroVec2_ToRhsNonZeroVec2_SetsXToCorrectValue()
    local lhs = vec2.new(12, -0.1)
    local rhs = vec2.new(-3.2, 1.45)
    local result = lhs + rhs

    CelesteAssert.areAlmostEqual(8.8, result.x, 0.000001);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_AddingLhsNonZeroVec2_ToRhsNonZeroVec2_SetsYToCorrectValue()
    local lhs = vec2.new(12, -0.1)
    local rhs = vec2.new(-3.2, 1.45)
    local result = lhs + rhs

    CelesteAssert.areAlmostEqual(1.35, result.y, 0.000001);
  end
	
  -- Subtraction Tests
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_SubtractingTwoZeroVec2s_SetsXToZero()
    local lhs = vec2.new()
    local rhs = vec2.new()
    local result = lhs - rhs

    CelesteAssert.areAlmostEqual(0, result.x);
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_SubtractingTwoZeroVec2s_SetsYToZero()
    local lhs = vec2.new()
    local rhs = vec2.new()
    local result = lhs - rhs

    CelesteAssert.areAlmostEqual(0, result.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_SubtractingLhsNonZeroVec2_FromRhsZeroVec2_SetsXToCorrectValue()
    local lhs = vec2.new(12, -0.1)
    local rhs = vec2.new()
    local result = lhs - rhs

    CelesteAssert.areAlmostEqual(12, result.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_SubtractingLhsNonZeroVec2_FromRhsZeroVec2_SetsYToCorrectValue()
    local lhs = vec2.new(12, -0.1)
    local rhs = vec2.new()
    local result = lhs - rhs

    CelesteAssert.areAlmostEqual(-0.1, result.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_SubtractingLhsNonZeroVec2_FromRhsNonZeroVec2_SetsXToCorrectValue()
    local lhs = vec2.new(12, -0.1)
    local rhs = vec2.new(-3.2, 1.45)
    local result = lhs - rhs

    CelesteAssert.areAlmostEqual(15.2, result.x, 0.000001);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_SubtractingLhsNonZeroVec2_FromRhsNonZeroVec2_SetsYToCorrectValue()
    local lhs = vec2.new(12, -0.1)
    local rhs = vec2.new(-3.2, 1.45)
    local result = lhs - rhs

    CelesteAssert.areAlmostEqual(-1.55, result.y, 0.000001);
  end
	
  -- Multiplication Tests
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_MultiplyingTwoZeroVec2s_SetsXToZero()
    local lhs = vec2.new()
    local rhs = vec2.new()
    local result = lhs * rhs

    CelesteAssert.areAlmostEqual(0, result.x);
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_MultiplyingTwoZeroVec2s_SetsYToZero()
    local lhs = vec2.new()
    local rhs = vec2.new()
    local result = lhs * rhs

    CelesteAssert.areAlmostEqual(0, result.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_MultiplyingLhsNonZeroVec2_FromRhsZeroVec2_SetsXToZero()
    local lhs = vec2.new(12, -0.1)
    local rhs = vec2.new()
    local result = lhs * rhs

    CelesteAssert.areAlmostEqual(0, result.x);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_MultiplyingLhsNonZeroVec2_FromRhsZeroVec2_SetsYToZero()
    local lhs = vec2.new(12, -0.1)
    local rhs = vec2.new()
    local result = lhs * rhs

    CelesteAssert.areAlmostEqual(0, result.y);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_MultiplyingLhsNonZeroVec2_FromRhsNonZeroVec2_SetsXToCorrectValue()
    local lhs = vec2.new(12, -0.1)
    local rhs = vec2.new(-3.2, 1.45)
    local result = lhs * rhs

    CelesteAssert.areAlmostEqual(-38.4, result.x, 0.00001);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_MultiplyingLhsNonZeroVec2_FromRhsNonZeroVec2_SetsYToCorrectValue()
    local lhs = vec2.new(12, -0.1)
    local rhs = vec2.new(-3.2, 1.45)
    local result = lhs * rhs

    CelesteAssert.areAlmostEqual(-0.145, result.y, 0.00001);
  end
	
  -- Division Tests
  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_DividingZeroXComponentVec2_ByNonZeroXComponentVec2_SetsXToZero()
    local lhs = vec2.new(0, -0.1)
    local rhs = vec2.new(-3.2, 1.45)
    local result = lhs / rhs

    CelesteAssert.areAlmostEqual(0, result.x);
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_DividingZeroYComponentVec2_ByNonZeroYComponentVec2_SetsYToZero()
    local lhs = vec2.new(-0.1, 0)
    local rhs = vec2.new(-3.2, 1.45)
    local result = lhs / rhs

    CelesteAssert.areAlmostEqual(0, result.y);
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_DividingNonZeroXComponentVec2_ByNonZeroXComponentVec2_SetsXToCorrectValue()
    local lhs = vec2.new(3.2, -0.1)
    local rhs = vec2.new(-0.5, 1.45)
    local result = lhs / rhs

    CelesteAssert.areAlmostEqual(-6.4, result.x);
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.addition_DividingNonZeroYComponentVec2_ByNonZeroYComponentVec2_SetsYToCorrectValue()
    local lhs = vec2.new(-0.1, 0.1)
    local rhs = vec2.new(-3.2, 10)
    local result = lhs / rhs

    CelesteAssert.areAlmostEqual(0.01, result.y);
  end
	
  -- Equality Operator Tests
  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_TwoVec2ComponentsEqual_ReturnsTrue()
    local lhs = vec2.new(-0.1, 0.1)
    local rhs = vec2.new(-0.1, 0.1)

    CelesteAssert.areEqual(lhs.x, rhs.x);
    CelesteAssert.areEqual(lhs.y, rhs.y);
    CelesteAssert.isTrue(lhs == rhs)
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_XComponentsDifferent_ReturnsFalse()
    local lhs = vec2.new(-0.1, 0.1)
    local rhs = vec2.new(122321, 0.1)

    CelesteAssert.areNotEqual(lhs.x, rhs.x);
    CelesteAssert.areEqual(lhs.y, rhs.y);
    CelesteAssert.isFalse(lhs == rhs)
  end
  
  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_YComponentsDifferent_ReturnsFalse()
    local lhs = vec2.new(-0.1, 0.1)
    local rhs = vec2.new(-0.1, 123132)

    CelesteAssert.areEqual(lhs.x, rhs.x);
    CelesteAssert.areNotEqual(lhs.y, rhs.y);
    CelesteAssert.isFalse(lhs == rhs)
  end
  
  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_XAndYComponentsDifferent_ReturnsFalse()
    local lhs = vec2.new(-0.1, 0.1)
    local rhs = vec2.new(12321, 123132)

    CelesteAssert.areNotEqual(lhs.x, rhs.x);
    CelesteAssert.areNotEqual(lhs.y, rhs.y);
    CelesteAssert.isFalse(lhs == rhs)
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_IsReflexive()
    local lhs = vec2.new(-0.1, 0.1)

    CelesteAssert.isTrue(lhs == lhs);
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_IsSymmetric()
    local lhs = vec2.new(-0.1, 0.1)
    local rhs = vec2.new(-0.1, 0.1)

    CelesteAssert.isTrue(lhs == rhs);
    CelesteAssert.isTrue(rhs == lhs);
  end
	
  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_IsTransitive()
    local a = vec2.new(-0.1, 0.1)
    local b = vec2.new(-0.1, 0.1)

    CelesteAssert.isTrue(a == b);

    local c = vec2.new(-0.1, 0.1)

    CelesteAssert.isTrue(b == c);
    CelesteAssert.isTrue(a == c);
  end

  -- Inequality Operator Tests
  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_TwoVec2ComponentsEqual_ReturnsFalse()
    local lhs = vec2.new(-0.1, 0.1)
    local rhs = vec2.new(-0.1, 0.1)

    CelesteAssert.areEqual(lhs.x, rhs.x)
    CelesteAssert.areEqual(lhs.y, rhs.y)
    CelesteAssert.isFalse(lhs ~= rhs)
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_XComponentsDifferent_ReturnsTrue()
    local lhs = vec2.new(-0.1, 0.1)
    local rhs = vec2.new(122321, 0.1)

    CelesteAssert.areNotEqual(lhs.x, rhs.x);
    CelesteAssert.areEqual(lhs.y, rhs.y);
    CelesteAssert.isTrue(lhs ~= rhs)
  end
  
  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_YComponentsDifferent_ReturnsTrue()
    local lhs = vec2.new(-0.1, 0.1)
    local rhs = vec2.new(-0.1, 123132)

    CelesteAssert.areEqual(lhs.x, rhs.x);
    CelesteAssert.areNotEqual(lhs.y, rhs.y);
    CelesteAssert.isTrue(lhs ~= rhs)
  end
  
  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_XAndYComponentsDifferent_ReturnsTrue()
    local lhs = vec2.new(-0.1, 0.1)
    local rhs = vec2.new(12321, 123132)

    CelesteAssert.areNotEqual(lhs.x, rhs.x);
    CelesteAssert.areNotEqual(lhs.y, rhs.y);
    CelesteAssert.isTrue(lhs ~= rhs)
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_IsNotReflexive()
    local lhs = vec2.new(-0.1, 0.1)

    CelesteAssert.isFalse(lhs ~= lhs);
  end

  ------------------------------------------------------------------------------------------------
  function TestVec2.equalityOperator_IsSymmetric()
    local lhs = vec2.new(-0.1, 0.1)
    local rhs = vec2.new(12, 13)

    CelesteAssert.isTrue(lhs ~= rhs);
    CelesteAssert.isTrue(rhs ~= lhs);
  end
	

return TestVec2