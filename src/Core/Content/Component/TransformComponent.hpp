#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/Entity/Entity.ipp>
#include <Core/Scene/Component/Component.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Math/Quaternion.hpp>
#include <Core/Utility/Json.hpp>
#include <Core/Utility/Macro.hpp>

namespace ax
{
    class AXION_CORE_API TransformComponent : public Component
    {
    public:
        COMPONENT_IDENTIFIER("transform")
        COMPONENT_REQUIREMENTS()
        
        TransformComponent(Entity& entity, const Json& json);
        TransformComponent(
            Entity& entity,
            Vector3f position = Vector3f(0.0f, 0.0f, 0.0f), 
            Quaternionf rotation = Quaternionf(), 
            Vector3f scale = Vector3f(1.0f, 1.0f, 1.0f)
        );
        ~TransformComponent();

        void setTranslation(float x = 0.0f, float y = 0.0f, float z = 0.0f) noexcept;
        void setTranslation(const Vector3f& position) noexcept;
        Vector3f getTranslation() const noexcept;
        void setRotation(float angle = 0.0f, const Vector3f& axis = Vector3f(0.0f, 1.0f, 0.0f)) noexcept;
        void setRotation(const Quaternionf& rotation) noexcept;
        Quaternionf getRotation() const noexcept;
        void setScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) noexcept;
        void setScale(const Vector3f& scale) noexcept;
        Vector3f getScale() const noexcept;

        void rotate(float angle, Vector3f axis) noexcept;
        void translate(Vector3f vec) noexcept;

        Vector3f getForwardVector() const noexcept;
        Vector3f getBackwardVector() const noexcept;
        Vector3f getLeftVector() const noexcept;
        Vector3f getRightVector() const noexcept;
        Vector3f getUpVector() const noexcept;
        Vector3f getDownVector() const noexcept;

        void attachTo(Entity& entity) noexcept;
        void attachTo(TransformComponent& newParent) noexcept;
        void detach() noexcept;
        bool isAttached() const noexcept;
        bool hasChild() const noexcept;

        Matrix4f getWorldMatrix() const noexcept;
        Matrix4f getMatrix() const noexcept;

        Entity& entity;

    private:
        void setParent(TransformComponent* newParent) noexcept;
        Matrix4f localToWorld() const noexcept;
        Matrix4f localToParent() const noexcept;

        Vector3f m_translation = Vector3f(0.0f, 0.0f, 0.0f);
        Quaternionf m_rotation = Quaternionf(0.0f, Vector3f(0.0f, 1.0f, 0.0f));
        Vector3f m_scale = Vector3f(1.0f, 1.0f, 1.0f);
 
        mutable Matrix4f m_transform;
        mutable bool m_requestCompute = true;

        TransformComponent* parent = nullptr;
        TransformComponent* firstChild = nullptr;
        TransformComponent* nextSibling = nullptr;
        TransformComponent* prevSibling = nullptr;
    };
}