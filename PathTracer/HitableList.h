#pragma once
#include "Hitable.h"

namespace PathTracer
{
    class HitableList : public Hitable
    {
    public:
        using Ptr = std::shared_ptr<HitableList>;


        virtual bool Hit(const Ray& ray, float stepMin, float stepMax, HitData& data) const override;
        void AddObjectToScene(Hitable::Ptr object);
    protected:

        std::vector<Hitable::Ptr> m_hitableObjects;
    };
}