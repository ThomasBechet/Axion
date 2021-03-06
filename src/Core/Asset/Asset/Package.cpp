#include <Core/Asset/Asset/Package.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Asset/AssetModule.hpp>
#include <Core/Asset/JsonAttributes.hpp>
#include <Core/Utility/Json.hpp>

#include <fstream>

using namespace ax;

Package::Package(const std::string& name, const Parameters& parameters) :
    Asset(name, identifier),
    m_parameters(parameters)
{

}

const std::vector<AssetReference<Material>>& Package::getMaterials() const noexcept
{
    return m_materials;
}
const std::vector<AssetReference<Mesh>>& Package::getMeshes() const noexcept
{
    return m_meshes;
}
const std::vector<AssetReference<Model>>& Package::getModels() const noexcept
{
    return m_models;
}
const std::vector<AssetReference<Scene>>& Package::getScenes() const noexcept
{
    return m_scenes;
}
const std::vector<AssetReference<Shader>>& Package::getShaders() const noexcept
{
    return m_shaders;
}
const std::vector<AssetReference<Texture>>& Package::getTextures() const noexcept
{
    return m_textures;
}

bool Package::onLoad() noexcept
{
    if(!m_parameters.source.empty())
    {
        if(m_parameters.source.extension() != ".json")
        {
            logLoadError("Loading <" + Package::identifier + "> from file '" + m_parameters.source + "'");
            return false;
        }

        std::ifstream jsonFile(m_parameters.source.str());
        if(!jsonFile.is_open())
        {
            logLoadError("Failed to open file '" + m_parameters.source.str() + "'");
            return false;
        }
        std::string jsonBuffer{std::istreambuf_iterator<char>(jsonFile), std::istreambuf_iterator<char>()};

        //Parse json
        try 
        {
            Json json = Json::parse(jsonBuffer);
            return loadFromJson(json);
        }
        catch(const Json::parse_error& error)
        {
            logLoadError(error.what());
            return false;
        }
    }
    else if(!m_parameters.json.is_null())
    {
        return loadFromJson(m_parameters.json);
    }
    else
    {
        return false;
    }
}
bool Package::onValidate() noexcept
{
    for(auto& it : m_dummyMaterials) m_materials.emplace_back(Engine::asset().material(it));
    m_dummyMaterials.clear();
    for(auto& it : m_dummyMeshes) m_meshes.emplace_back(Engine::asset().mesh(it));
    m_dummyMeshes.clear();
    for(auto& it : m_dummyModels) m_models.emplace_back(Engine::asset().model(it));
    m_dummyMaterials.clear();
    for(auto& it : m_dummyScenes) m_scenes.emplace_back(Engine::asset().scene(it));
    m_dummyScenes.clear();
    for(auto& it : m_dummyShaders) m_shaders.emplace_back(Engine::asset().shader(it));
    m_dummyShaders.clear();
    for(auto& it : m_dummyTextures) m_textures.emplace_back(Engine::asset().texture(it));
    m_dummyTextures.clear();

    return true;
}
bool Package::onUnload() noexcept
{
    for(auto it = m_materials.begin(); it != m_materials.end(); it++)
    {
        std::string materialName = it->get()->getName();
        it->reset();
        Engine::asset().material.unload(materialName);
    }
    m_materials.clear();
    for(auto it = m_models.begin(); it != m_models.end(); it++)
    {
        std::string modelName = it->get()->getName();
        it->reset();
        Engine::asset().model.unload(modelName);
    }
    m_models.clear();
    for(auto it = m_textures.begin(); it != m_textures.end(); it++)
    {
        std::string textureName = it->get()->getName();
        it->reset();
        Engine::asset().texture.unload(textureName);
    }
    m_textures.clear();
    for(auto it = m_meshes.begin(); it != m_meshes.end(); it++)
    {
        std::string meshName = it->get()->getName();
        it->reset();
        Engine::asset().mesh.unload(meshName);
    }
    m_meshes.clear();
    for(auto it = m_shaders.begin(); it != m_shaders.end(); it++)
    {
        std::string shaderName = it->get()->getName();
        it->reset();
        Engine::asset().shader.unload(shaderName);
    }
    m_shaders.clear();

    return true;
}

