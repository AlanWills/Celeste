#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "UtilityMacros/Unused.h"

#include "XML/ChildXMLElementWalker.h"


namespace TestCeleste
{
  using namespace tinyxml2;
  using namespace Celeste::XML;

  CELESTE_TEST_CLASS(TestChildXMLElementWalker)

#pragma region For Each Iteration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChildXMLElementWalker_ForeachIteration_WithNullptrElement_DoesNotIterate)
  {
    ChildXMLElementWalker<false> walker(nullptr);

    size_t counter = 0;
    for (XMLElement* element : walker)
    {
      UNUSED(element);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChildXMLElementWalker_ForeachIteration_ElementHasNoChildren_DoesNotIterate)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    Assert::IsTrue(element->NoChildren());

    ChildXMLElementWalker<false> walker(element);

    size_t counter = 0;
    for (XMLElement* e : walker)
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChildXMLElementWalker_ForeachIteration_ElementHasChildren_IteratesCorrectly)
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

    ChildXMLElementWalker<false> walker(element);

    size_t counter = 0;
    for (XMLElement* e : walker)
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)3, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChildXMLElementWalker_ForeachIteration_WithName_ElementHasNoChildren_DoesNotIterate)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    Assert::IsTrue(element->NoChildren());

    ChildXMLElementWalker<false> walker(element, "Test");

    size_t counter = 0;
    for (XMLElement* e : walker)
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChildXMLElementWalker_ForeachIteration_WithName_ElementHasNoChildrenWithName_DoesNotIterate)
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

    ChildXMLElementWalker<false> walker(element, "Test");

    size_t counter = 0;
    for (XMLElement* e : walker)
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChildXMLElementWalker_ForeachIteration_WithName_ElementHasChildrenWithName_IteratesCorrectly)
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

    ChildXMLElementWalker<false> walker(element, "Child1");

    size_t counter = 0;
    for (XMLElement* e : walker)
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)2, counter);
  }

#pragma endregion

#pragma region Children Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Children_WithNullptrElement_DoesNotIterate)
  {
    size_t counter = 0;
    for (XMLElement* element : children(static_cast<XMLElement*>(nullptr)))
    {
      UNUSED(element);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Children_ElementHasNoChildren_DoesNotIterate)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    Assert::IsTrue(element->NoChildren());

    size_t counter = 0;
    for (XMLElement* e : children(element))
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Children_ElementHasChildren_IteratesCorrectly)
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
    for (XMLElement* e : children(element))
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)3, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Children_WithName_ElementHasNoChildren_DoesNotIterate)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    Assert::IsTrue(element->NoChildren());

    size_t counter = 0;
    for (XMLElement* e : children(element))
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Children_WithName_ElementHasNoChildrenWithName_DoesNotIterate)
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
    for (XMLElement* e : children(element, "Test"))
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)0, counter);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Children_WithName_ElementHasChildrenWithName_IteratesCorrectly)
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
    for (XMLElement* e : children(element, "Child1"))
    {
      UNUSED(e);
      ++counter;
    }

    Assert::AreEqual((size_t)2, counter);
  }

#pragma endregion

#pragma region Child Count Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChildCount_WithNullptrElement_ReturnsZero)
  {
    Assert::AreEqual((size_t)0, child_count(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChildCount_ElementHasNoChildren_ReturnsZero)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    Assert::IsTrue(element->NoChildren());
    Assert::AreEqual((size_t)0, child_count(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChildCount_ElementHasChildren_ReturnsCorrectChildCount)
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
    Assert::AreEqual((size_t)3, child_count(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChildCount_WithName_ElementHasNoChildren_ReturnsZero)
  {
    XMLDocument document;
    XMLElement* element = document.NewElement("Root");
    document.InsertFirstChild(element);

    Assert::IsTrue(element->NoChildren());
    Assert::AreEqual((size_t)0, child_count(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChildCount_WithName_ElementHasNoChildrenWithName_ReturnsZero)
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
    Assert::AreEqual((size_t)0, child_count(element, "Child4"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ChildCount_WithName_ElementHasChildrenWithName_ReturnsCorrectCount)
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
    Assert::AreEqual((size_t)2, child_count(element, "Child1"));
  }

#pragma endregion

  };
}