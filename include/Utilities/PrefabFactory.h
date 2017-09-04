#ifndef __HAZ_PREFABFACTORY
#define __HAZ_PREFABFACTORY

#include <frameworkHaz/2DGOInclude.hpp>
#include <frameworkHaz/Interface/Factory.hpp>

enum class PrefabType {
    Hex
};

class PrefabFactory {
    typedef haz::Factory<haz::GameObject, PrefabType, haz::GameObject::CopyAllocator> Fact;
    
public:

    static haz::GameObject* createObject(PrefabType const& key, haz::GameObject* parent = nullptr);
        
private:

    static void Init();

    static bool init;
};

#endif
