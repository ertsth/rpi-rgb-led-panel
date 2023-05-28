#ifndef DUMMY_HANDLER
#define DUMMY_HANDLER

#include "ModeConstants.h"
#include "IModeHandler.h"
#include <iostream>

class DummyHandler : public IModeHandler {
public:
    void onInit();
    void onFinish();
    void execute();
    void updateParameters(ModeParameters parameters);
    MODE getModeName();

private:
};

#endif // DUMMY_HANDLER
