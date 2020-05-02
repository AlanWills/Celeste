#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Maths/Rectangle.h"

using namespace Celeste;


namespace TestCeleste
{
    CELESTE_TEST_CLASS(TestRectangle)

#pragma region Constructor Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_DefaultConstructor)
    {
      Celeste::Maths::Rectangle rectangle;

      Assert::IsTrue(glm::vec2() == rectangle.getCentre());
      Assert::IsTrue(glm::vec2() == rectangle.getDimensions());
      Assert::IsTrue(glm::vec2() == rectangle.getTop());
      Assert::IsTrue(glm::vec2() == rectangle.getBottom());
      Assert::IsTrue(glm::vec2() == rectangle.getLeft());
      Assert::IsTrue(glm::vec2() == rectangle.getRight());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_VectorConstructor)
    {
      Celeste::Maths::Rectangle rectangle(glm::vec2(100, 50), glm::vec2(50, 25));

      Assert::IsTrue(glm::vec2(100, 50) == rectangle.getCentre());
      Assert::IsTrue(glm::vec2(50, 25) == rectangle.getDimensions());
      Assert::IsTrue(glm::vec2(100, 62.5f) == rectangle.getTop());
      Assert::IsTrue(glm::vec2(100, 37.5f) == rectangle.getBottom());
      Assert::IsTrue(glm::vec2(75, 50) == rectangle.getLeft());
      Assert::IsTrue(glm::vec2(125, 50) == rectangle.getRight());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_FloatConstructor)
    {
      Celeste::Maths::Rectangle rectangle(100, 50, 50, 25);

      Assert::IsTrue(glm::vec2(100, 50) == rectangle.getCentre());
      Assert::IsTrue(glm::vec2(50, 25) == rectangle.getDimensions());
      Assert::IsTrue(glm::vec2(100, 62.5f) == rectangle.getTop());
      Assert::IsTrue(glm::vec2(100, 37.5f) == rectangle.getBottom());
      Assert::IsTrue(glm::vec2(75, 50) == rectangle.getLeft());
      Assert::IsTrue(glm::vec2(125, 50) == rectangle.getRight());
    }

#pragma endregion

#pragma region Contains Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_Contains_RectangleDegenerate_ShouldReturnFalse)
    {
      Celeste::Maths::Rectangle rectangle;

      Assert::AreEqual(glm::vec2(), rectangle.getDimensions());
      Assert::IsFalse(rectangle.contains(glm::vec2()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_Contains_ShouldReturnTrue)
    {
      Celeste::Maths::Rectangle rectangle(100, 50, 50, 25);

      // Centre
      Assert::IsTrue(rectangle.contains(glm::vec2(100, 50)));

      // Top left quadrant
      Assert::IsTrue(rectangle.contains(glm::vec2(90, 55)));

      // Top right quadrant
      Assert::IsTrue(rectangle.contains(glm::vec2(110, 55)));

      // Bottom left quadrant
      Assert::IsTrue(rectangle.contains(glm::vec2(90, 45)));

      // Bottom right quadrant
      Assert::IsTrue(rectangle.contains(glm::vec2(110, 45)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_Contains_OnEdges_ShouldReturnFalse)
    {
      Celeste::Maths::Rectangle rectangle(100, 50, 50, 25);

      // Left edge
      Assert::IsFalse(rectangle.contains(glm::vec2(75, 50)));

      // Top edge
      Assert::IsFalse(rectangle.contains(glm::vec2(100, 62.5f)));

      // Right edge
      Assert::IsFalse(rectangle.contains(glm::vec2(125, 50)));

      // Bottom edge
      Assert::IsFalse(rectangle.contains(glm::vec2(100, 37.5f)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_Contains_ShouldReturnFalse)
    {
      Celeste::Maths::Rectangle rectangle(100, 50, 50, 25);

      Assert::IsFalse(rectangle.contains(glm::vec2(1000, 1000)));
      Assert::IsFalse(rectangle.contains(glm::vec2(-1000, 50)));
      Assert::IsFalse(rectangle.contains(glm::vec2(100, 0)));
    }

#pragma endregion

#pragma region Intersects Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_Intersects_BothRectanglesDegenerate_ShouldReturnFalse)
    {
      Celeste::Maths::Rectangle rectangle;
      Celeste::Maths::Rectangle rectangle2;

      Assert::AreEqual(glm::vec2(), rectangle.getDimensions());
      Assert::AreEqual(glm::vec2(), rectangle2.getDimensions());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_Intersects_OneRectangleDegenerate_ShouldReturnFalse)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 100);
      Celeste::Maths::Rectangle rectangle2;

      Assert::AreEqual(glm::vec2(100, 100), rectangle.getDimensions());
      Assert::AreEqual(glm::vec2(), rectangle2.getDimensions());
      Assert::IsFalse(rectangle.intersects(rectangle2));
      Assert::IsFalse(rectangle2.intersects(rectangle));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_Intersects_ShouldReturnTrue)
    {
      Celeste::Maths::Rectangle rectangle(100, 50, 50, 25);

      // Completely inside
      Assert::IsTrue(rectangle.intersects(Celeste::Maths::Rectangle(90, 45, 5, 5)));

      // Top left quadrant
      Assert::IsTrue(rectangle.intersects(Celeste::Maths::Rectangle(90, 55, 100, 100)));

      // Top right quadrant
      Assert::IsTrue(rectangle.intersects(Celeste::Maths::Rectangle(110, 45, 100, 100)));

      // Bottom left quadrant
      Assert::IsTrue(rectangle.intersects(Celeste::Maths::Rectangle(90, 45, 100, 100)));

      // Bottom right quadrant
      Assert::IsTrue(rectangle.intersects(Celeste::Maths::Rectangle(110, 45, 100, 100)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_Intersects_EdgesTouching_ShouldReturnFalse)
    {
      Celeste::Maths::Rectangle rectangle(100, 50, 50, 25);

      // Left edge
      Assert::IsFalse(rectangle.intersects(Celeste::Maths::Rectangle(50, 100, 50, 1000)));

      // Top edge
      Assert::IsFalse(rectangle.intersects(Celeste::Maths::Rectangle(90, 75, 1000, 25)));

      // Right edge
      Assert::IsFalse(rectangle.intersects(Celeste::Maths::Rectangle(150, 0, 50, 1000)));

      // Bottom edge
      Assert::IsFalse(rectangle.intersects(Celeste::Maths::Rectangle(110, 25, 1000, 25)));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_Intersects_ShouldReturnFalse)
    {
      Celeste::Maths::Rectangle rectangle(100, 50, 50, 25);

      Assert::IsFalse(rectangle.intersects(Celeste::Maths::Rectangle(1000, 1000, 1, 1)));
      Assert::IsFalse(rectangle.intersects(Celeste::Maths::Rectangle(-1000, 50, 100, 10000)));
      Assert::IsFalse(rectangle.intersects(Celeste::Maths::Rectangle(100, 0, 20, 20)));
    }

#pragma endregion

#pragma region Stretch Width Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchWidth_DecreasingWidth_AnchorLeft_SetsWidthAndCentreToCorrectValues)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(100.0f, rectangle.getDimensions().x);

      rectangle.stretchWidth(60, UI::HorizontalAlignment::kLeft);

      Assert::AreEqual(-20.0f, rectangle.getCentre().x);
      Assert::AreEqual(60.0f, rectangle.getDimensions().x);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchWidth_SameWidth_AnchorLeft_DoesNothing)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(100.0f, rectangle.getDimensions().x);

      rectangle.stretchWidth(100, UI::HorizontalAlignment::kLeft);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(100.0f, rectangle.getDimensions().x);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchWidth_IncreasingWidth_AnchorLeft_SetsWidthAndCentreToCorrectValues)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(100.0f, rectangle.getDimensions().x);

      rectangle.stretchWidth(150, UI::HorizontalAlignment::kLeft);

      Assert::AreEqual(25.0f, rectangle.getCentre().x);
      Assert::AreEqual(150.0f, rectangle.getDimensions().x);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchWidth_DecreasingWidth_AnchorCentre_SetsWidthAndCentreToCorrectValues)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(100.0f, rectangle.getDimensions().x);

      rectangle.stretchWidth(60, UI::HorizontalAlignment::kCentre);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(60.0f, rectangle.getDimensions().x);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchWidth_SameWidth_AnchorCentre_DoesNothing)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(100.0f, rectangle.getDimensions().x);

      rectangle.stretchWidth(100, UI::HorizontalAlignment::kCentre);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(100.0f, rectangle.getDimensions().x);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchWidth_IncreasingWidth_AnchorCentre_SetsWidthAndCentreToCorrectValues)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(100.0f, rectangle.getDimensions().x);

      rectangle.stretchWidth(150, UI::HorizontalAlignment::kCentre);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(150.0f, rectangle.getDimensions().x);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchWidth_DecreasingWidth_AnchorRight_SetsWidthAndCentreToCorrectValues)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(100.0f, rectangle.getDimensions().x);

