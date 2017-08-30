#ifndef __HAZ_PREFABFACTORY
#define __HAZ_PREFABFACTORY

#include <frameworkHaz/2DGOInclude.hpp>
#include <frameworkHaz/Interface/Factory.hpp>

enum class PrefabType {
    Hex
};

class PrefabFactory {
    typedef haz::Factory<haz::GameObject, PrefabType> Fact;
    
public:

    static haz::GameObject* createObject(PrefabType const& key, haz::GameObject* parent = nullptr);

    static void useEnvironement(haz::Environement* env);
        
private:

    static void Init();

    static haz::Environement* env;
    static bool init;
};

#endif
