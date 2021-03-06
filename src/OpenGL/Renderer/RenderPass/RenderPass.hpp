#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Math/Vector.hpp>

namespace ax
{
    class RenderBuffer;
    class RenderContent;
    class RendererCameraGL;
    class RendererGUIViewportGL;

    class AXION_GL_API RenderPass
    {
    public:
        RenderPass(RenderContent& content, RendererGUIViewportGL& viewport);
        virtual ~RenderPass() = default;

    public:
        virtual void onInitialize(const Vector2u& resolution) noexcept = 0;
        virtual void onTerminate() noexcept = 0;
        virtual void onUpdateResolution(const Vector2u& resolution) noexcept = 0;
        virtual void onRender(const RenderBuffer& renderBuffer, const RendererCameraGL& camera, double alpha) noexcept = 0;

    protected:
        RenderContent& content;
        RendererGUIViewportGL& viewport;
    };
}