#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/Json.hpp>
#include <Core/Utility/Macro.hpp>
#include <Core/Math/Geometry/Vertex.hpp>
#include <Core/Asset/Asset.hpp>
#include <Core/Renderer/Asset/RendererMesh.hpp>

#include <string>
#include <vector>

namespace ax
{
    class AXION_CORE_API Mesh : public Asset
    {
    public:
        struct Parameters
        {
            Path source;
            Json json;
            std::vector<Vertex> vertices;
            bool computeTangent = false;
            bool computeNormal = false;
        };

    public:
        ASSET_IDENTIFIER("mesh")
        
        Mesh(const std::string& name, const Parameters& parameters);

        const std::vector<Vertex>& getVertices() const noexcept;
        RendererMeshHandle getHandle() const noexcept;

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;

    private:
        Parameters m_parameters;
        RendererMeshHandle m_handle;
    };
}