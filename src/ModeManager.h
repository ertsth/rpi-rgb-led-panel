#ifndef MODE_MANAGER
#define MODE_MANAGER

#include "ModeConstants.h"
#include "IModeHandler.h"
#include "DummyHandler.h"
#include "GameOfLifeHandler.h"
#include <thread>

class GameOfLifeHandler;

class ModeManager {
public:
    ModeManager();
    ~ModeManager();

    void startMode(MODE mode);
    void updateParameters(ModeParameters parameters);
    MODE getActiveMode();

    class ExecuteThread {
        public:
        void operator()(ModeManager* mm);
    };

private:
    void startActiveModeExecution();
    std::unique_ptr<IModeHandler> mActiveMode;
    std::unique_ptr<std::thread> mExecute;
};

#endif // MODE_MANAGER
