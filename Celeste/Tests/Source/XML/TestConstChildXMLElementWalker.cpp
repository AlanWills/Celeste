#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "UtilityMacros/Unused.h"

#include "XML/ChildXMLElementWalker.h"


namespace TestCeleste
{
  using namespace tinyxml2;
  using namespace Celeste::XML;

  CELESTE_TEST_CLASS(TestConstChildXMLElementWalker)

#pragma region For Each Iteration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstChildXMLElementWalker_ForeachIteration_WithNullptrElement_DoesNotIterate)
  {
    ChildXMLElementWalker<true> walker(nullptr);

    size_t counter = 0;
    for (const XMLElement* element : walker)
    {
      UNUSED(element);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstChildXMLElementWalker_ForeachIteration_ElementHasNoChildren_DoesNotIterate)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    Assert::IsTrue(element->NoChildren());

    ChildXMLElementWalker<true> walker(element);

    size_t counter = 0;
    for (const XMLElement* e : walker)
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstChildXMLElementWalker_ForeachIteration_ElementHasChildren_IteratesCorrectly)
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

    ChildXMLElementWalker<true> walker(element);

    size_t counter = 0;
    for (const XMLElement* e : walker)
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)3, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstChildXMLElementWalker_ForeachIteration_WithName_ElementHasNoChildren_DoesNotIterate)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    Assert::IsTrue(element->NoChildren());

    ChildXMLElementWalker<true> walker(element, "Test");

    size_t counter = 0;
    for (const XMLElement* e : walker)
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstChildXMLElementWalker_ForeachIteration_WithName_ElementHasNoChildrenWithName_DoesNotIterate)
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

    ChildXMLElementWalker<true> walker(element, "Test");

    size_t counter = 0;
    for (const XMLElement* e : walker)
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstChildXMLElementWalker_ForeachIteration_WithName_ElementHasChildrenWithName_IteratesCorrectly)
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

    ChildXMLElementWalker<true> walker(element, "Child1");

    size_t counter = 0;
    for (const XMLElement* e : walker)
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)2, counter);
  }

#pragma endregion

#pragma region Children Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstChildren_WithNullptrElement_DoesNotIterate)
  {
    size_t counter = 0;
    for (const XMLElement* e : children(static_cast<const XMLElement*>(nullptr)))
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstChildren_ElementHasNoChildren_DoesNotIterate)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    Assert::IsTrue(element->NoChildren());

    size_t counter = 0;
    for (const XMLElement* e : children(static_cast<const XMLElement*>(element)))
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstChildren_ElementHasChildren_IteratesCorrectly)
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

    size_t counter = 0;
    for (const XMLElement* e : children(static_cast<const XMLElement*>(element)))
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)3, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstChildren_WithName_ElementHasNoChildren_DoesNotIterate)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    Assert::IsTrue(element->NoChildren());

    size_t counter = 0;
    for (const XMLElement* e : children(static_cast<const XMLElement*>(element)))
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstChildren_WithName_ElementHasNoChildrenWithName_DoesNotIterate)
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

    size_t counter = 0;
    for (const XMLElement* e : children(static_cast<const XMLElement*>(element), "Test"))
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ConstChildren_WithName_ElementHasChildrenWithName_IteratesCorrectly)
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

    size_t counter = 0;
    for (const XMLElement* e : children(static_cast<const XMLElement*>(element), "Child1"))
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)2, counter);
  }

#pragma endregion

  };
}