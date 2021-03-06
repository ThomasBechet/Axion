#include <OpenGL/Renderer/Buffer/CameraUBO.hpp>

#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>

#include <cstring>

using namespace ax;

CameraUBO::CameraUBO()
{
    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraUBOData), nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_UNIFORM_BUFFER, CAMERA_UBO_BINDING_POINT, m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
CameraUBO::~CameraUBO()
{
    glDeleteBuffers(1, &m_ubo);
}

void CameraUBO::update(const Matrix4f& view, const Matrix4f& projection, const Matrix4f& invProjection) const noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);

    CameraUBOData* p = static_cast<CameraUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        0,
        sizeof(CameraUBOData),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    ));

    p->projectionMatrix = projection;
    p->viewMatrix = view;
    p->invProjectionMatrix = invProjection;

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}