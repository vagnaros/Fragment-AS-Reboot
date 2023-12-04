#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();

    //Loads image at specified path
    bool loadFromFile(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
    //Creates image from font string
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    //Set blending
    void setBlendMode(SDL_BlendMode blending);

    //Set alpha modulation
    void setAlpha(Uint8 alpha);

    //Renders texture at given point
    void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

//GUI Surfaces Constants
enum GUISpritesSheets
{
    GUI_SS_THEWORLD,
    GUI_SS_MAILER,
    GUI_SS_NEWS,
    GUI_SS_ACCESSORY,
    GUI_SS_AUDIO,
    GUI_SS_DATA,
    GUI_SS_TOTAL
};

enum GUIButtonStates
{
    BUTTON_MOUSE_OUT = 0,
    BUTTON_MOUSE_OVER_MOTION = 1,
    BUTTON_MOUSE_DOWN = 2,
    BUTTON_MOUSE_UP = 3,
    BUTTON_TOTAL = 4
};

//The mouse button
class LButton
{
public:
    //Initializes internal variables
    LButton();

    //Sets top left position
    void setPosition(int x, int y);

    //Handles mouse event
    void handleEvent(SDL_Event* e);

    //Shows button sprite
    void render();

private:
    //Top left position
    SDL_Point mPosition;

    //Currently used global sprite
    GUIButtonStates mCurrentState;
};