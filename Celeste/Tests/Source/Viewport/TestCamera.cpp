#include "UtilityHeaders/UnitTestHeaders.h"

#include "Viewport/Camera.h"
#include "Scene/SceneUtils.h"
#include "Input/Mouse.h"
#include "Input/InputUtils.h"
#include "AssertCel.h"
#include "AssertExt.h"

using namespace Celeste;
using namespace Celeste::Input;
using namespace Celeste::Maths;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestCamera)

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_Constructor_SetsCameraValuesToDefault)
  {
    Camera camera;
      
    Assert::AreEqual(1.0f, camera.getAspectRatio());
    Assert::AreNotEqual(0.0f, camera.getNearPlane());
    Assert::AreNotEqual(0.0f, camera.getFarPlane());
    Assert::AreEqual(glm::vec2(1), camera.getViewportDimensions());
    Assert::IsTrue(ProjectionMode::kPerspective == camera.getProjectionMode());
  }

#pragma endregion

#pragma region Get View Matrix Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_GetViewMatrix_PerspectiveMode_AppliesCameraTranslationOnly)
  {
    Camera camera;
    camera.getTransform().setTranslation(glm::vec3(-1, 3, 0.25f));
    camera.getTransform().rotate(2);
    camera.getTransform().scale(2, 0.5f, 0.6f);
    camera.setProjectionMode(ProjectionMode::kPerspective);

    Assert::IsTrue(camera.getProjectionMode() == ProjectionMode::kPerspective);
    Assert::AreEqual(glm::translate(glm::identity<glm::mat4>(), glm::vec3(1, -3, -0.25f)), camera.getViewMatrix());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_GetViewMatrix_OrthographicMode_ReturnsIdentityMatrix)
  {
    Camera camera;
    camera.getTransform().setTranslation(glm::vec3(-1, 3, 0.25f));
    camera.getTransform().rotate(2);
    camera.getTransform().scale(2, 0.5f, 0.6f);
    camera.setProjectionMode(ProjectionMode::kOrthographic);

    Assert::IsTrue(camera.getProjectionMode() == ProjectionMode::kOrthographic);
    Assert::AreEqual(glm::identity<glm::mat4>(), camera.getViewMatrix());
  }

#pragma endregion

#pragma region Get Projection Matrix Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_GetProjectionMatrix_Orthographic)
  {
    Camera camera;
    camera.setProjectionMode(ProjectionMode::kOrthographic);
    camera.setViewportDimensions(800, 600);
    camera.getTransform().setTranslation(glm::vec3(-1, 3, 0.25f));
    camera.getTransform().rotate(2);
    camera.getTransform().scale(2, 0.5f, 0.6f);

    Assert::IsTrue(ProjectionMode::kOrthographic == camera.getProjectionMode());

    float width = 800;
    float height = 600;
    Assert::AreEqual(glm::ortho<float>(0, width, 0, height), camera.getProjectionMatrix());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_GetProjectionMatrix_Perspective)
  {
    Camera camera;
    camera.setProjectionMode(ProjectionMode::kPerspective);
    camera.setViewportDimensions(800, 600);
    camera.getTransform().setTranslation(glm::vec3(-1, 3, 0.25f));
    camera.getTransform().rotate(2);
    camera.getTransform().scale(2, 0.5f, 0.6f);

    Assert::IsTrue(ProjectionMode::kPerspective == camera.getProjectionMode());

    float aRatio = camera.getAspectRatio();
    float nPlane = camera.getNearPlane();
    float fPlane = camera.getFarPlane();
    AssertExt::AreAlmostEqual(glm::perspective<float>(45.0f, aRatio, nPlane, fPlane), camera.getProjectionMatrix());
  }

#pragma endregion

