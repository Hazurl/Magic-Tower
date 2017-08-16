#include <Components/Renderer/Renderer.h>

std::map<haz::IDable::ID_t, Renderer*> Renderer::renderers = {}; 

Renderer::Renderer() : haz::IDable() {

}

Renderer::~Renderer() {
    
}

void Renderer::enable() {
   Renderer::_enable(this->id, this);
}

void Renderer::disable() {
    Renderer::_disable(this->id);
}

void Renderer::_enable(haz::IDable::ID_t id, Renderer* r) {
    renderers.insert({ id, r });
}

void Renderer::_disable(haz::IDable::ID_t id) {
    renderers.erase(id);
}

std::vector<Renderer*> Renderer::getRenderers() {
    std::vector<Renderer*> rends = {};
    for (auto& p : Renderer::renderers) {
        rends.push_back(p.second);
    }

    return rends;
}
