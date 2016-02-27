#pragma once
#include "pch.h"
using namespace DirectX;

namespace PathTracer
{
namespace Math
{
    struct Color : public XMFLOAT4
    {
        Color() : XMFLOAT4() {}
        Color(float r, float g, float b, float a) : XMFLOAT4(r, g, b, a) {}

        Color GammaEncode()
        {
            XMVECTOR colorVector = XMLoadFloat4(this);
            colorVector = XMColorRGBToSRGB(colorVector);
            Color sRGB;
            XMStoreFloat4(&sRGB, colorVector);
            return sRGB;
        }

        Color GammaDecode()
        {
            XMVECTOR colorVector = XMLoadFloat4(this);
            colorVector = XMColorSRGBToRGB(colorVector);
            Color RGB;
            XMStoreFloat4(&RGB, colorVector);
            return RGB;
        }

    };

    struct Vector3 : public XMFLOAT3
    {
        Vector3() : XMFLOAT3(0.f, 0.f, 0.f) {}
        Vector3(float x, float y, float z) : XMFLOAT3(x, y, z) {}

        float Length() 
        {
            sqrt((x*x) + (y*y) + (z*z));
        }

        void Normalise()
        {
            *this /= this->Length();
        }


        Vector3 operator+ ()
        {
            return *this;
        }

        Vector3 operator- ()
        {
            XMVECTOR c = XMLoadFloat3(this);
            Vector3 R;
            XMStoreFloat3(&R, XMVectorNegate(c));
            return R;
        }

        inline Vector3& Vector3::operator+= (const Vector3& V)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat3(this);
            XMVECTOR v2 = XMLoadFloat3(&V);
            XMVECTOR X = XMVectorAdd(v1, v2);
            XMStoreFloat3(this, X);
            return *this;
        }

        inline Vector3& Vector3::operator-= (const Vector3& V)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat3(this);
            XMVECTOR v2 = XMLoadFloat3(&V);
            XMVECTOR X = XMVectorSubtract(v1, v2);
            XMStoreFloat3(this, X);
            return *this;
        }

        inline Vector3& Vector3::operator*= (const Vector3& V)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat3(this);
            XMVECTOR v2 = XMLoadFloat3(&V);
            XMVECTOR X = XMVectorMultiply(v1, v2);
            XMStoreFloat3(this, X);
            return *this;
        }

        inline Vector3& Vector3::operator*= (float S)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat3(this);
            XMVECTOR X = XMVectorScale(v1, S);
            XMStoreFloat3(this, X);
            return *this;
        }

        inline Vector3& Vector3::operator/= (float S)
        {
            using namespace DirectX;
            assert(S != 0.0f);
            XMVECTOR v1 = XMLoadFloat3(this);
            XMVECTOR X = XMVectorScale(v1, 1.f / S);
            XMStoreFloat3(this, X);
            return *this;
        }

    };

    Vector3 operator+ (const Vector3& LHS, const Vector3& RHS)
    {
        return Vector3(LHS.x + RHS.x, LHS.y + RHS.y, LHS.z + RHS.z);
    }
    Vector3 operator- (const Vector3& LHS, const Vector3& RHS)
    {
        return Vector3(LHS.x - RHS.x, LHS.y - RHS.y, LHS.z - RHS.z);
    }
    Vector3 operator* (const Vector3& LHS, const Vector3& RHS)
    {
        return Vector3(LHS.x * RHS.x, LHS.y * RHS.y, LHS.z * RHS.z);
    }
    Vector3 operator* (const Vector3& LHS, float S)
    {
        return Vector3(LHS.x * S, LHS.y * S, LHS.z * S);
    }
    Vector3 operator/ (const Vector3& LHS, float S)
    {
        return Vector3(LHS.x / S, LHS.y / S, LHS.z / S);
    }
    Vector3 operator/ (const Vector3& LHS, const Vector3& RHS)
    {
        return Vector3(LHS.x / RHS.x, LHS.y / RHS.y, LHS.z / RHS.z);
    }
    Vector3 operator* (float S, const Vector3& RHS)
    {
        return Vector3(RHS.x * S, RHS.y * S, RHS.z * S);
    }

}// End Namespace Math
}// End Namespace PathTracer