#include <Core/Assets/Texture.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace ax;

std::shared_ptr<const Texture> TextureManager::operator()(std::string name) const noexcept
{
    try
    {
        return std::const_pointer_cast<const Texture>(m_textures.at(name));
    }
    catch(std::out_of_range e)
    {
        Engine::interrupt("Failed to access texture '" + name + "'");
    } 
}
std::shared_ptr<const Texture> TextureManager::load(std::string name, Path path) noexcept
{
    if(isLoaded(name))
    {
        Engine::logger().log("Failed to load texture '" + name + "' because it already exists.", Logger::Warning);
        return nullptr;
    }

    int width, height, bpp;
    Id handle;
    TextureFormat format;
    Byte* data = stbi_load(path.c_str(), &width, &height, &bpp, 0);
    if(!data)
    {
        Engine::logger().log("Failed to load texture '" + path.path() + "'", Logger::Warning);
        return nullptr;
    }

    if(bpp == 3)
        format = TextureFormat::RGB;
    else if(bpp == 4)
        format = TextureFormat::RGBA;

    try
    {
        handle = Engine::renderer().createTexture(
            Vector2u(width, height),
            format,
            data
        );
    }
    catch(const RendererException& exception)
    {
        Engine::logger().log("Failed to load texture '" + name + "' from renderer: ", Logger::Warning);
        Engine::logger().log(exception.what());
        stbi_image_free(data);
    }

    m_textures.emplace(name, std::make_shared<Texture>());
    Texture* texture = m_textures.at(name).get();
    texture->name = name;
    texture->data = data;
    texture->size.x = (unsigned)width;
    texture->size.y = (unsigned)height;

    return std::const_pointer_cast<const Texture>(m_textures.at(name));
}
bool TextureManager::unload(std::string name) noexcept
{
    try
    {
        if(m_textures.at(name).use_count() != 1) return false;
        stbi_image_free(m_textures.at(name)->data);
        m_textures.erase(name);
    }
    catch(const std::out_of_range& exception)
    {
        Engine::logger().log("Failed to unload texture '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    return true;
}
bool TextureManager::isLoaded(std::string name) const noexcept
{
    return m_textures.find(name) != m_textures.end();
}

void TextureManager::dispose() noexcept
{
    std::vector<std::string> keys;
    keys.reserve(m_textures.size());
    for(auto it : m_textures)
        keys.emplace_back(it.second->name);

    for(auto it : keys) unload(it);
}
void TextureManager::log() const noexcept
{
    Engine::logger().log("[   TEXTURE   ]", Logger::Info);
    
    for(auto it = m_textures.begin(); it != m_textures.end(); it++)
    {
        Engine::logger().log("- " + it->second.get()->name, Logger::Info);
    }
}