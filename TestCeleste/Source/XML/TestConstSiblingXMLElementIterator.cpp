#include "UtilityHeaders/UnitTestHeaders.h"

#include "XML/SiblingXMLElementIterator.h"

using namespace tinyxml2;
using namespace Celeste::XML;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestConstSiblingXMLElementIterator)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_Constructor_InputtingNullptr_SetsIteratorToNullptr)
  {
    SiblingXMLElementIterator<true> it(nullptr);

    Assert::IsNull(*it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_Constructor_InputtingElement_SetsIteratorToElement)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);

    Assert::IsTrue(element == *it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_Constructor_InputtingElementAndName_ElementNameIsNotInput_SetsIteratorToNullptr)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element, "Test");

    Assert::IsNull(*it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_Constructor_InputtingElementAndName_ElementNameIsInput_SetsIteratorToElement)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element, "Root");

    Assert::IsTrue(element == *it);
  }

#pragma endregion

#pragma region Dereference Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_Dereference_IteratorIsNullptr_ReturnsNullptr)
  {
    Assert::IsNull(*SiblingXMLElementIterator<true>(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_Dereference_IteratorIsNotNullptr_ReturnsCorrectXMLElementPtr)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);

    Assert::IsTrue(element == *it);
  }

#pragma endregion

#pragma region Pre Increment Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_PreIncrement_IteratorIsNullptr_LeavesIteratorAtNullptr)
  {
    SiblingXMLElementIterator<true> it(nullptr);

    Assert::IsNull(*it);

    ++it;

    Assert::IsNull(*it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_PreIncrement_IteratorIsNotNullptr_IteratesOverSiblingsCorrectly)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    XMLElement* child1 = document.NewElement("Child1");
    XMLElement* child2 = document.NewElement("Child2");
    XMLElement* child3 = document.NewElement("Child3");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child1);
    element->InsertEndChild(child2);
    element->InsertEndChild(child3);

    Assert::IsFalse(element->NoChildren());

    SiblingXMLElementIterator<true> it(child1);

    Assert::IsTrue(child1 == *it);

    ++it;

    Assert::IsTrue(child2 == *it);

    ++it;

    Assert::IsTrue(child3 == *it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_PreIncrement_WithName_IteratorIsNotNullptr_IteratesOverSiblingsWithMatchingNameCorrectly)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    XMLElement* child1 = document.NewElement("Child1");
    XMLElement* child2 = document.NewElement("Child2");
    XMLElement* child3 = document.NewElement("Child1");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child1);
    element->InsertEndChild(child2);
    element->InsertEndChild(child3);

    Assert::IsFalse(element->NoChildren());

    SiblingXMLElementIterator<true> it(child1, "Child1");

    Assert::IsTrue(child1 == *it);

    ++it;

    Assert::IsTrue(child3 == *it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_PreIncrement_IteratorIsAtFinalElement_SetsIteratorToNullptr)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);

    Assert::IsTrue(element == *it);

    ++it;

    Assert::IsNull(*it);
  }

#pragma endregion

#pragma region Post Increment Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_PostIncrement_IteratorIsNullptr_ReturnsIteratorAtNullptr)
  {
    SiblingXMLElementIterator<true> it(nullptr);

    Assert::IsNull(*it);

    it++;

    Assert::IsNull(*it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_PostIncrement_IteratorIsNotNullptr_ReturnsIteratorAtCorrectSibling)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    XMLElement* child1 = document.NewElement("Child1");
    XMLElement* child2 = document.NewElement("Child2");
    XMLElement* child3 = document.NewElement("Child3");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child1);
    element->InsertEndChild(child2);
    element->InsertEndChild(child3);

    SiblingXMLElementIterator<true> it(child1);

    Assert::IsTrue(child1 == *it);

    SiblingXMLElementIterator<true> it2 = it++;

    Assert::IsTrue(child2 == *it);
    Assert::IsTrue(child2 == *it2);
    Assert::IsFalse(&it == &it2);

    SiblingXMLElementIterator<true> it3 = it++;

    Assert::IsTrue(child3 == *it);
    Assert::IsTrue(child3 == *it3);
    Assert::IsFalse(&it == &it3);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_PostIncrement_WithName_IteratorIsNotNullptr_IteratesOverSiblingsWithMatchingNameCorrectly)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    XMLElement* child1 = document.NewElement("Child1");
    XMLElement* child2 = document.NewElement("Child2");
    XMLElement* child3 = document.NewElement("Child1");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child1);
    element->InsertEndChild(child2);
    element->InsertEndChild(child3);

    Assert::IsFalse(element->NoChildren());

    SiblingXMLElementIterator<true> it(child1, "Child1");

    Assert::IsTrue(child1 == *it);

    it++;

    Assert::IsTrue(child3 == *it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_PostIncrement_IteratorIsAtFinalElement_ReturnsIteratorAtNullptr)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);

    Assert::IsTrue(element == *it);

    it++;

    Assert::IsNull(*it);
  }

