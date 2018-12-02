#include <Core/Assets/Model.hpp>

using namespace ax;

Model::Model(){}
Model::Model(std::string name)
{
    m_name = name;
}
Model::~Model()
{
    unload();
}

bool Model::loadFromFile(Path path) noexcept
{
    if(path.extension() == ".obj")
        return loadObjModel(name, path);
    else
        return false;
}
bool Model::unload(bool tryDestroyMeshes = true, bool tryDestroyMaterials = true) noexcept
{
    if(m_isLoaded)
    {
        if(tryUnloadMeshes)
        {
            for(auto it = model->meshes.begin(); it != model->meshes.end(); it++)
            {
                std::string meshName = it->get()->name;
                it->reset();
                Engine::assets().mesh.destroy(meshName);
            }
        }
        model->meshes.clear();
        if(tryUnloadMaterials)
        {
            for(auto& it : model->materials)
            {
                std::string materialName = it.get()->name;
                it.reset();
                Engine::assets().material.destroy(materialName, tryUnloadTextures);            
            }
        }
        model->materials.clear();
    }

    m_isLoaded = false;
}

std::string Model::getName() const noexcept
{
    return m_name;
}

const std::vector<AssetReference<Mesh>>& Model::getMeshes() const noexcept
{
    return m_meshes;
}
const std::vector<AssetReference<Material>>& Model::getMaterials() const noexcept
{
    return m_materials;
}

bool Model::loadObjModel(Path path) noexcept
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), path.directory().c_str(), true);
    if(!ret)
    {
        Engine::logger().log("Failed to load model '" + name + "'", Logger::Warning);
        Engine::logger().log("TINYOBJ Error: " + err);
        return false;
    }

    //Loading materials
    for(const auto& material : materials)
    {
        if(!Engine::assets().material.exists(material.name))
        {
            MaterialParameters data;

            //Diffuse Texture
            Path diffusePath = path.directory() + material.diffuse_texname;
            bool hasDiffuseTex = !diffusePath.filename().empty() &&
                (Engine::assets().texture.exists(diffusePath.filename()) ||
                 Engine::assets().texture.create(diffusePath.filename(), diffusePath.path()));
            
            if(hasDiffuseTex)
                data.diffuseTexture = diffusePath.filename();
            else
            {
                data.diffuseUniform.r = material.diffuse[0];
                data.diffuseUniform.g = material.diffuse[1];
                data.diffuseUniform.b = material.diffuse[2];
            }

            //Normal Texture
            Path normalPath = path.directory() + material.normal_texname;
            bool hasNormalTex = !normalPath.filename().empty() &&
                (Engine::assets().texture.exists(normalPath.filename()) ||
                 Engine::assets().texture.create(normalPath.filename(), normalPath.path()));

            if(hasNormalTex)
                data.normalTexture = normalPath.filename();

            //Bump Texture
            Path bumpPath = path.directory() + material.bump_texname;
            bool hasBumpTex = !bumpPath.filename().empty() &&
                (Engine::assets().texture.exists(bumpPath.filename()) ||
                 Engine::assets().texture.create(bumpPath.filename(), bumpPath.path()));

            if(hasBumpTex)
                data.bumpTexture = bumpPath.filename();

            //Load material as assets
            Engine::assets().material.create(material.name, data);
        } 
    }

    //Loading meshes
    std::unordered_map<int, std::vector<Vertex>> meshes;
    for(size_t s = 0; s < shapes.size(); s++)
    {
        size_t index_offset = 0;
        for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            int fv = shapes[s].mesh.num_face_vertices[f];
            int materialId =  shapes[s].mesh.material_ids[f];

            for(size_t v = 0; v < fv; v++)
            {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                Vertex vertex;
                vertex.position.x = attrib.vertices[3 * idx.vertex_index + 0];
                vertex.position.y = attrib.vertices[3 * idx.vertex_index + 1];
                vertex.position.z = attrib.vertices[3 * idx.vertex_index + 2];
                
                if(!attrib.texcoords.empty())
                {
                    vertex.uv.x = attrib.texcoords[2 * idx.texcoord_index + 0];
                    vertex.uv.y = attrib.texcoords[2 * idx.texcoord_index + 1];
                }

                if(!attrib.normals.empty())
                {
                    vertex.normal.x = attrib.normals[3 * idx.normal_index + 0];
                    vertex.normal.y = attrib.normals[3 * idx.normal_index + 1];
                    vertex.normal.z = attrib.normals[3 * idx.normal_index + 2];                    
                }

                vertex.color.x = attrib.colors[3 * idx.vertex_index + 0];
                vertex.color.y = attrib.colors[3 * idx.vertex_index + 1];
                vertex.color.z = attrib.colors[3 * idx.vertex_index + 2];

                meshes[materialId].push_back(vertex);
            }

            index_offset += fv;
        }
    }

    //Loading models
    for(auto it = meshes.begin(); it != meshes.end(); it++)
    {
        size_t i = std::distance(meshes.begin(), it);
        
        std::string meshName = name + "_" + std::to_string(i);
        Engine::assets().mesh.load(meshName, it->second, true, attrib.normals.empty());
        m_meshes.emplace_back(Engine::assets().mesh(meshName));

        if(it->first != -1)
        {
            std::string materialName = materials[it->first].name;
            m_materials.emplace_back(Engine::assets().material(materialName));
        }
        else
        {
            m_materials.emplace_back(AssetReference<Material>());
        }
    }

    m_isLoaded = true;

    return true;
}