bool Package::loadFromJson(Json& json) noexcept
{
    try
    {
        auto jType = json[JsonAttributes::type];
        std::string type = jType.get<std::string>(); 
        json.erase(JsonAttributes::type);
        if(type != Package::identifier)
        {
            logLoadError("Loading <" + Package::identifier + "> without '" + Package::identifier + "' value for '" + JsonAttributes::type + "' attribute");
            return false;
        }
    }
    catch(const std::exception& e)
    {
        logLoadError("Loading <" + Package::identifier + "> without '" + JsonAttributes::type + "' attribute");
        return false;
    }

    try
    {
        auto jAssets = json[JsonAttributes::assets];
        if(!jAssets.is_array())
        {
            logLoadError("Invalid '" + JsonAttributes::assets + "' attribute");
            return false;
        }

        //Load each items
        for(auto& item : jAssets)
        {
            auto jItemName = item.find(JsonAttributes::name);
            auto jItemType = item.find(JsonAttributes::type);              
            if(jItemType != item.end() && jItemType->is_string() && jItemName != item.end() && jItemName->is_string())
            {
                std::string itemType = jItemType->get<std::string>();
                std::string itemName = jItemName->get<std::string>();

                //Remove name attribute because it is not required
                item.erase(JsonAttributes::name);
                
                if(itemType == Material::identifier)
                {
                    Material::Parameters materialParameters;
                    materialParameters.json = item;
                    if(m_parameters.asyncLoading)
                        Engine::asset().material.loadAsync(itemName, materialParameters);
                    else
                        Engine::asset().material.load(itemName, materialParameters);
                    m_dummyMaterials.emplace_back(itemName);
                }
                else if(itemType == Mesh::identifier)
                {
                    Mesh::Parameters meshParameters;
                    meshParameters.json = item;
                    if(m_parameters.asyncLoading)
                        Engine::asset().mesh.loadAsync(itemName, meshParameters);
                    else
                        Engine::asset().mesh.load(itemName, meshParameters);
                    m_dummyMeshes.emplace_back(itemName);
                }
                else if(itemType == Model::identifier)
                {
                    Model::Parameters modelParameters;
                    modelParameters.json = item;
                    modelParameters.asyncLoading = m_parameters.asyncLoading;
                    if(m_parameters.asyncLoading)
                        Engine::asset().model.loadAsync(itemName, modelParameters);
                    else
                        Engine::asset().model.load(itemName, modelParameters);
                    m_dummyModels.emplace_back(itemName);
                }
                else if(itemType == Package::identifier)
                {
                    
                }
                else if(itemType == Scene::identifier)
                {
                    Scene::Parameters sceneParameters;
                    sceneParameters.json = item;
                    if(m_parameters.asyncLoading)
                        Engine::asset().scene.loadAsync(itemName, sceneParameters);
                    else
                        Engine::asset().scene.load(itemName, sceneParameters);
                    m_dummyScenes.emplace_back(itemName);
                }
                else if(itemType == Shader::identifier)
                {
                    Shader::Parameters shaderParameters;
                    shaderParameters.json = item;
                    if(m_parameters.asyncLoading)
                        Engine::asset().shader.loadAsync(itemName, shaderParameters);
                    else
                        Engine::asset().shader.load(itemName, shaderParameters);
                    m_dummyShaders.emplace_back(itemName);
                }
                else if(itemType == Texture::identifier)
                {
                    Texture::Parameters textureParameters;
                    textureParameters.json = item;
                    if(m_parameters.asyncLoading)
                        Engine::asset().texture.loadAsync(itemName, textureParameters);
                    else
                        Engine::asset().texture.load(itemName, textureParameters);
                    m_dummyTextures.emplace_back(itemName);
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        logLoadError("Loading <" + Package::identifier + "> without '" + JsonAttributes::assets + "' attribute");
        return false;
    }

    return true;
}