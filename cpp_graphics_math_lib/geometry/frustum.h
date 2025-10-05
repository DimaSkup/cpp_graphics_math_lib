/**********************************************************************************\

    ******     ******    ******   ******    ********
    **    **  **    **  **    **  **    **  **    **
    **    **  **    **  **    **  **    **  **
    **    **  **    **  **    **  **    **  ********
    **    **  **    **  **    **  ******          **
    **    **  **    **  **    **  **  ***   **    **
    ******     ******    ******   **    **  ********

    Filename: frustum.h
    Desc:     a Frustum is a set of six Plane3d objects representing camera space.
              These planes are extracted from a camera matrix directly or from
              camera's field of view (fov), aspect ration, near and far plane distance.

              NOTE: the planes of a Frustum object are not normalized!!!
              This means they are only sutable for half-space testing.
              No distance values calculated using these planes will be accurate
              other than to show whether positions lie in the positive or negative
              half-space of the plane.

              This code I mainly rewrote from sources to the amazing book
              "Real Time 3D Terrain Engines Using C++ and DirectX"
              by Greg Snook

    Created:  17.09.2025 by DimaSkup
\**********************************************************************************/
#pragma once

#include <math/matrix.h>
#include <geometry/plane_3d.h>
#include <geometry/rect_3d.h>
#include <geometry/sphere.h>
#include <geometry/intersection_tests.h>

class Frustum
{
public:
    enum ePlaneClassifications
    {
        PLANE_FRONT = 0,
        PLANE_BACK,
        PLANE_INTERSECT
    };


#if 0
    ///////////////////////////////////////////////////////////

    enum eContainmentType
    {
        DISJOINT = 0,
        INTERSECTS = 1,
        CONTAINS = 2,
    };
#endif

    //-----------------------------------------------------
    // public data
    //-----------------------------------------------------
    Plane3d leftPlane;
    Plane3d rightPlane;
    Plane3d topPlane;
    Plane3d bottomPlane;
    Plane3d nearPlane;
    Plane3d farPlane;
  

    //-----------------------------------------------------
    // creators
    //-----------------------------------------------------
    Frustum();
    Frustum(const float fov, const float aspectRatio, const float zn, const float zf);
    Frustum(const Plane3d& l, const Plane3d& r, const Plane3d& t, const Plane3d& b, const Plane3d& n, const Plane3d& f);
    Frustum(const Matrix& proj);
    ~Frustum();

    //-----------------------------------------------------
    // mutators / setters
    //-----------------------------------------------------
    void Init(
        const float fov,
        const float aspectRatio,
        const float nearZ,
        const float farZ);

    void CreateFromProjMatrix(const Matrix& proj, const bool normalizePlanes = false);

    void Transform(Frustum& outFrustum, const Matrix& mat) const;

    void Copy(Frustum& dstFrustum) const;

    //-----------------------------------------------------
    // test operations
    //-----------------------------------------------------
    bool TestPoint(const Vec3& point) const;
    bool TestRect(const Rect3d& rect) const;
    bool TestSphere(const Sphere& sphere) const;
};


//==================================================================================
// INLINE METHODS
//==================================================================================

//---------------------------------------------------------
// Desc:   default constructor and destructor
//---------------------------------------------------------
inline Frustum::Frustum()
{
}

//---------------------------------------------------------

Frustum::Frustum(
    const float fov,
    const float aspectRatio, 
    const float zn, 
    const float zf)
{
    Init(fov, aspectRatio, zn, zf);
}

//---------------------------------------------------------

inline Frustum::Frustum(
    const Plane3d& left, 
    const Plane3d& right, 
    const Plane3d& top, 
    const Plane3d& bottom, 
    const Plane3d& near, 
    const Plane3d& far) 
    :
    leftPlane(left),
    rightPlane(right),
    topPlane(top),
    bottomPlane(bottom),
    nearPlane(near),
    farPlane(far)
{
}

//---------------------------------------------------------

inline Frustum::~Frustum()
{
}

