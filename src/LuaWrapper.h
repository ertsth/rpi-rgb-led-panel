#ifndef LUA_WRAPPER
#define LUA_WRAPPER

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include "LedMatrix.h"

#include <string>

class LuaWrapper {
public:
    static LuaWrapper& getInstance();

    void fill(int r, int g, int b);
    void setPixel(int x, int y, int r, int g, int b);
    void clear();

    void doFile(std::string name);

private:
    LuaWrapper();
    ~LuaWrapper();
    lua_State* L;
    std::unique_ptr<LedMatrix> matrix = std::make_unique<LedMatrix>();
};


#endif // LUA_WRAPPER
