//Declare Global Preprocessors (Means the Carries over when this doc is used as local preproccessor)
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "ClassWrapper.h"
#include "GUIFunctions.h"

//Screen dimension constants
const int scrWidth = 800;
const int scrHeight = 600;

//Create SDL Rectangle Containers for GUI Elements
SDL_Rect serverBttn;
SDL_Rect mapEditBttn;
SDL_Rect settingsBttn;
SDL_Rect exitBttn;

//Create SDL Pointers/Containers
SDL_Window* gWindow = NULL;		//The window we'll be rendering to
SDL_Renderer* gRenderer = NULL;     //The Renderer We'll Be Using

//Declare Function Prototypes
bool init();		//Starts up SDL and creates window
bool loadMedia();	//Loads media
void close();		//Frees media and shuts down SDL

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}
LTexture::~LTexture()
{
    //Deallocate
    free();
}

LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;

    mCurrentState = BUTTON_MOUSE_OUT;
}

//Button constants
const int BUTTON_WIDTH = 96;
const int BUTTON_HEIGHT = 96;
const int TOTAL_BUTTONS = 6;

//Globally used font
TTF_Font* gFont = NULL;

//Rendered texture
LTexture gTextTextures[GUI_SS_TOTAL];
LTexture gGUIButtonStatesTexture;

//Scene textures
LTexture gGUITextures[GUI_SS_TOTAL];
LTexture gBackgroundTexture;

//GUI animation
const int GUI_ANIMATION_FRAMES = 96;
SDL_Rect gSpriteClips[GUI_ANIMATION_FRAMES];
SDL_Rect gStateClips[BUTTON_TOTAL];

//Buttons objects
LButton gGUIButtons[TOTAL_BUTTONS];

void LButton::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}
void LButton::handleEvent(SDL_Event* e, int gGUIButton)
{
    //Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    //Check if mouse is in button
    bool inside = true;

    //Mouse Location Logic (inside or outside?)
    if (x < mPosition.x)
    {
        inside = false;
    }
    else if (x > mPosition.x + BUTTON_WIDTH)
    {
        inside = false;
    }
    else if (y < mPosition.y)
    {
        inside = false;
    }
    else if (y > mPosition.y + BUTTON_HEIGHT)
    {
        inside = false;
    }

    //Mouse is outside button
    if (!inside)
    {
       mCurrentState = BUTTON_MOUSE_OUT;
    }
    //Mouse is inside button
    else
    {
        //Set mouse over sprite
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            mCurrentState = BUTTON_MOUSE_OVER_MOTION;
            break;
        case SDL_MOUSEBUTTONUP:
            //-> ON CLICK LOGIC HERE
            if (gGUIButton == GUI_SS_THEWORLD) { serverBttnClicked(); break; }
            if(gGUIButton == GUI_SS_MAILER)     { announcerBttnClicked(); break; }
            if(gGUIButton == GUI_SS_NEWS)       { eventBttnClicked(); break; }
            if(gGUIButton == GUI_SS_ACCESSORY)  { areasBttnClicked(); break; }
            if(gGUIButton == GUI_SS_AUDIO)      { adminBttnClicked(); break; }
            if(gGUIButton == GUI_SS_DATA)       { meshnetBttnClicked(); break; }
            break;
        }
    }
}
void LButton::render()
{
    //Show current button sprite
    gGUIButtonStatesTexture.render(mPosition.x, mPosition.y, &gStateClips[mCurrentState], 0.0, NULL, SDL_FLIP_NONE);
}

bool LTexture::loadFromFile(std::string path)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 181, 230, 29));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    //Return success
    return mTexture != NULL;
}
#endif

void LTexture::free()
{
    //Free texture if it exists
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
void LTexture::render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}
int LTexture::getWidth()
{
    return mWidth;
}
int LTexture::getHeight()
{
    return mHeight;
}

