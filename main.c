#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_mixer.h.>

#define SIZE 4

 typedef struct {
    SDL_Texture *image2;
    SDL_Texture *image4;
    SDL_Texture *image8;
    SDL_Texture *image16;
    SDL_Texture *image32;
    SDL_Texture *image64;
    SDL_Texture *image128;
    SDL_Texture *image256;
    SDL_Texture *image512;
    SDL_Texture *image1024;
    SDL_Texture *image2048;
} IMAGES;

SDL_Texture* chosephoto(int numbr, IMAGES images)
{
    if (numbr == 2) {
        return images.image2; // Corrected to use . instead of ->
    } else if (numbr == 4) {
        return images.image4;
    } else if (numbr == 8) {
        return images.image8;
    } else if (numbr == 16) {
        return images.image16;
    } else if (numbr == 32) {
        return images.image32;
    } else if (numbr == 64){
        return images.image64;
    } else if (numbr == 128){
        return images.image128;
    } else if (numbr == 256) {
        return images.image256;
    } else if (numbr == 512) {
        return images.image512;
    } else if (numbr == 1024){
        return images.image1024;
    } else if (numbr == 2048){
        return images.image2048;
    }
}
void printimage(int i, int j, SDL_Renderer *renderer, IMAGES images, int matrix[SIZE][SIZE]) {
    SDL_Texture *image = chosephoto(matrix[i][j], images); // Corrected function call
    SDL_Rect imde = { 0, 0, 50, 100 };
    SDL_QueryTexture(image, NULL, NULL, &imde.w, &imde.h);
    SDL_Rect where = { (j * 200) + 114, (i * 200) + 195, 170, 170};
    SDL_RenderCopy(renderer, image, &imde, &where); // Corrected to use image instead of imageTexture
}
void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
SDL_bool AddRandomNumber (int matrix[SIZE][SIZE] )
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

    return SDL_TRUE;

}
void right(int matrix [SIZE][SIZE]) {

    int matrix2[SIZE][SIZE] = {0};  // Initialize matrix2 with zeroes
    int i, j, jj,jjj;;
    for (i = 0; i< SIZE; i++) {
        j = 3;
         jjj= 3;
        while (j >-1) {
            // Move 'i' to the next non-zero element
            while (j >-1 && matrix[i][j] == 0 ) {
                j--;
            }
            jj = j -1;
            // Find the next non-zero element
            while (jj >-1&& matrix[i][jj] == 0) {
                jj--;
            }
            if (j > -1 && jj > -1 ) { // Valid elements found
                if (matrix[i][j] == matrix[i][jj]) {
                    matrix2[i][jjj] = matrix[i][j] + matrix[i][jj];
                    jjj--;
                    j = jj -1 ;  // Move past the matched pair
                } else {
                    matrix2[i][jjj] = matrix[i][j];

                    jjj = jjj -1;
                    j = jj;  // Move to the next position
                }
            } else if (j>-1) {
                // Only one valid element left
                matrix2[i][jjj] = matrix[i][j];
                jjj--;
                j--; // Move past the current element
            }
        }
        // Fill remaining with zeroes
        while (jjj >= 0) {
            matrix2[i][jjj] = 0;
            jjj--;
        }
    }
memcpy(matrix, matrix2, sizeof(int) * SIZE * SIZE);
}
void left(int matrix [SIZE][SIZE]) {


    int matrix2[SIZE][SIZE] = {0};  // Initialize matrix2 with zeroes
    int i, j, jj,jjj
    ;

    for (i = 0; i< SIZE; i++) {
        j = 0;
         jjj= 0;
        while (j<4) {
            // Move 'i' to the previous non-zero element
            while (j <4 && matrix[i][j] == 0) {
                j++;
            }
            jj = j+ 1 ;
            // Find the previous non-zero element
            while (jj < 4 && matrix[i][jj] == 0) {
                jj++;
            }
            if (j < 4 && jj < 4) { // Valid elements found
                if (matrix[i][j] == matrix[i][jj]) {
                    matrix2[i][jjj] = matrix[i][j] + matrix[i][jj];
                    jjj++;
                    j = jj + 1;  // Move past the matched pair
                } else {
                    matrix2[i][jjj] = matrix[i][j];
                    jjj = jjj +1;
                    j = jj ;  // Move to the next position
                }
            } else if (j< 4) {
                // Only one valid element left
                matrix2[i][jjj] = matrix[i][j];
                jjj++;
                j ++; // Move past the current element
            }
        }
        // Fill remaining with zeroes
        while (jjj<3) {
            matrix2[i][jjj] = 0;
            jjj++;
        }
    }

    memcpy(matrix, matrix2, sizeof(int) * SIZE * SIZE);

}
void down(int matrix [SIZE][SIZE]) {
    int matrix2[SIZE][SIZE] = {0};  // Initialize matrix2 with zeroes
    int i, j, ii, iii;

    for (j = 0; j < SIZE; j++) {
        i =  3;
        iii = SIZE - 1;
        while (i > -1) {
            // Move 'i' to the next non-zero element
            while (i >-1 && matrix[i][j] == 0) {
                i--;
            }
            ii = i -1;
            // Find the next non-zero element
            while (ii > -1 && matrix[ii][j] == 0) {
                ii--;
            }
            if (i > -1 && ii > -1) { // Valid elements found
                if (matrix[i][j] == matrix[ii][j]) {
                    matrix2[iii][j] = matrix[i][j] + matrix[ii][j];
                    iii--;
                    i = ii-1 ;  // Move past the matched pair
                } else {
                    matrix2[iii][j] = matrix[i][j];
                    iii = iii - 1;
                    i = ii;  // Move to the next position
                }
            } else if (i > -1  ) {
                // Only one valid element left
                matrix2[iii][j] = matrix[i][j];
                iii--;
                i--; // Move past the current element
            }
        }
        // Fill remaining with zeroes
        while (iii >= 0) {
            matrix2[iii][j] = 0;
            iii--;
        }
    }

    memcpy(matrix, matrix2, sizeof(int) * SIZE * SIZE);

}
void up(int matrix[SIZE][SIZE]) {
    int matrix2[SIZE][SIZE] = {0};  // Initialize matrix2 with zeroes
    int i, j, ii, iii;

    for (j = 0; j < SIZE; j++) {  // Iterate over columns
        i = 0;
        iii = 0;
        while (i < SIZE) {
            // Move to the next non-zero element in the column
            while (i < SIZE && matrix[i][j] == 0) {
                i++;
            }
            ii = i + 1;
            // Find the next non-zero element below the current one
            while (ii < SIZE && matrix[ii][j] == 0) {
                ii++;
            }

            if (i < SIZE && ii < SIZE) {  // Valid elements found
                if (matrix[i][j] == matrix[ii][j]) {
                    // Merge matching tiles
                    matrix2[iii][j] = matrix[i][j] + matrix[ii][j];
                    iii++;
                    i = ii + 1;  // Move past the matched pair
                } else {
                    // Move current tile if no match
                    matrix2[iii][j] = matrix[i][j];
                    iii++;
                    i = ii;  // Move to the next non-zero position
                }
            } else if (i < SIZE) {
                // Only one valid element left in this column
                matrix2[iii][j] = matrix[i][j];
                iii++;
                i++;  // Move past the current element
            }
        }

        // Fill remaining spaces with zeroes
        while (iii < SIZE) {
            matrix2[iii][j] = 0;
            iii++;
        }
    }

    // Copy the result back into the original matrix
    memcpy(matrix, matrix2, sizeof(int) * SIZE * SIZE);
}
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filePath) {
    SDL_Surface* surface = SDL_LoadBMP(filePath);
    if (!surface) {
        fprintf(stderr, "SDL_LoadBMP Error (%s): %s\n", filePath, SDL_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error (%s): %s\n", filePath, SDL_GetError());
    }

    return texture;
}
void renderGame(int matrix[SIZE][SIZE], SDL_Renderer *renderer, IMAGES images) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] != 0) {
                printimage(i, j, renderer, images, matrix);
            }
        }
    }
    SDL_RenderPresent(renderer);
}
void handleMovement(int matrix[SIZE][SIZE], void (moveFunc)(int matrix[SIZE][SIZE]), SDL_Renderer *renderer, SDL_Texture *Solo, SDL_Rect backgroundRect, Mix_Chunk *buttonpress, SDL_bool *matrixnotfull) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, Solo, NULL, &backgroundRect);
    moveFunc(matrix);  // Call the specific movement function
    Mix_PlayChannel(1, buttonpress, 0);
    *matrixnotfull = AddRandomNumber(matrix);
    printMatrix(SIZE, SIZE, matrix);
    SDL_Delay(50);
}

