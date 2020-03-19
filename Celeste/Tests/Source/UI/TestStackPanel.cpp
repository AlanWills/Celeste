#include "UtilityHeaders/UnitTestHeaders.h"

#include "UI/StackPanel.h"
#include "Mocks/Rendering/MockSpriteRenderer.h"
#include "Resources/ResourceManager.h"
#include "Resources/TestResources.h"
#include "Registries/ComponentRegistry.h"
#include "AssertCel.h"

using namespace Celeste::Rendering;


namespace TestCeleste
{
  using namespace Celeste::UI;

  CELESTE_TEST_CLASS(TestStackPanel)

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(StackPanel_Constructor_SetsValuesToDefault)
  {
    GameObject gameObject;
    StackPanel stackPanel(gameObject);

    Assert::IsTrue(Orientation::kVertical == stackPanel.getOrientation());
    Assert::IsTrue(UI::HorizontalAlignment::kCentre == stackPanel.getHorizontalAlignment());
    Assert::IsTrue(UI::VerticalAlignment::kCentre == stackPanel.getVerticalAlignment());
    Assert::AreEqual(5.0f, stackPanel.getPadding());
    Assert::AreEqual(static_cast<size_t>(0), stackPanel.childCount());
  }

#pragma region Registration Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_IsRegisteredWithComponentRegistry)
    {
      Assert::IsTrue(ComponentRegistry::hasComponent<StackPanel>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_IsAllocatableFromComponentRegistry)
    {
      GameObject gameObject;

      observer_ptr<Component> component = ComponentRegistry::createComponent(StackPanel::type_name(), gameObject);

      Assert::IsNotNull(component);
      Assert::IsNotNull(dynamic_cast<StackPanel*>(component));
      Assert::AreEqual(&gameObject, component->getGameObject());
    }

#pragma endregion

#pragma region Add Children Single Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_AddChildren_ChildHasNoRenderer_DoesNotAddChildToStackPanel)
    {
      GameObject gameObject;
      StackPanel stackPanel(gameObject);
      GameObject child;

      Assert::IsNull(gameObject.findComponent<Renderer>());
      Assert::AreEqual(static_cast<size_t>(0), stackPanel.childCount());

      stackPanel.addChildren(child);

      Assert::AreEqual(static_cast<size_t>(0), stackPanel.childCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_AddChildren_ChildHasRenderer_NoParent_AddsChildToStackPanelOnly)
    {
      GameObject gameObject;
      StackPanel stackPanel(gameObject);
      observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<MockSpriteRenderer>();

      Assert::IsNotNull(gameObject.findComponent<SpriteRenderer>());

      stackPanel.addChildren(gameObject);

      Assert::IsNull(gameObject.getTransform()->getParent());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_AddChildren_ChildHasRenderer__WithParent_AddsChildToStackPanel_AndParentsChildTransformUnderStackPanelTransform)
    {
      GameObject parent;
      GameObject gameObject;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<SpriteRenderer> renderer = gameObject.addComponent<SpriteRenderer>();

      Assert::IsNotNull(stackPanel->getGameObject());
      Assert::IsNotNull(gameObject.findComponent<SpriteRenderer>());

      stackPanel->addChildren(gameObject);

      Assert::AreEqual((size_t)1, stackPanel->childCount());
      Assert::IsTrue(&gameObject == stackPanel->getChild(0));
      Assert::IsTrue(gameObject.getTransform()->getParent() == stackPanel->getTransform());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_AddChildren_AddingStackPanelParentGameObject_DoesNotAddGameObject)
    {
      // Shouldnt be able to add stack panel game object to itself
      GameObject parent;
      observer_ptr<SpriteRenderer> renderer = parent.addComponent<SpriteRenderer>();
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();

      stackPanel->addChildren(parent);

      Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());
      Assert::IsNull(parent.getTransform()->getParent());
    }

#pragma endregion

#pragma region Add Children Multiple Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_AddChildren_AddsOnlyChildrenWithRenderers)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      GameObject gameObject3;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<SpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<SpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();

      Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());

      stackPanel->addChildren(gameObject1, gameObject2, gameObject3);

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::IsTrue(&gameObject1 == stackPanel->getChild(0));
      Assert::IsTrue(&gameObject2 == stackPanel->getChild(1));
      Assert::IsTrue(gameObject1.getTransform()->getParent() == stackPanel->getTransform());
      Assert::IsTrue(gameObject2.getTransform()->getParent() == stackPanel->getTransform());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_AddChildren_DoesNotAddChildrenWhichAreTheParentGameObject)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<SpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<SpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();

      Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());

      stackPanel->addChildren(gameObject1, gameObject2, parent);

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::IsTrue(&gameObject1 == stackPanel->getChild(0));
      Assert::IsTrue(&gameObject2 == stackPanel->getChild(1));
      Assert::IsTrue(gameObject1.getTransform()->getParent() == stackPanel->getTransform());
      Assert::IsTrue(gameObject2.getTransform()->getParent() == stackPanel->getTransform());
    }

