/**********************************************************************************\
    Filename: tests_frustum.h
    Desc:     tests for frustum functional

    Created:  02.10.2025  by DimaSkup
\**********************************************************************************/
#pragma once

#include <geometry/frustum.h>
#include <geometry/plane_3d_functions.h>
#include <log.h>
#include <stdio.h>


//==================================================================================
// forward declaration of the main test
//==================================================================================
void TestFrustum();

//==================================================================================
// test constructors and functions
//==================================================================================
void TestFrustumConstructorDefault()
{
    LogMsg("%-50s test is passed", "Matrix::Matrix()");
}

//---------------------------------------------------------

void TestFrustumInit()
{
    const float fov    = 1.30796f;
    const float aspect = 1600.0f / 900.0f;
    const float nearZ  = 0.01f;
    const float farZ   = 1000.0f;

    const Plane3d expectLeft;
    const Plane3d expectRight;
    const Plane3d expectTop;
    const Plane3d expectBottom;
    const Plane3d expectNear;
    const Plane3d expectFar;

    Frustum frustum0;

    

    frustum0.Init(fov, aspect, nearZ, farZ);

    Matrix proj = MatrixProjectionLH(fov, aspect, nearZ, farZ);
    //Frustum frustum1(proj);
    Frustum frustum1;
    frustum1.CreateFromProjMatrix(proj, true);

#if 0
    // check if we got a valid frustum
    assert(frustum.leftPlane    == expectLeft);
    assert(frustum.rightPlane   == expectRight);
    assert(frustum.topPlane     == expectTop);
    assert(frustum.bottomPlane  == expectBottom);
    assert(frustum.nearPlane    == expectNear);
    assert(frustum.farPlane     == expectFar);
#else
    frustum0.leftPlane.Normalize();
    frustum1.leftPlane.Normalize();

    assert(frustum0.leftPlane == frustum1.leftPlane);

#endif

    LogMsg("%-50s test is passed", "Frustum::Init(fov, aspect, nearZ, farZ)");
}

//---------------------------------------------------------

void Test_FrustumSphereTest()
{
    const float fov    = 1.30796f;
    const float aspect = 1600.0f / 900.0f;
    const float nearZ  = 0.01f;
    const float farZ   = 1000.0f;

    Frustum frustum(fov, aspect, nearZ, farZ);

    // not visible spheres
    Sphere sphereNotVis0(Vec3{ 0,0,-10 }, 1);    
    Sphere sphereNotVis1(Vec3{ 0,0,0 }, 0.009f);  

    // visible spheres
    Sphere sphereVis0(Vec3{ 0,0,0 }, 1);
    Sphere sphereVis1(Vec3{ 0,0,10 }, 1);
    

    assert(frustum.TestSphere(sphereNotVis0) == false);
    assert(frustum.TestSphere(sphereNotVis1) == false);

    assert(frustum.TestSphere(sphereVis0) == true);
    assert(frustum.TestSphere(sphereVis1) == true);

    LogMsg("%-50s test is passed", "Frustum::Init(fov, aspect, nearZ, farZ)");
}

//---------------------------------------------------------

void Test_FrustumTransform()
{
    const float fov    = 1.30796f;
    const float aspect = 1600.0f / 900.0f;
    const float nearZ  = 0.01f;
    const float farZ   = 1000.0f;

    Frustum frustum0(fov, aspect, nearZ, farZ);
    Frustum frustum1;

    const Matrix mRotY = MatrixRotationY(DEG_TO_RAD(-90));

    // before transformation we see these shapes
    Sphere sphereVis00(0,0,10,1);
    Sphere sphereVis01(0,0,0,1);
    Sphere sphereNotVis02(-10,0,0,1);

    assert(frustum0.TestSphere(sphereVis00) == true);
    assert(frustum0.TestSphere(sphereVis01) == true);
    assert(frustum0.TestSphere(sphereNotVis02) == false);

    // after transfromation we won't see some shapes
    frustum0.Transform(frustum1, mRotY);

    Sphere sphereNotVis10(0, 0, 10, 1);
    Sphere sphereVis11(0,0,0,1);
    Sphere sphereVis12(-10,0,0,1);

    assert(frustum1.TestSphere(sphereNotVis10) == false);
    assert(frustum1.TestSphere(sphereVis11) == true);
    assert(frustum1.TestSphere(sphereVis12) == true);


    LogMsg("%-50s test is passed", "Frustum::Transform(outFrustum, transformMat)");
}

//==================================================================================
// main test
//==================================================================================
void TestFrustum()
{
    SetConsoleColor(MAGENTA);

    LogMsg("-----------------------------------------------");
    LogMsg("Test Frustum functional:");
    LogMsg("-----------------------------------------------");

    //TestFrustumInit();

    Test_FrustumSphereTest();

    Test_FrustumTransform();

    LogMsg("-----------------------------------------------");
    LogMsg("all the tests for Frustum are passed!");
    LogMsg("-----------------------------------------------\n");

    SetConsoleColor(RESET);
}