//---------------------------------------------------------
// Desc:   create view frustum plane vectors in camera space in
//         terms of the focal length, aspect ratio, near and far plane distance
// Args:   - fov:          field of view in radians
//         - aspectRatio:  screen width divided by height
//         - nearZ, farZ:  a distance to near and far planes by Z-axis
//---------------------------------------------------------
inline void Frustum::Init(
    const float fov,
    const float aspectRatio,
    const float nearZ,
    const float farZ)
{
    assert(fov > 0.0f);
    assert(aspectRatio > 0.0f);
    assert(nearZ > 0.0f && farZ > 0.0f);
    assert(nearZ < farZ);

    // compute focal length
    const float e   = 1.0f / tanf(fov * 0.5f);

    float invDenom1 = 1.0f / sqrtf(SQR(e) + 1);
    float invDenom2 = 1.0f / sqrtf(SQR(e) + SQR(1.0f/aspectRatio));

    // normalized normal vectors
    float horizNx = e * invDenom1;
    float horizNz = invDenom1;
    float vertNy  = e * invDenom2;
    float vertNz  = invDenom2 * aspectRatio;


    nearPlane   = Plane3d(0, 0, +1, -nearZ);
    farPlane    = Plane3d(0, 0, -1, farZ);

    // since we have Z-forward the nz component for r/l/t/b planes is POSITIVE
    rightPlane  = Plane3d(-horizNx, 0, horizNz, 0);
    leftPlane   = Plane3d(+horizNx, 0, horizNz, 0);

    topPlane    = Plane3d(0, -vertNy, vertNz, 0);
    bottomPlane = Plane3d(0, +vertNy, vertNz, 0);
}


//---------------------------------------------------------
// Desc:   setup the fructum clipping planes using input proj matrix
//---------------------------------------------------------
inline Frustum::Frustum(const Matrix& m)
{

    Matrix mt;
    MatrixTranspose(m, mt);

#if 0
    const Vec4 row1(m[0][0], m[0][1], m[0][2], m[0][3]);
    const Vec4 row2(m[1][0], m[1][1], m[1][2], m[1][3]);
    const Vec4 row3(m[2][0], m[2][1], m[2][2], m[2][3]);
    const Vec4 row4(m[3][0], m[3][1], m[3][2], m[3][3]);
#elif 1
    const Vec4 row1(mt[0][0], mt[0][1], mt[0][2], mt[0][3]);
    const Vec4 row2(mt[1][0], mt[1][1], mt[1][2], mt[1][3]);
    const Vec4 row3(mt[2][0], mt[2][1], mt[2][2], mt[2][3]);
    const Vec4 row4(mt[3][0], mt[3][1], mt[3][2], mt[3][3]);
#else
    const Vec4 row1(m[0][0], m[1][0], m[2][0], m[3][0]);
    const Vec4 row2(m[0][1], m[1][1], m[2][1], m[3][1]);
    const Vec4 row3(m[0][2], m[1][2], m[2][2], m[3][2]);
    const Vec4 row4(m[0][3], m[1][3], m[2][3], m[3][3]);
#endif

#if 1
    nearPlane   = { row3 + row4 };
    farPlane    = { row3 - row4 };
    rightPlane  = { row1 - row4 };
    leftPlane   = { row1 + row4 };
    topPlane    = { row2 - row4 };
    bottomPlane = { row2 + row4 };
#else

    nearPlane   = row4 + row3;
    farPlane    = row4 - row3;

    leftPlane   = row4 + row1;
    rightPlane  = row4 - row1;

    bottomPlane = row4 + row2;
    topPlane    = row4 - row2;
#endif
    

    nearPlane.Normalize();
    farPlane.Normalize();
    rightPlane.Normalize();
    leftPlane.Normalize();
    topPlane.Normalize();
    bottomPlane.Normalize();
}


