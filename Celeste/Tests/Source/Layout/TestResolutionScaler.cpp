#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "Layout/ResolutionScaler.h"
#include "Objects/GameObject.h"

using namespace Celeste;
using namespace Celeste::Layout;


namespace TestCeleste::Layout
{
  CELESTE_TEST_CLASS(TestResolutionScaler)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResolutionScaler_Constructor_MarksForRescale)
  {
    GameObject gameObject;
    ResolutionScaler scaler(gameObject);

    Assert::IsTrue(scaler.needsRescale());
  }

#pragma endregion

#pragma region Set Target Dimensions Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResolutionScaler_SetTargetDimensions_UpdatesTargetDimensions)
  {
    GameObject gameObject;
    ResolutionScaler scaler(gameObject);
    scaler.setTargetResolution(glm::vec2(400, 300));
    
    Assert::AreEqual(glm::vec2(400, 300), scaler.getTargetResolution());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResolutionScaler_SetTargetDimensions_MarksForRescale)
  {
    GameObject gameObject;
    ResolutionScaler scaler(gameObject);
    scaler.rescale(glm::vec2(100, 200), glm::vec2(100, 200));

    Assert::IsFalse(scaler.needsRescale());

    scaler.setTargetResolution(glm::vec2(300, 400));

    Assert::IsTrue(scaler.needsRescale());
  }

#pragma endregion

#pragma region Rescale Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResolutionScaler_Rescale_OldResolutionEqualsNewResolution_ScalesGameObjectCorrectly)
  {
    GameObject gameObject;
    ResolutionScaler scaler(gameObject);
    scaler.setTargetResolution(glm::vec2(200, 1000));
    scaler.rescale(glm::vec2(100, 200), glm::vec2(100, 200));

    Assert::AreEqual(glm::vec3(0.5f, 0.2f, 1), gameObject.getTransform()->getScale());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResolutionScaler_Rescale_OldResolutionEqualsNewResolution_TranslatesGameObjectCorrectly)
  {
    GameObject gameObject;
    ResolutionScaler scaler(gameObject);
    scaler.setTargetResolution(glm::vec2(200, 1000));
    scaler.rescale(glm::vec2(100, 200), glm::vec2(100, 200));

    Assert::AreEqual(glm::vec3(-50.0f, -400.0f, 0), gameObject.getTransform()->getTranslation());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResolutionScaler_Rescale_OldResolutionEqualsNewResolution_DoesNotMarkForRescale)
  {
    GameObject gameObject;
    ResolutionScaler scaler(gameObject);
    scaler.setTargetResolution(glm::vec2(200, 1000));

    Assert::IsTrue(scaler.needsRescale());

    scaler.rescale(glm::vec2(100, 200), glm::vec2(100, 200));

    Assert::IsFalse(scaler.needsRescale());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResolutionScaler_Rescale_OldResolutionDoesNotEqualNewResolution_ScalesGameObjectCorrectly)
  {
    GameObject gameObject;
    ResolutionScaler scaler(gameObject);
    scaler.setTargetResolution(glm::vec2(200, 1000));
    scaler.rescale(glm::vec2(100, 200), glm::vec2(800, 2000));

    Assert::AreEqual(glm::vec3(8, 10, 1), gameObject.getTransform()->getScale());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResolutionScaler_Rescale_OldResolutionDoesNotEqualNewResolution_TranslatesGameObjectCorrectly)
  {
    GameObject gameObject;
    ResolutionScaler scaler(gameObject);
    scaler.setTargetResolution(glm::vec2(200, 1000));
    scaler.rescale(glm::vec2(100, 200), glm::vec2(400, 2000));

    Assert::AreEqual(glm::vec3(150.0f, 900.0f, 0), gameObject.getTransform()->getTranslation());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ResolutionScaler_Rescale_OldResolutionDoesNotEqualNewResolution_DoesNotMarkForRescale)
  {
    GameObject gameObject;
    ResolutionScaler scaler(gameObject);
    scaler.setTargetResolution(glm::vec2(200, 1000));

    Assert::IsTrue(scaler.needsRescale());

    scaler.rescale(glm::vec2(100, 200), glm::vec2(100, 200));

    Assert::IsFalse(scaler.needsRescale());
  }

#pragma endregion

  };
}