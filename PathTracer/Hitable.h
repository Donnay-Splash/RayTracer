#pragma once
#include "SimpleMath.h"
#include "Ray.h"
namespace PathTracer
{
    // forward declaration
    class Material;


    struct HitData
    {
        float RayStep = 0.0f;
        Math::Vector3 Position = {0.0f, 0.0f, 0.0f};
        Math::Vector3 Normal = { 0.0f, 0.0f, 0.0f };
        Material* Material;
    };

    class Hitable
    {
    public:
        using Ptr = std::shared_ptr<Hitable>;
        virtual bool Hit(const Ray& ray, float stepMin, float stepMax, HitData& data) const = 0;
    };

    class Material
    {
    public:
        using Ptr = std::shared_ptr<Material>;
        virtual bool Scatter(const Ray& rayIn, const HitData& data, Math::Color& attenuation, Ray& rayScattered) const = 0;
    };

    class Lambertian : public Material
    {
    public:
        Lambertian(const Math::Color& albedo) : m_albedo(albedo) {}

        bool Scatter(const Ray& rayIn, const HitData& data, Math::Color& attenuation, Ray& rayScattered) const override
        {
            Vector3 target = data.Position + data.Normal + Math::RandomInUnitSphere();
            rayScattered = Ray(data.Position, target - data.Position);
            attenuation = m_albedo;
            return true;
        }

    private:
        Math::Color m_albedo;
    };

    class Metal : public Material
    {
    public:
        Metal(const Math::Color albedo, float roughness=0.0f) : m_albedo(albedo), m_roughness(roughness) {}

        bool Scatter(const Ray& rayIn, const HitData& data, Math::Color& attenuation, Ray& rayScattered) const override
        {
            Math::Vector3 reflected = Math::Reflect(Math::Vector3::Normalise(rayIn.Direction()), data.Normal);
            rayScattered = Ray(data.Position, reflected + m_roughness * Math::RandomInUnitSphere());
            attenuation = m_albedo;
            return Math::Vector3::Dot(rayScattered.Direction(), data.Normal) > 0;
        }

    private:
        Math::Color m_albedo;
        float m_roughness;
    };

    class Dielectric : public Material
    {
    public:
        Dielectric(float ri) : m_refractiveIndex(ri) {}

        bool Scatter(const Ray& rayIn, const HitData& data, Math::Color& attenuation, Ray& rayScattered) const override
        {
            Math::Vector3 outwardNormal;
            Math::Vector3 reflected = Math::Reflect(rayIn.Direction(), data.Normal);
            float niOnt;
            attenuation = Color(1.0f, 1.0f, 1.0f, 1.0f);
            Math::Vector3 refracted;
            float cosine;
            float reflectProbability;
            if (Math::Vector3::Dot(rayIn.Direction(), data.Normal) > 0)
            {
                outwardNormal = -data.Normal;
                niOnt = m_refractiveIndex;
                cosine = Vector3::Dot(rayIn.Direction(), data.Normal) / rayIn.Direction().Length();
                cosine = sqrt(1.0f - m_refractiveIndex*m_refractiveIndex*(1.0f - cosine*cosine));
            }
            else
            {
                outwardNormal = data.Normal;
                niOnt = 1.0f / m_refractiveIndex;
                cosine = -Vector3::Dot(rayIn.Direction(), data.Normal) / rayIn.Direction().Length();
            }

            if (Math::Refract(rayIn.Direction(), outwardNormal, niOnt, refracted))
            {
                reflectProbability = Math::Schlick(cosine, m_refractiveIndex);
            }
            else
            {
                reflectProbability = 1.0f;
            }

            if (Math::kRand() < reflectProbability)
            {
                rayScattered = Ray(data.Position, reflected);
            }
            else
            {
                rayScattered = Ray(data.Position, refracted);
            }
            return true;
        }

    private:
        float m_refractiveIndex;
    };

}// End namespace PathTracer