#pragma endregion

#pragma region Remove Children Single Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_RemoveChildren_ChildNotAddedToStackPanel_DoesNothing)
    {
      GameObject gameObject;
      StackPanel stackPanel(gameObject);
      GameObject child;

      Assert::IsNull(child.findComponent<Renderer>());
      Assert::AreEqual(static_cast<size_t>(0), stackPanel.childCount());

      stackPanel.removeChildren(child);

      Assert::AreEqual(static_cast<size_t>(0), stackPanel.childCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_RemoveChildren_ChildAddedToStackPanel_RemovesChild)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<SpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<SpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();

      Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());

      stackPanel->addChildren(gameObject1, gameObject2);

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::IsTrue(&gameObject1 == stackPanel->getChild(0));
      Assert::IsTrue(&gameObject2 == stackPanel->getChild(1));

      stackPanel->removeChildren(gameObject1);

      Assert::AreEqual((size_t)1, stackPanel->childCount());
      Assert::IsTrue(&gameObject2 == stackPanel->getChild(0));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_RemoveChildren_PerformsLayout)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<MockSpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();

      renderer1->setDimensions(100, 100);
      renderer2->setDimensions(100, 100);

      Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());

      stackPanel->addChildren(gameObject1, gameObject2);

      Assert::AreNotEqual(glm::vec3(), gameObject2.getTransform()->getTranslation());

      stackPanel->removeChildren(gameObject1);

      Assert::AreEqual(glm::vec3(), gameObject2.getTransform()->getTranslation());
    }

#pragma endregion

#pragma region Remove Children Multiple Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_RemoveMultipleChildren_ChildNotAddedToStackPanel_DoesNothing)
    {
      GameObject gameObject;
      StackPanel stackPanel(gameObject);
      GameObject child;
      GameObject child2;

      Assert::IsNull(gameObject.findComponent<Renderer>());
      Assert::AreEqual(static_cast<size_t>(0), stackPanel.childCount());

      stackPanel.removeChildren(child, child2);

      Assert::AreEqual(static_cast<size_t>(0), stackPanel.childCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_RemoveMultipleChildren_ChildrenAddedToStackPanel_RemovesChildren)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      GameObject gameObject3;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<SpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<SpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();
      observer_ptr<SpriteRenderer> renderer3 = gameObject3.addComponent<MockSpriteRenderer>();

      Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());

      stackPanel->addChildren(gameObject1, gameObject2, gameObject3);

      Assert::AreEqual((size_t)3, stackPanel->childCount());
      Assert::IsTrue(&gameObject1 == stackPanel->getChild(0));
      Assert::IsTrue(&gameObject2 == stackPanel->getChild(1));
      Assert::IsTrue(&gameObject3 == stackPanel->getChild(2));

      stackPanel->removeChildren(gameObject1, gameObject3);

      Assert::AreEqual((size_t)1, stackPanel->childCount());
      Assert::IsTrue(&gameObject2 == stackPanel->getChild(0));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_RemoveMultipleChildren_PerformsLayout)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      GameObject gameObject3;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<MockSpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer3 = gameObject3.addComponent<MockSpriteRenderer>();

      renderer1->setDimensions(100, 100);
      renderer2->setDimensions(100, 100);
      renderer3->setDimensions(100, 100);

      Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());

      stackPanel->addChildren(gameObject1, gameObject2, gameObject3);

      Assert::AreNotEqual(glm::vec3(), gameObject3.getTransform()->getTranslation());

      stackPanel->removeChildren(gameObject1, gameObject2);

      Assert::AreEqual(glm::vec3(), gameObject3.getTransform()->getTranslation());
    }

#pragma endregion

#pragma region Clear Children Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_ClearChildren_NoChildren_DoesNothing)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<SpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<SpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();

      Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());

      stackPanel->addChildren(gameObject1, gameObject2, parent);

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::IsTrue(&gameObject1 == stackPanel->getChild(0));
      Assert::IsTrue(&gameObject2 == stackPanel->getChild(1));

      stackPanel->clearChildren();

      Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_ClearChildren_WithChildren_RemovesChildrenFromStackPanel)
    {
      GameObject parent;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();

      Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());

      stackPanel->clearChildren();

      Assert::AreEqual(static_cast<size_t>(0), stackPanel->childCount());
    }

