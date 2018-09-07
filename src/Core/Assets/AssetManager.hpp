#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/Vertex.hpp>
#include <Core/Assets/Texture.hpp>
#include <Core/Assets/Mesh.hpp>
#include <Core/Assets/Material.hpp>
#include <Core/Assets/Model.hpp>
#include <Core/Assets/Package.hpp>
#include <Core/Assets/Shader.hpp>

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace ax
{
    class AXION_CORE_API AssetManager
    {
    public:
        ~AssetManager();

        void logInfo() const noexcept;

        bool loadPackage(Path path) noexcept;
        bool unloadPackage(std::string name) noexcept;
        bool packageExists(std::string name) noexcept;
        std::shared_ptr<const Package> package(std::string name) noexcept;

        bool loadTexture(std::string name, Path path) noexcept;
        bool unloadTexture(std::string name) noexcept;
        bool textureExists(std::string name) noexcept;
        std::shared_ptr<const Texture> texture(std::string name) noexcept;

        bool loadMesh(std::string name, const std::vector<Vertex>& vertices) noexcept;
        bool unloadMesh(std::string name) noexcept;
        bool meshExists(std::string name) noexcept;
        std::shared_ptr<const Mesh> mesh(std::string name) noexcept;

        bool loadMaterial(std::string name, const MaterialData& material) noexcept;
        bool unloadMaterial(std::string name) noexcept;
        bool materialExists(std::string name) noexcept;
        std::shared_ptr<const Material> material(std::string name) noexcept;

        bool loadModel(std::string name, Path path) noexcept;
        bool unloadModel(std::string name) noexcept;
        bool modelExists(std::string name) noexcept;
        std::shared_ptr<const Model> model(std::string name) noexcept;

        bool loadShader(std::string name, Path vertex, Path fragment) noexcept;
        bool unloadShader(std::string name) noexcept;
        bool shaderExists(std::string name) noexcept;
        std::shared_ptr<const Shader> shader(std::string name) noexcept;
    
    private:
        bool loadObjModel(std::string name, Path path) noexcept;

    private:
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
        std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;
        std::unordered_map<std::string, std::shared_ptr<Material>> m_materials;
        std::unordered_map<std::string, std::shared_ptr<Model>> m_models;
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
        std::unordered_map<std::string, std::shared_ptr<Package>> m_packages;
    };
}