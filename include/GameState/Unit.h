#ifndef __UNIT
#define __UNIT

#include <SFML/Graphics.hpp>
#include <vector>

#include <Action/Action.h>
#include <Utilities/DebugMacro.h>

class Unit {
    GIVE_ACCESS_DEBUG()
public:
    Unit(const Hex* hex);
    virtual ~Unit();

    const Hex* getHex() const;
    void setHex(const Hex* h);
    std::vector<const Hex*> getPossibleActionHexes(Map const& map, unsigned int action) const;
    void doAction (Map const& map, unsigned int action, const Hex* hex);

protected:
    std::vector<Action*> actions = {};
    int movement_point = 1;

private:
    const Hex* hex;
};

#endif 