#pragma endregion

#pragma region Horizontal Layout Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_Layout_Horizontal_LeftHorizontalAlignment)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<MockSpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();

      stackPanel->setOrientation(Orientation::kHorizontal);
      stackPanel->setHorizontalAlignment(UI::HorizontalAlignment::kLeft);

      Assert::IsTrue(Orientation::kHorizontal == stackPanel->getOrientation());
      Assert::IsTrue(UI::HorizontalAlignment::kLeft == stackPanel->getHorizontalAlignment());

      float padding = stackPanel->getPadding();

      renderer1->setTexture(TestResources::getBlockPngRelativePath());
      renderer2->setTexture(TestResources::getContainerJpgRelativePath());

      const glm::vec2& renderer1Dims = renderer1->getDimensions();
      const glm::vec2& renderer2Dims = renderer2->getDimensions();

      stackPanel->addChildren(gameObject1);
      stackPanel->layout();

      Assert::AreEqual((size_t)1, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(renderer1Dims.x * 0.5f, 0, 0), gameObject1.getTransform()->getTranslation());

      stackPanel->addChildren(gameObject2);
      stackPanel->layout();

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(renderer1Dims.x * 0.5f, 0, 0), gameObject1.getTransform()->getTranslation());
      Assert::AreEqual(glm::vec3(renderer1Dims.x + padding + renderer2Dims.x * 0.5f, 0, 0), gameObject2.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_Layout_Horizontal_CentreHorizontalAlignment)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<MockSpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();

      stackPanel->setOrientation(Orientation::kHorizontal);
      stackPanel->setHorizontalAlignment(UI::HorizontalAlignment::kCentre);
      
      Assert::IsTrue(Orientation::kHorizontal == stackPanel->getOrientation());
      Assert::IsTrue(UI::HorizontalAlignment::kCentre == stackPanel->getHorizontalAlignment());

      float padding = stackPanel->getPadding();

      renderer1->setTexture(TestResources::getBlockPngRelativePath());
      renderer2->setTexture(TestResources::getContainerJpgRelativePath());

      const glm::vec2& renderer1Dims = renderer1->getDimensions();
      const glm::vec2& renderer2Dims = renderer2->getDimensions();

      stackPanel->addChildren(gameObject1);
      stackPanel->layout();

      Assert::AreEqual((size_t)1, stackPanel->childCount());
      Assert::AreEqual(glm::zero<glm::vec3>(), gameObject1.getTransform()->getTranslation());

      stackPanel->addChildren(gameObject2);
      stackPanel->layout();

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(-(renderer2Dims.x + padding) * 0.5f, 0, 0), gameObject1.getTransform()->getTranslation());
      Assert::AreEqual(glm::vec3((renderer1Dims.x + padding) * 0.5f, 0, 0), gameObject2.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_Layout_Horizontal_RightHorizontalAlignment)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<MockSpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();

      stackPanel->setOrientation(Orientation::kHorizontal);
      stackPanel->setHorizontalAlignment(UI::HorizontalAlignment::kRight);

      Assert::IsTrue(Orientation::kHorizontal == stackPanel->getOrientation());
      Assert::IsTrue(UI::HorizontalAlignment::kRight == stackPanel->getHorizontalAlignment());

      float padding = stackPanel->getPadding();

      renderer1->setTexture(TestResources::getBlockPngRelativePath());
      renderer2->setTexture(TestResources::getContainerJpgRelativePath());

      const glm::vec2& renderer1Dims = renderer1->getDimensions();
      const glm::vec2& renderer2Dims = renderer2->getDimensions();

      stackPanel->addChildren(gameObject1);
      stackPanel->layout();

      Assert::AreEqual((size_t)1, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(-renderer1Dims.x * 0.5f, 0, 0), gameObject1.getTransform()->getTranslation());

      stackPanel->addChildren(gameObject2);
      stackPanel->layout();

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(-renderer1Dims.x * 0.5f - padding - renderer2Dims.x, 0, 0), gameObject1.getTransform()->getTranslation());
      Assert::AreEqual(glm::vec3(-renderer2Dims.x * 0.5f, 0, 0), gameObject2.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_Layout_Horizontal_NoChildren)
    {
      GameObject parent;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      stackPanel->setOrientation(Orientation::kHorizontal);
      stackPanel->setHorizontalAlignment(UI::HorizontalAlignment::kLeft);

      Assert::IsTrue(Orientation::kHorizontal == stackPanel->getOrientation());
      Assert::IsTrue(UI::HorizontalAlignment::kLeft == stackPanel->getHorizontalAlignment());

      // Check this doesn't throw
      stackPanel->layout();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_Layout_Horizontal_NoVisibleChildren)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      gameObject1.getTransform()->setTranslation(100, 0);
      gameObject2.getTransform()->setTranslation(200, 0);

      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<MockSpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();
      renderer1->setActive(false);
      renderer2->setActive(false);

      stackPanel->setOrientation(Orientation::kHorizontal);
      stackPanel->setHorizontalAlignment(UI::HorizontalAlignment::kLeft);

      Assert::IsTrue(Orientation::kHorizontal == stackPanel->getOrientation());
      Assert::IsTrue(UI::HorizontalAlignment::kLeft == stackPanel->getHorizontalAlignment());

      stackPanel->addChildren(gameObject1);
      stackPanel->layout();

      Assert::AreEqual((size_t)1,stackPanel->childCount());
      Assert::AreEqual(glm::vec3(100, 0, 0), gameObject1.getTransform()->getTranslation());

      stackPanel->addChildren(gameObject2);
      stackPanel->layout();

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(100, 0, 0), gameObject1.getTransform()->getTranslation());
      Assert::AreEqual(glm::vec3(200, 0, 0), gameObject2.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_Layout_Horizontal_DoesNotIncludedNonRendererdObjects)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      gameObject1.getTransform()->setTranslation(100, 0);
      gameObject2.getTransform()->setTranslation(200, 0);

      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<MockSpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();
      renderer1->setActive(false);

      stackPanel->setOrientation(Orientation::kHorizontal);
      stackPanel->setHorizontalAlignment(UI::HorizontalAlignment::kLeft);

      Assert::IsTrue(Orientation::kHorizontal == stackPanel->getOrientation());
      Assert::IsTrue(UI::HorizontalAlignment::kLeft == stackPanel->getHorizontalAlignment());

      stackPanel->addChildren(gameObject1, gameObject2);
      stackPanel->layout();

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(100, 0, 0), gameObject1.getTransform()->getTranslation());
      Assert::AreEqual(glm::vec3(renderer1->getDimensions().x * 0.5f, 0, 0), gameObject2.getTransform()->getTranslation());
    }

