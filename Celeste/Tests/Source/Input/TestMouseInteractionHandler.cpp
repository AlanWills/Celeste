#include "UtilityHeaders/UnitTestHeaders.h"

#include "Input/MouseInteractionHandler.h"
#include "Objects/GameObject.h"
#include "Physics/RectangleCollider.h"
#include "Input/InputManager.h"
#include "Registries/ComponentRegistry.h"
#include "Utils/InputUtils.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Input;
using namespace Celeste::Physics;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestMouseInteractionHandler)

    bool called = false;
    void callback(Celeste::GameObject& /*gameObject*/)
    {
      called = true;
    }

    //------------------------------------------------------------------------------------------------
    void TestMouseInteractionHandler::testInitialize()
    {
      called = false;
      getMouse().flush();
    }

#pragma region Registration Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_IsRegisteredWithComponentRegistry)
    {
      Assert::IsTrue(ComponentRegistry::hasComponent<MouseInteractionHandler>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_IsAllocatableFromComponentRegistry)
    {
      GameObject gameObject;

      observer_ptr<Component> component = ComponentRegistry::createComponent(MouseInteractionHandler::type_name(), gameObject);

      Assert::IsNotNull(component);
      Assert::IsNotNull(dynamic_cast<MouseInteractionHandler*>(component));
      Assert::IsTrue(&gameObject == component->getGameObject());
    }

#pragma endregion

#pragma region Handle Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_WithNoCollider_DoesNotThrow)
    {
      GameObject gameObject;
      MouseInteractionHandler handler(gameObject);
      handler.handleInput();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverLastFrame_MouseOverThisFrame_TriggersOnEnter)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnEnterEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      handler->handleInput();

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverLastFrame_MouseNotOverThisFrame_TriggersOnLeave)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnLeaveEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);

      Assert::IsTrue(collider->isHitByRay());

      handler->handleInput();
      collider->setHitByRay(false);

      Assert::IsFalse(collider->isHitByRay());

      handler->handleInput();

      Assert::IsTrue(called);
    }

#pragma region Left Button Down

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisFrameAndLeftMouseButtonDown_TriggersOnLeftButtonDown)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnLeftButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      simulateMouseButtonPressed(MouseButton::kLeft);

      Assert::IsTrue(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

      handler->handleInput();

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverThisFrameAndLeftMouseButtonDown_DoesNotTriggerOnLeftButtonDown)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnLeftButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setDimensions(glm::vec2(100, 100));
      getMouse().getTransform().setTranslation(10000, 10000);
      simulateMouseButtonClicked(MouseButton::kLeft);

      Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kLeft));

      handler->handleInput();

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisFrameAndLeftMouseButtonUp_DoesNotTriggerOnLeftButtonDown)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnLeftButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setDimensions(glm::vec2(100, 100));
      getMouse().getTransform().setTranslation(0, 0);

      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kLeft));

      handler->handleInput();

      Assert::IsFalse(called);
    }

#pragma endregion

#pragma region Left Button Up

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_ClickedLastFrameAndLeftMouseButtonUpOverCollider_TriggersOnLeftButtonUp)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnLeftButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      simulateMouseButtonPressed(MouseButton::kLeft);

      Assert::IsTrue(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

      handler->handleInput();
      simulateMouseButtonReleased(MouseButton::kLeft);
      
      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kLeft));

      handler->handleInput();

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_ClickedLastFrameAndLeftMouseButtonUpNotOverCollider_DoesNotTriggerOnLeftButtonUp)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnLeftButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      simulateMouseButtonPressed(MouseButton::kLeft);

      Assert::IsTrue(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

      handler->handleInput();
      simulateMouseButtonReleased(MouseButton::kLeft);
      collider->setHitByRay(false);

      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kLeft));
      Assert::IsFalse(collider->isHitByRay());

      handler->handleInput();

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_ClickedLastFrameAndLeftMouseButtonNotUp_DoesNotTriggerOnLeftButtonUp)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnLeftButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      simulateMouseButtonPressed(MouseButton::kLeft);

      Assert::IsTrue(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

      handler->handleInput();

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

      handler->handleInput();

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_NotClickedLastFrameAndLeftMouseButtonUp_DoesNotTriggerOnLeftButtonUp)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnLeftButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      simulateMouseButtonPressed(MouseButton::kLeft);

      Assert::IsFalse(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

      handler->handleInput();

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

      handler->handleInput();

      Assert::IsFalse(called);
    }

#pragma endregion

