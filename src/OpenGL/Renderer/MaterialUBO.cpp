#include <OpenGL/Renderer/MaterialUBO.hpp>

#include <OpenGL/Renderer/MaterialGL.hpp>

#include <cstring>

using namespace ax;

MaterialUBO::MaterialUBO()
{
    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialUBOData) * MATERIAL_MAX_NUMBER, nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_UNIFORM_BUFFER, MATERIAL_BINDING_POINT, m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
MaterialUBO::~MaterialUBO()
{
    glDeleteBuffers(1, &m_ubo);
}

void MaterialUBO::load(MaterialGL& material) noexcept
{
    if(!m_free.empty())
    {
        material.uboIndex = m_free.back();
        m_free.pop_back();
    }
    else
    {
        material.uboIndex = m_next;
        m_next++;
    }

    update(material);
}
void MaterialUBO::unload(MaterialGL& material) noexcept
{
    m_free.emplace_back(material.uboIndex);
}
void MaterialUBO::update(const MaterialGL& material) noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);

    MaterialUBOData* p = static_cast<MaterialUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        sizeof(MaterialUBOData) * material.uboIndex,
        sizeof(MaterialUBOData),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT
    ));

    if(material.useDiffuseTexture)
        p->flags |= MATERIAL_USE_DIFFUSE_TEXTURE;

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}