#pragma endregion

#pragma region Layout Vertical Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_Layout_Vertical_TopVerticalAlignment)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<MockSpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();

      stackPanel->setOrientation(Orientation::kVertical);
      stackPanel->setVerticalAlignment(UI::VerticalAlignment::kTop);

      Assert::IsTrue(Orientation::kVertical == stackPanel->getOrientation());
      Assert::IsTrue(UI::VerticalAlignment::kTop == stackPanel->getVerticalAlignment());

      float padding = stackPanel->getPadding();

      renderer1->setTexture(TestResources::getBlockPngRelativePath());
      renderer2->setTexture(TestResources::getContainerJpgRelativePath());

      const glm::vec2& renderer1Dims = renderer1->getDimensions();
      const glm::vec2& renderer2Dims = renderer2->getDimensions();

      stackPanel->addChildren(gameObject1);
      stackPanel->layout();

      Assert::AreEqual((size_t)1, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(0, -renderer1Dims.y * 0.5f, 0), gameObject1.getTransform()->getTranslation());

      stackPanel->addChildren(gameObject2);
      stackPanel->layout();

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(0, -renderer1Dims.y * 0.5f - padding - renderer2Dims.y, 0), gameObject1.getTransform()->getTranslation());
      Assert::AreEqual(glm::vec3(0, -renderer2Dims.y * 0.5f, 0), gameObject2.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_Layout_Vertical_CentreVerticalAlignment)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<MockSpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();

      stackPanel->setOrientation(Orientation::kVertical);
      stackPanel->setVerticalAlignment(UI::VerticalAlignment::kCentre);

      Assert::IsTrue(Orientation::kVertical == stackPanel->getOrientation());
      Assert::IsTrue(UI::VerticalAlignment::kCentre == stackPanel->getVerticalAlignment());

      float padding = stackPanel->getPadding();

      renderer1->setTexture(TestResources::getBlockPngRelativePath());
      renderer2->setTexture(TestResources::getContainerJpgRelativePath());

      const glm::vec2& renderer1Dims = renderer1->getDimensions();
      const glm::vec2& renderer2Dims = renderer2->getDimensions();

      stackPanel->addChildren(gameObject1);
      stackPanel->layout();

      Assert::AreEqual((size_t)1, stackPanel->childCount());
      Assert::AreEqual(glm::zero<glm::vec3>(), gameObject1.getTransform()->getTranslation());

      stackPanel->addChildren(gameObject2);
      stackPanel->layout();

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(0, -(renderer2Dims.y + padding) * 0.5f, 0), gameObject1.getTransform()->getTranslation());
      Assert::AreEqual(glm::vec3(0, (renderer1Dims.y + padding) * 0.5f, 0), gameObject2.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_Layout_Vertical_BottomVerticalAlignment)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<MockSpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();

      stackPanel->setOrientation(Orientation::kVertical);
      stackPanel->setVerticalAlignment(UI::VerticalAlignment::kBottom);

      Assert::IsTrue(Orientation::kVertical == stackPanel->getOrientation());
      Assert::IsTrue(UI::VerticalAlignment::kBottom == stackPanel->getVerticalAlignment());

      float padding = stackPanel->getPadding();

      renderer1->setTexture(TestResources::getBlockPngRelativePath());
      renderer2->setTexture(TestResources::getContainerJpgRelativePath());

      const glm::vec2& renderer1Dims = renderer1->getDimensions();
      const glm::vec2& renderer2Dims = renderer2->getDimensions();

      stackPanel->addChildren(gameObject1);
      stackPanel->layout();

      Assert::AreEqual((size_t)1, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(0, renderer1Dims.x * 0.5f, 0), gameObject1.getTransform()->getTranslation());

      stackPanel->addChildren(gameObject2);
      stackPanel->layout();

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(0, renderer1Dims.y * 0.5f, 0), gameObject1.getTransform()->getTranslation());
      Assert::AreEqual(glm::vec3(0, renderer1Dims.y + padding + renderer2Dims.y * 0.5f, 0), gameObject2.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_Layout_Vertical_NoChildren)
    {
      GameObject parent;
      
      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      stackPanel->setOrientation(Orientation::kVertical);
      stackPanel->setVerticalAlignment(UI::VerticalAlignment::kBottom);

      Assert::IsTrue(Orientation::kVertical == stackPanel->getOrientation());
      Assert::IsTrue(UI::VerticalAlignment::kBottom == stackPanel->getVerticalAlignment());

      // Check this doesn't throw
      stackPanel->layout();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_Layout_Vertical_NoVisibleChildren)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;
      gameObject1.getTransform()->setTranslation(0, 100);
      gameObject2.getTransform()->setTranslation(0, 200);

      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      observer_ptr<MockSpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();
      renderer1->setActive(false);
      renderer2->setActive(false);

      stackPanel->setOrientation(Orientation::kVertical);
      stackPanel->setVerticalAlignment(UI::VerticalAlignment::kBottom);

      Assert::IsTrue(Orientation::kVertical == stackPanel->getOrientation());
      Assert::IsTrue(UI::VerticalAlignment::kBottom == stackPanel->getVerticalAlignment());

      stackPanel->addChildren(gameObject1);
      stackPanel->layout();

      Assert::AreEqual((size_t)1, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(0, 100, 0), gameObject1.getTransform()->getTranslation());

      stackPanel->addChildren(gameObject2);
      stackPanel->layout();

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(0, 100, 0), gameObject1.getTransform()->getTranslation());
      Assert::AreEqual(glm::vec3(0, 200, 0), gameObject2.getTransform()->getTranslation());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StackPanel_Layout_Vertical_DoesNotIncludedNonRendererdObjects)
    {
      GameObject parent;
      GameObject gameObject1;
      GameObject gameObject2;

      observer_ptr<MockSpriteRenderer> renderer1 = gameObject1.addComponent<MockSpriteRenderer>();
      observer_ptr<MockSpriteRenderer> renderer2 = gameObject2.addComponent<MockSpriteRenderer>();
      renderer1->setActive(false);

      observer_ptr<StackPanel> stackPanel = parent.addComponent<StackPanel>();
      stackPanel->setOrientation(Orientation::kVertical);
      stackPanel->setVerticalAlignment(UI::VerticalAlignment::kBottom);

      Assert::IsTrue(Orientation::kVertical == stackPanel->getOrientation());
      Assert::IsTrue(UI::VerticalAlignment::kBottom == stackPanel->getVerticalAlignment());

      stackPanel->addChildren(gameObject1, gameObject2);
      stackPanel->layout();

      Assert::AreEqual((size_t)2, stackPanel->childCount());
      Assert::AreEqual(glm::vec3(), gameObject1.getTransform()->getTranslation());
      Assert::AreEqual(glm::vec3(0, renderer2->getDimensions().y * 0.5f, 0), gameObject2.getTransform()->getTranslation());
    }

#pragma endregion

  };
}