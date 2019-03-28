#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>
#include <Core/Renderer/RendererCameraParameters.hpp>

#include <string>

namespace ax
{
    struct AXION_CORE_API CameraComponent : public Component
    {
    public:
        static const std::string name;
        
        CameraComponent(const Entity& entity);
        ~CameraComponent();

        void bindDefaultViewport() noexcept;
        void bindViewport(Id viewport) noexcept;

        void setFov(float fov) noexcept;
        float getFov() const noexcept;
        void setFarPlane(float far) noexcept;
        float getFarPlane() const noexcept;
        void setNearPlane(float near) noexcept;
        float getNearPlane() const noexcept;

        TransformComponent& transform;

    private:
        void updateRendererParameters() noexcept;
        
        Id m_handle;
        RendererCameraParameters m_parameters;
    };
}