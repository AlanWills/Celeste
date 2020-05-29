#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Input/MouseInteractionHandler.h"
#include "Objects/GameObject.h"
#include "Input/InputManager.h"
#include "Registries/ComponentRegistry.h"
#include "TestUtils/Utils/InputUtils.h"
#include "TestUtils/Assert/AssertCel.h"

using namespace Celeste;
using namespace Celeste::Input;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestMouseInteractionHandler)

  bool called = false;
  void callback(Celeste::GameObject& /*gameObject*/)
  {
    called = true;
  }

  //------------------------------------------------------------------------------------------------
  void testInitialize()
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
    Assert::AreSame(gameObject, component->getGameObject());
  }

#pragma endregion

#pragma region Handle Input Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverLastFrame_MouseOverThisFrame_TriggersOnEnter)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnEnterEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    getMouse().getTransform().setTranslation(0, 0);
    handler->update();

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverLastFrame_MouseNotOverThisFrame_TriggersOnLeave)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnLeaveEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);

    Assert::IsTrue(handler->isMouseOver());

    handler->update();
    handler->setMouseOver(false);

    Assert::IsFalse(handler->isMouseOver());

    handler->update();

    Assert::IsTrue(called);
  }

#pragma region Left Button Down

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisFrameAndLeftMouseButtonDown_TriggersOnLeftButtonDown)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnLeftButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    simulateMouseButtonPressed(MouseButton::kLeft);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

    handler->update();

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverThisFrameAndLeftMouseButtonDown_DoesNotTriggerOnLeftButtonDown)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnLeftButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    simulateMouseButtonClicked(MouseButton::kLeft);

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kLeft));

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisFrameAndLeftMouseButtonUp_DoesNotTriggerOnLeftButtonDown)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnLeftButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kLeft));

    handler->update();

    Assert::IsFalse(called);
  }

#pragma endregion

#pragma region Left Button Up

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisAndLastFrameLeftMouseButtonUpThisFrame_TriggersOnLeftButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnLeftButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    simulateMouseButtonPressed(MouseButton::kLeft);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

    handler->update();
    simulateMouseButtonReleased(MouseButton::kLeft);
      
    Assert::IsTrue(handler->isMouseOver());
    Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kLeft));

    handler->update();

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverLastFrameButNotThisFrame_AndLeftMouseButtonUp_DoesNotTriggerOnLeftButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnLeftButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    simulateMouseButtonPressed(MouseButton::kLeft);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

    handler->update();
    simulateMouseButtonReleased(MouseButton::kLeft);
    handler->setMouseOver(false);

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kLeft));

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisAndLastFrameAndLeftMouseButtonNotUp_DoesNotTriggerOnLeftButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnLeftButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    simulateMouseButtonPressed(MouseButton::kLeft);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

    handler->update();

    Assert::IsTrue(handler->isMouseOver()); 
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverLastFrameButThisFrame_AndLeftMouseButtonUp_DoesNotTriggerOnLeftButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnLeftButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    simulateMouseButtonPressed(MouseButton::kLeft);

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

    handler->setMouseOver(true);
    handler->update();

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverLastOrThisFrameButThisFrame_AndLeftMouseButtonUp_DoesNotTriggerOnLeftButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnLeftButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    simulateMouseButtonPressed(MouseButton::kLeft);

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

    handler->update();

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kLeft));

    handler->update();

    Assert::IsFalse(called);
  }

#pragma endregion

#pragma region Middle Button Down

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisAndLastFrameAndMiddleMouseButtonDown_TriggersOnMiddleButtonDown)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnMiddleButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    simulateMouseButtonClicked(MouseButton::kMiddle);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kMiddle));

    handler->update();

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverThisFrameAndMiddleMouseButtonDown_DoesNotTriggerOnMiddleButtonDown)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnMiddleButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    simulateMouseButtonClicked(MouseButton::kMiddle);

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kMiddle));

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisFrameAndMiddleMouseButtonUp_DoesNotTriggerOnMiddleButtonDown)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnMiddleButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kMiddle));

    handler->update();

    Assert::IsFalse(called);
  }

#pragma endregion

