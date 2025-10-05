/**********************************************************************************\

    ******     ******    ******   ******    ********
    **    **  **    **  **    **  **    **  **    **
    **    **  **    **  **    **  **    **  **
    **    **  **    **  **    **  **    **  ********
    **    **  **    **  **    **  ******          **
    **    **  **    **  **    **  **  ***   **    **
    ******     ******    ******   **    **  ********

    Filename: tests_plane_3d.h
    Desc:     tests for 3d plane functional

    Created:  27.09.2025  by DimaSkup
\**********************************************************************************/
#pragma once

#include <geometry/plane_3d.h>
#include <geometry/plane_3d_functions.h>
#include <math/math_constants.h>

#include <log.h>
#include <stdio.h>
#include <assert.h>


//==================================================================================
// forward declaration of the main test
//==================================================================================
void TestPlane3d();


//==================================================================================
// test constructors
//==================================================================================
void Test_Plane3dConstructor_Default()
{
    Plane3d pl;

    // test as arr of members
    assert(pl.m[0] < EPSILON_E5);
    assert(pl.m[1] < EPSILON_E5);
    assert(pl.m[2] < EPSILON_E5);
    assert(pl.m[3] < EPSILON_E5);

    // test as distance and normal vector
    assert(pl.distance < EPSILON_E5);
    assert(pl.normal.x < EPSILON_E5);
    assert(pl.normal.y < EPSILON_E5);
    assert(pl.normal.z < EPSILON_E5);

    LogMsg("%-50s test is passed", "Plane3d::Plane3d()");
}

//---------------------------------------------------------

void Test_Plane3dConstructor_With4Floats()
{
    const float nx = 1;
    const float ny = 2;
    const float nz = 3;
    const float dist = 4;

    const Plane3d pl(nx, ny, nz, dist);

    assert(pl.normal.x == nx);
    assert(pl.normal.y == ny);
    assert(pl.normal.z == nz);
    assert(pl.distance == dist);

    LogMsg("%-50s test is passed", "Plane3d::Plane3d(nx, ny, nz, dist)");
}

//---------------------------------------------------------

void Test_Plane3dConstructor_Copy()
{
    const Plane3d planeSrc(1, 2, 3, 4);
    const Plane3d planeDst(planeSrc);

    assert(planeDst.normal.x == planeSrc.normal.x);
    assert(planeDst.normal.y == planeSrc.normal.y);
    assert(planeDst.normal.z == planeSrc.normal.z);
    assert(planeDst.distance == planeSrc.distance);

    LogMsg("%-50s test is passed", "Plane3d::Plane3d(srcPlane3d)");
}

//---------------------------------------------------------

void Test_Plane3dConstructor_With3Points()
{
    // setup with 3 points in a clockwise ordering
    const Vec3 p0( 0, 1, 1);
    const Vec3 p1( 1,-1, 1);
    const Vec3 p2(-1,-1, 1);

    const Plane3d pl(p0, p1, p2);

    assert(pl.normal.x < EPSILON_E5);
    assert(pl.normal.y < EPSILON_E5);
    assert(pl.normal.z == 1);
    assert(pl.distance == -1);

    LogMsg("%-50s test is passed", "Plane3d::Plane3d(point0, point1, point2)");
}

//---------------------------------------------------------

void Test_Plane3dConstructor_WithNormalAndDistance()
{
    const Vec3 normal(1, 1, 1);
    const float dist = 10;

    const Plane3d pl(normal, dist);

    assert(pl.normal.x == normal.x);
    assert(pl.normal.y == normal.y);
    assert(pl.normal.z == normal.z);
    assert(pl.distance == dist);

    LogMsg("%-50s test is passed", "Plane3d::Plane3d(normalVec, distance)");
}

//---------------------------------------------------------

void Test_Plane3dConstructor_WithPointAndNormal()
{
    const Vec3 p0(1, 1, 1);
    const Vec3 n0(0, 1, 0);
    const Vec3 p1(1, 1, 2);
    const Vec3 n1(1, 1, 1);

    const Plane3d pl0(p0, n0);
    const Plane3d pl1(p1, n1);

    assert(pl0.normal.x == n0.x);
    assert(pl0.normal.y == n0.y);
    assert(pl0.normal.z == n0.z);
    assert(pl0.distance == -1);

    assert(pl1.normal.x == n1.x);
    assert(pl1.normal.y == n1.y);
    assert(pl1.normal.z == n1.z);
    assert(pl1.distance == -4);

    LogMsg("%-50s test is passed", "Plane3d::Plane3d(point, normalVec)");
}


