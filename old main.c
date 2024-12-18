#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

int main(int argc, char *argv[])
{
    SDL_Renderer *render = NULL;
    SDL_Window *window = NULL;
    SDL_Texture* texture = NULL, *temp = NULL;
    SDL_Surface *surface = NULL, *windowsurface = NULL;
    SDL_Rect rect = {300, 300, 100, 100};
    SDL_Event event;
    SDL_bool quit = SDL_FALSE, mousetest = SDL_FALSE;
    SDL_bool continuer = SDL_TRUE;
    Uint8 *keyboard;
    int status = EXIT_FAILURE;


    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "ERROR SDL_Init: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 1024, SDL_WINDOW_SHOWN);
    if (NULL == window)
    {
        fprintf(stderr, "Couldn't create window: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == render)
    {
        fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    texture = SDL_CreateTexture(render,SDL_PIXELFORMAT_RGBA8888 , SDL_TEXTUREACCESS_STREAMING, 100, 100);
    if( NULL == texture)
    {
        fprintf (stderr, "error creating texture : %s", SDL_GetError());
        SDL_DestroyTexture(texture);
        SDL_Quit;
        return EXIT_FAILURE;
    }
    surface = SDL_CreateRGBSurface (0, 300, 200, 32, 0, 0, 0, 0);
    if ( NULL == surface)
    {
        fprintf (stderr, "couldnt create surface : %s", SDL_GetError());
        SDL_FreeSurface (surface);
        SDL_Quit;
        return EXIT_FAILURE;
    }
    
    
    surface = SDL_LoadBMP ("simple-start-screen-for-a-game-similar-to-2048.bmp");
    texture = SDL_CreateTextureFromSurface (render, surface);
    SDL_FreeSurface(surface);
    SDL_RenderCopy(render, texture, NULL, NULL);
    SDL_RenderPresent(render);
    
    while (!mousetest)
    {
        SDL_WaitEvent(&event);

        if (event.type == SDL_MOUSEBUTTONDOWN && (event.button.x > 400 && event.button.x < 620 && event.button.y > 410 && event.button.y < 600))
        {
            printf ("the game should start now\n");
            SDL_Delay(100);
            mousetest = SDL_TRUE;
        } else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_RETURN )
             {
                printf ("the game should start now\n");
                SDL_Delay(100);
                mousetest = SDL_TRUE;
             }   
    }
   

   
    while(!quit)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_QUIT){ quit = SDL_TRUE;}
    }
    status = EXIT_SUCCESS;
    if (NULL != texture) {SDL_DestroyTexture(texture);}
    if (NULL != render) {SDL_DestroyRenderer(render);}
    if (NULL != window) {SDL_DestroyWindow(window);}
    if (NULL != surface){SDL_FreeSurface(surface);}
    SDL_Quit();

    return status;
}
