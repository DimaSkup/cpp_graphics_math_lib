#include <tests/tests_rect_3d.h>
#include <tests/tests_matrix.h>
#include <tests/tests_plane_3d.h>
#include <tests/tests_frustum.h>
#include <stdlib.h>

int main()
{
    InitLogger("log_cpp_graphics_math_lib.txt");

    TestRect3d();
    TestMatrix();
    TestPlane3d();
    TestFrustum();

    CloseLogger();

    return 0;
}