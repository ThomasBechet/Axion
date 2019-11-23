#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Renderer/Scene/RendererDirectionalLight.hpp>
#include <Core/Scene/Component/Component.hpp>
#include <Core/Content/Component/TransformComponent.hpp>

namespace ax
{
    class AXION_CORE_API DirectionalLightComponent : public Component
    {
    public:
        COMPONENT_IDENTIFIER("directional_light")
        COMPONENT_REQUIREMENTS(TransformComponent)
        
        DirectionalLightComponent(Entity& entity, const Json& json);
        DirectionalLightComponent(Entity& entity);
        ~DirectionalLightComponent();

        void setColor(Color3 color) noexcept;
        Color3 getColor() const noexcept;

        TransformComponent& transform;
    
    private:
        RendererDirectionalLightHandle m_handle;
        RendererDirectionalLightParameters m_parameters;
    };
}