#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Renderer/Light/DirectionalLightParameters.hpp>
#include <Core/World/Component/Component.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>

namespace ax
{
    struct AXION_CORE_API DirectionalLightComponent : public Component
    {
    public:
        static const std::string name;

        DirectionalLightComponent(const Entity& entity);
        ~DirectionalLightComponent();

        void setColor(Color3 color) noexcept;
        Color3 getColor() const noexcept;

        TransformComponent& transform;
    
    private:
        Id m_handle;
        DirectionalLightParameters m_parameters;
    };
}