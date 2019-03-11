#pragma once

#include <Core/System/System.hpp>

class CustomSystem : public ax::System
{
public:
    static const std::string name;

    void setSpawnTransform(ax::TransformComponent* transform)
    {
        m_spawn = transform;
    }

    void onStart() override
    {
        spawnButton = &ax::Engine::input().addButton("test");
        spawnButton->bind(ax::Keyboard::C);

        ax::MaterialParameters lightMaterialParameters;
        lightMaterialParameters.shader = "light_emission";
        ax::AssetReference<ax::Material> m = ax::Engine::assets().material.loadFromMemory("light_emission_material", lightMaterialParameters);

        m_pointlights.reserve(MAX_X * MAX_Y);
        for(int x = 0; x < MAX_X; x++)
        {
            for(int y = 0; y < MAX_Y; y++)
            {
                ax::Entity& pointLight = ax::Engine::world().entities().create();
                ax::TransformComponent* lightTransform = &pointLight.addComponent<ax::TransformComponent>();
                lightTransform->setTranslation(0.0f + x * 5.0f, 0.2f, 50.0f + y * 5.0f);
                m_pointlights.emplace_back(lightTransform);
                pointLight.addComponent<ax::PointLightComponent>(pointLight).setRadius(5.0f);
                pointLight.addComponent<ax::UVSphereComponent>(pointLight, 0.2f).setMaterial(m);
            }
        }

        //Rotation light
        ax::Entity light = ax::Engine::world().entities().create();
        m_lightTransform = &light.addComponent<ax::TransformComponent>();
        light.addComponent<ax::PointLightComponent>(light).setRadius(5.0f);
        light.addComponent<ax::UVSphereComponent>(light, 0.2f, 20, 20).setMaterial(m);
    }

    void onUpdate() override
    {
        float delta = ax::Engine::context().getDeltaTime().asSeconds();
        m_time += delta;

        for(int x = 0; x < MAX_X; x++)
        {
            for(int y = 0; y < MAX_Y; y++)
            {
                ax::TransformComponent* component = m_pointlights.at(y * MAX_X + x);
                ax::Vector3f trans = component->getTranslation();
                trans.y = 1.2f + std::cos(m_time + x * y);
                component->setTranslation(trans);
            }
        }

        if(spawnButton->isJustPressed())
        {
            ax::Entity& light = ax::Engine::world().entities().create();
            light.addComponent<ax::TransformComponent>().setTranslation(m_spawn->getTranslation() + m_spawn->getForwardVector());
            light.addComponent<ax::PointLightComponent>(light).setRadius(10);
            light.addComponent<ax::UVSphereComponent>(light, 0.2f, 20, 20).setMaterial("light_emission_material"); 
        }

        ax::Vector3f lightPos;
        lightPos.x = std::cos(m_time);
        lightPos.z = std::sin(m_time);
        lightPos.y = 1.0f;
        m_lightTransform->setTranslation(lightPos);
    }

private:
    std::vector<ax::TransformComponent*> m_pointlights;
    int MAX_X = 10;
    int MAX_Y = 10;

    ax::TransformComponent* m_spawn;
    ax::Button* spawnButton;

    ax::TransformComponent* m_lightTransform;
    
    float m_time = 0.0f;
};

const std::string CustomSystem::name = "Custom";