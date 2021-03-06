#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Geometry/Sphere.hpp>
#include <Core/Math/Geometry/Vertex.hpp>

#include <vector>

namespace ax
{
    class AXION_CORE_API UVSphere : public Sphere
    {
    public:
        UVSphere(float radius = 1.0f, unsigned UN = 10, unsigned VN = 10);

    public:
        static std::vector<Vertex> vertices(
            float radius = 1.0f, 
            unsigned UN = 30, 
            unsigned UV = 30, 
            bool smooth = true, 
            float coordinateFactor = 1.0f
        ) noexcept;

        void setSliceCount(unsigned slice) noexcept;
        void setStackCount(unsigned stack) noexcept; 

    protected:
        unsigned m_UN = 10;
        unsigned m_VN = 10;
    };
}