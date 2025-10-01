//==================================================================================
// Filename:   math_helpers.h
// Desc:       different math helpers
//
// Created:    06.07.2025  by DimaSkup
//==================================================================================
#pragma once

#include <math/math_constants.h>
#include <math.h>

//---------------------------------------------------------
// Angles convertion
//---------------------------------------------------------
#define DEG_TO_RAD( angle )	  ( ( angle )  *PIOVER180 )
#define RAD_TO_DEG( radians ) ( ( radians )*PIUNDER180 )


// --------------------------------------------------------
// Desc:   check if input value is power of 2
// Args:   - value: a value to check
// Ret:    - true if is power of 2
// --------------------------------------------------------
inline bool IsPow2(const int value)
{
    return (value && !(value & (value - 1)));
}

//---------------------------------------
// swapping values with XOR (NOTE: works only for INTEGER values)
//---------------------------------------
#define SWAP(a, b) ((a ^= b), (b ^= a), (a ^= b))

//---------------------------------------
// Desc:   helpers to get a square/cube of input value
//---------------------------------------
inline int   SQR(const int num)     { return num*num; }
inline float SQR(const float num)   { return num*num; }
inline int   CUBE(const int num)    { return num*num*num; }
inline float CUBE(const float num)  { return num*num*num; }

// ----------------------------------------------------
template<typename T>
static T Clamp(const T& x, const T& low, const T& high)
{
    return x < low ? low : (x > high ? high : x);
}

// ----------------------------------------------------
inline void ClampPitch(float& pitch)
{
    // limit the pitch value in range (-(PI/2)+0.1f < pitch < (PI/2)-0.1f)
    if (pitch > PIDIV2 - 0.1f)
    {
        pitch = PIDIV2 - 0.1f;
    }
    else if (pitch < -PIDIV2 + 0.1f)
    {
        pitch = -PIDIV2 + 0.1f;
    }
}

// ----------------------------------------------------
inline void ClampYaw(float& yaw)
{
    // limit the yaw value in range (-2PI < yaw < 2PI)
    if (yaw > M_2PI)
    {
        yaw = -M_2PI;
    }
    else if (yaw < -M_2PI)
    {
        yaw = M_2PI;
    }
}

// ----------------------------------------------------

inline int powi(const int value, const int power)
{
    return (int)exp(log(value) * power);
}

// ----------------------------------------------------

inline int FastMin(const int x, const int y)
{
    return y ^ ((x ^ y) & -(x < y)); // min(x, y)
}

// ----------------------------------------------------

inline int FastMax(const int x, const int y)
{
    return x ^ ((x ^ y) & -(x < y)); // max(x, y)
}

// ----------------------------------------------------

template <class T>
inline T Min(const T x, const T y)
{
    return (x < y) ? x : y;
}

// ----------------------------------------------------

template <class T>
inline T Max(const T x, const T y)
{
    return (x > y) ? x : y;
}

//---------------------------------------------------------
// a little helper to check if 2 input floats are "equal"
//---------------------------------------------------------
inline bool FloatEqual(const float a, const float b)
{
    return fabsf(a - b) < EPSILON_E5;
}
