/***************************************************************\

    ******     ******    ******   ******    ********
    **    **  **    **  **    **  **    **  **    **
    **    **  **    **  **    **  **    **  **
    **    **  **    **  **    **  **    **  ********
    **    **  **    **  **    **  ******          **
    **    **  **    **  **    **  **  ***   **    **
    ******     ******    ******   **    **  ********

    Filename: tests_rect_3d.h
    Desc:     tests for 3d rectangle

    Created:  14.09.2025 by DimaSkup
\***************************************************************/
#pragma once

#include <geometry/rect_3d.h>
#include <geometry/rect_3d_functions.h>

#include <log.h>
#include <stdio.h>
#include <assert.h>

//==================================================================================
// forward declaration of the main test for Rect3d
//==================================================================================
void TestRect3d();


//==================================================================================
// Test constructors
//==================================================================================
void Rect3dTestConstructorDefault()
{
    const Rect3d rect;

    assert(rect.x0 == 0.0f);
    assert(rect.x1 == 0.0f);
    assert(rect.y0 == 0.0f);
    assert(rect.y1 == 0.0f);
    assert(rect.z0 == 0.0f);
    assert(rect.z1 == 0.0f);

    LogMsg("%-50s test is passed", "Rect3d::Rect3d())");
}

//---------------------------------------------------------

void Rect3dTestConstructorFloats()
{
    const Rect3d rect(1,2, 3,4, 5,6);

    assert(rect.x0 == 1.0f);
    assert(rect.x1 == 2.0f);
    assert(rect.y0 == 3.0f);
    assert(rect.y1 == 4.0f);
    assert(rect.z0 == 5.0f);
    assert(rect.z1 == 6.0f);

    LogMsg("%-50s test is passed", "Rect3d::Rect3d(six floats))");
}

//---------------------------------------------------------

void Rect3dTestConstructorCopy()
{
    const Rect3d rectSrc(1,2, 3,4, 5,6);
    const Rect3d rectDst(rectSrc);

    assert(rectDst.x0 == 1.0f);
    assert(rectDst.x1 == 2.0f);
    assert(rectDst.y0 == 3.0f);
    assert(rectDst.y1 == 4.0f);
    assert(rectDst.z0 == 5.0f);
    assert(rectDst.z1 == 6.0f);

    LogMsg("%-50s test is passed", "Rect3d::Rect3d(const Rect3d&))");
}

//---------------------------------------------------------

void Rect3dTestConstructorSize()
{
    const Rect3d rect(1, 2, 3);

    assert(rect.x0 == -0.5f);
    assert(rect.x1 == +0.5f);
    assert(rect.y0 == -1.0f);
    assert(rect.y1 == +1.0f);
    assert(rect.z0 == -1.5f);
    assert(rect.z1 == +1.5f);

    LogMsg("%-50s test is passed", "Rect3d::Rect3d(float, float, float))");
}

//---------------------------------------------------------

void Rect3dTestConstructorVecSize()
{
    const Vec3   vec(1, 2, 3);
    const Rect3d rect(vec);

    assert(rect.x0 == -0.5f);
    assert(rect.x1 == +0.5f);
    assert(rect.y0 == -1.0f);
    assert(rect.y1 == +1.0f);
    assert(rect.z0 == -1.5f);
    assert(rect.z1 == +1.5f);

    LogMsg("%-50s test is passed", "Rect3d::Rect3d(Vec3))");
}

//==================================================================================
// Test operators
//==================================================================================

void Rect3dTestOperatorEqualityInequality()
{
    const Rect3d rect(1,2, 3,4, 5,6);

    assert(rect == Rect3d(1,2, 3,4, 5,6));

    assert(rect != Rect3d(0,2, 3,4, 5,6));
    assert(rect != Rect3d(1,0, 3,4, 5,6));
    assert(rect != Rect3d(1,2, 0,4, 5,6));
    assert(rect != Rect3d(1,2, 3,0, 5,6));
    assert(rect != Rect3d(1,2, 3,4, 0,6));
    assert(rect != Rect3d(1,2, 3,4, 5,0));

    LogMsg("%-50s test is passed", "Rect3d::operator == (Rect3d)");
    LogMsg("%-50s test is passed", "Rect3d::operator != (Rect3d)");
}

