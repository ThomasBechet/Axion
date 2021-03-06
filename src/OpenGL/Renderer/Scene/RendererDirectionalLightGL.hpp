#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Renderer/Scene/RendererDirectionalLight.hpp>

#include <GL/glew.h>

namespace ax
{
    class Transform;
    class RenderContent;

    struct AXION_GL_API RendererDirectionalLightGL : public RendererDirectionalLight
    {
    public:
        void setTransform(Transform* transform) override;
        void setParameters(const RendererDirectionalLightParameters& parameters) override;

        Transform* transform = nullptr;

        Color3 color;

        GLuint uboIndex;

        Id id;
        RenderContent* content = nullptr;
    }; 
}