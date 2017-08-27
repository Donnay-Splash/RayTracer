#pragma once

#include "SimpleMath.h"

namespace PathTracer
{
    using namespace Math;
    class Ray
    {
    public:
        Ray() {}
        ~Ray() {};
        Ray(const Vector3& endPoint, const Vector3& direction) 
            : m_endPoint(endPoint), m_direction(direction){}
        Ray& operator=(const Ray&) = default;

        inline Vector3 EndPoint() const { return m_endPoint; }
        inline Vector3 Direction() const { return m_direction; }

        Vector3 PointAt(float t) const;
    private:
        Vector3 m_endPoint = {0.0f, 0.0f, 0.0f};
        Vector3 m_direction = {0.0f, 0.0f, 0.0f};
    };
} // End namespace PathTracer

