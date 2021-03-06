#include <OpenGL/Renderer/Buffer/MaterialUBO.hpp>

#include <OpenGL/Renderer/Asset/RendererMaterialGL.hpp>
#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>

#include <cstring>

using namespace ax;

MaterialUBO::MaterialUBO()
{
    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(MaterialUBOData) * MATERIAL_MAX_NUMBER, nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_UNIFORM_BUFFER, MATERIAL_UBO_BINDING_POINT, m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
MaterialUBO::~MaterialUBO()
{
    glDeleteBuffers(1, &m_ubo);
}

void MaterialUBO::load(RendererMaterialGL& material) noexcept
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
}
void MaterialUBO::unload(RendererMaterialGL& material) noexcept
{
    m_free.emplace_back(material.uboIndex);
}
void MaterialUBO::updateMaterial(const RendererMaterialGL& material) noexcept
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);

    MaterialUBOData* p = static_cast<MaterialUBOData*>(glMapBufferRange(
        GL_UNIFORM_BUFFER,
        sizeof(MaterialUBOData) * material.uboIndex,
        sizeof(MaterialUBOData),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_UNSYNCHRONIZED_BIT
    ));

    p->diffuseColor = material.parameters.diffuseColor;
    p->specularUniform = material.parameters.specularUniform;

    p->flags = 0;

    if(material.parameters.useDiffuseTexture)
        p->flags |= MATERIAL_USE_DIFFUSE_TEXTURE;

    if(material.parameters.useDiffuseColor)
        p->flags |= MATERIAL_USE_DIFFUSE_COLOR;

    if(material.parameters.useNormalTexture)
    {
        p->flags |= MATERIAL_USE_NORMAL_TEXTURE;
        if(material.parameters.isBumpTexture)
            p->flags |= MATERIAL_IS_BUMP_TEXTURE;
    }

    if(material.parameters.useSpecularTexture)
        p->flags |= MATERIAL_USE_SPECULAR_TEXTURE;

    glUnmapBuffer(GL_UNIFORM_BUFFER);
}