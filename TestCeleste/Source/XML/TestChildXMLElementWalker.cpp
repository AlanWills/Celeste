#include "UtilityHeaders/UnitTestHeaders.h"

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
    for (XMLElement* element : walker)
    {
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
    for (XMLElement* element : walker)
    {
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
    for (XMLElement* element : walker)
    {
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
    for (XMLElement* element : walker)
    {
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
    for (XMLElement* element : walker)
    {
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
    for (XMLElement* element : children(element))
    {
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
    for (XMLElement* element : children(element))
    {
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
    for (XMLElement* element : children(element))
    {
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
    for (XMLElement* element : children(element, "Test"))
    {
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
    for (XMLElement* element : children(element, "Child1"))
    {
      ++counter;
    }

    Assert::AreEqual((size_t)2, counter);
  }

#pragma endregion

  };
}