#pragma region Middle Button Down

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisFrameAndMiddleMouseButtonDown_TriggersOnMiddleButtonDown)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnMiddleButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      simulateMouseButtonClicked(MouseButton::kMiddle);

      Assert::IsTrue(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kMiddle));

      handler->handleInput();

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverThisFrameAndMiddleMouseButtonDown_DoesNotTriggerOnMiddleButtonDown)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnMiddleButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setDimensions(glm::vec2(100, 100));
      getMouse().getTransform().setTranslation(10000, 10000);
      simulateMouseButtonClicked(MouseButton::kMiddle);

      Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kMiddle));

      handler->handleInput();

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisFrameAndMiddleMouseButtonUp_DoesNotTriggerOnMiddleButtonDown)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnMiddleButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setDimensions(glm::vec2(100, 100));
      getMouse().getTransform().setTranslation(0, 0);

      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kMiddle));

      handler->handleInput();

      Assert::IsFalse(called);
    }

#pragma endregion

#pragma region Middle Button Up

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_ClickedLastFrameAndMiddleMouseButtonUpOverCollider_TriggersOnMiddleButtonUp)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnMiddleButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      simulateMouseButtonPressed(MouseButton::kMiddle);

      Assert::IsTrue(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

      handler->handleInput();
      simulateMouseButtonReleased(MouseButton::kMiddle);

      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kMiddle));

      handler->handleInput();

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_ClickedLastFrameAndMiddleMouseButtonUpNotOverCollider_DoesNotTriggerOnMiddleButtonUp)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnMiddleButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      simulateMouseButtonPressed(MouseButton::kMiddle);

      Assert::IsTrue(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

      handler->handleInput();
      simulateMouseButtonReleased(MouseButton::kMiddle);
      collider->setHitByRay(false);

      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kMiddle));
      Assert::IsFalse(collider->isHitByRay());

      handler->handleInput();

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_ClickedLastFrameAndMiddleMouseButtonDown_DoesNotTriggerOnMiddleButtonUp)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnMiddleButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      simulateMouseButtonPressed(MouseButton::kMiddle);

      Assert::IsTrue(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

      handler->handleInput();

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

      handler->handleInput();

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_NotClickedLastFrameAndMiddleMouseButtonUp_DoesNotTriggerOnMiddleButtonUp)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnMiddleButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      simulateMouseButtonPressed(MouseButton::kMiddle);

      Assert::IsFalse(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

      handler->handleInput();

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

      handler->handleInput();

      Assert::IsFalse(called);
    }

#pragma endregion

#pragma region Right Button Down

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisFrameAndRightMouseButtonDown_TriggersOnRightButtonDown)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnRightButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      simulateMouseButtonClicked(MouseButton::kRight);

      Assert::IsTrue(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kRight));

      handler->handleInput();

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverThisFrameAndRightMouseButtonDown_DoesNotTriggerOnRightButtonDown)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnRightButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setDimensions(glm::vec2(100, 100));
      getMouse().getTransform().setTranslation(10000, 10000);
      simulateMouseButtonClicked(MouseButton::kRight);

      Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kRight));

      handler->handleInput();

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisFrameAndRightMouseButtonUp_DoesNotTriggerOnRightButtonDown)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnRightButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setDimensions(glm::vec2(100, 100));
      getMouse().getTransform().setTranslation(0, 0);

      Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kRight));

      handler->handleInput();

      Assert::IsFalse(called);
    }

#pragma endregion

#pragma region Right Button Up

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_ClickedLastFrameAndRightMouseButtonUpOverCollider_TriggersOnRightButtonUp)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnRightButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      simulateMouseButtonPressed(MouseButton::kRight);

      Assert::IsTrue(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kRight));

      handler->handleInput();
      simulateMouseButtonReleased(MouseButton::kRight);

      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kRight));

      handler->handleInput();

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_ClickedLastFrameAndRightMouseButtonUpNotOverCollider_DoesNotTriggerOnRightButtonUp)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnRightButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      simulateMouseButtonPressed(MouseButton::kRight);

      Assert::IsTrue(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kRight));

      handler->handleInput();
      simulateMouseButtonReleased(MouseButton::kRight);
      collider->setHitByRay(false);

      Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kRight));
      Assert::IsFalse(collider->isHitByRay());

      handler->handleInput();

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_ClickedLastFrameAndRightMouseButtonUp_DoesNotTriggerOnRightButtonUp)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnRightButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      simulateMouseButtonPressed(MouseButton::kRight);

      Assert::IsTrue(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kRight));

      handler->handleInput();

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kRight));

      handler->handleInput();

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_NotClickedLastFrameAndRightMouseButtonUp_DoesNotTriggerOnRightButtonUp)
    {
      GameObject gameObject;
      observer_ptr<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnRightButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      simulateMouseButtonPressed(MouseButton::kMiddle);

      Assert::IsFalse(collider->isHitByRay());
      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

      handler->handleInput();

      Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

      handler->handleInput();

      Assert::IsFalse(called);
    }

#pragma endregion

#pragma endregion

  };
}