#pragma once
#include "SimpleMath.h"
#include "Ray.h"
namespace PathTracer
{
    struct HitData
    {
        float RayStep = 0.0f;
        Math::Vector3 Position = {0.0f, 0.0f, 0.0f};
        Math::Vector3 Normal = { 0.0f, 0.0f, 0.0f };
    };

    class Hitable
    {
    public:
        using Ptr = std::shared_ptr<Hitable>;
        virtual bool Hit(const Ray& ray, float stepMin, float stepMax, HitData& data) const = 0;
    };
}// End namespace PathTracer