      rectangle.stretchWidth(60, UI::HorizontalAlignment::kRight);

      Assert::AreEqual(20.0f, rectangle.getCentre().x);
      Assert::AreEqual(60.0f, rectangle.getDimensions().x);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchWidth_SameWidth_AnchorRight_DoesNothing)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(100.0f, rectangle.getDimensions().x);

      rectangle.stretchWidth(100, UI::HorizontalAlignment::kRight);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(100.0f, rectangle.getDimensions().x);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchWidth_IncreasingWidth_AnchorRight_SetsWidthAndCentreToCorrectValues)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().x);
      Assert::AreEqual(100.0f, rectangle.getDimensions().x);

      rectangle.stretchWidth(150, UI::HorizontalAlignment::kRight);

      Assert::AreEqual(-25.0f, rectangle.getCentre().x);
      Assert::AreEqual(150.0f, rectangle.getDimensions().x);
    }

#pragma endregion

#pragma region Stretch Height Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchHeight_DecreasingHeight_AnchorTop_SetsHeightAndCentreToCorrectValues)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(200.0f, rectangle.getDimensions().y);

      rectangle.stretchHeight(60, UI::VerticalAlignment::kTop);

      Assert::AreEqual(70.0f, rectangle.getCentre().y);
      Assert::AreEqual(60.0f, rectangle.getDimensions().y);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchHeight_SameHeight_AnchorTop_DoesNothing)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(200.0f, rectangle.getDimensions().y);

      rectangle.stretchHeight(200, UI::VerticalAlignment::kTop);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(200.0f, rectangle.getDimensions().y);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchHeight_IncreasingHeight_AnchorTop_SetsHeightAndCentreToCorrectValues)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(200.0f, rectangle.getDimensions().y);

      rectangle.stretchHeight(250, UI::VerticalAlignment::kTop);

      Assert::AreEqual(-25.0f, rectangle.getCentre().y);
      Assert::AreEqual(250.0f, rectangle.getDimensions().y);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchHeight_DecreasingHeight_AnchorCentre_SetsHeightAndCentreToCorrectValues)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(200.0f, rectangle.getDimensions().y);

      rectangle.stretchHeight(60, UI::VerticalAlignment::kCentre);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(60.0f, rectangle.getDimensions().y);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchHeight_SameHeight_AnchorCentre_DoesNothing)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(200.0f, rectangle.getDimensions().y);

      rectangle.stretchHeight(200, UI::VerticalAlignment::kCentre);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(200.0f, rectangle.getDimensions().y);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchHeight_IncreasingHeight_AnchorCentre_SetsHeightAndCentreToCorrectValues)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(200.0f, rectangle.getDimensions().y);

      rectangle.stretchHeight(250, UI::VerticalAlignment::kCentre);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(250.0f, rectangle.getDimensions().y);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchHeight_DecreasingHeight_AnchorBottom_SetsHeightAndCentreToCorrectValues)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(200.0f, rectangle.getDimensions().y);

      rectangle.stretchHeight(60, UI::VerticalAlignment::kBottom);

      Assert::AreEqual(-70.0f, rectangle.getCentre().y);
      Assert::AreEqual(60.0f, rectangle.getDimensions().y);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchHeight_SameHeight_AnchorBottom_DoesNothing)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(200.0f, rectangle.getDimensions().y);

      rectangle.stretchHeight(200, UI::VerticalAlignment::kBottom);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(200.0f, rectangle.getDimensions().y);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_StretchHeight_IncreasingHeight_AnchorBottom_SetsHeightAndCentreToCorrectValues)
    {
      Celeste::Maths::Rectangle rectangle(0, 0, 100, 200);

      Assert::AreEqual(0.0f, rectangle.getCentre().y);
      Assert::AreEqual(200.0f, rectangle.getDimensions().y);

      rectangle.stretchHeight(250, UI::VerticalAlignment::kBottom);

      Assert::AreEqual(25.0f, rectangle.getCentre().y);
      Assert::AreEqual(250.0f, rectangle.getDimensions().y);
    }

