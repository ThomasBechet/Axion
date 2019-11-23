#pragma once

#include <Core/Export.hpp>
#include <Core/Content/Component/TransformComponent.hpp>

namespace ax
{
    struct AXION_CORE_API RendererPointLightParameters
    {
        Color3 color = Color3(1.0f, 1.0f, 1.0f);
        float radius = 10.0f;
        float intensity = 1.0f;
    };

    class AXION_CORE_API RendererPointLight
    {
    public:
        virtual void setTransform(TransformComponent* transform) = 0;
        virtual void setParameters(const RendererPointLightParameters& parameters) = 0;
    };

    class AXION_CORE_API NullRendererPointLight : public RendererPointLight
    {
    public:
        void setTransform(TransformComponent* transform) override {}
        void setParameters(const RendererPointLightParameters& parameters) override {}
    };

    using RendererPointLightHandle = RendererPointLight*;
}