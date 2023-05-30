#ifndef MODE_CONSTANTS
#define MODE_CONSTANTS

#include <string>

typedef std::pair<std::string,std::string> ModeParameters;

enum MODE {
    NONE = -1,
    PAINT,
    SPOTIFY,
    GAME_OF_LIFE,
    IMAGE,
    SNAKE,
    CUSTOM
};

class ModeConstants {
    public:
    // Modes
    const static char* MODE_PAINT;
    const static char* MODE_SPOTIFY;
    const static char* MODE_GAME_OF_LIFE;
    const static char* MODE_IMAGE;
    const static char* MODE_SNAKE;
    const static char* MODE_CUSTOM;

    // General commands
    const static char* KEY_GENERAL_MODE_NAME;
    const static char* KEY_GENERAL_SET_PIXEL;
    const static char* KEY_GENERAL_FILL_MATRIX;
    const static char* KEY_GENERAL_NEW_MODE;
    // Spotify mode
    const static char* KEY_SPOTIFY_TOKEN;
    // Game of life mode
    const static char* KEY_GAME_OF_LIFE_MODE_ACTION;
    const static char* KEY_GAME_OF_LIFE_MODE_COLOR_ALIVE;
    const static char* KEY_GAME_OF_LIFE_MODE_COLOR_DEAD;
    const static char* KEY_GAME_OF_LIFE_MODE_RULE_BIRTH;
    const static char* KEY_GAME_OF_LIFE_MODE_RULE_SURVIVE;
    const static char* KEY_GAME_OF_LIFE_MODE_SPEED;
    // Custom mode
    const static char* KEY_CUSTOM_SCRIPT;
    // Snake mode
    const static char* KEY_SNAKE_COLOR_FIELD;
    const static char* KEY_SNAKE_COLOR_SNAKE;
    const static char* KEY_SNAKE_COLOR_FOOD;
    const static char* KEY_SNAKE_DIRECTION;
    const static char* KEY_SNAKE_SPEED;
};

#endif // MODE_CONSTANTS
