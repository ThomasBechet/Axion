#include <OpenGL/Renderer/GUI/RendererGUILayoutGL.hpp>
#include <OpenGL/Renderer/RendererModuleGL.hpp>

#include <OpenGL/Renderer/GUI/RendererGUIRectangleGL.hpp>
#include <OpenGL/Renderer/GUI/RendererGUIScalableRectangleGL.hpp>

#include <algorithm>

using namespace ax;

RendererGUILayoutHandle RendererModuleGL::createGUILayout()
{
    //Id id = m_content.layouts.add(std::make_unique<RendererGUILayoutGL>());
    //RendererGUILayoutGL* layout = m_content.layouts.get(id).get();
    //layout->id = id;

    return nullptr;
}
void RendererModuleGL::destroyGUILayout(RendererGUILayoutHandle& layout)
{
    //RendererGUILayoutGL* layout = static_cast<RendererGUILayoutGL*>(layout);
    //m_content.layouts.remove(layout->id);
    layout = nullptr;
}

RendererGUILayoutGL::RendererGUILayoutGL(
    GLuint guiRectangleShader,
    GLuint guiScalableRectangleShader
) : 
m_guiRectangleShader(guiRectangleShader),
m_guiScalableRectangleShader(guiScalableRectangleShader)
{

}

RendererGUIRectangleHandle RendererGUILayoutGL::createRectangle()
{
    m_components.emplace_back(std::make_pair(
        m_components.empty() ? 0 : m_components.back().first, 
        std::make_unique<RendererGUIRectangleGL>(*this, m_guiRectangleShader)
    ));
    return static_cast<RendererGUIRectangleGL*>(m_components.back().second.get());
}
void RendererGUILayoutGL::destroyRectangle(RendererGUIRectangleHandle& handle)
{
    m_components.erase(std::remove_if(m_components.begin(), m_components.end(), 
        [&](std::pair<int, std::unique_ptr<RendererGUIComponentGL>>& ptr)
            {return (ptr.second.get() == static_cast<RendererGUIRectangleGL*>(handle));}));
    handle = nullptr;
}

RendererGUIScalableRectangleHandle RendererGUILayoutGL::createScalableRectangle()
{
    //scalableRectangles.emplace_back(std::make_unique<RendererGUIScalableRectangleGL>());
    //return scalableRectangles.back().get();

    return nullptr;
}
void RendererGUILayoutGL::destroyScalableRectangle(RendererGUIScalableRectangleHandle& handle)
{
    /*scalableRectangles.erase(std::remove_if(scalableRectangles.begin(), scalableRectangles.end(), 
        [&](std::unique_ptr<RendererGUIScalableRectangleGL> ptr){ptr.get() == handle;}));
    handle = nullptr;*/
}

void RendererGUILayoutGL::draw() noexcept
{
    for(auto& component : m_components)
    {
        component.second->draw();
    }
}
void RendererGUILayoutGL::changeDepthComponent(const RendererGUIComponentGL& component, int depth) noexcept
{
    auto iterator = std::find_if(m_components.begin(), m_components.end(), 
        [&](const auto& element){return element.second.get() == &component;}
    );

    if(iterator != m_components.end() && iterator->first != depth)
    {
        iterator->first = depth;
        std::sort(m_components.begin(), m_components.end(), 
            [](const auto& e1, const auto& e2){return e1.first < e2.first;}
        );
    }
}