//==================================================================================
// test operators
//==================================================================================
void Test_Plane3dOperator_Assignment()
{
    const Plane3d plSrc(1, 2, 3, 4);
    Plane3d plDst(10, 10, 10, 10);

    plDst = plSrc;

    assert(plDst.normal.x == plSrc.normal.x);
    assert(plDst.normal.y == plSrc.normal.y);
    assert(plDst.normal.z == plSrc.normal.z);
    assert(plDst.distance == plSrc.distance);

    LogMsg("%-50s test is passed", "Plane3d::operator =  (const Plane3d&)");
}

//---------------------------------------------------------

void Test_Plane3dOperator_Comparison()
{
    const Plane3d pl0(1, 2, 3, 4);
    const Plane3d pl1(1, 2, 3, 4);
    const Plane3d pl2(0, 2, 3, 4);
    const Plane3d pl3(1, 0, 3, 4);
    const Plane3d pl4(1, 2, 0, 4);
    const Plane3d pl5(1, 2, 3, 0);

    assert(pl0 == pl1);

    assert((pl0 == pl2) == false);
    assert((pl0 == pl3) == false);
    assert((pl0 == pl4) == false);
    assert((pl0 == pl5) == false);

    assert(pl0 != pl2);
    assert(pl0 != pl3);
    assert(pl0 != pl4);
    assert(pl0 != pl5);

    LogMsg("%-50s test is passed", "Plane3d::operator == (const Plane3d&)");
}


//==================================================================================
// test functions
//==================================================================================
void Test_Plane3d_Normalize()
{
    const Vec3 point(1, 1, 1);
    const Vec3 normal(0, 2, 0);
    Plane3d pl(point, normal);

    // test non-normalized plane
    assert(pl.normal.x < EPSILON_E5);
    assert(pl.normal.y == 2.0f);
    assert(pl.normal.z < EPSILON_E5);
    assert(pl.distance == -2);

    pl.Normalize();

    // test normalized plane
    assert(pl.normal.x < EPSILON_E5);
    assert(pl.normal.y == 1.0f);
    assert(pl.normal.z < EPSILON_E5);
    assert(pl.distance == -1.0f);
    

    LogMsg("%-50s test is passed", "Plane3d::Normalize()");
}

//---------------------------------------------------------

void Test_Plane3d_SolveForXYZ()
{
    // plane equation: Ax + By + Cz + D = 0
    Vec3 normal(1, 1, 1);
    Vec3Normalize(normal);

    const float distance = 2;
    const Plane3d pl(normal, distance);

    // solve for X:
    const float x = pl.SolveForX(0, 0);
    const float y = pl.SolveForY(0, 0);
    const float z = pl.SolveForZ(0, 0);

    assert(x == -3.46410179f);
    assert(y == -3.46410179f);
    assert(z == -3.46410179f);

    LogMsg("%-50s test is passed", "Plane3d::SolveForX/Y/Z()");
}

//---------------------------------------------------------

void Test_Plane3d_ProjectPointToPlane()
{
    Vec3 n0(1, 1, 1);
    Vec3Normalize(n0);

    const float dist = 10;
    const Plane3d pl(n0, dist);

    // case 1:
    const Vec3 p0(20, 20, 20);
    const Vec3 projPoint0 = pl.ProjectPointToPlane(p0);

    assert(projPoint0.x == -5.77350044f);
    assert(projPoint0.y == -5.77350044f);
    assert(projPoint0.z == -5.77350044f);

    // case 2:
    const Vec3 p1(100, -100, 0);
    const Vec3 projPoint1 = pl.ProjectPointToPlane(p1);

    assert(projPoint1.x == 94.2265015f);
    assert(projPoint1.y == -105.773499f);
    assert(projPoint1.z == -5.77350235f);

    LogMsg("%-50s test is passed", "Plane3d::ProjectPointToPlane()");
}

//---------------------------------------------------------

void Test_Plane3d_Set()
{
    // test Set(3 points)
    const Vec3 p0(0, 1, 1);
    const Vec3 p1(1, -1, 1);
    const Vec3 p2(-1, -1, 1);

    Plane3d pl0;
    pl0.Set(p0, p1, p2);

    assert(pl0.normal.x < EPSILON_E5);
    assert(pl0.normal.y < EPSILON_E5);
    assert(pl0.normal.z == 1);
    assert(pl0.distance == -1);


    // test Set(normalVec, distance)
    const Vec3 norm(1, 1, 1);
    const float distance = 10;

    Plane3d pl1;
    pl1.Set(norm, distance);

    assert(pl1.normal.x == norm.x);
    assert(pl1.normal.x == norm.y);
    assert(pl1.normal.x == norm.z);
    assert(pl1.distance == distance);


    // test Set(point, normalVec)
    const Vec3 point(1, 1, 1);
    const Vec3 normal(0, 1, 0);
    const Plane3d plane(point, normal);

    assert(plane.normal.x == normal.x);
    assert(plane.normal.y == normal.y);
    assert(plane.normal.z == normal.z);
    assert(plane.distance == -1);


    LogMsg("%-50s test is passed", "Plane3d::Set(point0, point1, point2)");
    LogMsg("%-50s test is passed", "Plane3d::Set(normalVec, distance)");
    LogMsg("%-50s test is passed", "Plane3d::Set(point, normalVec)");
}

