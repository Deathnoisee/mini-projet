#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>


SDL_bool AddRandomNumber (int matrix[4][4] )
{
/*  1st - check the given matrix for 0 / return true if theres 0 or 1 if theres none
    2nd - create new list with the position on the 0 in the first list
    3rd - create new matrix with the old values of the first matrix
    4th - put random 2 or 4 in the 0 given from the list in 2nd step
    5th - return the new matrix / or other approach need to be checked, return the first matrix */
    int i, j, k = 0, random_cell1, random_cell2;
    typedef struct {
        int row;
        int columns;
    }poz;
    poz listofpos[16];
    for ( i = 0; i < 4; i++)
    {
        for ( j = 0; j < 4; j++)
        {
            if (matrix[i][j] == 0)
            {
                listofpos[k].row = i;
                listofpos[k].columns=j;
                k++;
            }
        }
    }
    if (k == 0){
        return SDL_FALSE;
    }
    // srand(time(null)) inside the code not the function for random seeds
    random_cell1 = rand() % k;
    int x = listofpos[random_cell1].row;
    int y = listofpos[random_cell1].columns;
    matrix[x][y]= (rand() % 10 == 0) ? 4 : 2;
    if (k > 1) 
    {
       do
       {
        random_cell2 = rand() % k;
       } while (random_cell1 == random_cell2);
       x = listofpos[random_cell2].row;
       y = listofpos[random_cell2].columns;
       matrix[x][y]= (rand() % 10 == 0) ? 4 : 2;
    }
    return SDL_TRUE;

}


int main (int argc, char *argv[])
{

SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Arrow Key Detection", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;
    srand(time(NULL));





    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;




}