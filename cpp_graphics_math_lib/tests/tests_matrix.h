/**********************************************************************************\

    ******     ******    ******   ******    ********
    **    **  **    **  **    **  **    **  **    **
    **    **  **    **  **    **  **    **  **
    **    **  **    **  **    **  **    **  ********
    **    **  **    **  **    **  ******          **
    **    **  **    **  **    **  **  ***   **    **
    ******     ******    ******   **    **  ********

    Filename: tests_matrix.h
    Desc:     tests for 4x4 matrix functional

    Created:  23.09.2025  by DimaSkup
\**********************************************************************************/
#pragma once
#include <math/matrix.h>
#include <math/math_helpers.h>
#include <log.h>
#include <stdio.h>


//==================================================================================
// forward declaration of the main test
//==================================================================================
void TestMatrix();


//==================================================================================
// test matrix constructors
//==================================================================================
void TestMatrixConstructorDefault()
{
    const Matrix m;

    for (int i = 0; i < 16; ++i)
        assert(m.mat[i] < EPSILON_E5);    // is zero

    LogMsg("%-50s test is passed", "Matrix::Matrix()");
}

//---------------------------------------------------------

void TestMatrixConstructorWithArr()
{
    constexpr float arr[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    const Matrix m(arr);

    for (int i = 0; i < 16; ++i)
        assert(FloatEqual(m.mat[i], arr[i]));

    LogMsg("%-50s test is passed", "Matrix::Matrix(float* arr16)");
}

//---------------------------------------------------------

void TestMatrixConstructor16Floats()
{
    constexpr float arr[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    const Matrix m(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);

    for (int i = 0; i < 16; ++i)
        assert(FloatEqual(m.mat[i], arr[i]));

    LogMsg("%-50s test is passed", "Matrix::Matrix(16 floats)");
}


//---------------------------------------------------------

void TestMatrixConstructorCopy()
{
    constexpr float arr[16] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
    const Matrix matSrc(arr);
    const Matrix matDst(matSrc);

    for (int i = 0; i < 16; ++i)
        assert(FloatEqual(matSrc.mat[i], matDst.mat[i]));

    LogMsg("%-50s test is passed", "Matrix::Matrix(const Matrix&)");
}

//---------------------------------------------------------

void TestMatrixConstructorVec4()
{
    const Vec4 v1(1, 2, 3, 4);
    const Vec4 v2(5, 6, 7, 8);
    const Vec4 v3(9, 10, 11, 12);
    const Vec4 v4(13, 14, 15, 16);

    const Matrix m(v1, v2, v3, v4);

    for (int i = 0; i < 16; ++i)
        assert(FloatEqual(m.mat[i], (float)(i+1)));

    LogMsg("%-50s test is passed", "Matrix::Matrix(Vec4&, Vec4&, Vec4&, Vec4&)");
}


//==================================================================================
// test matrix functions
//==================================================================================
void TestMatrixPrint()
{
    const Matrix m(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);

    printf("\n%s print matrix: \n%s", YELLOW, GREEN);
    MatrixPrint(m);
    printf("\n");

    LogMsg("%-50s test is passed", "MatrixPrint(const Matrix&)");
}

//---------------------------------------------------------

void TestMatrixEqual()
{
    float arr[16]{ 0 };

    // fill matrices with values
    for (int i = 0; i < 16; ++i)
        arr[i] = sqrtf((float)(i + 1));

    Matrix m1(arr);
    Matrix m2(arr);


    assert(MatrixEqual(m1, m2) == true);

    // manyally check if matrices are equal to each other
    for (int i = 0; i < 16; ++i)
        assert(FloatEqual(m1.mat[i], m2.mat[i]));

    // test for each element isn't equal
    for (int i = 0; i < 16; ++i)
    {
        Matrix m3(m1);
        m3.mat[i] = 0;
        assert(MatrixEqual(m1, m3) == false);
    }

    LogMsg("%-50s test is passed", "MatrixEqual(const Matrix&, const Matrix&)");
}

//---------------------------------------------------------

void TestMatrixZero()
{
    Matrix m(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);

    MatrixZero(m);

    for (int i = 0; i < 16; ++i)
        assert(m.mat[i] < EPSILON_E5);    // is zero

    LogMsg("%-50s test is passed", "MatrixZero(Matrix&)");
}

//---------------------------------------------------------

void TestMatrixIdentity()
{
    Matrix m0(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
    Matrix m1(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);

    // make both matrices to be Identity
    MatrixIdentity(m0);
    m1 = MatrixIdentity();

    // check if both matrices are Identity
    for (int i = 0; i < 16; ++i)
        assert(FloatEqual(m0.mat[i], IDENTITY_MAT_4X4.mat[i]));

    for (int i = 0; i < 16; ++i)
        assert(FloatEqual(m1.mat[i], IDENTITY_MAT_4X4.mat[i]));

    LogMsg("%-50s test is passed", "MatrixIdentity(Matrix&)");
    LogMsg("%-50s test is passed", "MatrixIdentity()");
}

//---------------------------------------------------------

void TestMatrixCopy()
{
    const Matrix mSrc(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
    Matrix mDst;

    MatrixCopy(mSrc, mDst);
    
    assert(MatrixEqual(mSrc, mDst) == true);

    LogMsg("%-50s test is passed", "MatrixCopy(const Matrix& src, Matrix& dst)");
}

//---------------------------------------------------------

void TestMatrixTranspose()
{
    const Matrix m(1,  2,  3,  4,
                   5,  6,  7,  8,
                   9,  10, 11, 12,
                   13, 14, 15, 16 );

    const Matrix mt0(1, 5, 9,  13,
                    2, 6, 10, 14,
                    3, 7, 11, 15,
                    4, 8, 12, 16);

    // test 2 versions of MatrixTranspose function
    Matrix transposed;
    MatrixTranspose(m, transposed);          // store result into 2nd param
    assert(MatrixEqual(transposed, mt0) == true);

    Matrix mt1(m);
    MatrixTranspose(mt1);                    // modify input matrix
    assert(MatrixEqual(mt0, mt1) == true);

    LogMsg("%-50s test is passed", "MatrixTranspose(Matrix& m)");
    LogMsg("%-50s test is passed", "MatrixTranspose(const Matrix& m, Matrix& mt)");
}

//---------------------------------------------------------

void TestMatrixGetDeterminant()
{
    const Matrix m0(4,1,8,0,  9,6,2,0,  1,6,2,0,  0,0,0,0);
    const Matrix m1(1,0,0,0,  0,2,0,0,  0,0,4,0,  1,2,3,1);

    const float detM0 = MatrixDeterminant(m0);
    const float detM1 = MatrixDeterminant(m1);

    assert(FloatEqual(detM0, 368.0f));
    assert(FloatEqual(detM1, 8.0f));

    LogMsg("%-50s test is passed", "MatrixDeterminant(const Matrix&)");
}

//---------------------------------------------------------

void TestMatrixGetInverse()
{
    const Matrix matA(4,1,8,0,  9,6,2,0,  1,6,2,0,  10,20,30,1);
    const Matrix matB(1,0,0,0,  0,2,0,0,  0,0,4,0,  1,2,3,1);

    Matrix invA;
    Matrix invB;

    float detA = 0;
    float detB = 0;

    MatrixInverse(invA, &detA, matA);
    MatrixInverse(invB, &detB, matB);

    // assert that our determinant is correct
    assert(FloatEqual(detA, 368.0f));
    assert(FloatEqual(detB, 8.0f));

    // assert that the inverse matrix elements is correct

    // test inverse of matrix A
    assert(invA.m00 < EPSILON_E5);      // is zero
    assert(invA.m01 == +0.125f);
    assert(invA.m02 == -0.125f);
    assert(invA.m03 < EPSILON_E5);

    assert(invA.m10 == -1.0f / 23.0f);
    assert(invA.m11 < EPSILON_E5);      
    assert(invA.m12 = 4.0f / 23.0f);
    assert(invA.m13 < EPSILON_E5);

    assert(invA.m20 == 3.0f / 23.0f);
    assert(invA.m21 == -1.0f / 16.0f);
    assert(invA.m22 == 15.0f / 368.0f);
    assert(invA.m23 < EPSILON_E5);

    assert(invA.m30 == -70.0f / 23.0f);
    assert(invA.m31 == 5.0f / 8.0f);
    assert(invA.m32 == -635.0f / 184.0f);
    assert(invA.m33 == 1.0f);


    // test inverse of matrix B
    assert(FloatEqual(invB.m00, 1.0f));
    assert(FloatEqual(invB.m01, 0.0f));
    assert(FloatEqual(invB.m02, 0.0f));
    assert(FloatEqual(invB.m03, 0.0f));

    assert(FloatEqual(invB.m10, 0.0f));
    assert(FloatEqual(invB.m11, 0.5f));
    assert(FloatEqual(invB.m12, 0.0f));
    assert(FloatEqual(invB.m13, 0.0f));

    assert(FloatEqual(invB.m20, 0.0f));
    assert(FloatEqual(invB.m21, 0.0f));
    assert(FloatEqual(invB.m22, 0.25f));
    assert(FloatEqual(invB.m23, 0.0f));

    assert(FloatEqual(invB.m30, -1.0f));
    assert(FloatEqual(invB.m31, -1.0f));
    assert(FloatEqual(invB.m32, -0.75f));
    assert(FloatEqual(invB.m33, 1.0f));
      

    // assert that we receive an identity matrix when multiply matrix by its inverse
    Matrix I = MatrixIdentity();
    Matrix m0;
    Matrix m1;

    MatrixMul(matA, invA, m0);
    MatrixMul(matB, invB, m1);

    assert(MatrixEqual(m0, I) == true);
    assert(MatrixEqual(m1, I) == true);

    LogMsg("%-50s test is passed", "MatrixInverse(const Matrix&, float&, Matrix&)");
}

//---------------------------------------------------------

void TestMatrixMultiplyMatrix()
{
    const Matrix matA(4, 1, 8, 0, 9, 6, 2, 0, 1, 6, 2, 0, 10, 20, 30, 1);
    Matrix invA;
    Matrix I = MatrixIdentity();
    Matrix mRes;
    float det = 0;

    MatrixInverse(invA, &det, matA);

    // multiply a matrix by its inverse so we expect to receive an Identity matrix
    MatrixMul(matA, invA, mRes);

    assert(MatrixEqual(I, mRes) == true);

    LogMsg("%-50s test is passed", "MatrixMul(const Matrix&, const Matrix&, Matrix&)");
}

//---------------------------------------------------------

void TestMatrixTranslation()
{
    const Vec3   t    = { 1.5312312f, 2.55345345f, 3.54234234f };   // translation vec
    const Matrix mat1 = MatrixTranslation(t.x, t.y, t.z);

    const float values[16] =
    { 
        1,   0,   0,   0,
        0,   1,   0,   0,
        0,   0,   1,   0,
        t.x, t.y, t.z, 1.0f 
    };

    for (int i = 0; i < 16; ++i)
        assert(FloatEqual(mat1.mat[i], values[i]));

    LogMsg("%-50s test is passed", "MatrixTranslation(tx, ty, tz)");
}
 
//---------------------------------------------------------

void TestMatrixRotationX_Helper(const float angleInRad)
{
    const Matrix mat = MatrixRotationX(angleInRad);

    const float s = sinf(angleInRad);
    const float c = cosf(angleInRad);

    const float values[16] =
    {  
        1,  0,  0,  0,
        0,  c,  s,  0,
        0, -s,  c,  0,
        0,  0,  0,  1  
    };

    for (int i = 0; i < 16; ++i)
        assert(FloatEqual(mat.mat[i], values[i]));
}

//---------------------------------------------------------

void TestMatrixRotationY_Helper(const float angleInRad)
{
    const Matrix mat = MatrixRotationY(angleInRad);

    const float s = sinf(angleInRad);
    const float c = cosf(angleInRad);

    const float values[16] =
    {
        c,  0, -s,  0,
        0,  1,  0,  0,
        s,  0,  c,  0,
        0,  0,  0,  1
    };

    for (int i = 0; i < 16; ++i)
        assert(FloatEqual(mat.mat[i], values[i]));
}

//---------------------------------------------------------

void TestMatrixRotationZ_Helper(const float angleInRad)
{
    const Matrix mat = MatrixRotationZ(angleInRad);

    const float s = sinf(angleInRad);
    const float c = cosf(angleInRad);

    const float values[16] =
    { 
        c,  s,  0,  0,
       -s,  c,  0,  0,
        0,  0,  1,  0,
        0,  0,  0,  1 
    };

    for (int i = 0; i < 16; ++i)
        assert(FloatEqual(mat.mat[i], values[i]));
}

//---------------------------------------------------------

void TestMatrixRotationX()
{
    // check the rotation matrix around X-axis by 30/45/60/90 deg
    TestMatrixRotationX_Helper(DEG_TO_RAD(30));
    TestMatrixRotationX_Helper(DEG_TO_RAD(45));
    TestMatrixRotationX_Helper(DEG_TO_RAD(60));
    TestMatrixRotationX_Helper(DEG_TO_RAD(90));

    LogMsg("%-50s test is passed", "MatrixRotationX(angleInRad)");
}

//---------------------------------------------------------

void TestMatrixRotationY()
{
    // check the rotation matrix around Y-axis by 30/45/60/90 deg
    TestMatrixRotationY_Helper(DEG_TO_RAD(30));
    TestMatrixRotationY_Helper(DEG_TO_RAD(45));
    TestMatrixRotationY_Helper(DEG_TO_RAD(60));
    TestMatrixRotationY_Helper(DEG_TO_RAD(90));

    LogMsg("%-50s test is passed", "MatrixRotationY(angleInRad)");
}

//---------------------------------------------------------

void TestMatrixRotationZ()
{
    // check the rotation matrix around Z-axis by 30/45/60/90 deg
    TestMatrixRotationZ_Helper(DEG_TO_RAD(30));
    TestMatrixRotationZ_Helper(DEG_TO_RAD(45));
    TestMatrixRotationZ_Helper(DEG_TO_RAD(60));
    TestMatrixRotationZ_Helper(DEG_TO_RAD(90));

    LogMsg("%-50s test is passed", "MatrixRotationZ(angleInRad)");
}

//---------------------------------------------------------

void TestMatrixMulVec3_Helper(const Vec3& v, const Matrix& m, const Vec3& expect)
{
    Vec3 res = { 0,0,0 };

    // transform a vector/point
    MatrixMulVec3(v, m, res);

    assert(FloatEqual(res.x, expect.x));
    assert(FloatEqual(res.y, expect.y));
    assert(FloatEqual(res.z, expect.z));
}

//---------------------------------------------------------

void TestMatrixMulVec4_Helper(const Vec4& v, const Matrix& m, const Vec4& expect)
{
    Vec4 res = { 0,0,0,0 };

    // transform a vector/point
    MatrixMulVec4(v, m, res);

    assert(FloatEqual(res.x, expect.x));
    assert(FloatEqual(res.y, expect.y));
    assert(FloatEqual(res.z, expect.z));
    assert(FloatEqual(res.w, expect.w));
}

//---------------------------------------------------------

void TestMatrixMultiplyVec3()
{
    // for rotation around Y-axis we have CLOCKWISE order
    const Matrix mRotY = MatrixRotationY(DEG_TO_RAD(-90));

    // for rotation around X,Z-axis we have COUNTER CLOCKWISE order
    const Matrix mRotX = MatrixRotationX(DEG_TO_RAD(90));
    const Matrix mRotZ = MatrixRotationZ(DEG_TO_RAD(90));


    // test transformation of a x/y/z unit vector
    TestMatrixMulVec3_Helper(Vec3{ 1,0,0 }, mRotX, Vec3{ 1,0,0 });
    TestMatrixMulVec3_Helper(Vec3{ 0,1,0 }, mRotX, Vec3{ 0,0,1 });
    TestMatrixMulVec3_Helper(Vec3{ 0,0,1 }, mRotX, Vec3{ 0,-1,0 });

    TestMatrixMulVec3_Helper(Vec3{ 1,0,0 }, mRotY, Vec3{  0,0,1  });
    TestMatrixMulVec3_Helper(Vec3{ 0,1,0 }, mRotY, Vec3{  0,1,0  });
    TestMatrixMulVec3_Helper(Vec3{ 0,0,1 }, mRotY, Vec3{ -1,0,0  });

    TestMatrixMulVec3_Helper(Vec3{ 1,0,0 }, mRotZ, Vec3{  0,1,0  });
    TestMatrixMulVec3_Helper(Vec3{ 0,1,0 }, mRotZ, Vec3{ -1,0,0  });
    TestMatrixMulVec3_Helper(Vec3{ 0,0,1 }, mRotZ, Vec3{  0,0,1  });

    // test transformation of a (1,1,1,0) vector
    TestMatrixMulVec3_Helper(Vec3{ 1,1,1 }, mRotX, Vec3{  1,-1, 1 });
    TestMatrixMulVec3_Helper(Vec3{ 1,1,1 }, mRotY, Vec3{ -1, 1, 1 });
    TestMatrixMulVec3_Helper(Vec3{ 1,1,1 }, mRotZ, Vec3{ -1, 1, 1 });

    LogMsg("%-50s test is passed", "MatrixMulVec3(origVec, matrix, outVec)");
}
 
//---------------------------------------------------------

void TestMatrixMultiplyVec4()
{
    // for rotation around Y-axis we have CLOCKWISE order
    const Matrix mRotY = MatrixRotationY(DEG_TO_RAD(-90));

    // for rotation around X,Z-axis we have COUNTER CLOCKWISE order
    const Matrix mRotX = MatrixRotationX(DEG_TO_RAD(90));
    const Matrix mRotZ = MatrixRotationZ(DEG_TO_RAD(90));


    // test transformation of a x/y/z unit vector
    TestMatrixMulVec4_Helper(Vec4{ 1,0,0,0 }, mRotX, Vec4{ 1,0,0,0 });
    TestMatrixMulVec4_Helper(Vec4{ 0,1,0,0 }, mRotX, Vec4{ 0,0,1,0 });
    TestMatrixMulVec4_Helper(Vec4{ 0,0,1,0 }, mRotX, Vec4{ 0,-1,0,0 });

    TestMatrixMulVec4_Helper(Vec4{ 1,0,0,0 }, mRotY, Vec4{ 0,0,1,0 });
    TestMatrixMulVec4_Helper(Vec4{ 0,1,0,0 }, mRotY, Vec4{ 0,1,0,0 });
    TestMatrixMulVec4_Helper(Vec4{ 0,0,1,0 }, mRotY, Vec4{-1,0,0,0 });

    TestMatrixMulVec4_Helper(Vec4{ 1,0,0,0 }, mRotZ, Vec4{ 0,1,0,0 });
    TestMatrixMulVec4_Helper(Vec4{ 0,1,0,0 }, mRotZ, Vec4{ -1,0,0,0 });
    TestMatrixMulVec4_Helper(Vec4{ 0,0,1,0 }, mRotZ, Vec4{ 0,0,1,0 });

    // test transformation of a (1,1,1,0) vector
    TestMatrixMulVec4_Helper(Vec4{ 1,1,1,0 }, mRotX, Vec4{  1,-1, 1, 0 });
    TestMatrixMulVec4_Helper(Vec4{ 1,1,1,0 }, mRotY, Vec4{ -1, 1, 1, 0 });
    TestMatrixMulVec4_Helper(Vec4{ 1,1,1,0 }, mRotZ, Vec4{ -1, 1, 1, 0 });
    
    LogMsg("%-50s test is passed", "MatrixMulVec4(origVec, matrix, outVec)");
}

//---------------------------------------------------------

void TestMatrixRotationAxis()
{
    const Matrix mRot      = MatrixRotationAxis(Vec3{1,1,1}, DEG_TO_RAD(-90));
    const Vec4 origPoint   = Vec4{ 1,0,0,1 };
    const Vec4 expectPoint = Vec4{ 0.333333284f, -0.244016945f, 0.910683572f, 1.000000000f };

    TestMatrixMulVec4_Helper(origPoint, mRot, expectPoint);

    LogMsg("%-50s test is passed", "MatrixRotationAxis(angle, axis)");
}


//==================================================================================
// test operators
//==================================================================================
void TestMatrixOperatorMulAssign()
{
    Matrix matA(4, 1, 8, 0, 9, 6, 2, 0, 1, 6, 2, 0, 10, 20, 30, 1);
    Matrix invA;
    Matrix I = MatrixIdentity();;
    float det = 0;

    MatrixInverse(invA, &det, matA);

    // multiply a matrix by its inverse so we expect to receive an Identity matrix
    matA *= invA;

    assert(MatrixEqual(I, matA) == true);

    LogMsg("%-50s test is passed", "Matrix::operator *= (const Matrix&)");
}

//---------------------------------------------------------

void TestMatrixOperatorMatMulMat()
{
    Matrix I = MatrixIdentity();
    Matrix matA(4, 1, 8, 0, 9, 6, 2, 0, 1, 6, 2, 0, 10, 20, 30, 1);
    Matrix invA;
    float det = 0;

    MatrixInverse(invA, &det, matA);

    // multiply a matrix by its inverse so we expect to receive an Identity matrix
    Matrix mRes = matA * invA;
    
    assert(MatrixEqual(I, mRes) == true);

    LogMsg("%-50s test is passed", "Matrix::operator * (const Matrix&, const Matrix&)");
}

//---------------------------------------------------------

void TestMatrixOperatorAssign()
{
    const Matrix mSrc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Matrix mDst;

    mDst = mSrc;

    assert(MatrixEqual(mSrc, mDst) == true);

    LogMsg("%-50s test is passed", "Matrix::operator = (const Matrix&)");
}


//==================================================================================
// tests by groups
//==================================================================================
void TestMatrixConstructors()
{
    printf("\n%s matrix: test constructors\n%s", YELLOW, GREEN);
    TestMatrixConstructorDefault();
    TestMatrixConstructorWithArr();
    TestMatrixConstructor16Floats();
    TestMatrixConstructorCopy();
    TestMatrixConstructorVec4();
}

//---------------------------------------------------------

void TestMatrixFunctions()
{
    printf("\n%s matrix: test functions\n%s", YELLOW, GREEN);
    TestMatrixPrint();
    TestMatrixEqual();
    TestMatrixZero();
    TestMatrixIdentity();
    TestMatrixCopy();
    TestMatrixTranspose();

    TestMatrixGetDeterminant();
    TestMatrixGetInverse();
    TestMatrixMultiplyMatrix();

    TestMatrixTranslation();

    TestMatrixRotationX();
    TestMatrixRotationY();
    TestMatrixRotationZ();

    TestMatrixMultiplyVec3();
    TestMatrixMultiplyVec4();
    TestMatrixRotationAxis();
}

//---------------------------------------------------------

void TestMatrixOperators()
{
    printf("\n%s matrix: test operators\n%s", YELLOW, GREEN);
    TestMatrixOperatorMulAssign();
    TestMatrixOperatorMatMulMat();
    TestMatrixOperatorAssign();
}

//==================================================================================
// main test
//==================================================================================
void TestMatrix()
{
    SetConsoleColor(GREEN);

    LogMsg("-----------------------------------------------");
    LogMsg("Test Matrix functional:");
    LogMsg("-----------------------------------------------");


    TestMatrixConstructors();
    TestMatrixFunctions();
    TestMatrixOperators();

    LogMsg("-----------------------------------------------");
    LogMsg("all the Matrix tests are passed!");
    LogMsg("-----------------------------------------------\n");

    SetConsoleColor(RESET);
}