#pragma endregion

#pragma region Set Centre X Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_SetCentreX_UpdatesXCentreCorrectly)
    {
      Celeste::Maths::Rectangle rectangle;
      rectangle.setCentre(500, 100);

      Assert::AreEqual(500.0f, rectangle.getCentre().x);

      rectangle.setCentreX(150);

      Assert::AreEqual(150.0f, rectangle.getCentre().x);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_SetCentreX_DoesNotChangeYCentre)
    {
      Celeste::Maths::Rectangle rectangle;
      rectangle.setCentre(500, 100);

      Assert::AreEqual(100.0f, rectangle.getCentre().y);

      rectangle.setCentreX(150);

      Assert::AreEqual(100.0f, rectangle.getCentre().y);
    }

#pragma endregion

#pragma region Set Centre Y Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_SetCentreY_UpdatesYCentreCorrectly)
    {
      Celeste::Maths::Rectangle rectangle;
      rectangle.setCentre(500, 100);

      Assert::AreEqual(100.0f, rectangle.getCentre().y);

      rectangle.setCentreY(150);

      Assert::AreEqual(150.0f, rectangle.getCentre().y);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_SetCentreY_DoesNotChangeXCentre)
    {
      Celeste::Maths::Rectangle rectangle;
      rectangle.setCentre(500, 100);

      Assert::AreEqual(500.0f, rectangle.getCentre().x);

      rectangle.setCentreY(150);

      Assert::AreEqual(500.0f, rectangle.getCentre().x);
    }

#pragma endregion

#pragma region Set Centre Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_SetCentre_UpdatesCentreCorrectly)
    {
      Celeste::Maths::Rectangle rectangle;
      rectangle.setCentre(500, 100);

      Assert::AreEqual(glm::vec2(500, 100.0f), rectangle.getCentre());

      rectangle.setCentre(glm::vec2(-10, 0.1f));

      Assert::AreEqual(glm::vec2(-10, 0.1f), rectangle.getCentre());
    }

#pragma endregion

#pragma region Set Dimensions Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Rectangle_SetDimensions_UpdatesDimensionsCorrectly)
    {
      Celeste::Maths::Rectangle rectangle;
      rectangle.setDimensions(500, 100);

      Assert::AreEqual(glm::vec2(500, 100.0f), rectangle.getDimensions());

      rectangle.setDimensions(glm::vec2(-10, 0.1f));

      Assert::AreEqual(glm::vec2(-10, 0.1f), rectangle.getDimensions());
    }

#pragma endregion

    };
}