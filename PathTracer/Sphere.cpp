#include "pch.h"
#include "Sphere.h"

namespace PathTracer
{

    bool Sphere::Hit(const Ray& ray, float stepMin, float stepMax, HitData& data) const 
    {
        Vector3 oc = ray.EndPoint() - m_centre;
        float a = Vector3::Dot(ray.Direction(), ray.Direction());
        float b = Vector3::Dot(oc, ray.Direction());
        float c = Vector3::Dot(oc, oc) - (m_radius * m_radius);
        float discriminant = b*b - a*c;

        if (discriminant > 0)
        {
            float temp = (-b - sqrt(discriminant)) / a;
            if (temp < stepMax && temp > stepMin)
            {
                data.RayStep = temp;
                data.Position = ray.PointAt(data.RayStep);
                data.Normal = (data.Position - m_centre) / m_radius;
                return true;
            }

            temp = (-b + sqrt(discriminant)) / a;
            if (temp < stepMax && temp > stepMin)
            {
                data.RayStep = temp;
                data.Position = ray.PointAt(data.RayStep);
                data.Normal = (data.Position - m_centre) / m_radius;
                return true;
            }
        }
        return false;
    }
}// End namespace PathTracer
