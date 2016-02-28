#pragma once
#include "Hitable.h"

namespace PathTracer
{
    class Sphere : public Hitable
    {
    public:
        Sphere(const Vector3& centre, const float radius)
            : m_centre(centre), m_radius(radius) {}


        virtual bool Hit(const Ray& ray, float stepMin, float stepMax, HitData& data) const override;

        inline Vector3 GetCentre() const { return m_centre; }
        inline void SetCentre(const Vector3& centre) { m_centre = centre; }

        inline float GetRadius() const { return m_radius; }
        inline void SetRadius(float radius) { m_radius = radius; }

    protected:
        Vector3 m_centre;
        float m_radius;
    };
}// End namespace PathTracer