//---------------------------------------------------------

void Rect3dTestOperatorAssignment()
{
    Rect3d rect1(1,2, 3,4, 5,6);
    Rect3d rect2(2,3, 4,5, 6,7);

    rect1 = rect2;

    // assert that rect1 was changed
    assert(rect1 == rect2);

    // assert that rect2 wasn't changed
    assert(rect2.x0 == 2);
    assert(rect2.x1 == 3);
    assert(rect2.y0 == 4);
    assert(rect2.y1 == 5);
    assert(rect2.z0 == 6);
    assert(rect2.z1 == 7);

    LogMsg("%-50s test is passed", "Rect3d::operator = (Rect3d)");
}

//---------------------------------------------------------

void Rect3dTestOperatorAddAssignVec()
{
    const Vec3 vec(1, 2, 3);
    Rect3d rect(1,2, 3,4, 5,6);

    rect += vec;

    assert(rect.x0 == 2.0f);
    assert(rect.x1 == 3.0f);
    assert(rect.y0 == 5.0f);
    assert(rect.y1 == 6.0f);
    assert(rect.z0 == 8.0f);
    assert(rect.z1 == 9.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator += (Vec3)");
}

//---------------------------------------------------------

void Rect3dTestOperatorAddAssignScalar()
{
    const float scalar = 1.0f;
    Rect3d rect(1,2, 3,4, 5,6);

    rect += scalar;

    assert(rect.x0 == 2.0f);
    assert(rect.x1 == 3.0f);
    assert(rect.y0 == 4.0f);
    assert(rect.y1 == 5.0f);
    assert(rect.z0 == 6.0f);
    assert(rect.z1 == 7.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator += (float)");
}

//---------------------------------------------------------

void Rect3dTestOperatorRectAddVec()
{
    const Vec3 vec(1, 1, 1);
    const Rect3d rectSrc(1,2, 3,4, 5,6);

    const Rect3d rect(rectSrc + vec);

    assert(rect.x0 == 2.0f);
    assert(rect.x1 == 3.0f);
    assert(rect.y0 == 4.0f);
    assert(rect.y1 == 5.0f);
    assert(rect.z0 == 6.0f);
    assert(rect.z1 == 7.0f);

    LogMsg("%-50s test is passed", "Rect3d operator + (Rect3d, Vec3)");
}

//---------------------------------------------------------

void Rect3dTestOperatorRectAddScalar()
{
    const float scalar = 1.0f;
    const Rect3d rectSrc(1,2, 3,4, 5,6);

    const Rect3d rect(rectSrc + scalar);

    assert(rect.x0 == 2.0f);
    assert(rect.x1 == 3.0f);
    assert(rect.y0 == 4.0f);
    assert(rect.y1 == 5.0f);
    assert(rect.z0 == 6.0f);
    assert(rect.z1 == 7.0f);

    LogMsg("%-50s test is passed", "Rect3d operator + (Rect3d, float)");
}

//---------------------------------------------------------

void Rect3dTestOperatorScalarAddRect()
{
    const float scalar = 1.0f;
    const Rect3d rectSrc(1, 2, 3, 4, 5, 6);

    const Rect3d rect(scalar + rectSrc);

    assert(rect.x0 == 2.0f);
    assert(rect.x1 == 3.0f);
    assert(rect.y0 == 4.0f);
    assert(rect.y1 == 5.0f);
    assert(rect.z0 == 6.0f);
    assert(rect.z1 == 7.0f);

    LogMsg("%-50s test is passed", "Rect3d operator + (float, Rect3d)");
}

//---------------------------------------------------------

void Rect3dTestOperatorSubAssignVec()
{
    const Vec3 vec(1, 2, 3);
    Rect3d rect(10,20, 30,40, 50,60);

    rect -= vec;

    assert(rect.x0 == 9.0f);
    assert(rect.x1 == 19.0f);
    assert(rect.y0 == 28.0f);
    assert(rect.y1 == 38.0f);
    assert(rect.z0 == 47.0f);
    assert(rect.z1 == 57.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator -= (Vec3)");
}

//---------------------------------------------------------

void Rect3dTestOperatorSubAssignScalar()
{
    const float s = 10;
    Rect3d rect(10,20, 30,40, 50,60);

    rect -= s;

    assert(rect.x0 == 0.0f);
    assert(rect.x1 == 10.0f);
    assert(rect.y0 == 20.0f);
    assert(rect.y1 == 30.0f);
    assert(rect.z0 == 40.0f);
    assert(rect.z1 == 50.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator -= (float)");
}

//---------------------------------------------------------

void Rect3dTestOperatorRectSubVec()
{
    const Rect3d rect(1,2, 3,4, 5,6);
    const Vec3 vec(1,2,3);

    const Rect3d rectRes(rect - vec);

    assert(rectRes.x0 == 0.0f);
    assert(rectRes.x1 == 1.0f);
    assert(rectRes.y0 == 1.0f);
    assert(rectRes.y1 == 2.0f);
    assert(rectRes.z0 == 2.0f);
    assert(rectRes.z1 == 3.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator - (Rect3d, Vec3)");
}

//---------------------------------------------------------

void Rect3dTestOperatorRectSubScalar()
{
    const Rect3d rect(1,2, 3,4, 5,6);
    const float scalar = 1.0f;

    const Rect3d rectRes(rect - scalar);

    assert(rectRes.x0 == 0.0f);
    assert(rectRes.x1 == 1.0f);
    assert(rectRes.y0 == 2.0f);
    assert(rectRes.y1 == 3.0f);
    assert(rectRes.z0 == 4.0f);
    assert(rectRes.z1 == 5.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator - (Rect3d, float)");
}

//---------------------------------------------------------

void Rect3dTestOperatorNegate()
{
    const Rect3d rect(10, 20,  30, 40,  50, 60);
    const Rect3d negRect(-rect);

    assert(negRect.x0 == -20);
    assert(negRect.x1 == -10);
    assert(negRect.y0 == -40);
    assert(negRect.y1 == -30);
    assert(negRect.z0 == -60);
    assert(negRect.z1 == -50);

    LogMsg("%-50s test is passed", "Rect3d::operator - ()");
}

//---------------------------------------------------------

void Rect3dTestOperatorMulAssignScalar()
{
    Rect3d rect(1,2, 3,4, 5,6);
    const float scalar = 2.0f;

    rect *= scalar;

    assert(rect.x0 == 2.0f);
    assert(rect.x1 == 4.0f);
    assert(rect.y0 == 6.0f);
    assert(rect.y1 == 8.0f);
    assert(rect.z0 == 10.0f);
    assert(rect.z1 == 12.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator *= (float)");
}

//---------------------------------------------------------

void Rect3dTestOperatorMulAssignVec()
{
    const Vec3 vec(2, 3, 4);
    Rect3d rect(1,2, 3,4, 5,6);

    rect *= vec;

    assert(rect.x0 == 2.0f);
    assert(rect.x1 == 4.0f);
    assert(rect.y0 == 9.0f);
    assert(rect.y1 == 12.0f);
    assert(rect.z0 == 20.0f);
    assert(rect.z1 == 24.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator *= (Vec3)");
}

//---------------------------------------------------------

void Rect3dTestOperatorRectMulVec()
{
    const Rect3d rectSrc(1,2, 3,4, 5,6);
    const Vec3 vec(2, 3, 4);

    const Rect3d rect(rectSrc * vec);

    assert(rect.x0 == 2.0f);
    assert(rect.x1 == 4.0f);
    assert(rect.y0 == 9.0f);
    assert(rect.y1 == 12.0f);
    assert(rect.z0 == 20.0f);
    assert(rect.z1 == 24.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator * (Rect3d, Vec3)");
}

//---------------------------------------------------------

void Rect3dTestOperatorVecMulRect()
{
    const Rect3d rectSrc(1, 2, 3, 4, 5, 6);
    const Vec3 vec(2, 3, 4);

    const Rect3d rect(vec * rectSrc);

    assert(rect.x0 == 2.0f);
    assert(rect.x1 == 4.0f);
    assert(rect.y0 == 9.0f);
    assert(rect.y1 == 12.0f);
    assert(rect.z0 == 20.0f);
    assert(rect.z1 == 24.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator * (Vec3, Rect3d)");
}

//---------------------------------------------------------

void Rect3dTestOperatorRectMulScalar()
{
    const Rect3d rectSrc(1,2, 3,4, 5,6);
    const float scalar = 2.0f;

    const Rect3d rect(rectSrc * scalar);

    assert(rect.x0 == 2.0f);
    assert(rect.x1 == 4.0f);
    assert(rect.y0 == 6.0f);
    assert(rect.y1 == 8.0f);
    assert(rect.z0 == 10.0f);
    assert(rect.z1 == 12.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator * (Rect3d, float)");
}

//---------------------------------------------------------

void Rect3dTestOperatorScalarMulRect()
{
    const Rect3d rectSrc(1, 2, 3, 4, 5, 6);
    const float scalar = 2.0f;

    const Rect3d rect(scalar * rectSrc);

    assert(rect.x0 == 2.0f);
    assert(rect.x1 == 4.0f);
    assert(rect.y0 == 6.0f);
    assert(rect.y1 == 8.0f);
    assert(rect.z0 == 10.0f);
    assert(rect.z1 == 12.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator * (float, Rect3d)");
}

//---------------------------------------------------------

void Rect3dTestOperatorDivAssignScalar()
{
    Rect3d rect(1,2, 3,4, 5,6);
    const float scalar = 2.0f;

    rect /= scalar;

    assert(rect.x0 == 0.5f);
    assert(rect.x1 == 1.0f);
    assert(rect.y0 == 1.5f);
    assert(rect.y1 == 2.0f);
    assert(rect.z0 == 2.5f);
    assert(rect.z1 == 3.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator /= (float)");
}

//---------------------------------------------------------

void Rect3dTestOperatorDivAssignVec()
{
    Rect3d rect(1,2, 3,4, 5,6);
    const Vec3 vec(2, 2, 2);

    rect /= vec;

    assert(rect.x0 == 0.5f);
    assert(rect.x1 == 1.0f);
    assert(rect.y0 == 1.5f);
    assert(rect.y1 == 2.0f);
    assert(rect.z0 == 2.5f);
    assert(rect.z1 == 3.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator /= (Vec)");
}

//---------------------------------------------------------

void Rect3dTestOperatorRectDivVec()
{
    const Rect3d rectSrc(1,2, 3,4, 5,6);
    const Vec3 vec(2, 2, 2);

    const Rect3d rect(rectSrc / vec);

    assert(rect.x0 == 0.5f);
    assert(rect.x1 == 1.0f);
    assert(rect.y0 == 1.5f);
    assert(rect.y1 == 2.0f);
    assert(rect.z0 == 2.5f);
    assert(rect.z1 == 3.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator / (Rect3d, Vec3)");
}

//---------------------------------------------------------

void Rect3dTestOperatorRectDivScalar()
{
    const Rect3d rectSrc(1,2, 3,4, 5,6);
    const float scalar = 2.0f;

    const Rect3d rect(rectSrc / scalar);

    assert(rect.x0 == 0.5f);
    assert(rect.x1 == 1.0f);
    assert(rect.y0 == 1.5f);
    assert(rect.y1 == 2.0f);
    assert(rect.z0 == 2.5f);
    assert(rect.z1 == 3.0f);

    LogMsg("%-50s test is passed", "Rect3d::operator / (Rect3d, float)");
}

//==================================================================================
// Test calculations / operations
//==================================================================================

void Rect3dTestClear()
{
    Rect3d rect(1,2, 3,4, 5,6);

    assert(!rect.IsClear());

    rect.Clear();
    assert(rect.x0 == 0);
    assert(rect.x1 == 0);
    assert(rect.y0 == 0);
    assert(rect.y1 == 0);
    assert(rect.z0 == 0);
    assert(rect.z1 == 0);
    assert(rect.IsClear() == true);

    LogMsg("%-50s test is passed", "Rect3d::Clear()");
    LogMsg("%-50s test is passed", "Rect3d::IsClear()");
}

//---------------------------------------------------------

void Rect3dTestSetFloor()
{
    Rect3d rect;
    rect.SetFloor(Rect3d(1.4f, 2.5f, 3.6f, 4.7f, 5.8f, 6.9f));

    assert(rect.x0 == 1.0f);
    assert(rect.x1 == 2.0f);
    assert(rect.y0 == 3.0f);
    assert(rect.y1 == 4.0f);
    assert(rect.z0 == 5.0f);
    assert(rect.z1 == 6.0f);

    LogMsg("%-50s test is passed", "Rect3d::SetFloor(Rect3d)");
}

//---------------------------------------------------------

void Rect3dTestSetCeiling()
{
    Rect3d rect;
    rect.SetCeiling(Rect3d(1.4f, 2.5f, 3.6f, 4.7f, 5.8f, 6.9f));

    assert(rect.x0 == 2.0f);
    assert(rect.x1 == 3.0f);
    assert(rect.y0 == 4.0f);
    assert(rect.y1 == 5.0f);
    assert(rect.z0 == 6.0f);
    assert(rect.z1 == 7.0f);

    LogMsg("%-50s test is passed", "Rect3d::SetCeiling(Rect3d)");
}

//---------------------------------------------------------

void Rect3dTestValid()
{
    const Rect3d rectValid(1,2, 3,4, 5,6);
    const Rect3d rectInvalid1(2,1, 3,4, 5,6);
    const Rect3d rectInvalid2(1,2, 4,3, 5,6);
    const Rect3d rectInvalid3(1,2, 3,4, 6,5);

    assert(rectValid.IsValid() == true);
    assert(rectInvalid1.IsValid() == false);
    assert(rectInvalid2.IsValid() == false);
    assert(rectInvalid3.IsValid() == false);

    LogMsg("%-50s test is passed", "Rect3d::IsValid()");
}

//---------------------------------------------------------

void Rect3dTestResizeMax()
{
    Rect3d rect(1,2, 3,4, 5,6);

    rect.ResizeMax(Vec3(2, 2, 2));

    assert(rect.x0 == 1.0f);
    assert(rect.x1 == 3.0f);
    assert(rect.y0 == 3.0f);
    assert(rect.y1 == 5.0f);
    assert(rect.z0 == 5.0f);
    assert(rect.z1 == 7.0f);

    LogMsg("%-50s test is passed", "Rect3d::ResizeMax(Vec3)");
}

//---------------------------------------------------------

void Rect3dTestResizeMin()
{
    Rect3d rect(1,2, 3,4, 5,6);

    rect.ResizeMin(Vec3(2,4,6));

    assert(rect.x0 == 0.0f);
    assert(rect.x1 == 2.0f);
    assert(rect.y0 == 0.0f);
    assert(rect.y1 == 4.0f);
    assert(rect.z0 == 0.0f);
    assert(rect.z1 == 6.0f);

    LogMsg("%-50s test is passed", "Rect3d::ResizeMin(Vec3)");
}

//---------------------------------------------------------

void Rect3dTestResize()
{
    Rect3d rect(1, 2, 3);

    // resize rect3d along x,y, and z axis
    rect.Resize(Vec3(11, 21, 31));

    assert(rect.x0 == -5.5f);
    assert(rect.x1 == +5.5f);
    assert(rect.y0 == -10.5f);
    assert(rect.y1 == +10.5f);
    assert(rect.z0 == -15.5f);
    assert(rect.z1 == +15.5f);

    LogMsg("%-50s test is passed", "Rect3d::Resize(Vec3)");
}

//---------------------------------------------------------

void Rect3dTestMid()
{
    const Rect3d rect(0.0f, 10.0f,  -20.0f, 30.0f,  40.0f, 50.0f);
    const Vec3 vec = rect.MidPoint();

    assert(rect.MidX() == 5.0f);
    assert(rect.MidY() == 5.0f);
    assert(rect.MidZ() == 45.0f);

    assert(vec.x == 5.0f);
    assert(vec.y == 5.0f);
    assert(vec.z == 45.0f);

    LogMsg("%-50s test is passed", "Rect3d::MidPoint()");
}

//---------------------------------------------------------

void Rect3dTestSize()
{
    const Rect3d rect(1,2, 3,4, 5,6);
    const Vec3 size = rect.Size();

    assert(rect.SizeX() == 1.0f);
    assert(rect.SizeY() == 1.0f);
    assert(rect.SizeZ() == 1.0f);

    assert(size.x == 1.0f);
    assert(size.y == 1.0f);
    assert(size.z == 1.0f);

    LogMsg("%-50s test is passed", "Rect3d::Size()");
}

//---------------------------------------------------------

void Rect3dTestMinMaxPoint()
{
    const Rect3d rect(1,2, 3,4, 5,6);
    const Vec3 minP = rect.MinPoint();
    const Vec3 maxP = rect.MaxPoint();

    assert(minP.x == 1.0f);
    assert(minP.y == 3.0f);
    assert(minP.z == 5.0f);

    assert(maxP.x == 2.0f);
    assert(maxP.y == 4.0f);
    assert(maxP.z == 6.0f);

    LogMsg("%-50s test is passed", "Rect3d::MinPoint()");
    LogMsg("%-50s test is passed", "Rect3d::MaxPoint()");
}

//---------------------------------------------------------

void Rect3dTestVolume()
{
    const Rect3d rect(0,5, 0,5, 0,5);
    const float volume = rect.Volume();

    assert(volume == 125.0f);

    LogMsg("%-50s test is passed", "Rect3d::Volume()");
}

//---------------------------------------------------------

void Rect3dTestExpand()
{
    Rect3d rect;
    Rect3d rect1;
    Rect3d rect2;

    rect.Expand(10.0f);

    assert(rect.x0 == -10.0f);
    assert(rect.x1 == +10.0f);
    assert(rect.y0 == -10.0f);
    assert(rect.y1 == +10.0f);
    assert(rect.z0 == -10.0f);
    assert(rect.z1 == +10.0f);

    rect1.ExpandX(20.0f);
    rect1.ExpandY(40.0f);
    rect1.ExpandZ(60.0f);

    assert(rect1.x0 == -20.0f);
    assert(rect1.x1 == +20.0f);
    assert(rect1.y0 == -40.0f);
    assert(rect1.y1 == +40.0f);
    assert(rect1.z0 == -60.0f);
    assert(rect1.z1 == +60.0f);

    rect2.Expand(Vec3(20.0f, 40.0f, 60.0f));

    assert(rect2.x0 == -20.0f);
    assert(rect2.x1 == +20.0f);
    assert(rect2.y0 == -40.0f);
    assert(rect2.y1 == +40.0f);
    assert(rect2.z0 == -60.0f);
    assert(rect2.z1 == +60.0f);

    LogMsg("%-50s test is passed", "Rect3d::Expand(float)");
    LogMsg("%-50s test is passed", "Rect3d::ExpandX(float)");
    LogMsg("%-50s test is passed", "Rect3d::ExpandY(float)");
    LogMsg("%-50s test is passed", "Rect3d::ExpandZ(float)");
    LogMsg("%-50s test is passed", "Rect3d::Expand(Vec3)");
}

//---------------------------------------------------------

void Rect3dTestNormalize()
{
    Rect3d rect(2,1, 4,3, 6,5);

    rect.Normalize();

    assert(rect.x0 == 1.0f);
    assert(rect.x1 == 2.0f);
    assert(rect.y0 == 3.0f);
    assert(rect.y1 == 4.0f);
    assert(rect.z0 == 5.0f);
    assert(rect.z1 == 6.0f);

    LogMsg("%-50s test is passed", "Rect3d::Normalize()");
}

//---------------------------------------------------------

void Rect3dTestPointInRect()
{
    const Rect3d rect(0,1, 0,1, 0,1);
    const Vec3 pin(0.5f, 0.5f, 0.5f);
    const Vec3 pout(10, 10, 10);

    assert(rect.PointInRect(pin) == true);
    assert(rect.PointInRect(pout) == false);

    LogMsg("%-50s test is passed", "Rect3d::PointInRect(Vec3)");
}

//---------------------------------------------------------
// main test
//---------------------------------------------------------
void TestRect3d()
{
    SetConsoleColor(CYAN);

    printf("\n\n");

    LogMsg("-----------------------------------------------");
    LogMsg("Test Rect3d functional:");
    LogMsg("-----------------------------------------------\n");

    // test constructors
    Rect3dTestConstructorDefault();
    Rect3dTestConstructorFloats();
    Rect3dTestConstructorCopy();
    Rect3dTestConstructorSize();
    Rect3dTestConstructorVecSize();

    printf("\n");

    // test operators
    Rect3dTestOperatorEqualityInequality();
    Rect3dTestOperatorAssignment();

    printf("\n");

    Rect3dTestOperatorAddAssignVec();
    Rect3dTestOperatorAddAssignScalar();
    Rect3dTestOperatorRectAddVec();
    Rect3dTestOperatorRectAddScalar();
    Rect3dTestOperatorScalarAddRect();

    printf("\n");

    Rect3dTestOperatorSubAssignVec();
    Rect3dTestOperatorSubAssignScalar();
    Rect3dTestOperatorRectSubVec();
    Rect3dTestOperatorRectSubScalar();
    Rect3dTestOperatorNegate();

    printf("\n");

    Rect3dTestOperatorMulAssignScalar();
    Rect3dTestOperatorMulAssignVec();
    Rect3dTestOperatorRectMulVec();
    Rect3dTestOperatorVecMulRect();
    Rect3dTestOperatorRectMulScalar();
    Rect3dTestOperatorScalarMulRect();

    printf("\n");

    Rect3dTestOperatorDivAssignScalar();
    Rect3dTestOperatorDivAssignVec();
    Rect3dTestOperatorRectDivVec();
    Rect3dTestOperatorRectDivScalar();

    printf("\n");

    // test calculations/operations
    Rect3dTestClear();
    Rect3dTestSetFloor();
    Rect3dTestSetCeiling();
    Rect3dTestValid();
    Rect3dTestResizeMax();
    Rect3dTestResizeMin();

    printf("\n");

    Rect3dTestResize();
    Rect3dTestMid();
    Rect3dTestSize();
    Rect3dTestMinMaxPoint();

    printf("\n");

    Rect3dTestVolume();
    Rect3dTestExpand();
    Rect3dTestNormalize();
    Rect3dTestPointInRect();

   
    LogMsg("-----------------------------------------------");
    LogMsg("all the Rect3d tests are passed!");
    LogMsg("-----------------------------------------------\n");

    SetConsoleColor(RESET);
}