//---------------------------------------------------------
// Desc:   extract frustum planes from input projection matrix
//---------------------------------------------------------
inline void Frustum::CreateFromProjMatrix(
    const Matrix& proj,
    const bool normalizePlanes)
{
    const Matrix& matrix = proj;

    // Left clipping plane
    leftPlane.normal.x = matrix.m03 + matrix.m00;
    leftPlane.normal.y = matrix.m13 + matrix.m10;
    leftPlane.normal.z = matrix.m23 + matrix.m20;
    leftPlane.distance = matrix.m33 + matrix.m30;

    // Right clipping plane
    rightPlane.normal.x = matrix.m03 - matrix.m00;
    rightPlane.normal.y = matrix.m13 - matrix.m10;
    rightPlane.normal.z = matrix.m23 - matrix.m20;
    rightPlane.distance = matrix.m33 - matrix.m30;

    // Top clipping plane
    topPlane.normal.x = matrix.m03 - matrix.m01;
    topPlane.normal.y = matrix.m13 - matrix.m11;
    topPlane.normal.z = matrix.m23 - matrix.m21;
    topPlane.distance = matrix.m33 - matrix.m31;

    // Bottom clipping plane
    bottomPlane.normal.x = matrix.m03 + matrix.m01;
    bottomPlane.normal.y = matrix.m13 + matrix.m11;
    bottomPlane.normal.z = matrix.m23 + matrix.m21;
    bottomPlane.distance = matrix.m33 + matrix.m31;

    // Near clipping plane 
    nearPlane.normal.x = matrix.m02;
    nearPlane.normal.y = matrix.m12;
    nearPlane.normal.z = matrix.m22;
    nearPlane.distance = matrix.m32;

    // Far clipping plane 
    farPlane.normal.x = matrix.m03 - matrix.m02;
    farPlane.normal.y = matrix.m13 - matrix.m12;
    farPlane.normal.z = matrix.m23 - matrix.m22;
    farPlane.distance = matrix.m33 - matrix.m32;


    // it is not always nessesary to normalize the planes of the frustum.
    // Non-normalized planes can still be used for basic intersection tests.
    if (normalizePlanes)
    {
        leftPlane.Normalize();
        rightPlane.Normalize();
        topPlane.Normalize();
        bottomPlane.Normalize();
        nearPlane.Normalize();
        farPlane.Normalize();
    }
}

//---------------------------------------------------------
// Desc:   transform the current frustum with input matrix and 
//         store the result into outFrustum
//---------------------------------------------------------
inline void Frustum::Transform(Frustum& outFrustum, const Matrix& mat) const
{
    // compute an inverse transpose matrix for proper
    // transformation of the plane's normal vector
    Matrix invMT;
    MatrixInverse(invMT, nullptr, mat);
    MatrixTranspose(invMT);

    outFrustum = *this;

    outFrustum.leftPlane.Transform(invMT);
    outFrustum.rightPlane.Transform(invMT);
    outFrustum.topPlane.Transform(invMT);
    outFrustum.bottomPlane.Transform(invMT);
    outFrustum.nearPlane.Transform(invMT);
    outFrustum.farPlane.Transform(invMT);
}

//==================================================================================
// TESTS
//==================================================================================
inline bool Frustum::TestPoint(const Vec3& p) const
{
    return  (leftPlane.SignedDistance(p)        >= 0.0f) ||
            (rightPlane.SignedDistance(p)       >= 0.0f) ||
            (topPlane.SignedDistance(p)         >= 0.0f) ||
            (bottomPlane.SignedDistance(p)      >= 0.0f) ||
            (nearPlane.SignedDistance(p)        >= 0.0f) ||
            (farPlane.SignedDistance(p)         >= 0.0f);
}


//---------------------------------------------------------
// Desc:  test if input 3d rectangle is contained or intersected by the frustum
//---------------------------------------------------------
inline bool Frustum::TestRect(const Rect3d& rect) const
{
    return  (PlaneClassify(rect, leftPlane)     != PLANE_BACK) ||
            (PlaneClassify(rect, rightPlane)    != PLANE_BACK) ||
            (PlaneClassify(rect, topPlane)      != PLANE_BACK) ||
            (PlaneClassify(rect, bottomPlane)   != PLANE_BACK) ||
            (PlaneClassify(rect, nearPlane)     != PLANE_BACK) ||
            (PlaneClassify(rect, farPlane)      != PLANE_BACK);
}

//---------------------------------------------------------
// Desc:   test if inter sphere is contained or intersected by the frustum
//---------------------------------------------------------
inline bool Frustum::TestSphere(const Sphere& sphere) const
{
#if 0
    return  (PlaneClassify(sphere, leftPlane)   != PLANE_BACK) ||
            (PlaneClassify(sphere, rightPlane)  != PLANE_BACK) ||
            (PlaneClassify(sphere, topPlane)    != PLANE_BACK) ||
            (PlaneClassify(sphere, bottomPlane) != PLANE_BACK) ||
            (PlaneClassify(sphere, nearPlane)   != PLANE_BACK) ||
            (PlaneClassify(sphere, farPlane)    != PLANE_BACK);
#elif 1
    return
        leftPlane.SignedDistance(sphere.center)     >= -sphere.radius &&
        rightPlane.SignedDistance(sphere.center)    >= -sphere.radius &&
        topPlane.SignedDistance(sphere.center)      >= -sphere.radius &&
        bottomPlane.SignedDistance(sphere.center)   >= -sphere.radius &&
        nearPlane.SignedDistance(sphere.center)     >= -sphere.radius &&
        farPlane.SignedDistance(sphere.center)      >= -sphere.radius;
#else
    // for debugging
    bool l = leftPlane.SignedDistance(sphere.center) >= -sphere.radius;
    bool r = rightPlane.SignedDistance(sphere.center) >= -sphere.radius;
    bool t = topPlane.SignedDistance(sphere.center) >= -sphere.radius;
    bool b = bottomPlane.SignedDistance(sphere.center) >= -sphere.radius;
    bool n = nearPlane.SignedDistance(sphere.center) >= -sphere.radius;
    bool f = farPlane.SignedDistance(sphere.center) >= -sphere.radius;

    return l && r && t && b && n && f;
#endif
}

