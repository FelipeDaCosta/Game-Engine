#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <cstdlib>
#include <string>
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Resources.h"

class Music {
    private:
        Mix_Music* music;
    public:
        Music();
        Music(std::string file);
        void Play(int times);
        void Stop(int msToStop);
        void Open(std::string file);
        bool IsOpen();
};

#endif