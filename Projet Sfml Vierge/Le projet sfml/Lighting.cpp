#include "Lighting.h"

Lighting::Lighting(Player* _player)
{
    player = _player;
    if (!shader.loadFromFile("shader.frag", sf::Shader::Fragment))
    {
        std::cerr << "Failed to load shader" << std::endl;
    }
}

void Lighting::updateLighting()
{
    posLight.x = player->GetPos().x;
    posLight.y = player->GetPos().y;
    shader.setUniform("texture", sf::Shader::CurrentTexture);
    shader.setUniform("AmbientLight", sf::Glsl::Vec3(0.1f, 0.1f, 0.1f));
    shader.setUniform("LightPosition", posLight);
    shader.setUniform("LightColor", sf::Glsl::Vec3(0.4f, 0.4f, 0.4f));
    shader.setUniform("LightRadius", 200.0f);
    shader.setUniform("LightFalloff", 0.1f);
}