#if 0


//---------------------------------------------------------
// Desc:   test a point for inclusion in the viewing frustum
// Args:   - x,y,z: vertex position in 3D space
// Ret:    A boolean value: true if the vertex is visible
//---------------------------------------------------------
bool Frustum::PointTest(const float x, const float y, const float z) const
{
    // dot(n,p) + d: where n is a normal; p is an input point; d = -n*p0

    return
        ((Vec3Dot(nearClipPlane_.n,   { x,y,z }) + nearClipPlane_.d)   > 0) &&
        ((Vec3Dot(farClipPlane_.n,    { x,y,z }) + farClipPlane_.d)    > 0) &&
        ((Vec3Dot(leftClipPlane_.n,   { x,y,z }) + leftClipPlane_.d)   > 0) &&
        ((Vec3Dot(rightClipPlane_.n,  { x,y,z }) + rightClipPlane_.d)  > 0) &&
        ((Vec3Dot(topClipPlane_.n,    { x,y,z }) + topClipPlane_.d)    > 0) &&
        ((Vec3Dot(bottomClipPlane_.n, { x,y,z }) + bottomClipPlane_.d) > 0);
}

//---------------------------------------------------------
// Desc:   check if frustum contains sphere
// Args:   - x, y, z: input sphere center in 3D space
//         - r:       sphere radius
// Ret:    true if frustum intersects or completely contains the sphere
//---------------------------------------------------------
bool Frustum::SphereTest(
    const float x,
    const float y,
    const float z,
    const float r) const
{
    return
       ((Vec3Dot(nearClipPlane_.n,   { x,y,z }) + nearClipPlane_.d)   >= -r) &&
       ((Vec3Dot(farClipPlane_.n,    { x,y,z }) + farClipPlane_.d)    >= -r) &&
       ((Vec3Dot(leftClipPlane_.n,   { x,y,z }) + leftClipPlane_.d)   >= -r) &&
       ((Vec3Dot(rightClipPlane_.n,  { x,y,z }) + rightClipPlane_.d)  >= -r) &&
       ((Vec3Dot(topClipPlane_.n,    { x,y,z }) + topClipPlane_.d)    >= -r) &&
       ((Vec3Dot(bottomClipPlane_.n, { x,y,z }) + bottomClipPlane_.d) >= -r);
}

//---------------------------------------------------------
// Desc:   test the six vertices of the axis-aligned bounding box
//         against the viewing frustum
// Args:   - x,y,z:    center of the cube (NOTE: must be translated into camera space)
//         - halfSize: half of the cube size along each axis
// Ret:    boolean value: true if any part of the cube is in the frustum 
//---------------------------------------------------------
bool Frustum::CubeTest(
    const float x,
    const float y,
    const float z,
    const float halfSize) const
{
    const Vec3 cube[8] =
    {
        // bottom part
        {x-halfSize, y-halfSize, z-halfSize},
        {x+halfSize, y-halfSize, z-halfSize},
        {x-halfSize, y-halfSize, z+halfSize},
        {x+halfSize, y-halfSize, z+halfSize},

        // upper part
        {x-halfSize, y+halfSize, z-halfSize},
        {x+halfSize, y+halfSize, z-halfSize},
        {x-halfSize, y+halfSize, z+halfSize},
        {x+halfSize, y+halfSize, z+halfSize},
    };

    for (int i = 0; i < 8; ++i)
    {
        if (PointTest(cube[i].x, cube[i].y, cube[i].z))
            return true;
    }

    return false;
}


#endif