#pragma endregion

#pragma region Equality Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_EqualityOperator_IteratorsAtSameElementPtr_ShouldReturnTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);
    SiblingXMLElementIterator<true> it2(element);

    Assert::IsTrue(element == *it);
    Assert::IsTrue(element == *it2);
    Assert::IsTrue(it == it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_EqualityOperator_IteratorsBothNullptr_ShouldReturnTrue)
  {
    SiblingXMLElementIterator<true> it(nullptr);
    SiblingXMLElementIterator<true> it2(nullptr);

    Assert::IsNull(*it);
    Assert::IsNull(*it2);
    Assert::IsTrue(it == it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_EqualityOperator_IteratorsAtDifferentElementPtrs_ShouldReturnFalse)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    XMLElement* child1 = document.NewElement("Child1");
    XMLElement* child2 = document.NewElement("Child2");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child1);
    element->InsertEndChild(child2);

    SiblingXMLElementIterator<true> it(child1);
    SiblingXMLElementIterator<true> it2(child2);

    Assert::IsTrue(child1 == *it);
    Assert::IsTrue(child2 == *it2);
    Assert::IsFalse(it == it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_EqualityOperator_OneIteratorNullptr_OneNotNullptr_ShouldReturnFalse)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);
    SiblingXMLElementIterator<true> it2(nullptr);

    Assert::IsTrue(element == *it);
    Assert::IsNull(*it2);
    Assert::IsFalse(it == it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_EqualityOperator_IsReflexive)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);

    Assert::IsTrue(element == *it);
    Assert::IsTrue(it == it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_EqualityOperator_IsSymmetric)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);
    SiblingXMLElementIterator<true> it2(element);

    Assert::IsTrue(element == *it);
    Assert::IsTrue(element == *it2);
    Assert::IsTrue(it == it2);
    Assert::IsTrue(it2 == it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_EqualityOperator_IsTransitive)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);
    SiblingXMLElementIterator<true> it2(element);
    SiblingXMLElementIterator<true> it3(element);

    Assert::IsTrue(element == *it);
    Assert::IsTrue(element == *it2);
    Assert::IsTrue(element == *it3);
    Assert::IsTrue(it == it2);
    Assert::IsTrue(it2 == it3);
    Assert::IsTrue(it == it3);
  }

#pragma endregion

#pragma region Inequality Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_InequalityOperator_IteratorsAtSameElementPtr_ShouldReturnFalse)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);
    SiblingXMLElementIterator<true> it2(element);

    Assert::IsTrue(element == *it);
    Assert::IsTrue(element == *it2);
    Assert::IsFalse(it != it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_InequalityOperator_IteratorsBothNullptr_ShouldReturnFalse)
  {
    SiblingXMLElementIterator<true> it(nullptr);
    SiblingXMLElementIterator<true> it2(nullptr);

    Assert::IsNull(*it);
    Assert::IsNull(*it2);
    Assert::IsFalse(it != it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_InequalityOperator_IteratorsAtDifferentElementPtrs_ShouldReturnTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    XMLElement* child1 = document.NewElement("Child1");
    XMLElement* child2 = document.NewElement("Child2");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child1);
    element->InsertEndChild(child2);

    SiblingXMLElementIterator<true> it(child1);
    SiblingXMLElementIterator<true> it2(child2);

    Assert::IsTrue(child1 == *it);
    Assert::IsTrue(child2 == *it2);
    Assert::IsTrue(it != it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_InequalityOperator_OneIteratorNullptr_OneNotNullptr_ShouldReturnTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);
    SiblingXMLElementIterator<true> it2(nullptr);

    Assert::IsTrue(element == *it);
    Assert::IsNull(*it2);
    Assert::IsTrue(it != it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_InequalityOperator_CompareToSelf_ShouldReturnFalse)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);

    Assert::IsTrue(element == *it);
    Assert::IsFalse(it != it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstSiblingXMLElementIterator_InequalityOperator_IsSymmetric)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<true> it(element);
    SiblingXMLElementIterator<true> it2(nullptr);

    Assert::IsTrue(element == *it);
    Assert::IsNull(*it2);
    Assert::IsTrue(it != it2);
    Assert::IsTrue(it2 != it);
  }

#pragma endregion

  };
}