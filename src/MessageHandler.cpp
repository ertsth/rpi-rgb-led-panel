#include "MessageHandler.h"

// Modes
const char* MessageHandler::MODE_PAINT = "PAINT";
const char* MessageHandler::MODE_SPOTIFY = "SPOTIFY";
const char* MessageHandler::MODE_GAME_OF_LIFE = "GAME_OF_LIFE";
const char* MessageHandler::MODE_IMAGE = "IMAGE";
const char* MessageHandler::MODE_SNAKE = "SNAKE";
const char* MessageHandler::MODE_CUSTOM = "CUSTOM";

// General commands
const char* MessageHandler::KEY_GENERAL_MODE_NAME = "name";
const char* MessageHandler::KEY_GENERAL_SET_PIXEL = "set_pixel";
const char* MessageHandler::KEY_GENERAL_FILL_MATRIX = "fill_matrix";
// Spotify mode
const char* MessageHandler::KEY_SPOTIFY_TOKEN = "token";
// Game of life mode
const char* MessageHandler::KEY_GAME_OF_LIFE_MODE_ACTION = "";
const char* MessageHandler::KEY_GAME_OF_LIFE_MODE_COLOR_ALIVE = "";
const char* MessageHandler::KEY_GAME_OF_LIFE_MODE_COLOR_DEAD = "";
const char* MessageHandler::KEY_GAME_OF_LIFE_MODE_RULE_BIRTH = "";
const char* MessageHandler::KEY_GAME_OF_LIFE_MODE_RULE_SURVIVE = "";
const char* MessageHandler::KEY_GAME_OF_LIFE_MODE_SPEED = "";
// Custom mode
const char* MessageHandler::KEY_CUSTOM_SCRIPT = "script";
// Snake mode
const char* MessageHandler::KEY_SNAKE_COLOR_BACKGROUND = "";
const char* MessageHandler::KEY_SNAKE_COLOR_SNAKE = "";
const char* MessageHandler::KEY_SNAKE_COLOR_FOOD = "";
const char* MessageHandler::KEY_SNAKE_DIRECTION = "";

void MessageHandler::handleMessage(std::string msg) {
    try
    {
        nlohmann::json json = nlohmann::json::parse(msg);

        std::string mode = json[KEY_GENERAL_MODE_NAME];
        std::cout << "Handling msg for mode: " << mode << std::endl;

        if(mode.compare(MODE_PAINT) == 0) {
            if (json.find(KEY_GENERAL_SET_PIXEL) != json.end()) {
                nlohmann::json jobj_pixel = json[KEY_GENERAL_SET_PIXEL];
                std::cout << "Parsed: " << jobj_pixel["x"] << " " << jobj_pixel["y"] << " " << jobj_pixel["color"] << std::endl;
                mMatrix.setPixel(jobj_pixel["x"], jobj_pixel["y"], Color::fromHex(jobj_pixel["color"]));
            } else if (json.find(KEY_GENERAL_FILL_MATRIX) != json.end()) {
                nlohmann::json jobj_fill = json[KEY_GENERAL_FILL_MATRIX];
                std::cout << "Parsed: " << jobj_fill << std::endl;
                mMatrix.fill(Color::fromHex(jobj_fill));
            }
        } else if (mode.compare(MODE_SPOTIFY) == 0) {
            if (json.find(KEY_SPOTIFY_TOKEN) != json.end()) {
                nlohmann::json jobj_token = json[KEY_SPOTIFY_TOKEN];
                std::cout << "Parsed: " << jobj_token << std::endl;

            }
        } else if (mode.compare(MODE_GAME_OF_LIFE) == 0) {

        } else if (mode.compare(MODE_IMAGE) == 0) {
            if (json.find(KEY_GENERAL_SET_PIXEL) != json.end()) {
                nlohmann::json jobj_pixel = json[KEY_GENERAL_SET_PIXEL];
                std::cout << "Parsed: " << jobj_pixel["x"] << " " << jobj_pixel["y"] << " " << jobj_pixel["color"] << std::endl;
                mMatrix.setPixel(jobj_pixel["x"], jobj_pixel["y"], Color::fromHex(jobj_pixel["color"]));
            }
        } else if (mode.compare(MODE_SNAKE) == 0) {

        } else if (mode.compare(MODE_CUSTOM) == 0) {
            std::string script = json[KEY_CUSTOM_SCRIPT];
            std::cout << "Parsed: " << script << std::endl;
            // std::ofstream file;
            // file.open("modes/custom.lua", std::ios_base::out);
            // file << script;
            LuaWrapper::getInstance().doString(script);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}