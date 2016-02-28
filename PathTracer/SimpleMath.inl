#include "pch.h"
#include "SimpleMath.h"

namespace PathTracer
{
    namespace Math
    {

        inline Color operator+ (const Color& LHS, const Color& RHS)
        {
            return Color(LHS.x + RHS.x, LHS.y + RHS.y, LHS.z + RHS.z, LHS.w + RHS.w);
        }
        inline Color operator- (const Color& LHS, const Color& RHS)
        {
            return Color(LHS.x - RHS.x, LHS.y - RHS.y, LHS.z - RHS.z, LHS.w - RHS.w);
        }
        inline Color operator* (const Color& LHS, const Color& RHS)
        {
            return Color(LHS.x * RHS.x, LHS.y * RHS.y, LHS.z * RHS.z, LHS.w * RHS.w);
        }
        inline Color operator* (const Color& LHS, float S)
        {
            return Color(LHS.x * S, LHS.y * S, LHS.z * S, LHS.w * S);
        }
        inline Color operator/ (const Color& LHS, float S)
        {
            return Color(LHS.x / S, LHS.y / S, LHS.z / S, LHS.w / S);
        }
        inline Color operator/ (const Color& LHS, const Color& RHS)
        {
            return Color(LHS.x / RHS.x, LHS.y / RHS.y, LHS.z / RHS.z, LHS.w / RHS.w);
        }
        inline Color operator* (float S, const Color& RHS)
        {
            return Color(RHS.x * S, RHS.y * S, RHS.z * S, RHS.w * S);
        }


        inline Vector3 operator+ (const Vector3& LHS, const Vector3& RHS)
        {
            return Vector3(LHS.x + RHS.x, LHS.y + RHS.y, LHS.z + RHS.z);
        }
        inline Vector3 operator- (const Vector3& LHS, const Vector3& RHS)
        {
            return Vector3(LHS.x - RHS.x, LHS.y - RHS.y, LHS.z - RHS.z);
        }
        inline Vector3 operator* (const Vector3& LHS, const Vector3& RHS)
        {
            return Vector3(LHS.x * RHS.x, LHS.y * RHS.y, LHS.z * RHS.z);
        }
        inline Vector3 operator* (const Vector3& LHS, float S)
        {
            return Vector3(LHS.x * S, LHS.y * S, LHS.z * S);
        }
        inline Vector3 operator/ (const Vector3& LHS, float S)
        {
            return Vector3(LHS.x / S, LHS.y / S, LHS.z / S);
        }
        inline Vector3 operator/ (const Vector3& LHS, const Vector3& RHS)
        {
            return Vector3(LHS.x / RHS.x, LHS.y / RHS.y, LHS.z / RHS.z);
        }
        inline Vector3 operator* (float S, const Vector3& RHS)
        {
            return Vector3(RHS.x * S, RHS.y * S, RHS.z * S);
        }
    }
}