#pragma region Create Ray Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_CreateRay_Perspective_Simple)
  {
    Camera camera;
    camera.setProjectionMode(ProjectionMode::kPerspective);

    Assert::IsTrue(camera.getProjectionMode() == ProjectionMode::kPerspective);

    Mouse& mouse = getMouse();
    mouse.getTransform().setTranslation(glm::vec3(camera.getViewportDimensions() * 0.5f, 0));

    Ray actual = camera.createRay();

    Assert::AreEqual(camera.getTransform().getWorldTranslation(), actual.m_origin);
    Assert::AreEqual(glm::vec3(0, 0, -1), actual.m_direction);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_CreateRay_Perspective_Complex)
  {
    Camera camera;
    camera.setProjectionMode(ProjectionMode::kPerspective);
    camera.setViewportDimensions(1920, 1080);

    Assert::IsTrue(camera.getProjectionMode() == ProjectionMode::kPerspective);

    Mouse& mouse = getMouse();
    mouse.getTransform().setTranslation(glm::vec3(1, -2, 0));

    Ray actual = camera.createRay();

    Assert::AreEqual(camera.getTransform().getWorldTranslation(), actual.m_origin);
    AssertExt::AreAlmostEqual(getRayDirection(glm::vec2(1, -2), camera), actual.m_direction);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_CreateRay_InputtingValues_Perspective_Simple)
  {
    Camera camera;

    camera.getTransform().setTranslation(glm::vec3(0, 0, 5));
    camera.setViewportDimensions(800, 600);
    camera.setProjectionMode(ProjectionMode::kPerspective);

    Assert::IsTrue(ProjectionMode::kPerspective == camera.getProjectionMode());

    Ray ray = camera.createRay(glm::vec2(400, 300));
    Assert::AreEqual(glm::vec3(0, 0, 5), ray.m_origin);
    Assert::AreEqual(glm::vec3(0, 0, -1), ray.m_direction);

    ray = camera.createRay(glm::vec2(0, 0));
    const glm::vec3& expectedDirection = getRayDirection(glm::vec2(0, 0), camera);

    Assert::AreEqual(glm::vec3(0, 0, 5), ray.m_origin);
    Assert::AreEqual(expectedDirection, ray.m_direction);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_CreateRay_InputtingValues_Perspective_Complex)
  {
    Camera camera;

    camera.getTransform().setTranslation(glm::vec3(0.25f, -2, 5));
    camera.setViewportDimensions(800, 600);
    camera.setProjectionMode(ProjectionMode::kPerspective);

    Assert::IsTrue(ProjectionMode::kPerspective == camera.getProjectionMode());

    Ray ray = camera.createRay(glm::vec2(12, 50));
    const glm::vec3& expectedDirection = getRayDirection(glm::vec2(12, 50), camera);

    Assert::AreEqual(glm::vec3(0.25f, -2, 5), ray.m_origin);
    Assert::AreEqual(expectedDirection, ray.m_direction);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_CreateRay_Orthographic)
  {
    Camera camera;
    camera.setProjectionMode(ProjectionMode::kOrthographic);

    Assert::IsTrue(camera.getProjectionMode() == ProjectionMode::kOrthographic);

    Mouse& mouse = getMouse();
    mouse.getTransform().setTranslation(glm::vec3(5, -2.123f, 0));

    Ray actual = camera.createRay();

    Assert::AreEqual(glm::vec3(5, -2.123f, 0) + camera.getTransform().getWorldTranslation(), actual.m_origin);
    Assert::AreEqual(glm::vec3(0, 0, -1), actual.m_direction);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_CreateRay_InputtingValues_Orthographic)
  {
    Camera camera;

    camera.getTransform().setTranslation(glm::vec3(1, -3.5f, 5));
    camera.setProjectionMode(ProjectionMode::kOrthographic);

    Assert::IsTrue(ProjectionMode::kOrthographic == camera.getProjectionMode());

    Ray ray = camera.createRay(glm::vec2(400, 300));
    Assert::AreEqual(glm::vec3(401, 296.5f, 5), ray.m_origin);
    Assert::AreEqual(glm::vec3(0, 0, -1), ray.m_direction);

    ray = camera.createRay(glm::vec2(0, 0));

    Assert::AreEqual(glm::vec3(1, -3.5f, 5), ray.m_origin);
    Assert::AreEqual(glm::vec3(0, 0, -1), ray.m_direction);

    ray = camera.createRay(glm::vec2(-1, 3.5f));

    Assert::AreEqual(glm::vec3(0, 0, 5), ray.m_origin);
    Assert::AreEqual(glm::vec3(0, 0, -1), ray.m_direction);
  }

#pragma endregion

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_SetProjectionMode)
  {
    Camera camera;
    camera.setProjectionMode(ProjectionMode::kPerspective);

    Assert::IsTrue(ProjectionMode::kPerspective == camera.getProjectionMode());

    camera.setProjectionMode(ProjectionMode::kOrthographic);

    Assert::IsTrue(ProjectionMode::kOrthographic == camera.getProjectionMode());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Camera_SetViewportDimensions_ChangesAspectRatio)
  {
    Camera camera;
    camera.setViewportDimensions(300, 150);

    Assert::AreEqual(2.0f, camera.getAspectRatio());

    camera.setViewportDimensions(glm::vec2(0.01f, 2));

    Assert::AreEqual(0.005f, camera.getAspectRatio());
  }

  private:

    //------------------------------------------------------------------------------------------------
    glm::vec3 getRayDirection(
      const glm::vec2& screenPosition, 
      const Camera& camera) const
    {
      float mouseX = screenPosition.x / (camera.getViewportDimensions().x  * 0.5f) - 1.0f;
      float mouseY = screenPosition.y / (camera.getViewportDimensions().y * 0.5f) - 1.0f;

      glm::mat4 invP = glm::inverse(glm::perspective<float>(45.0f, camera.getAspectRatio(), camera.getNearPlane(), camera.getFarPlane()));
      glm::vec4 clipSpace = glm::vec4(mouseX, mouseY, -1, 1);
      glm::vec4 eyeSpace = invP * clipSpace;
      eyeSpace.z = -1;
      eyeSpace.w = 0;
      glm::mat4 invV = glm::inverse(camera.getViewMatrix());
      glm::vec4 worldPos = invV * eyeSpace;

      return glm::normalize(glm::vec3(worldPos));
    }
  };
}