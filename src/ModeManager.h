#ifndef MODE_MANAGER
#define MODE_MANAGER

#include "LuaWrapper.h"

class ModeManager {
public:
    ModeManager();
    ~ModeManager();

    enum MODE {
        HELLO,
        GAME_LIFE
    };

    void startMode(ModeManager::MODE mode);

private:

};

#endif // MODE_MANAGER
