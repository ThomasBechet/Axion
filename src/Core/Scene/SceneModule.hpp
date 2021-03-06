#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/GameMode/GameModeManager.hpp>
#include <Core/Scene/UI/UIManager.hpp>
#include <Core/Scene/Entity/EntityManager.hpp>
#include <Core/Scene/Component/ComponentManager.hpp>
#include <Core/Scene/System/SystemManager.hpp>
#include <Core/Asset/Asset/Scene.hpp>
#include <Core/Asset/AssetReference.hpp>

#include <memory>

namespace ax
{
    class AXION_CORE_API SceneModule
    {
    public:    
        ComponentManager component;
        EntityManager entity;
        SystemManager system;
        UIManager ui;
        GameModeManager gamemode;

    public:
        void open(const std::string& scene) noexcept;
        void open(AssetReference<Scene> scene) noexcept;
    };
}