//---------------------------------------------------------

void Test_Plane3d_Transform()
{
    Plane3d pl(1,2,3,4);
    Matrix mRotZ        = MatrixRotationZ(DEG_TO_RAD(90));
    Matrix mTranslate   = MatrixTranslation(1,2,3);
    Matrix transform    = mRotZ * mTranslate;

    // compute an inverse transpose matrix of the original transformation
    Matrix invM0 = MatrixInverse(nullptr, transform);
    MatrixTranspose(invM0);

    // transform using inverse transpose matrix of the original transformation matrix
    pl.Transform(invM0);

    assert(pl.plane == Vec4(-2, 1, 3, -5));

    //=================================

    Plane3d pl1(0,0,1,0);
    Matrix S1 = MatrixScaling(2, 1, 1);
    Matrix R1 = MatrixRotationX(DEG_TO_RAD(30));
    Matrix T1 = MatrixTranslation(0, 1, 2);

    Matrix transform1 = S1 * R1 * T1;

    // compute an inverse transpose matrix of the original transformation
    Matrix invM1 = MatrixInverse(nullptr, transform1);
    MatrixTranspose(invM1);

    // transform using inverse transpose matrix of the original transformation matrix
    pl1.Transform(invM1);

    assert(pl1.plane == Vec4(0, -0.5f, 0.8660254f, -1.23205081f));

    //=================================

    Plane3d pl2(1,2,3,4);
    Matrix S2 = MatrixScaling(2, 1, 0.5f);
    Matrix R2 = MatrixRotationZ(DEG_TO_RAD(45));
    Matrix T2 = MatrixTranslation(1,2,3);

    Matrix transform2 = S2 * R2 * T2;

    // compute an inverse transpose matrix of the original transformation
    Matrix invM2 = MatrixInverse(nullptr, transform2);
    MatrixTranspose(invM2);

    // transform using inverse transpose matrix of the original transformation matrix
    pl2.Transform(invM2);

    assert(pl2.plane == Vec4(-1.06066f, 1.767766f, 6.0f, -16.4748745f));

    LogMsg("%-50s test is passed", "Plane3d::Transform(const Matrix& invTranspose)");
}

//==================================================================================
// tests by groups
//==================================================================================
void TestPlane3dConstructors()
{
    printf("\n%s Plane3d: test constructors\n%s", CYAN, YELLOW);

    Test_Plane3dConstructor_Default();
    Test_Plane3dConstructor_With4Floats();
    Test_Plane3dConstructor_Copy();
    Test_Plane3dConstructor_With3Points();
    Test_Plane3dConstructor_WithNormalAndDistance();
    Test_Plane3dConstructor_WithPointAndNormal();
}

//---------------------------------------------------------

void TestPlane3dFunctions()
{
    printf("\n%s Plane3d: test functions\n%s", CYAN, YELLOW);

    Test_Plane3d_Normalize();
    Test_Plane3d_SolveForXYZ();
    Test_Plane3d_ProjectPointToPlane();
    Test_Plane3d_Set();
    Test_Plane3d_Transform();
}

//---------------------------------------------------------

void TestPlane3dOperators()
{
    printf("\n%s Plane3d: test operators\n%s", CYAN, YELLOW);

    Test_Plane3dOperator_Assignment();
    Test_Plane3dOperator_Comparison();
}


//==================================================================================
// main test
//==================================================================================
void TestPlane3d()
{
    SetConsoleColor(YELLOW);

    LogMsg("-----------------------------------------------");
    LogMsg("Test Plane3d functional:");
    LogMsg("-----------------------------------------------");

    TestPlane3dConstructors();
    TestPlane3dOperators();
    TestPlane3dFunctions();

    LogMsg("-----------------------------------------------");
    LogMsg("all the Plane3d tests are passed!");
    LogMsg("-----------------------------------------------\n");

    SetConsoleColor(RESET);
}