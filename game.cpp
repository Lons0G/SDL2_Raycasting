#include "game.hpp"

Game::Game(){

}

Game::~Game(){

}

int contador = 0;
#define WIDTH 800
#define HEIGHT 600
#define MAP_SIZE 24

int RED = 0;
int BLUE = 0;
int GREEN = 0;

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

double pos_x = 22;
double pos_y = 12;
double dir_x = -1;
double dir_y = 0;
double plane_x = 0;
double plane_y = 0.66;
//double _time = 0.0;
//double oldtime = 0.0;
double movespeed = 0.05;
double rot_speed = 0.05;
bool forward = false;
bool backward = false;
bool left = false;
bool right = false;

bool Game::IsRunning(){
    return _Running; 
}

void Game::Init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    SDL_Init(SDL_INIT_EVERYTHING);

    _Window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
    
    if(_Window == NULL){
        std::cout << "SDL Window Failed To Initialise " << SDL_GetError() << std::endl;
    }

    _Render = SDL_CreateRenderer(_Window, -1, 0);

     if(_Render == NULL){
        std::cout << "SDL Render Failed To Initialise " << SDL_GetError() << std::endl;
    }else{std::cout << "SDL Render se inicio" << std::endl; }

    if(_Window == NULL || _Render == NULL){ _Running = false; }
}

void Game::Loop(){
    if(forward == true){
        if(Map[int (pos_x + dir_x * movespeed)][int(pos_y)] == false) { pos_x += dir_x * movespeed; }
        if(Map[int (pos_x)][int(pos_y + dir_y * movespeed)] == false) { pos_y += dir_y * movespeed; }
    }
    else if(backward == true){
        if(Map[int (pos_x - dir_x * movespeed)][int(pos_y)] == false) { pos_x -= dir_x * movespeed; }
        if(Map[int (pos_x)][int(pos_y - dir_y * movespeed)] == false) { pos_y -= dir_y * movespeed; }
    }
    if(left == true){
        double old_dir_x = dir_x;
        dir_x = dir_x * cos(rot_speed) - dir_y * sin(rot_speed);
        dir_y = old_dir_x * sin(rot_speed) + dir_y * cos(rot_speed);
        double old_plane_x = plane_x;
        plane_x = plane_x * cos(rot_speed) - plane_y * sin(rot_speed);
        plane_y = old_plane_x * sin(rot_speed) + plane_y * cos(rot_speed); 
    }else if (right == true){
        double old_dir_x = dir_x;
        dir_x = dir_x * cos(-rot_speed) - dir_y * sin(-rot_speed);
        dir_y = old_dir_x * sin(-rot_speed) + dir_y * cos(-rot_speed);
        double old_plane_x = plane_x;
        plane_x = plane_x * cos(-rot_speed) - plane_y * sin(-rot_speed);
        plane_y = old_plane_x * sin(-rot_speed) + plane_y * cos(-rot_speed); 
    }
}

void Game::Input(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            _Running = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_w){
                //if(Map[int (pos_x + dir_x * movespeed)][int(pos_y)] == false) { pos_x += dir_x * movespeed; }
                //if(Map[int (pos_x)][int(pos_y + dir_y * movespeed)] == false) { pos_y += dir_y * movespeed; }
                //std::cout << "Key W" << std::endl;
                forward = true;
            }else if(event.key.keysym.sym == SDLK_s){
                //if(Map[int (pos_x - dir_x * movespeed)][int(pos_y)] == false) { pos_x -= dir_x * movespeed; }
                //f(Map[int (pos_x)][int(pos_y - dir_y * movespeed)] == false) { pos_y -= dir_y * movespeed; }
                //std::cout << "Key S" << std::endl;
                backward = true;
            }else if(event.key.keysym.sym == SDLK_a){
                //double old_dir_x = dir_x;
                //dir_x = dir_x * cos(rot_speed) - dir_y * sin(rot_speed);
                //dir_y = old_dir_x * sin(rot_speed) + dir_y * cos(rot_speed);
                //double old_plane_x = plane_x;
                //plane_x = plane_x * cos(rot_speed) - plane_y * sin(rot_speed);
                //plane_y = old_plane_x * sin(rot_speed) + plane_y * cos(rot_speed); 
                //std::cout << "Key A" << std::endl;
                left = true;
            }else if(event.key.keysym.sym == SDLK_d){
                //double old_dir_x = dir_x;
                //dir_x = dir_x * cos(-rot_speed) - dir_y * sin(-rot_speed);
                //dir_y = old_dir_x * sin(-rot_speed) + dir_y * cos(-rot_speed);
                //double old_plane_x = plane_x;
                //plane_x = plane_x * cos(-rot_speed) - plane_y * sin(-rot_speed);
                //plane_y = old_plane_x * sin(-rot_speed) + plane_y * cos(-rot_speed); 
                //std::cout << "Key D" << std::endl;
                right = true;
            }
            break;
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_w){ forward = false; }
                if(event.key.keysym.sym == SDLK_s){ backward = false; }
                if(event.key.keysym.sym == SDLK_a){ left = false; }
                if(event.key.keysym.sym == SDLK_d){ right = false; }
                break;
        default:
            break;
    }
}

void Game::Render(){
    SDL_SetRenderDrawColor(_Render, 50, 50, 50, 255);
    SDL_RenderClear(_Render);
    
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

            SDL_SetRenderDrawColor(_Render, RED, GREEN, BLUE, 255);
            SDL_RenderDrawLine(_Render, x, start_draw, x, end_draw);
            
        }


    SDL_RenderPresent(_Render);
}

void Game::Clean(){
    SDL_DestroyRenderer(_Render);
    SDL_DestroyWindow(_Window);
    SDL_Quit();
    std::cout << "Game Exit" << std::endl;
}