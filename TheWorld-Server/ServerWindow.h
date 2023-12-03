//Declare Preprocessors
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int scrWidth = 800;
const int scrHeight = 600;

//GUI Surfaces Constants
enum GUISurfaces
{
    GUI_SURFACE_SERVER,
    GUI_SURFACE_MAPEDIT,
    GUI_SURFACE_SETTINGS,
    GUI_SURFACE_EXIT,
    GUI_SURFACE_TOTAL
};

//Create SDL Rectangle Containers for GUI Elements
SDL_Rect serverBttn;
SDL_Rect mapEditBttn;
SDL_Rect settingsBttn;
SDL_Rect exitBttn;

//Create SDL Pointers/Containers
SDL_Window*  gWindow = NULL;		//The window we'll be rendering to
SDL_Surface* gScreenSurface = NULL; //The surface contained by the window
SDL_Surface* gBackground = NULL;        	    //The image we will load and show on the screen
SDL_Surface* gGUISurfaces[GUI_SURFACE_TOTAL];   //The images that correspond to a keypress
SDL_Surface* loadSurface(std::string path)      //Loads Individual Images
{
    //The final optimized image
    SDL_Surface* optimizedSurface = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if (optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

//Declare Function Prototypes
bool init();		//Starts up SDL and creates window
bool loadMedia();	//Loads media
void close();		//Frees media and shuts down SDL

//Define Functions
bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("TheWorld - Server",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            scrWidth, scrHeight, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
            }
            else
            {
                //Get window surface
                gScreenSurface = SDL_GetWindowSurface(gWindow);

                //Create Position and Scale GUI Elements Rects
                serverBttn.x = 0; serverBttn.y = 0;
                serverBttn.w = 80; serverBttn.h = 80;

                mapEditBttn.x = 0; mapEditBttn.y = 100;
                mapEditBttn.w = 80; mapEditBttn.h = 80;

                settingsBttn.x = 0; settingsBttn.y = 200;
                settingsBttn.w = 80; settingsBttn.h = 80;

                exitBttn.x = 0; exitBttn.y = 300;
                exitBttn.w = 80; exitBttn.h = 80;
            }
        }
    }

    return success;
}
bool loadMedia() {
    //Loading success flag
    bool success = true;

    //Load splash image
    gBackground = loadSurface("media/bgImage.webp");
    if (gBackground == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "media/bgImage.webp", SDL_GetError());
        success = false;
    }

    gGUISurfaces[GUI_SURFACE_SERVER] = loadSurface("media/GUI/server.png");
    if (gGUISurfaces[GUI_SURFACE_SERVER] == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "media/GUI/server.png", SDL_GetError());
        success = false;
    }

    gGUISurfaces[GUI_SURFACE_MAPEDIT] = loadSurface("media/GUI/map.png");
    if (gGUISurfaces[GUI_SURFACE_MAPEDIT] == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "media/GUI/map.png", SDL_GetError());
        success = false;
    }

    gGUISurfaces[GUI_SURFACE_SETTINGS] = loadSurface("media/GUI/settings.png");
    if (gGUISurfaces[GUI_SURFACE_SETTINGS] == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "media/GUI/settings.png", SDL_GetError());
        success = false;
    }

    gGUISurfaces[GUI_SURFACE_EXIT] = loadSurface("media/GUI/exit.png");
    if (gGUISurfaces[GUI_SURFACE_EXIT] == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "media/GUI/exit.png", SDL_GetError());
        success = false;
    }

    return success;
}
void close() {
    //Deallocate surface
    SDL_FreeSurface(gBackground);
    gBackground = NULL;
    SDL_FreeSurface(gGUISurfaces[GUI_SURFACE_SERVER, GUI_SURFACE_MAPEDIT, GUI_SURFACE_SETTINGS, GUI_SURFACE_EXIT]);
    gGUISurfaces[GUI_SURFACE_SERVER] = NULL;
    gGUISurfaces[GUI_SURFACE_MAPEDIT] = NULL;
    gGUISurfaces[GUI_SURFACE_SETTINGS] = NULL;
    gGUISurfaces[GUI_SURFACE_EXIT]      = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
