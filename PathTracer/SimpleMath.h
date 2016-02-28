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

        static Color Lerp(const Color& startColor, const Color& endColor, float t)
        {
            auto vectorStart = XMLoadFloat4(&startColor);
            auto vectorEnd = XMLoadFloat4(&endColor);
            auto lerpedVector = XMVectorLerp(vectorStart, vectorEnd, t);
            Color R;
            XMStoreFloat4(&R, lerpedVector);
            return R;
        }

        Color operator+ ()
        {
            return *this;
        }

        Color operator- ()
        {
            XMVECTOR c = XMLoadFloat4(this);
            Color R;
            XMStoreFloat4(&R, XMVectorNegate(c));
            return R;
        }

        inline Color& operator+= (const Color& V)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat4(this);
            XMVECTOR v2 = XMLoadFloat4(&V);
            XMVECTOR X = XMVectorAdd(v1, v2);
            XMStoreFloat4(this, X);
            return *this;
        }

        inline Color& operator-= (const Color& V)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat4(this);
            XMVECTOR v2 = XMLoadFloat4(&V);
            XMVECTOR X = XMVectorSubtract(v1, v2);
            XMStoreFloat4(this, X);
            return *this;
        }

        inline Color& operator*= (const Color& V)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat4(this);
            XMVECTOR v2 = XMLoadFloat4(&V);
            XMVECTOR X = XMVectorMultiply(v1, v2);
            XMStoreFloat4(this, X);
            return *this;
        }

        inline Color& operator*= (float S)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat4(this);
            XMVECTOR X = XMVectorScale(v1, S);
            XMStoreFloat4(this, X);
            return *this;
        }

        inline Color& operator/= (float S)
        {
            using namespace DirectX;
            assert(S != 0.0f);
            XMVECTOR v1 = XMLoadFloat4(this);
            XMVECTOR X = XMVectorScale(v1, 1.f / S);
            XMStoreFloat4(this, X);
            return *this;
        }

    };

    Color operator+ (const Color& LHS, const Color& RHS);
    Color operator- (const Color& LHS, const Color& RHS);
    Color operator* (const Color& LHS, const Color& RHS);
    Color operator* (const Color& LHS, float S);
    Color operator/ (const Color& LHS, float S);
    Color operator/ (const Color& LHS, const Color& RHS);
    Color operator* (float S, const Color& RHS);

    struct Vector3 : public XMFLOAT3
    {
        Vector3() : XMFLOAT3(0.f, 0.f, 0.f) {}
        Vector3(float x, float y, float z) : XMFLOAT3(x, y, z) {}

        float Length() const
        {
            sqrt((x*x) + (y*y) + (z*z));
        }

        void Normalise()
        {
            *this /= this->Length();
        }

        static Vector3 Normalise(const Vector3& vec)
        {
            auto vector = XMLoadFloat3(&vec);
            auto normailizedVector = XMVector3Normalize(vector);
            Vector3 R;
            XMStoreFloat3(&R, normailizedVector);
            return R;
        }

        static Vector3 Lerp(const Vector3& startVec, const Vector3& endVec, float t)
        {
            auto vectorStart = XMLoadFloat3(&startVec);
            auto vectorEnd = XMLoadFloat3(&endVec);
            auto lerpedVector = XMVectorLerp(vectorStart, vectorEnd, t);
            Vector3 R;
            XMStoreFloat3(&R, lerpedVector);
            return R;
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

        inline Vector3& operator+= (const Vector3& V)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat3(this);
            XMVECTOR v2 = XMLoadFloat3(&V);
            XMVECTOR X = XMVectorAdd(v1, v2);
            XMStoreFloat3(this, X);
            return *this;
        }

        inline Vector3& operator-= (const Vector3& V)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat3(this);
            XMVECTOR v2 = XMLoadFloat3(&V);
            XMVECTOR X = XMVectorSubtract(v1, v2);
            XMStoreFloat3(this, X);
            return *this;
        }

        inline Vector3& operator*= (const Vector3& V)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat3(this);
            XMVECTOR v2 = XMLoadFloat3(&V);
            XMVECTOR X = XMVectorMultiply(v1, v2);
            XMStoreFloat3(this, X);
            return *this;
        }

        inline Vector3& operator*= (float S)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat3(this);
            XMVECTOR X = XMVectorScale(v1, S);
            XMStoreFloat3(this, X);
            return *this;
        }

        inline Vector3& operator/= (float S)
        {
            using namespace DirectX;
            assert(S != 0.0f);
            XMVECTOR v1 = XMLoadFloat3(this);
            XMVECTOR X = XMVectorScale(v1, 1.f / S);
            XMStoreFloat3(this, X);
            return *this;
        }

        static inline float Dot(const Vector3& LHS, const Vector3& RHS)
        {
            using namespace DirectX;
            XMVECTOR v1 = XMLoadFloat3(&LHS);
            XMVECTOR v2 = XMLoadFloat3(&RHS);
            XMVECTOR X = XMVector3Dot(v1, v2);
            return XMVectorGetX(X);
        }

        static inline Vector3 Cross(const Vector3& LHS, const Vector3& RHS)
        {
            XMVECTOR v1 = XMLoadFloat3(&LHS);
            XMVECTOR v2 = XMLoadFloat3(&RHS);
            XMVECTOR R = XMVector3Cross(v1, v2);

            Vector3 result;
            XMStoreFloat3(&result, R);
            return result;
        }

        static const Vector3 kOne;
    };

    Vector3 operator+ (const Vector3& LHS, const Vector3& RHS);
    Vector3 operator- (const Vector3& LHS, const Vector3& RHS);
    Vector3 operator* (const Vector3& LHS, const Vector3& RHS);
    Vector3 operator* (const Vector3& LHS, float S);
    Vector3 operator/ (const Vector3& LHS, float S);
    Vector3 operator/ (const Vector3& LHS, const Vector3& RHS);
    Vector3 operator* (float S, const Vector3& RHS);

}// End Namespace Math
}// End Namespace PathTracer

#include "SimpleMath.inl"