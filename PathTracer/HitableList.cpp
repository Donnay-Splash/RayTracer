#include "pch.h"
#include "HitableList.h"

namespace PathTracer
{
    bool HitableList::Hit(const Ray& ray, float stepMin, float stepMax, HitData& data) const
    {
        HitData tempData;
        bool hitSomething = false;
        float closestT = stepMax;
        for (auto hitableObject : m_hitableObjects)
        {
            if (hitableObject->Hit(ray, stepMin ,closestT, tempData))
            {
                hitSomething = true;
                closestT = tempData.RayStep;
                data = tempData;
            }
        }
        return hitSomething;
    }

    void HitableList::AddObjectToScene(Hitable::Ptr object)
    {
        m_hitableObjects.push_back(object);
    }
} // End namespace PathTracer