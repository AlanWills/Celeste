#include "UtilityHeaders/UnitTestHeaders.h"

#include "XML/SiblingXMLElementIterator.h"

using namespace tinyxml2;
using namespace Celeste::XML;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestSiblingXMLElementIterator)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_Constructor_InputtingNullptr_SetsIteratorToNullptr)
  {
    SiblingXMLElementIterator<false> it(nullptr);

    Assert::IsNull(*it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_Constructor_InputtingElement_SetsIteratorToElement)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);

    Assert::IsTrue(element == *it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_Constructor_InputtingElementAndName_ElementNameIsNotInput_SetsIteratorToNullptr)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element, "Test");

    Assert::IsNull(*it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_Constructor_InputtingElementAndName_ElementNameIsInput_SetsIteratorToElement)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element, "Root");

    Assert::IsTrue(element == *it);
  }

#pragma endregion

#pragma region Dereference Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_Dereference_IteratorIsNullptr_ReturnsNullptr)
  {
    Assert::IsNull(*SiblingXMLElementIterator<false>(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_Dereference_IteratorIsNotNullptr_ReturnsCorrectXMLElementPtr)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);

    Assert::IsTrue(element == *it);
  }

#pragma endregion

#pragma region Pre Increment Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_PreIncrement_IteratorIsNullptr_LeavesIteratorAtNullptr)
  {
    SiblingXMLElementIterator<false> it(nullptr);

    Assert::IsNull(*it);

    ++it;

    Assert::IsNull(*it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_PreIncrement_IteratorIsNotNullptr_IteratesOverSiblingsCorrectly)
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

    SiblingXMLElementIterator<false> it(child1);

    Assert::IsTrue(child1 == *it);

    ++it;

    Assert::IsTrue(child2 == *it);

    ++it;

    Assert::IsTrue(child3 == *it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_PreIncrement_WithName_IteratorIsNotNullptr_IteratesOverSiblingsWithMatchingNameCorrectly)
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

    SiblingXMLElementIterator<false> it(child1, "Child1");

    Assert::IsTrue(child1 == *it);

    ++it;

    Assert::IsTrue(child3 == *it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_PreIncrement_IteratorIsAtFinalElement_SetsIteratorToNullptr)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);

    Assert::IsTrue(element == *it);

    ++it;

    Assert::IsNull(*it);
  }

#pragma endregion

#pragma region Post Increment Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_PostIncrement_IteratorIsNullptr_ReturnsIteratorAtNullptr)
  {
    SiblingXMLElementIterator<false> it(nullptr);

    Assert::IsNull(*it);

    it++;

    Assert::IsNull(*it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_PostIncrement_IteratorIsNotNullptr_ReturnsIteratorAtCorrectSibling)
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

    SiblingXMLElementIterator<false> it(child1);

    Assert::IsTrue(child1 == *it);

    SiblingXMLElementIterator<false> it2 = it++;

    Assert::IsTrue(child2 == *it);
    Assert::IsTrue(child2 == *it2);
    Assert::IsFalse(&it == &it2);

    SiblingXMLElementIterator<false> it3 = it++;

    Assert::IsTrue(child3 == *it);
    Assert::IsTrue(child3 == *it3);
    Assert::IsFalse(&it == &it3);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_PostIncrement_WithName_IteratorIsNotNullptr_IteratesOverSiblingsWithMatchingNameCorrectly)
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

    SiblingXMLElementIterator<false> it(child1, "Child1");

    Assert::IsTrue(child1 == *it);

    it++;

    Assert::IsTrue(child3 == *it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_PostIncrement_IteratorIsAtFinalElement_ReturnsIteratorAtNullptr)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);

    Assert::IsTrue(element == *it);

    it++;

    Assert::IsNull(*it);
  }

#pragma endregion

