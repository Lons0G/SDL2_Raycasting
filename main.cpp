#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>

#define WIDTH 800
#define HEIGHT 600
#define MAP_SIZE 24

int Map[MAP_SIZE][MAP_SIZE] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} 
};

int RED = 0;
int BLUE = 0;
int GREEN = 0;

int main(int argc, char *argv[]){

    double pos_x = 22;
    double pos_y = 12;
    double dir_x = -1;
    double dir_y = 0;
    double plane_x = 0;
    double plane_y = 0.66;
    double time = 0;
    double oldtime = 0;

    //Inicializa el SLD
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *Window = SDL_CreateWindow("SDL2 C++", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    
    if(Window == NULL){
        std::cout << "SDL Window Failed To Initialise " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *render = SDL_CreateRenderer(Window, -1, SDL_RENDERER_PRESENTVSYNC);

     if(render == NULL){
        std::cout << "SDL Render Failed To Initialise " << SDL_GetError() << std::endl;
        return 1;
    }else{std::cout << "SDL Render se inicio" << std::endl; }

    SDL_Event WindowEvent;

    while(true){

        SDL_SetRenderDrawColor(render, 50, 50, 50, 255);
        SDL_RenderClear(render);

        if (SDL_PollEvent(&WindowEvent)) {
            if(SDL_QUIT == WindowEvent.type){ break; }
        }

        for(int x = 0; x < WIDTH; x++){
            double camera_x = 2 * x / double(WIDTH) - 1;
            double ray_dir_x = dir_x + plane_x * camera_x;
            double ray_dir_y = dir_y + plane_y * camera_x;

            int map_x = int(pos_x);
            int map_y = int(pos_y);

            double side_dist_x;
            double side_dist_y;

            double delta_dist_x = std::abs(1 / ray_dir_x);
            double delta_dist_y = std::abs(1 / ray_dir_y);
            double perp_wall_dist;

            int step_x;
            int step_y;

            int hit = 0;
            int side;

            if(ray_dir_x < 0){
                step_x = -1;
                side_dist_x = (pos_x - map_x) * delta_dist_x;
            }else{
                step_x = 1;
                side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
            }
            if(ray_dir_y < 0){
                step_y = -1;
                side_dist_y = (pos_y - map_y) * delta_dist_y;
            }else{
                step_y = 1;
                side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
            }

            while (hit == 0) {
                if(side_dist_x < side_dist_y){
                    side_dist_x += delta_dist_x;
                    map_x += step_x;
                    side = 0;
                }else{
                    side_dist_y += delta_dist_y;
                    map_y += step_y;
                    side = 1;
                }
                if(Map[map_x][map_y] > 0){ hit = 1; }
            }

            if(side == 0) { perp_wall_dist = (side_dist_x - delta_dist_x); }
            else{ perp_wall_dist = (side_dist_y - delta_dist_y); }

            int line_height = (int)(HEIGHT / perp_wall_dist);

            int start_draw = -line_height / 2 + HEIGHT / 2;
            if(start_draw < 0){ start_draw = 0; }
            int end_draw = line_height / 2 + HEIGHT / 2;
            if(end_draw < 0){ end_draw = HEIGHT - 1; }\

            switch (Map[map_x][map_y]) {
            case 1:
                RED = 255;
                BLUE = 0;
                GREEN = 0;
                break;
            case 2:
                RED = 0;
                BLUE = 0;
                GREEN = 255;
                break;
            case 3:
                RED = 0;
                BLUE = 255;
                GREEN = 0;
                break;
            case 4:
                RED = 255;
                BLUE = 255;
                GREEN = 255;
                break;
            default:
                RED = 255;
                BLUE = 255;
                GREEN = 0;
                break;
            }

            if(side == 1){
                RED /= 2;
                BLUE /= 2;
                GREEN /= 2;
            }

            SDL_SetRenderDrawColor(render, RED, GREEN, BLUE, 255);
            SDL_RenderDrawLine(render, x, start_draw, x, end_draw);
            
        }

        SDL_RenderPresent(render);
    }

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}