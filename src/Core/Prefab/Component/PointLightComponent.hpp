#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Renderer/Scene/RendererPointLight.hpp>
#include <Core/Scene/Component/Component.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>

namespace ax
{
    struct AXION_CORE_API PointLightComponent : public Component
    {
    public:
        COMPONENT_IDENTIFIER("point_light")
        COMPONENT_REQUIREMENT(TransformComponent)
        
        PointLightComponent(const Entity& entity, const Json& json);
        PointLightComponent(const Entity& entity);
        ~PointLightComponent();

        void setRadius(float radius) noexcept;
        float getRadius() const noexcept;

        void setColor(Color3 color) noexcept;
        Color3 getColor() const noexcept;
  
        TransformComponent& transform;
    
    private:
        RendererPointLightHandle m_handle;
        RendererPointLightParameters m_parameters;
    };
}