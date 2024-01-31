#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <cmath>
class Game{
    private:
        SDL_Window* _Window;
        SDL_Renderer* _Render;

        Uint32 _gamespeed;
        
        bool _Running = true;
    
    public:
        Game();
        ~Game();

        void Init(const char* title, int x_pos, int y_pos, int width, int height, bool fullscreen);
        void Loop();
        void Input();
        void Render();
        void Clean();
        bool IsRunning();

};