//Define Functions
bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {

        //Create window
        gWindow = SDL_CreateWindow("TheWorld - Server",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            scrWidth, scrHeight, SDL_WINDOW_SHOWN);
        if (gWindow == NULL){
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {

            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL){
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {

                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize WEBP loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)){
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                } else {

                    //Create Position and Scale GUI Elements Rects
                    serverBttn.x = 0; serverBttn.y = 0;
                    serverBttn.w = 80; serverBttn.h = 80;

                    mapEditBttn.x = 0; mapEditBttn.y = 100;
                    mapEditBttn.w = 80; mapEditBttn.h = 80;

                    settingsBttn.x = 0; settingsBttn.y = 200;
                    settingsBttn.w = 80; settingsBttn.h = 80;

                    exitBttn.x = 0; exitBttn.y = 300;
                    exitBttn.w = 80; exitBttn.h = 80;

                    //Initialize SDL_ttf
                    if (TTF_Init() == -1)
                    {
                        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                        success = false;
                    }
                }
            }
        }
    }

    return success;
}
bool loadMedia() {
    //Loading success flag
    bool success = true;

    //Load splash image
    if (!gBackgroundTexture.loadFromFile("media/bgImage.png"))
    {
        printf("Unable to load image %s! SDL Error: %s\n", "media/bgImage.png", SDL_GetError());
        success = false;
    }

    if (!gGUITextures[GUI_SS_THEWORLD].loadFromFile("media/GUI/TheWorldSS.png")) {
        printf("Unable to load image %s! SDL Error: %s\n", "media/GUI/TheWorldSS.png", SDL_GetError());
        success = false;
    }
    if (!gGUITextures[GUI_SS_MAILER].loadFromFile("media/GUI/MailerSS.png")) {
        printf("Unable to load image %s! SDL Error: %s\n", "media/GUI/MailerSS.png", SDL_GetError());
        success = false;
    }
    if (!gGUITextures[GUI_SS_NEWS].loadFromFile("media/GUI/NewsSS.png")) {
        printf("Unable to load image %s! SDL Error: %s\n", "media/GUI/NewsSS.png", SDL_GetError());
        success = false;
    }
    if (!gGUITextures[GUI_SS_ACCESSORY].loadFromFile("media/GUI/AccessorySS.png")) {
        printf("Unable to load image %s! SDL Error: %s\n", "media/GUI/AccessorySS.png", SDL_GetError());
        success = false;
    }
    if (!gGUITextures[GUI_SS_AUDIO].loadFromFile("media/GUI/AudioSS.png")) {
        printf("Unable to load image %s! SDL Error: %s\n", "media/GUI/AudioSS.png", SDL_GetError());
        success = false;
    }
    if (!gGUITextures[GUI_SS_DATA].loadFromFile("media/GUI/DataSS.png")) {
        printf("Unable to load image %s! SDL Error: %s\n", "media/GUI/DataSS.png", SDL_GetError());
        success = false;
    }

    //Iterate through the 96 array items
    for (int i = 0; i < 96; i++) {
        //Set sprite clips
        gSpriteClips[i].x = 96 * i; //Increments at 96px starting with 0 (96 * 0)
        gSpriteClips[i].y = 0;
        gSpriteClips[i].w = 96;
        gSpriteClips[i].h = 96;
    }

    //Open the font
    gFont = TTF_OpenFont("media/GUI/font.ttf", 18);
    if (gFont == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 3, 157, 252 };
        if (!gTextTextures[GUI_SS_THEWORLD].loadFromRenderedText("Server", textColor))
        {
            printf("Failed to render text texture!\n");
            success = false;
        }
        if (!gTextTextures[GUI_SS_MAILER].loadFromRenderedText("Announcer", textColor)) {
            printf("Failed to render text texture!\n");
            success = false;
        }
        if (!gTextTextures[GUI_SS_NEWS].loadFromRenderedText("Events", textColor)) {
            printf("Failed to render text texture!\n");
            success = false;
        }
        if (!gTextTextures[GUI_SS_ACCESSORY].loadFromRenderedText("Areas", textColor)) {
            printf("Failed to render text texture!\n");
            success = false;
        }
        if (!gTextTextures[GUI_SS_AUDIO].loadFromRenderedText("Admin", textColor)) {
            printf("Failed to render text texture!\n");
            success = false;
        }
        if (!gTextTextures[GUI_SS_DATA].loadFromRenderedText("MeshNet", textColor)) {
            printf("Failed to render text texture!\n");
            success = false;
        }
    }

    //Load sprites
    if (!gGUIButtonStatesTexture.loadFromFile("media/GUI/ButtonStates.png"))
    {
        printf("Failed to load button state texture!\n");
        success = false;
    }
    else
    {
        //Set sprites
        for (int i = 0; i < BUTTON_TOTAL; ++i)
        {
            gStateClips[i].x = 96 * i;
            gStateClips[i].y = 0;
            gStateClips[i].w = BUTTON_WIDTH;
            gStateClips[i].h = BUTTON_HEIGHT;
        }

        //Set buttons positions
        for (int i = 0; i < TOTAL_BUTTONS; i++) {
            gGUIButtons[i].setPosition(0, 100 * i);
        }
    }

    return success;
}
void close() {
    //Free loaded images
    gGUITextures[GUI_SS_THEWORLD, GUI_SS_MAILER, GUI_SS_NEWS, GUI_SS_ACCESSORY, GUI_SS_AUDIO, GUI_SS_DATA].free();
    gBackgroundTexture.free();
    gTextTextures[GUI_SS_THEWORLD, GUI_SS_MAILER, GUI_SS_NEWS, GUI_SS_ACCESSORY, GUI_SS_AUDIO, GUI_SS_DATA].free();

    //Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
