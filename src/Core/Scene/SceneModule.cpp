#include <Core/Scene/SceneModule.hpp>

#include <Core/Asset/AssetModule.ipp>

using namespace ax;

bool SceneModule::hasNext() noexcept
{
    return m_nextScene.isValid() || gamemode.hasNext();
}
void SceneModule::next() noexcept
{
    if(m_nextScene)
    {
        openScene(*m_nextScene.get());
        m_nextScene.reset();
    }

    gamemode.next();
}

void SceneModule::open(const std::string& scene) noexcept
{
    open(Engine::asset().get<SceneAsset>(scene));
}
void SceneModule::open(Reference<SceneAsset> scene) noexcept
{
    if(scene) openScene(*scene.get());
}
void SceneModule::openScene(const SceneAsset& scene) noexcept
{
    for(auto& [key, item] : scene.getEntities().items())
        Engine::scene().entity.create(key, item);
}