#pragma once
#include "Hitable.h"

namespace PathTracer
{
    class Sphere : public Hitable
    {
    public:
        Sphere(const Vector3& centre, const float radius, Material::Ptr material)
            : m_centre(centre), m_radius(radius), m_material(material) {}


        virtual bool Hit(const Ray& ray, float stepMin, float stepMax, HitData& data) const override;

        inline Vector3 GetCentre() const { return m_centre; }
        inline void SetCentre(const Vector3& centre) { m_centre = centre; }

        inline float GetRadius() const { return m_radius; }
        inline void SetRadius(float radius) { m_radius = radius; }

        inline Material::Ptr GetMaterial() const { return m_material; }
        inline void SetMaterial(Material::Ptr material) { m_material = material; }

    protected:
        Vector3 m_centre;
        float m_radius;
        Material::Ptr m_material;
    };
}// End namespace PathTracer