int main(int argc, char *argv[]) 
{
    int matrix[SIZE][SIZE] = {0};
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) 
    {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    return -1;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) 
    {
    printf("SDL_mixer could not initialize audio! SDL_mixer Error: %s\n", Mix_GetError());
    return -1;
    }
    SDL_Window *window = SDL_CreateWindow("2048 G4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,  1000, 1000, SDL_WINDOW_SHOWN);
    if (!window) 
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) 
    {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    SDL_Surface* iconesurface = SDL_LoadBMP("photos/window icon.bmp");
    SDL_SetWindowIcon(window,iconesurface);
    SDL_FreeSurface(iconesurface);
    IMAGES images;
    images.image2 = loadTexture(renderer, "photos/2IMAGE.bmp");
    images.image4 = loadTexture(renderer, "photos/4IMAGE.bmp");
    images.image8 = loadTexture(renderer, "photos/8IMAGE.bmp");
    images.image16 = loadTexture(renderer, "photos/16IMAGE.bmp");
    images.image32 = loadTexture(renderer, "photos/32IMAGE.bmp");
    images.image64 = loadTexture(renderer, "photos/64IMAGE.bmp");
    images.image128 = loadTexture(renderer, "photos/128IMAGE.bmp");
    images.image256 = loadTexture(renderer, "photos/256IMAGE.bmp");
    images.image512 = loadTexture(renderer, "photos/512IMAGE.bmp");
    images.image1024 = loadTexture(renderer, "photos/1024IMAGE.bmp");
    images.image2048 = loadTexture(renderer, "photos/2048IMAGE.bmp");

    SDL_Texture* MainMenu = loadTexture(renderer, "photos/Main Menu.bmp");
    SDL_Texture* Solo = loadTexture(renderer, "photos/Solo.bmp");

    SDL_Rect backgroundRect = {0, 0, 1000, 1000}; 
    SDL_RenderCopy(renderer, MainMenu, NULL, &backgroundRect);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_bool quit = SDL_TRUE;
    SDL_bool matrixnotfull = AddRandomNumber(matrix);
    SDL_Event event;
    int sound = 0;
    srand(time(NULL));
    Mix_Music* titlemusic = Mix_LoadMUS("Sounds/Main menu.mp3");
    Mix_Chunk* buttonpress = Mix_LoadWAV("Sounds/ButtonClick.wav");
    SDL_Texture* mouseover = loadTexture(renderer,"photos/mouseover click.bmp");
    SDL_Texture* playVSmachine = loadTexture(renderer, "photos/PlayVSmachine.bmp");
    SDL_bool press_start = SDL_TRUE;
    Mix_PlayMusic(titlemusic, -1);
    SDL_bool isHovering = SDL_TRUE;
    while(quit && press_start)
    {
        while(SDL_WaitEvent(&event))
       {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = SDL_FALSE;
                press_start = SDL_FALSE;
                break;

            case SDL_MOUSEMOTION:
                if (event.motion.x > 350 && event.motion.y > 590 && event.motion.x < 650 && event.motion.y < 660) 
                {
                    if (!isHovering) 
                    {
                        isHovering = SDL_TRUE;
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, mouseover, NULL, &backgroundRect);
                        SDL_RenderPresent(renderer);
                    }
                }
                else 
                {
                    if (isHovering) 
                    {
                        isHovering = SDL_FALSE;
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, MainMenu, NULL, &backgroundRect);
                        SDL_RenderPresent(renderer);
                    }
                }   
                break;
            
            case SDL_MOUSEBUTTONDOWN :
                if (event.button.x > 350 && event.button.y > 590 && event.button.x < 650 && event.button.y < 660) 
                {
                    printf("The click worked \n");
                    matrixnotfull = AddRandomNumber(matrix);
                    SDL_RenderClear(renderer);
                    SDL_Texture* clickplayalone = loadTexture(renderer, "photos/after playalone click.bmp");
                    SDL_RenderCopy(renderer, clickplayalone, NULL, &backgroundRect);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(100);
                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, Solo, NULL, &backgroundRect);
                    for (int i = 0; i < SIZE; i++) 
                    {
                        for (int j = 0; j < SIZE; j++) 
                        {
                            if (matrix[i][j] != 0) 
                            {
                                printimage(i, j, renderer, images, matrix);
                            }
                        }
                    }
                    SDL_RenderPresent(renderer);
                    printMatrix(4, 4, matrix);
                    press_start = SDL_FALSE;
                    break;
                }
                else if (event.motion.x > 903 && event.motion.y > 54 && event.motion.x < 947 && event.motion.y < 90)
                {
                    if (sound == 0)
                    {
                    Mix_VolumeMusic(0);
                    sound = 1;
                    } else if (sound == 1)
                    {
                    Mix_VolumeMusic(MIX_MAX_VOLUME);

                    sound = 0;
                    }

                }
                break;

            case SDL_KEYDOWN : 
                switch (event.key.keysym.scancode) 
                {
                    case SDL_SCANCODE_DOWN:
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, playVSmachine, NULL, &backgroundRect);
                        SDL_RenderPresent(renderer);
                        break;

                    case SDL_SCANCODE_RETURN:
                        matrixnotfull = AddRandomNumber(matrix);
                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, Solo, NULL, &backgroundRect);
                        for (int i = 0; i < SIZE; i++) {
                            for (int j = 0; j < SIZE; j++) {
                                if (matrix[i][j] != 0) {
                                    printimage(i, j, renderer, images, matrix);
                                }
                            }
                        }
                        SDL_RenderPresent(renderer);
                        printMatrix(4, 4, matrix);
                        press_start = SDL_FALSE;
                        break;
                }
            default:
                break;
            }
            
            if (!quit || !press_start) break;
            
            
       }
    }
    while (quit && matrixnotfull) 
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                {
                    quit = SDL_FALSE;
                    matrixnotfull = SDL_FALSE;
                    break;
                }
            case SDL_KEYDOWN:
            {
                 switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                    printf("up arrow pressed \n");
                    handleMovement(matrix, up, renderer, Solo, backgroundRect, buttonpress, &matrixnotfull);
                    break;
                    }
                    case SDLK_DOWN:
                    {

                        printf("Down arrow pressed\n");
                        handleMovement(matrix, down, renderer, Solo, backgroundRect, buttonpress, &matrixnotfull);
                        break;
                    }
                    case SDLK_LEFT:
                    {

                        printf("Left arrow pressed\n");
                        handleMovement(matrix, left, renderer, Solo, backgroundRect, buttonpress, &matrixnotfull);
                        break;
                    }
                    case SDLK_RIGHT: 
                    {

                        printf("Right arrow pressed\n");
                        handleMovement(matrix, right, renderer, Solo, backgroundRect, buttonpress, &matrixnotfull);
                        break;
                    }
                    default:
                        break;
                } break;

                case SDL_MOUSEBUTTONDOWN: 
                {
                    if (event.motion.x > 903 && event.motion.y > 54 && event.motion.x < 947 && event.motion.y < 90)
                        {
                            if (sound == 0)
                            {
                                Mix_VolumeMusic(0);
                                sound = 1;
                                break;
                            } 
                                else if (sound == 1)
                                { 
                                    Mix_VolumeMusic(MIX_MAX_VOLUME);
                                    sound = 0;
                                    break;
                                }
                        }
                        break;
                }
                default:
                    break;
            
            }
        }
            renderGame(matrix, renderer, images);
        }
    } 
    

    Mix_FreeMusic(titlemusic);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
    
}