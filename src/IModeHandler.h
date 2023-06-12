#ifndef I_MODE_HANDLER
#define I_MODE_HANDLER

#include "ModeConstants.h"

class IModeHandler {
public:
    virtual void onInit() {};
    virtual void onFinish() {};
    virtual void execute() = 0;
    virtual void updateParameters(ModeParameters parameters) = 0;
    virtual MODE getModeName() = 0;
};

#endif // I_MODE_HANDLER