#pragma region Middle Button Up

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisAndLastFrameAndMiddleMouseButtonUp_TriggersOnMiddleButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnMiddleButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    simulateMouseButtonPressed(MouseButton::kMiddle);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

    handler->update();
    simulateMouseButtonReleased(MouseButton::kMiddle);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kMiddle));

    handler->update();

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverLastFrameButNotThisFrame_AndMiddleMouseButtonUp_DoesNotTriggerOnMiddleButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnMiddleButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    simulateMouseButtonPressed(MouseButton::kMiddle);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

    handler->update();
    simulateMouseButtonReleased(MouseButton::kMiddle);
    handler->setMouseOver(false);

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kMiddle));

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisAndLastFrameAndMiddleMouseButtonDown_DoesNotTriggerOnMiddleButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnMiddleButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    simulateMouseButtonPressed(MouseButton::kMiddle);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

    handler->update();

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverLastFrameButThisFrame_AndMiddleMouseButtonUp_DoesNotTriggerOnMiddleButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnMiddleButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    simulateMouseButtonPressed(MouseButton::kMiddle);

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

    handler->setMouseOver(true);
    handler->update();

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverLastOrThisFrameButThisFrame_AndMiddleMouseButtonUp_DoesNotTriggerOnMiddleButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnMiddleButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    simulateMouseButtonPressed(MouseButton::kMiddle);

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

    handler->update();

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

    handler->update();

    Assert::IsFalse(called);
  }

#pragma endregion

#pragma region Right Button Down

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisFrameAndRightMouseButtonDown_TriggersOnRightButtonDown)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnRightButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    simulateMouseButtonClicked(MouseButton::kRight);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kRight));

    handler->update();

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverThisFrameAndRightMouseButtonDown_DoesNotTriggerOnRightButtonDown)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnRightButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    simulateMouseButtonClicked(MouseButton::kRight);

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonClicked(MouseButton::kRight));

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisFrameAndRightMouseButtonUp_DoesNotTriggerOnRightButtonDown)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnRightButtonDownEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsFalse(getMouse().isButtonClicked(MouseButton::kRight));

    handler->update();

    Assert::IsFalse(called);
  }

#pragma endregion

#pragma region Right Button Up

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisAndLastLastFrameRightMouseButtonUpThisFrame_TriggersOnRightButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnRightButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    simulateMouseButtonPressed(MouseButton::kRight);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kRight));

    handler->update();
    simulateMouseButtonReleased(MouseButton::kRight);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kRight));

    handler->update();

    Assert::IsTrue(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverLastFrameButNotThisFrame_AndRightMouseButtonUp_DoesNotTriggerOnRightButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnRightButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    simulateMouseButtonPressed(MouseButton::kRight);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kRight));

    handler->update();
    simulateMouseButtonReleased(MouseButton::kRight);
    handler->setMouseOver(false);

    Assert::IsFalse(getMouse().isButtonPressed(MouseButton::kRight));
    Assert::IsFalse(handler->isMouseOver());

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseOverThisAndLastFrameAndRightMouseButtonUp_DoesNotTriggerOnRightButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnRightButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    handler->setMouseOver(true);
    simulateMouseButtonPressed(MouseButton::kRight);

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kRight));

    handler->update();

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kRight));

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverLastFrameButThisFrame_AndRightMouseButtonUp_DoesNotTriggerOnRightButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnRightButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    simulateMouseButtonPressed(MouseButton::kMiddle);

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

    handler->setMouseOver(true);
    handler->update();

    Assert::IsTrue(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kMiddle));

    handler->update();

    Assert::IsFalse(called);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(MouseInteractionHandler_HandleInput_MouseNotOverLastOrThisFrameButThisFrame_AndRightMouseButtonUp_DoesNotTriggerOnRightButtonUp)
  {
    GameObject gameObject;
    observer_ptr<MouseInteractionHandler> handler = gameObject.addComponent<MouseInteractionHandler>();

    handler->getOnRightButtonUpEvent().subscribe(std::bind(&TestMouseInteractionHandler::callback, this, std::placeholders::_1));
    simulateMouseButtonPressed(MouseButton::kRight);

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kRight));

    handler->update();

    Assert::IsFalse(handler->isMouseOver());
    Assert::IsTrue(getMouse().isButtonPressed(MouseButton::kRight));

    handler->update();

    Assert::IsFalse(called);
  }

#pragma endregion

#pragma endregion

  };
}