#pragma region Equality Operator Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_EqualityOperator_IteratorsAtSameElementPtr_ShouldReturnTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);
    SiblingXMLElementIterator<false> it2(element);

    Assert::IsTrue(element == *it);
    Assert::IsTrue(element == *it2);
    Assert::IsTrue(it == it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_EqualityOperator_IteratorsBothNullptr_ShouldReturnTrue)
  {
    SiblingXMLElementIterator<false> it(nullptr);
    SiblingXMLElementIterator<false> it2(nullptr);

    Assert::IsNull(*it);
    Assert::IsNull(*it2);
    Assert::IsTrue(it == it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_EqualityOperator_IteratorsAtDifferentElementPtrs_ShouldReturnFalse)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    XMLElement* child1 = document.NewElement("Child1");
    XMLElement* child2 = document.NewElement("Child2");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child1);
    element->InsertEndChild(child2);

    SiblingXMLElementIterator<false> it(child1);
    SiblingXMLElementIterator<false> it2(child2);

    Assert::IsTrue(child1 == *it);
    Assert::IsTrue(child2 == *it2);
    Assert::IsFalse(it == it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_EqualityOperator_OneIteratorNullptr_OneNotNullptr_ShouldReturnFalse)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);
    SiblingXMLElementIterator<false> it2(nullptr);

    Assert::IsTrue(element == *it);
    Assert::IsNull(*it2);
    Assert::IsFalse(it == it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_EqualityOperator_IsReflexive)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);

    Assert::IsTrue(element == *it);
    Assert::IsTrue(it == it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_EqualityOperator_IsSymmetric)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);
    SiblingXMLElementIterator<false> it2(element);

    Assert::IsTrue(element == *it);
    Assert::IsTrue(element == *it2);
    Assert::IsTrue(it == it2);
    Assert::IsTrue(it2 == it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_EqualityOperator_IsTransitive)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);
    SiblingXMLElementIterator<false> it2(element);
    SiblingXMLElementIterator<false> it3(element);

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
  TEST_METHOD(SiblingXMLElementIterator_InequalityOperator_IteratorsAtSameElementPtr_ShouldReturnFalse)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);
    SiblingXMLElementIterator<false> it2(element);

    Assert::IsTrue(element == *it);
    Assert::IsTrue(element == *it2);
    Assert::IsFalse(it != it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_InequalityOperator_IteratorsBothNullptr_ShouldReturnFalse)
  {
    SiblingXMLElementIterator<false> it(nullptr);
    SiblingXMLElementIterator<false> it2(nullptr);

    Assert::IsNull(*it);
    Assert::IsNull(*it2);
    Assert::IsFalse(it != it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_InequalityOperator_IteratorsAtDifferentElementPtrs_ShouldReturnTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    XMLElement* child1 = document.NewElement("Child1");
    XMLElement* child2 = document.NewElement("Child2");
    document.InsertFirstChild(element);
    element->InsertFirstChild(child1);
    element->InsertEndChild(child2);

    SiblingXMLElementIterator<false> it(child1);
    SiblingXMLElementIterator<false> it2(child2);

    Assert::IsTrue(child1 == *it);
    Assert::IsTrue(child2 == *it2);
    Assert::IsTrue(it != it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_InequalityOperator_OneIteratorNullptr_OneNotNullptr_ShouldReturnTrue)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);
    SiblingXMLElementIterator<false> it2(nullptr);

    Assert::IsTrue(element == *it);
    Assert::IsNull(*it2);
    Assert::IsTrue(it != it2);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_InequalityOperator_CompareToSelf_ShouldReturnFalse)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);

    Assert::IsTrue(element == *it);
    Assert::IsFalse(it != it);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(SiblingXMLElementIterator_InequalityOperator_IsSymmetric)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    SiblingXMLElementIterator<false> it(element);
    SiblingXMLElementIterator<false> it2(nullptr);

    Assert::IsTrue(element == *it);
    Assert::IsNull(*it2);
    Assert::IsTrue(it != it2);
    Assert::IsTrue(it2 != it);
  }

#pragma endregion

  };
}