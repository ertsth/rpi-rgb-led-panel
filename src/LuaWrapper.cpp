#include "LuaWrapper.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

int __fill(lua_State *L) {
    // Get the number of parameters
    // int n = lua_gettop(L);
    // TODO: assert n = 3

    int r = lua_tointeger(L, 1);
    int g = lua_tointeger(L, 2);
    int b = lua_tointeger(L, 3);

    LuaWrapper::getInstance().fill(r, g, b);

    return 0;
}

int __setPixel(lua_State *L) {
    // Get the number of parameters
    // int n = lua_gettop(L);
    // TODO: assert n = 5
    int x = lua_tointeger(L, 1);
    int y = lua_tointeger(L, 2);
    int r = lua_tointeger(L, 3);
    int g = lua_tointeger(L, 4);
    int b = lua_tointeger(L, 5);

    LuaWrapper::getInstance().setPixel(x, y, r, g, b);

    return 0;
}

int __clear(lua_State *L) {
    // Get the number of parameters
    // int n = lua_gettop(L);
    // TODO: assert n = 0

    LuaWrapper::getInstance().clear();

    return 0;
}

LuaWrapper::LuaWrapper() {
    // initialize Lua interpreter
    this->L = luaL_newstate();

    // load Lua base libraries (print / math / etc)
    luaL_openlibs(this->L);

    // register C++ API to call from lua
    lua_register(this->L, "matrix_fill", __fill);
    lua_register(this->L, "matrix_set_pixel", __setPixel);
    lua_register(this->L, "matrix_clear", __clear);
}

void LuaWrapper::fill(int r, int g, int b) {
    this->matrix->fill(*(new Color(r, g, b)));
}

void LuaWrapper::setPixel(int x, int y, int r, int g, int b) {
    this->matrix->setPixel(x, y, *(new Color(r, g, b)));
}

void LuaWrapper::clear() {
    this->matrix->clear();
}

LuaWrapper::~LuaWrapper() {
    // Cleanup:  Deallocate all space assocatated with the lua state */
    lua_close(this->L);
}

LuaWrapper& LuaWrapper::getInstance() {
    static LuaWrapper instance;
    return instance;
}

void LuaWrapper::doFile(std::string name) {
    luaL_dofile(this->L, name.c_str());
}