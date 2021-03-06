#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Utility/Color.hpp>

namespace ax
{
    struct AXION_CORE_API RendererDirectionalLightParameters
    {
        Color3 color = Color3(1.0f, 1.0f, 1.0f);
        float intensity = 1.0f;
    };

    class AXION_CORE_API RendererDirectionalLight
    {
    public:
        virtual void setTransform(Transform* transform) = 0;
        virtual void setParameters(const RendererDirectionalLightParameters& parameters) = 0;
    };

    class AXION_CORE_API NullRendererDirectionalLight : public RendererDirectionalLight
    {
    public:
        void setTransform(Transform* transform) override {}
        void setParameters(const RendererDirectionalLightParameters& parameters) override {}
    };

    using RendererDirectionalLightHandle = RendererDirectionalLight*;
}