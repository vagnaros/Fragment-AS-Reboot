#include "ServerWindow.h" // - Local Preprocessor
#include <SDL.h>		  // - Global Preprocessor

int main(int argc, char* args[]) {

    //Apply the image stretched
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = scrWidth;
    stretchRect.h = scrHeight;
    

    //Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        //Load media
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            //Apply the image
            SDL_BlitScaled(gBackground, NULL, gScreenSurface, &stretchRect);

            //Apply GUI Surfaces to Screen Surface as Rects
            SDL_BlitScaled(gGUISurfaces[GUI_SURFACE_SERVER], NULL, gScreenSurface, &serverBttn);
            SDL_BlitScaled(gGUISurfaces[GUI_SURFACE_MAPEDIT], NULL, gScreenSurface, &mapEditBttn);
            SDL_BlitScaled(gGUISurfaces[GUI_SURFACE_SETTINGS], NULL, gScreenSurface, &settingsBttn);
            SDL_BlitScaled(gGUISurfaces[GUI_SURFACE_EXIT], NULL, gScreenSurface, &exitBttn);
            
            //Update the surface
            SDL_UpdateWindowSurface(gWindow);
            
            //Use Event loop to keep window open until window close event is manualy triggered by user
            SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
        }
    }

    //Free resources and close SDL
    close();

	return 0;
}