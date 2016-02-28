#include "pch.h"
#include "Ray.h"

namespace PathTracer
{
    Vector3 Ray::PointAt(float t) const
    {
        return m_endPoint + (m_direction * t);
    }
}