#pragma once

#include "SimpleMath.h"

namespace PathTracer
{
    using namespace Math;
    class Ray
    {
    public:
        Ray();
        Ray(const Vector3& endPoint, const Vector3& direction) 
            : m_endPoint(endPoint), m_direction(direction){}

        inline Vector3 EndPoint() const { return m_endPoint; }
        inline Vector3 Direction() const { return m_direction; }

        Vector3 PointAt(float t) const;
    private:
        const Vector3 m_endPoint = {0.0f, 0.0f, 0.0f};
        const Vector3 m_direction = {0.0f, 0.0f, 0.0f};
    };
} // End namespace PathTracer

