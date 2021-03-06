#include <Core/Math/Geometry/Rectangle.hpp>

using namespace ax;

Rectangle::Rectangle(
    float xMin, float xMax,
    float yMin, float yMax,
    float zMin, float zMax
) :
m_xMin(xMin), m_xMax(xMax),
m_yMin(yMin), m_yMax(yMax),
m_zMin(zMin), m_zMax(zMax)
{
    if(m_xMin > m_xMax) m_xMin = m_xMax;
    if(m_xMax < m_xMin) m_xMax = m_xMin;
    if(m_yMin > m_yMax) m_yMin = m_yMax;
    if(m_yMax < m_yMin) m_yMax = m_yMin;
    if(m_zMin > m_zMax) m_zMin = m_zMax;
    if(m_zMax < m_zMin) m_zMax = m_zMin;
}

float Rectangle::getMinX() const noexcept
{
    return m_xMin;
}
void Rectangle::setMinX(float x) noexcept
{
    m_xMin = x;
    if(m_xMin > m_xMax) m_xMin = m_xMax;
}

float Rectangle::getMaxX() const noexcept
{
    return m_xMax;
}
void Rectangle::setMaxX(float x) noexcept
{
    m_xMax = x;
    if(m_xMax < m_xMin) m_xMax = m_xMin;
}

float Rectangle::getMinY() const noexcept
{
    return m_yMin;
}
void Rectangle::setMinY(float y) noexcept
{
    m_yMin = y;
    if(m_yMin > m_yMax) m_yMin = m_yMax;
}

float Rectangle::getMaxY() const noexcept
{
    return m_yMax;
}
void Rectangle::setMaxY(float y) noexcept
{
    m_yMax = y;
    if(m_yMax < m_yMin) m_yMax = m_yMin;
}

float Rectangle::getMinZ() const noexcept
{
    return m_zMin;
}
void Rectangle::setMinZ(float z) noexcept
{
    m_zMin = z;
    if(m_zMin > m_zMax) m_zMin = m_zMax;
}

float Rectangle::getMaxZ() const noexcept
{
    return m_zMax;
}
void Rectangle::setMaxZ(float z) noexcept
{
    m_zMax = z;
    if(m_zMax < m_zMin) m_zMax = m_zMin;
}

