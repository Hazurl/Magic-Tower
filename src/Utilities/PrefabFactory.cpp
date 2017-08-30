#include <Utilities/PrefabFactory.h>

#include <Components/Data/Hex.h>
#include <Components/Renderer/Renderer.h>

#include <cmath>

haz::Environement* PrefabFactory::env = nullptr;
bool PrefabFactory::init = false;

void PrefabFactory::Init() {
    PrefabFactory::init = true;

    haz::GameObject* hex = new haz::GameObject("Hex");
    hex->addComponent<Hex>();
    hex->addComponent<Renderer>();
    float factor = sqrt(3) / 4;
    hex->addComponent<haz::_2D::PolygonCollider>(std::vector<haz::_2D::Vectorf>{{0, -0.5}, {factor, -0.25}, {factor, 0.25}, {0, 0.5}, {-factor, 0.25}, {-factor, -0.25}});
    hex->setActive(false);
    hex->setLayers(haz::Layers::Ground);

    Fact::registerObject(PrefabType::Hex, hex);
}

haz::GameObject* PrefabFactory::createObject(PrefabType const& key, haz::GameObject* parent) {
    if (!PrefabFactory::init)
        PrefabFactory::Init();

    haz::GameObject* go = env->instantiate(*Fact::original(key));
    go->setActive(true);

    if (parent != nullptr)
        go->parent(parent);

    return go;
}

void PrefabFactory::useEnvironement(haz::Environement* env) {
    PrefabFactory::env = env;
}