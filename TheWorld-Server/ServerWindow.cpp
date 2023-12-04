#include "ServerWindow.h" // - Local Preprocessor (Using Interal Global Preprocessors)

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

            //Current animation frame
            int frame = 0;

            //Use Event loop to keep window open until window close event is manualy triggered by user
            SDL_Event e; bool quit = false;  while (quit == false) { while (SDL_PollEvent(&e) != 0) { if (e.type == SDL_QUIT) quit = true; } 
                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render background texture to screen
                gBackgroundTexture.render(0, 0);

                //Render current frame
                SDL_Rect* currentClip = &gSpriteClips[frame / 4]; //Speed can be controlled [frame / 96] etc

                //Render GUI Sprites to the screen
                gGUITextures[GUI_SS_THEWORLD].render(0, 0, currentClip);
                gTextTextures[GUI_SS_THEWORLD].render(20, 80); //TTF Text
                gGUITextures[GUI_SS_MAILER].render(0, 100, currentClip);
                gTextTextures[GUI_SS_MAILER].render(0, 180); //TTF Text
                gGUITextures[GUI_SS_NEWS].render(0, 200, currentClip);
                gTextTextures[GUI_SS_NEWS].render(20, 280); //TTF Text
                gGUITextures[GUI_SS_ACCESSORY].render(0, 300, currentClip);
                gTextTextures[GUI_SS_ACCESSORY].render(20, 380); //TTF Text
                gGUITextures[GUI_SS_AUDIO].render(0, 400, currentClip);
                gTextTextures[GUI_SS_AUDIO].render(20, 480); //TTF Text
                gGUITextures[GUI_SS_DATA].render(0, 500, currentClip);
                gTextTextures[GUI_SS_DATA].render(10, 580); //TTF Text

                //Update screen
                SDL_RenderPresent(gRenderer);

                //Go to next frame
                ++frame;

                //Cycle animation
                if (frame / 4 >= GUI_ANIMATION_FRAMES)
                {
                    frame = 0;
                }
            }
        }
    }

    //Free resources and close SDL
    close();

	return 0;
}