std::vector<Vertex> Rectangle::vertices(
    float xMin, float xMax, 
    float yMin, float yMax, 
    float zMin, float zMax,
    float coordinateFactor
) noexcept
{
    std::vector<Vertex> vertices;

    vertices.reserve(6 * 6);

    Vertex vertex;
    Vector2f uv0, uv1, uv2, uv3;
    Vector3f p0, p1, p2, p3, p4, p5, p6, p7;

    //Generate positions;
    p0 = Vector3f(xMin, yMax, zMin);
    p1 = Vector3f(xMax, yMax, zMin);
    p2 = Vector3f(xMax, yMax, zMax);
    p3 = Vector3f(xMin, yMax, zMax);
    p4 = Vector3f(xMin, yMin, zMin);
    p5 = Vector3f(xMax, yMin, zMin);
    p6 = Vector3f(xMax, yMin, zMax);
    p7 = Vector3f(xMin, yMin, zMax);

    //Generate uvs;
    uv0 = Vector2f(0.0f, 1.0f * coordinateFactor);
    uv1 = Vector2f(1.0f * coordinateFactor, 1.0f * coordinateFactor);
    uv2 = Vector2f(1.0f * coordinateFactor, 0.0f);
    uv3 = Vector2f(0.0f, 0.0f);

    //Top
    vertex.normal = Vector3f::up;
    vertex.tangent = Vector3f::right;

    vertex.position = p0;
    vertex.uv = uv0;
    vertices.emplace_back(vertex);

    vertex.position = p3;
    vertex.uv = uv3;
    vertices.emplace_back(vertex);

    vertex.position = p2;
    vertex.uv = uv2;
    vertices.emplace_back(vertex);

    vertex.position = p2;
    vertex.uv = uv2;
    vertices.emplace_back(vertex);
    
    vertex.position = p1;
    vertex.uv = uv1;
    vertices.emplace_back(vertex);

    vertex.position = p0;
    vertex.uv = uv0;
    vertices.emplace_back(vertex);

    //Bottom
    vertex.normal = Vector3f::down;
    vertex.tangent = Vector3f::right;

    vertex.position = p4;
    vertex.uv = uv3;
    vertices.emplace_back(vertex);

    vertex.position = p5;
    vertex.uv = uv2;
    vertices.emplace_back(vertex);

    vertex.position = p6;
    vertex.uv = uv1;
    vertices.emplace_back(vertex);

    vertex.position = p6;
    vertex.uv = uv1;
    vertices.emplace_back(vertex);
    
    vertex.position = p7;
    vertex.uv = uv0;
    vertices.emplace_back(vertex);

    vertex.position = p4;
    vertex.uv = uv3;
    vertices.emplace_back(vertex);

    //Left
    vertex.normal = Vector3f::left;
    vertex.tangent = Vector3f::backward;

    vertex.position = p3;
    vertex.uv = uv1;
    vertices.emplace_back(vertex);

    vertex.position = p0;
    vertex.uv = uv0;
    vertices.emplace_back(vertex);

    vertex.position = p4;
    vertex.uv = uv3;
    vertices.emplace_back(vertex);

    vertex.position = p4;
    vertex.uv = uv3;
    vertices.emplace_back(vertex);
    
    vertex.position = p7;
    vertex.uv = uv2;
    vertices.emplace_back(vertex);

    vertex.position = p3;
    vertex.uv = uv1;
    vertices.emplace_back(vertex);

    //Right
    vertex.normal = Vector3f::right;
    vertex.tangent = Vector3f::forward;

    vertex.position = p1;
    vertex.uv = uv1;
    vertices.emplace_back(vertex);

    vertex.position = p2;
    vertex.uv = uv0;
    vertices.emplace_back(vertex);

    vertex.position = p6;
    vertex.uv = uv3;
    vertices.emplace_back(vertex);

    vertex.position = p6;
    vertex.uv = uv3;
    vertices.emplace_back(vertex);
    
    vertex.position = p5;
    vertex.uv = uv2;
    vertices.emplace_back(vertex);

    vertex.position = p1;
    vertex.uv = uv1;
    vertices.emplace_back(vertex);

    //Backward
    vertex.normal = Vector3f::backward;
    vertex.tangent = Vector3f::right;

    vertex.position = p2;
    vertex.uv = uv1;
    vertices.emplace_back(vertex);

    vertex.position = p3;
    vertex.uv = uv0;
    vertices.emplace_back(vertex);

    vertex.position = p7;
    vertex.uv = uv3;
    vertices.emplace_back(vertex);

    vertex.position = p7;
    vertex.uv = uv3;
    vertices.emplace_back(vertex);
    
    vertex.position = p6;
    vertex.uv = uv2;
    vertices.emplace_back(vertex);

    vertex.position = p2;
    vertex.uv = uv1;
    vertices.emplace_back(vertex);

    //Forward
    vertex.normal = Vector3f::forward;
    vertex.tangent = Vector3f::left;

    vertex.position = p0;
    vertex.uv = uv1;
    vertices.emplace_back(vertex);

    vertex.position = p1;
    vertex.uv = uv0;
    vertices.emplace_back(vertex);

    vertex.position = p5;
    vertex.uv = uv3;
    vertices.emplace_back(vertex);

    vertex.position = p5;
    vertex.uv = uv3;
    vertices.emplace_back(vertex);
    
    vertex.position = p4;
    vertex.uv = uv2;
    vertices.emplace_back(vertex);

    vertex.position = p0;
    vertex.uv = uv1;
    vertices.emplace_back(vertex);

    return vertices;
}