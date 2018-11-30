#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

//Material
Id RendererGL::createMaterial(RendererMaterialParameters settings)
{
    Id id = m_content.materials.add(std::pair<MaterialGL, std::vector<Id>>());
    MaterialGL& material = m_content.materials.get(id).first;

    material.useDiffuseTexture = settings.useDiffuseTexture;
    material.diffuseUniform = settings.diffuseUniform;
    material.diffuseTexture = settings.diffuseTexture;

    material.useNormalTexture = settings.useNormalTexture;
    material.normalTexture = settings.normalTexture;
    material.useBumpTexture = settings.useBumpTexture;
    material.bumpTexture = settings.bumpTexture;

    m_content.materialUBO->load(material);

    return id;
}
void RendererGL::destroyMaterial(Id id)
{
    MaterialGL& material = m_content.materials.get(id).first;

    m_content.materialUBO->unload(material);

    m_content.materials.remove(id);
}