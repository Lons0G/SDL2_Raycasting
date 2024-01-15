#include "game.hpp"

Game::Game(){

}

Game::~Game(){

}

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

}

void Game::Input(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            _Running = false;
            break;

        default:
            break;
    }
}

void Game::Render(){
    SDL_RenderClear(_Render);

    SDL_RenderPresent(_Render);
}

void Game::Clean(){
    SDL_DestroyRenderer(_Render);
    SDL_DestroyWindow(_Window);
    SDL_Quit();
    std::cout << "Game Exit" << std::endl;
}