#include <Core/Asset/Shader.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Renderer/RendererException.hpp>

#include <fstream>
#include <streambuf>

using namespace ax;

Shader::Shader() {}
Shader::Shader(std::string name)
{
    m_name = name;
}
Shader::~Shader()
{
    unload();
}

bool Shader::loadFromFile(Path vertex, Path fragment) noexcept
{
    unload();

    try
    {
        std::ifstream vertexFile(vertex.path());
        if(!vertexFile.is_open()) return false;
        std::string vertexBuffer{std::istreambuf_iterator<char>(vertexFile), std::istreambuf_iterator<char>()};
        
        std::ifstream fragmentFile(fragment.path());
        if(!fragmentFile.is_open()) return false;
        std::string fragmentBuffer{std::istreambuf_iterator<char>(fragmentFile), std::istreambuf_iterator<char>()};

        Id handle = Engine::renderer().createShader(&vertexBuffer, &fragmentBuffer);
        
        m_vertex = vertexBuffer;
        m_fragment = fragmentBuffer;
        m_handle = handle;
    }
    catch(const RendererException& exception)
    {
        Engine::logger().log("Failed to compile shader '" + m_name + "'", Logger::Warning);
        Engine::logger().log(exception.what(), Logger::Warning);
        
        return false;
    }

    m_isLoaded = true;

    return true;
}
bool Shader::unload() noexcept
{
    if(isLoaded())
    {
        try
        {
            Engine::renderer().destroyShader(m_handle);
        }
        catch(const RendererException& exception)
        {
            Engine::logger().log("Failed to unload shader '" + m_name + "' from renderer: ", Logger::Warning);
            Engine::logger().log(exception.what(), Logger::Warning);
            
            return false;
        }
    }

    m_isLoaded = false;

    return true;
}
bool Shader::isLoaded() const noexcept
{
    return m_isLoaded;
}

std::string Shader::getName() const noexcept
{
    return m_name;
}
std::string Shader::getVertexCode() const noexcept
{
    return m_vertex;
}
std::string Shader::getFragmentCode() const noexcept
{
    return m_fragment;
}

Id Shader::getHandle() const noexcept
{
    return m_handle;
}