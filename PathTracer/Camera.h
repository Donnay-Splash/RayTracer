#pragma once

#include "Ray.h"
namespace PathTracer
{
    class Camera
    {
    public:
        Camera()
            :m_origin({ 0.0f, 0.0f, 0.0f }), m_bottomLeftCorner(-2.0f, -1.0f, -1.0f),
            m_horizontal(4.0f, 0.0f, 0.0f), m_vertical(0.0f, 2.0f, 0.0f) {}


        Ray GetRay(float u, float v) { return Ray(m_origin, m_bottomLeftCorner + (u*m_horizontal) + (v * m_vertical) - m_origin); }
    private:
        Vector3 m_origin;
        Vector3 m_bottomLeftCorner;
        Vector3 m_horizontal;
        Vector3 m_vertical;
    };
} // End namespace PathTracer