#include <Core/Assets/TextureManager.hpp>

using namespace ax;

AssetReference<Texture> TextureManager::operator()(std::string name) const noexcept
{
    try
    {
        return m_textures.at(name)->reference();
    }
    catch(std::out_of_range e)
    {
        Engine::interrupt("Failed to access texture '" + name + "'");
    } 
}
AssetReference<Texture> TextureManager::create(std::string name, Path path) noexcept
{
    if(exists(name))
    {
        Engine::logger().log("Failed to create texture '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Texture>();
    }

    m_textures.emplace(name, std::make_unique<AssetHolder<Texture>>(name));
    m_textures.at(name)->get()->loadFromFile(path);

    return m_textures.at(name)->reference();
}
bool TextureManager::destroy(std::string name) noexcept
{
    if(!exists(name))
    {
        Engine::logger().log("Failed to destroy texture '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    if(m_textures.at(name)->referenceCount() > 0) return false;

    if(!m_textures.at(name)->get()->unload())
    {
        Engine::logger().log("Failed to destroy texture '" + name + "'", Logger::Warning);
        return false;
    }

    m_textures.erase(name);

    return true;
}
bool TextureManager::exists(std::string name) const noexcept
{
    return m_textures.find(name) != m_textures.end();
}

void TextureManager::dispose() noexcept
{
    std::vector<std::string> keys;
    keys.reserve(m_textures.size());
    for(auto& it : m_textures)
        keys.emplace_back(it.first);

    for(auto it : keys) unload(it);
}
void TextureManager::log() const noexcept
{
    Engine::logger().log("[TEXTURE]", Logger::Info);
    
    for(auto& it : m_textures)
    {
        Engine::logger().log(" \\_ " + it.first, Logger::Info);
    }
}