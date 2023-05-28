#include "MessageHandler.h"

void MessageHandler::handleMessage(std::string msg) {
    ModeParameters param;
    try
    {
        nlohmann::json json = nlohmann::json::parse(msg);
        std::string mode = json[ModeConstants::KEY_GENERAL_MODE_NAME];

        if(mode.compare(ModeConstants::MODE_PAINT) == 0) {
            if (json.find(ModeConstants::KEY_GENERAL_SET_PIXEL) != json.end()) {
                nlohmann::json jobj_pixel = json[ModeConstants::KEY_GENERAL_SET_PIXEL];
                // std::cout << "Parsed: " << jobj_pixel["x"] << " " << jobj_pixel["y"] << " " << jobj_pixel["color"] << std::endl;
                LedMatrix::getInstance()->setPixel(jobj_pixel["x"], jobj_pixel["y"], Color::fromHex(jobj_pixel["color"]));
            } else if (json.find(ModeConstants::KEY_GENERAL_FILL_MATRIX) != json.end()) {
                nlohmann::json jobj_fill = json[ModeConstants::KEY_GENERAL_FILL_MATRIX];
                // std::cout << "Parsed: " << jobj_fill << std::endl;
                LedMatrix::getInstance()->fill(Color::fromHex(jobj_fill));
            }
        } else if (mode.compare(ModeConstants::MODE_SPOTIFY) == 0) {
            if (json.find(ModeConstants::KEY_SPOTIFY_TOKEN) != json.end()) {
                nlohmann::json jobj_token = json[ModeConstants::KEY_SPOTIFY_TOKEN];
                std::cout << "Parsed: " << jobj_token << std::endl;
            }
        } else if (mode.compare(ModeConstants::MODE_GAME_OF_LIFE) == 0) {
            if (mModeManager.getActiveMode() != MODE::GAME_OF_LIFE) mModeManager.startMode(MODE::GAME_OF_LIFE);
            if (json.find(ModeConstants::KEY_GAME_OF_LIFE_MODE_ACTION) != json.end()) {
                param.first = ModeConstants::KEY_GAME_OF_LIFE_MODE_ACTION;
                param.second = json[ModeConstants::KEY_GAME_OF_LIFE_MODE_ACTION];
            } else if (json.find(ModeConstants::KEY_GAME_OF_LIFE_MODE_COLOR_ALIVE) != json.end()) {
                nlohmann::json colorAlive = json[ModeConstants::KEY_GAME_OF_LIFE_MODE_COLOR_ALIVE];
                param.first = ModeConstants::KEY_GAME_OF_LIFE_MODE_COLOR_ALIVE;
                param.second = colorAlive;
            } else if (json.find(ModeConstants::KEY_GAME_OF_LIFE_MODE_COLOR_DEAD) != json.end()) {
                nlohmann::json colorDead = json[ModeConstants::KEY_GAME_OF_LIFE_MODE_COLOR_DEAD];
                param.first = ModeConstants::KEY_GAME_OF_LIFE_MODE_COLOR_DEAD;
                param.second = colorDead;
            } else if (json.find(ModeConstants::KEY_GAME_OF_LIFE_MODE_RULE_BIRTH) != json.end()) {
                nlohmann::json rule = json[ModeConstants::KEY_GAME_OF_LIFE_MODE_RULE_BIRTH];
                param.first = ModeConstants::KEY_GAME_OF_LIFE_MODE_RULE_BIRTH;
                param.second = rule;
            } else if (json.find(ModeConstants::KEY_GAME_OF_LIFE_MODE_RULE_SURVIVE) != json.end()) {
                nlohmann::json rule = json[ModeConstants::KEY_GAME_OF_LIFE_MODE_RULE_SURVIVE];
                param.first = ModeConstants::KEY_GAME_OF_LIFE_MODE_RULE_SURVIVE;
                param.second = rule;
            } else if (json.find(ModeConstants::KEY_GAME_OF_LIFE_MODE_SPEED) != json.end()) {
                nlohmann::json speed = json[ModeConstants::KEY_GAME_OF_LIFE_MODE_SPEED];
                param.first = ModeConstants::KEY_GAME_OF_LIFE_MODE_SPEED;
                param.second = speed;
            }
        } else if (mode.compare(ModeConstants::MODE_IMAGE) == 0) {
            if (json.find(ModeConstants::KEY_GENERAL_SET_PIXEL) != json.end()) {
                nlohmann::json jobj_pixel = json[ModeConstants::KEY_GENERAL_SET_PIXEL];
                // std::cout << "Parsed: " << jobj_pixel["x"] << " " << jobj_pixel["y"] << " " << jobj_pixel["color"] << std::endl;
                LedMatrix::getInstance()->setPixel(jobj_pixel["x"], jobj_pixel["y"], Color::fromHex(jobj_pixel["color"]));
            }
        } else if (mode.compare(ModeConstants::MODE_SNAKE) == 0) {

        } else if (mode.compare(ModeConstants::MODE_CUSTOM) == 0) {
            std::string script = json[ModeConstants::KEY_CUSTOM_SCRIPT];
            // std::cout << "Parsed: " << script << std::endl;
            LuaWrapper::getInstance().doString(script);
        }
        mModeManager.updateParameters(param);
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        std::cout << "Can't process: " + msg << std::endl;
    }
}