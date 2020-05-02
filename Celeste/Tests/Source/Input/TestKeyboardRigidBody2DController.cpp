#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Input/KeyboardRigidBody2DController.h"
#include "Physics/RigidBody2D.h"
#include "Objects/GameObject.h"
#include "Registries/ComponentRegistry.h"
#include "Input/InputUtils.h"
#include "Input/InputEnums.h"
#include "Input/Keyboard.h"
#include "TestUtils/Assert/AssertCel.h"
#include "TestUtils/Assert/AssertExt.h"

using namespace Celeste;
using namespace Celeste::Input;
using namespace Celeste::Physics;


namespace TestCeleste::Input
{

  CELESTE_TEST_CLASS(TestKeyboardRigidBody2DController)

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    getKeyboard().flush();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_IsRegisteredWithComponentRegistry)
  {
    Assert::IsTrue(ComponentRegistry::hasComponent<KeyboardRigidBody2DController>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_IsAllocatableFromComponentRegistry)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentRegistry::createComponent(KeyboardRigidBody2DController::type_name(), gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<KeyboardRigidBody2DController*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Constructor_SetsAllValuesToDefault)
  {
    GameObject gameObject;
    KeyboardRigidBody2DController controller(gameObject);

    Assert::AreEqual(-1, controller.getDecreaseXLinearVelocityKey());
    Assert::AreEqual(-1, controller.getIncreaseXLinearVelocityKey());
    Assert::AreEqual(-1, controller.getIncreaseYLinearVelocityKey());
    Assert::AreEqual(-1, controller.getDecreaseYLinearVelocityKey());
    Assert::AreEqual(-1, controller.getDecreaseAngularVelocityKey());
    Assert::AreEqual(-1, controller.getIncreaseAngularVelocityKey());
    Assert::AreNotEqual(glm::vec2(), controller.getLinearVelocityDelta());
    Assert::AreNotEqual(0.0f, controller.getAngularVelocityDelta());
    Assert::IsTrue(Maths::Space::kLocal == controller.getSpace());
    Assert::IsTrue(Celeste::Input::IncrementMode::kContinuous == controller.getIncrementMode());
  }

#pragma endregion

#pragma region Handle Input Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_WithNoRigidBody2D_DoesNotThrow)
  {
    GameObject gameObject;
    KeyboardRigidBody2DController controller(gameObject);
    controller.update(0);
  }

#pragma region (kLocal)

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_DecreaseXLinearVelocityKeyDown_DecrementsXLinearVelocity)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setDecreaseXLinearVelocityKey(GLFW_KEY_A);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);

    getKeyboard().setKeyPressed(controller->getDecreaseXLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
    AssertExt::AreAlmostEqual(0.0f, rigidBody->getLinearVelocity().x);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_IncreaseXLinearVelocityKeyDown_IncrementsXLinearVelocity)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);

    getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(-controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
    AssertExt::AreAlmostEqual(0.0f, rigidBody->getLinearVelocity().x);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_DecreaseYLinearVelocityKeyDown_DecrementsYLinearVelocity)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setDecreaseYLinearVelocityKey(GLFW_KEY_B);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().y);

    getKeyboard().setKeyPressed(controller->getDecreaseYLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(-controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
    AssertExt::AreAlmostEqual(0.0f, rigidBody->getLinearVelocity().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_KLocal_IncreaseYLinearVelocityKeyDown_IncrementsYLinearVelocity)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_B);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().y);

    getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
    AssertExt::AreAlmostEqual(0.0f, rigidBody->getLinearVelocity().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_DecreaseAngularVelocityKeyDown_DecrementsAngularVelocity)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setDecreaseAngularVelocityKey(GLFW_KEY_A);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
    Assert::AreEqual(0.0f, rigidBody->getAngularVelocity());

    getKeyboard().setKeyPressed(controller->getDecreaseAngularVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseAngularVelocityKey()));

    controller->update(0);

    Assert::AreEqual(-controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_IncreaseAngularVelocityKeyDown_IncrementsAngularVelocity)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseAngularVelocityKey(GLFW_KEY_A);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
    Assert::AreEqual(0.0f, rigidBody->getAngularVelocity());

    getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

    controller->update(0);

    Assert::AreEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_BothIncreaseAndDecreaseXVelocityPressed_DoesNothing)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setDecreaseXLinearVelocityKey(GLFW_KEY_B);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);

    getKeyboard().setKeyPressed(controller->getDecreaseXLinearVelocityKey());
    getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_BothIncreaseAndDecreaseYVelocityPressed_DoesNothing)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_A);
    controller->setDecreaseYLinearVelocityKey(GLFW_KEY_B);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().y);

    getKeyboard().setKeyPressed(controller->getDecreaseYLinearVelocityKey());
    getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_BothIncreaseAndDecreaseAngularVelocityPressed_DoesNothing)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseAngularVelocityKey(GLFW_KEY_A);
    controller->setDecreaseAngularVelocityKey(GLFW_KEY_B);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
    Assert::AreEqual(0.0f, rigidBody->getAngularVelocity());

    getKeyboard().setKeyPressed(controller->getDecreaseAngularVelocityKey());
    getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseAngularVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

    controller->update(0);

    Assert::AreEqual(0.0f, rigidBody->getAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_BothDecreaseXAndYLinearVelocityPressed_DecrementsXAndYLinearVelocities)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setDecreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setDecreaseYLinearVelocityKey(GLFW_KEY_B);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);

    getKeyboard().setKeyPressed(controller->getDecreaseXLinearVelocityKey());
    getKeyboard().setKeyPressed(controller->getDecreaseYLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));

    controller->update(0);

    AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
    AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_BothIncreaseXAndYLinearVelocityPressed_IncrementsXAndYLinearVelocities)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_B);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);

    getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
    getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

    controller->update(0);

    AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
    AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_BothIncreaseLinearVelocityAndAngularVelocity_IncrementsLinearAndVelocities)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_B);
    controller->setIncreaseAngularVelocityKey(GLFW_KEY_C);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);

    getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
    getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
    getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

    controller->update(0);

    AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
    AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
    Assert::AreEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_kContinuous_AccumulatesChangesInLinearVelocity)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_B);
    controller->setDecreaseXLinearVelocityKey(GLFW_KEY_C);
    controller->setDecreaseYLinearVelocityKey(GLFW_KEY_D);
    controller->setIncrementMode(Celeste::Input::IncrementMode::kContinuous);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);
     
    // Increment once
    {
      getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
    }

    // Increment again
    {
      getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(2 * controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(-2 * controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
    }

    // -ve Increment
    {
      getKeyboard().setKeyReleased(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyReleased(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_kContinuous_AccumulatesChangesInAngularVelocity)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseAngularVelocityKey(GLFW_KEY_A);
    controller->setDecreaseAngularVelocityKey(GLFW_KEY_B);
    controller->setIncrementMode(Celeste::Input::IncrementMode::kContinuous);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);

    // Increment once
    {
      getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }

    // Increment again
    {
      getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(2 * controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }

    // -ve Increment
    {
      getKeyboard().setKeyReleased(controller->getIncreaseAngularVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_kToggle_SetsLinearVelocityToDeltaWhenKeyDown)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_B);
    controller->setDecreaseXLinearVelocityKey(GLFW_KEY_C);
    controller->setDecreaseYLinearVelocityKey(GLFW_KEY_D);
    controller->setIncrementMode(Celeste::Input::IncrementMode::kToggle);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);

    // Increment once
    {
      getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
    }

    // Increment again
    {
      getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
    }

    // -ve Increment
    {
      getKeyboard().setKeyReleased(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyReleased(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_kToggle_SetsLinearVelocityToZeroWhenKeyUp)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_B);
    controller->setDecreaseXLinearVelocityKey(GLFW_KEY_C);
    controller->setDecreaseYLinearVelocityKey(GLFW_KEY_D);
    controller->setIncrementMode(Celeste::Input::IncrementMode::kToggle);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);

    // Increment once
    {
      getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
    }

    {
      getKeyboard().setKeyReleased(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyReleased(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsFalse(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
      Assert::IsFalse(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

      controller->update(0);

      Assert::AreEqual(glm::vec2(), rigidBody->getLinearVelocity());
    }

    // -ve Increment
    {
      getKeyboard().setKeyPressed(controller->getDecreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().y);
    }

    {
      getKeyboard().setKeyReleased(controller->getDecreaseXLinearVelocityKey());
      getKeyboard().setKeyReleased(controller->getDecreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsFalse(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));
      Assert::IsFalse(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));

      controller->update(0);

      Assert::AreEqual(glm::vec2(), rigidBody->getLinearVelocity());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_kToggle_SetsAngularVelocityToDeltaWhenKeyDown)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseAngularVelocityKey(GLFW_KEY_A);
    controller->setDecreaseAngularVelocityKey(GLFW_KEY_B);
    controller->setIncrementMode(Celeste::Input::IncrementMode::kToggle);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);

    // Increment once
    {
      getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }

    // Increment again
    {
      getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }

    // -ve Increment
    {
      getKeyboard().setKeyReleased(controller->getIncreaseAngularVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(-controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kLocal_kToggle_SetsAngularVelocityToZeroWhenKeyUp)
  {
    GameObject gameObject;
    gameObject.getTransform()->setRotation(glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseAngularVelocityKey(GLFW_KEY_A);
    controller->setDecreaseAngularVelocityKey(GLFW_KEY_B);
    controller->setIncrementMode(Celeste::Input::IncrementMode::kToggle);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kLocal);

    // Increment once
    {
      getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }

    {
      getKeyboard().setKeyReleased(controller->getIncreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsFalse(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

      controller->update(0);

      Assert::AreEqual(0.0f, rigidBody->getAngularVelocity());
    }

    // -ve Increment
    {
      getKeyboard().setKeyPressed(controller->getDecreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(-controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }

    {
      getKeyboard().setKeyReleased(controller->getDecreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsFalse(getKeyboard().isKeyPressed(controller->getDecreaseAngularVelocityKey()));

      controller->update(0);

      Assert::AreEqual(0.0f, rigidBody->getAngularVelocity());
    }
  }

#pragma endregion

#pragma region (kWorld)

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_DecreaseXLinearVelocityKeyDown_DecrementsXLinearVelocity)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setSpace(Maths::Space::kWorld);
    controller->setDecreaseXLinearVelocityKey(GLFW_KEY_A);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);

    getKeyboard().setKeyPressed(controller->getDecreaseXLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(-controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().x);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_IncreaseXLinearVelocityKeyDown_IncrementsXLinearVelocity)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);

    getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().x);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_DecreaseYLinearVelocityKeyDown_DecrementsYLinearVelocity)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setSpace(Maths::Space::kWorld);
    controller->setDecreaseYLinearVelocityKey(GLFW_KEY_A);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().y);

    getKeyboard().setKeyPressed(controller->getDecreaseYLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(-controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_IncreaseYLinearVelocityKeyDown_IncrementsYLinearVelocity)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_A);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().y);

    getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_DecreaseAngularVelocityKeyDown_DecrementsAngularVelocity)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setSpace(Maths::Space::kWorld);
    controller->setDecreaseAngularVelocityKey(GLFW_KEY_A);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
    Assert::AreEqual(0.0f, rigidBody->getAngularVelocity());

    getKeyboard().setKeyPressed(controller->getDecreaseAngularVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseAngularVelocityKey()));

    controller->update(0);

    Assert::AreEqual(-controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_IncreaseAngularVelocityKeyDown_IncrementsAngularVelocity)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncreaseAngularVelocityKey(GLFW_KEY_A);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
    Assert::AreEqual(0.0f, rigidBody->getAngularVelocity());

    getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

    controller->update(0);

    Assert::AreEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_BothIncreaseAndDecreaseXVelocityPressed_DoesNothing)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setDecreaseXLinearVelocityKey(GLFW_KEY_B);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);

    getKeyboard().setKeyPressed(controller->getDecreaseXLinearVelocityKey());
    getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_BothIncreaseAndDecreaseYVelocityPressed_DoesNothing)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_A);
    controller->setDecreaseYLinearVelocityKey(GLFW_KEY_B);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().y);

    getKeyboard().setKeyPressed(controller->getDecreaseYLinearVelocityKey());
    getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().y);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_BothIncreaseAndDecreaseAngularVelocityPressed_DoesNothing)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncreaseAngularVelocityKey(GLFW_KEY_A);
    controller->setDecreaseAngularVelocityKey(GLFW_KEY_B);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
    Assert::AreEqual(0.0f, rigidBody->getAngularVelocity());

    getKeyboard().setKeyPressed(controller->getDecreaseAngularVelocityKey());
    getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseAngularVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

    controller->update(0);

    Assert::AreEqual(0.0f, rigidBody->getAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_BothDecreaseXAndYLinearVelocityPressed_DecrementsXAndYLinearVelocities)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setSpace(Maths::Space::kWorld);
    controller->setDecreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setDecreaseYLinearVelocityKey(GLFW_KEY_B);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);

    getKeyboard().setKeyPressed(controller->getDecreaseXLinearVelocityKey());
    getKeyboard().setKeyPressed(controller->getDecreaseYLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(-controller->getLinearVelocityDelta(), rigidBody->getLinearVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_BothIncreaseXAndYLinearVelocityPressed_IncrementsXAndYLinearVelocities)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_B);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);

    getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
    getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

    controller->update(0);

    Assert::AreEqual(controller->getLinearVelocityDelta(), rigidBody->getLinearVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_BothIncreaseLinearVelocityAndAngularVelocity_IncrementsLinearAndVelocities)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_B);
    controller->setIncreaseAngularVelocityKey(GLFW_KEY_C);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
    Assert::AreEqual(0.0f, rigidBody->getLinearVelocity().x);

    getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
    getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
    getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
    getKeyboard().update();

    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));
    Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

    controller->update(0);

    Assert::AreEqual(controller->getLinearVelocityDelta(), rigidBody->getLinearVelocity());
    Assert::AreEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_kContinuous_AccumulatesChangesInLinearVelocity)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_B);
    controller->setDecreaseXLinearVelocityKey(GLFW_KEY_C);
    controller->setDecreaseYLinearVelocityKey(GLFW_KEY_D);
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncrementMode(Celeste::Input::IncrementMode::kContinuous);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);

    // Increment once
    {
      getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().y);
    }

    // Increment again
    {
      getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(2 * controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(2 * controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().y);
    }

    // -ve Increment
    {
      getKeyboard().setKeyReleased(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyReleased(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().y);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_kContinuous_AccumulatesChangesInAngularVelocity)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseAngularVelocityKey(GLFW_KEY_A);
    controller->setDecreaseAngularVelocityKey(GLFW_KEY_B);
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncrementMode(Celeste::Input::IncrementMode::kContinuous);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);

    // Increment once
    {
      getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }

    // Increment again
    {
      getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(2 * controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }

    // -ve Increment
    {
      getKeyboard().setKeyReleased(controller->getIncreaseAngularVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_kToggle_SetsLinearVelocityToDeltaWhenKeyDown)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_B);
    controller->setDecreaseXLinearVelocityKey(GLFW_KEY_C);
    controller->setDecreaseYLinearVelocityKey(GLFW_KEY_D);
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncrementMode(Celeste::Input::IncrementMode::kToggle);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);

    // Increment once
    {
      getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().y);
    }

    // Increment again
    {
      getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().y);
    }

    // -ve Increment
    {
      getKeyboard().setKeyReleased(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyReleased(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().y);
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_kToggle_SetsLinearVelocityToZeroWhenKeyUp)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseXLinearVelocityKey(GLFW_KEY_A);
    controller->setIncreaseYLinearVelocityKey(GLFW_KEY_B);
    controller->setDecreaseXLinearVelocityKey(GLFW_KEY_C);
    controller->setDecreaseYLinearVelocityKey(GLFW_KEY_D);
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncrementMode(Celeste::Input::IncrementMode::kToggle);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);

    // Increment once
    {
      getKeyboard().setKeyPressed(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().y);
    }

    {
      getKeyboard().setKeyReleased(controller->getIncreaseXLinearVelocityKey());
      getKeyboard().setKeyReleased(controller->getIncreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsFalse(getKeyboard().isKeyPressed(controller->getIncreaseXLinearVelocityKey()));
      Assert::IsFalse(getKeyboard().isKeyPressed(controller->getIncreaseYLinearVelocityKey()));

      controller->update(0);

      Assert::AreEqual(glm::vec2(), rigidBody->getLinearVelocity());
    }

    // -ve Increment
    {
      getKeyboard().setKeyPressed(controller->getDecreaseXLinearVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));
      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().x, rigidBody->getLinearVelocity().x);
      AssertExt::AreAlmostEqual(-controller->getLinearVelocityDelta().y, rigidBody->getLinearVelocity().y);
    }

    {
      getKeyboard().setKeyReleased(controller->getDecreaseXLinearVelocityKey());
      getKeyboard().setKeyReleased(controller->getDecreaseYLinearVelocityKey());
      getKeyboard().update();

      Assert::IsFalse(getKeyboard().isKeyPressed(controller->getDecreaseXLinearVelocityKey()));
      Assert::IsFalse(getKeyboard().isKeyPressed(controller->getDecreaseYLinearVelocityKey()));

      controller->update(0);

      Assert::AreEqual(glm::vec2(), rigidBody->getLinearVelocity());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_kToggle_SetsAngularVelocityToDeltaWhenKeyDown)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseAngularVelocityKey(GLFW_KEY_A);
    controller->setDecreaseAngularVelocityKey(GLFW_KEY_B);
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncrementMode(Celeste::Input::IncrementMode::kToggle);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);
      
    // Increment once
    {
      getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }

    // Increment again
    {
      getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }

    // -ve Increment
    {
      getKeyboard().setKeyReleased(controller->getIncreaseAngularVelocityKey());
      getKeyboard().setKeyPressed(controller->getDecreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(-controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(KeyboardRigidBody2DController_Update_kWorld_kToggle_SetsAngularVelocityToZeroWhenKeyUp)
  {
    Transform transform;
    transform.setRotation(glm::half_pi<float>());

    GameObject gameObject;
    gameObject.getTransform()->setParent(&transform);
    gameObject.getTransform()->setRotation(-glm::half_pi<float>());

    observer_ptr<RigidBody2D> rigidBody = gameObject.addComponent<RigidBody2D>();
    observer_ptr<KeyboardRigidBody2DController> controller = gameObject.addComponent<KeyboardRigidBody2DController>();
    controller->setIncreaseAngularVelocityKey(GLFW_KEY_A);
    controller->setDecreaseAngularVelocityKey(GLFW_KEY_B);
    controller->setSpace(Maths::Space::kWorld);
    controller->setIncrementMode(Celeste::Input::IncrementMode::kToggle);

    Assert::IsTrue(controller->getSpace() == Maths::Space::kWorld);

    // Increment once
    {
      getKeyboard().setKeyPressed(controller->getIncreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }

    {
      getKeyboard().setKeyReleased(controller->getIncreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsFalse(getKeyboard().isKeyPressed(controller->getIncreaseAngularVelocityKey()));

      controller->update(0);

      Assert::AreEqual(0.0f, rigidBody->getAngularVelocity());
    }

    // -ve Increment
    {
      getKeyboard().setKeyPressed(controller->getDecreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsTrue(getKeyboard().isKeyPressed(controller->getDecreaseAngularVelocityKey()));

      controller->update(0);

      AssertExt::AreAlmostEqual(-controller->getAngularVelocityDelta(), rigidBody->getAngularVelocity());
    }

    {
      getKeyboard().setKeyReleased(controller->getDecreaseAngularVelocityKey());
      getKeyboard().update();

      Assert::IsFalse(getKeyboard().isKeyPressed(controller->getDecreaseAngularVelocityKey()));

      controller->update(0);

      Assert::AreEqual(0.0f, rigidBody->getAngularVelocity());
    }
  }

#pragma endregion

#pragma endregion

  };
}