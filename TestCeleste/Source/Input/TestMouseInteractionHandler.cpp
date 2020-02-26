#include "UtilityHeaders/UnitTestHeaders.h"

#include "Input/MouseInteractionHandler.h"
#include "Objects/GameObject.h"
#include "Physics/RectangleCollider.h"
#include "Input/InputManager.h"
#include "Registries/ComponentRegistry.h"
#include "Utils/ObjectUtils.h"
#include "Utils/InputUtils.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Input;
using namespace Celeste::Physics;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestMouseInteractionHandler)

    bool called = false;
    void callback(Celeste::GameObject& gameObject)
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
      GAMEOBJECT(gameObject);

      AutoDeallocator<Component> component = ComponentRegistry::allocateComponent(MouseInteractionHandler::type_name(), gameObject);

      Assert::IsNotNull(component.get());
      Assert::IsNotNull(dynamic_cast<MouseInteractionHandler*>(component.get()));
      Assert::IsTrue(&gameObject == component->getGameObject());
    }

#pragma endregion

#pragma region Handle Input Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_WithNoCollider_DoesNotThrow)
    {
      MouseInteractionHandler handler;
      handler.handleInput();
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverLastFrame_MouseOverThisFrame_TriggersOnEnter)
    {
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

      handler->getOnEnterEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      collider->setHitByRay(true);
      getMouse().getTransform().setTranslation(0, 0);
      handler->handleInput();

      Assert::IsTrue(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverLastFrame_MouseNotOverThisFrame_TriggersOnLeave)
    {
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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
      GAMEOBJECT(gameObject);
      AutoDeallocator<RectangleCollider> collider = gameObject.addComponent<RectangleCollider>();
      AutoDeallocator<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

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

#pragma region Die Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_Die_UnsubscribesAllFromOnEnterEvent)
    {
      AutoDeallocator<MouseInteractionHandler> handler = MouseInteractionHandler::allocate(GameObject());
      handler->getOnEnterEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      handler->getOnEnterEvent().invoke(GameObject());

      Assert::IsTrue(called);

      called = false;
      handler->die();
      handler->getOnEnterEvent().invoke(GameObject());

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_Die_UnsubscribesAllFromOnLeaveEvent)
    {
      AutoDeallocator<MouseInteractionHandler> handler = MouseInteractionHandler::allocate(GameObject());
      handler->getOnLeaveEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      handler->getOnLeaveEvent().invoke(GameObject());

      Assert::IsTrue(called);

      called = false;
      handler->die();
      handler->getOnLeaveEvent().invoke(GameObject());

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_Die_UnsubscribesAllFromOnLeftButtonDownEvent)
    {
      AutoDeallocator<MouseInteractionHandler> handler = MouseInteractionHandler::allocate(GameObject());
      handler->getOnLeftButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      handler->getOnLeftButtonDownEvent().invoke(GameObject());

      Assert::IsTrue(called);

      called = false;
      handler->die();
      handler->getOnLeftButtonDownEvent().invoke(GameObject());

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_Die_UnsubscribesAllFromOnLeftButtonUpEvent)
    {
      AutoDeallocator<MouseInteractionHandler> handler = MouseInteractionHandler::allocate(GameObject());
      handler->getOnLeftButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      handler->getOnLeftButtonUpEvent().invoke(GameObject());

      Assert::IsTrue(called);

      called = false;
      handler->die();
      handler->getOnLeftButtonUpEvent().invoke(GameObject());

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_Die_UnsubscribesAllFromOnMiddleButtonDownEvent)
    {
      AutoDeallocator<MouseInteractionHandler> handler = MouseInteractionHandler::allocate(GameObject());
      handler->getOnMiddleButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      handler->getOnMiddleButtonDownEvent().invoke(GameObject());

      Assert::IsTrue(called);

      called = false;
      handler->die();
      handler->getOnMiddleButtonDownEvent().invoke(GameObject());

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_Die_UnsubscribesAllFromOnMiddleButtonUpEvent)
    {
      AutoDeallocator<MouseInteractionHandler> handler = MouseInteractionHandler::allocate(GameObject());
      handler->getOnMiddleButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      handler->getOnMiddleButtonUpEvent().invoke(GameObject());

      Assert::IsTrue(called);

      called = false;
      handler->die();
      handler->getOnMiddleButtonUpEvent().invoke(GameObject());

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_Die_UnsubscribesAllFromOnRightButtonDownEvent)
    {
      AutoDeallocator<MouseInteractionHandler> handler = MouseInteractionHandler::allocate(GameObject());
      handler->getOnRightButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      handler->getOnRightButtonDownEvent().invoke(GameObject());

      Assert::IsTrue(called);

      called = false;
      handler->die();
      handler->getOnRightButtonDownEvent().invoke(GameObject());

      Assert::IsFalse(called);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(MouseInteractionHandler_Die_UnsubscribesAllFromOnRightButtonUpEvent)
    {
      AutoDeallocator<MouseInteractionHandler> handler = MouseInteractionHandler::allocate(GameObject());
      handler->getOnRightButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
      handler->getOnRightButtonUpEvent().invoke(GameObject());

      Assert::IsTrue(called);

      called = false;
      handler->die();
      handler->getOnRightButtonUpEvent().invoke(GameObject());

      Assert::IsFalse(called);
    }

#pragma endregion
  };
}