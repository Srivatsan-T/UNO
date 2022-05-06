/*    Copyright (C) 2021  Srivatsan-T,jatin-tarachandani,JeevanIITH,shashank-anirudh-rachapalle

    This file is part of You Know UNO?.

    You Know UNO? is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    You Know UNO? is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include "soundclass.h"
#include <SDL.h>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

soundclass *soundclass::instance=0;
void soundclass::initilisation()
{
    //std::cout << "initilisation called" << std::endl;
    SDL_Init(SDL_INIT_AUDIO);
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;

    if (Mix_OpenAudio(audio_rate, MIX_DEFAULT_FORMAT, audio_channels, audio_buffers) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio :%s", Mix_GetError());
        exit(-1);
     }

    //set volume to half of music;
    Mix_VolumeMusic(MIX_MAX_VOLUME/4);
}

soundclass::~soundclass()
{
    //std::cout<<"destructor called"<<std::endl;
    this->instance=nullptr;
   // std::cout<<"destructor called"<<std::endl;
    music.clear();
    effects.clear();
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
    this->delete_all();
   // std::cout<<"destructor called"<<std::endl;

}

void soundclass::addmusic(const char* path)
{
    Mix_Music* tmpmusic = Mix_LoadMUS(path);
    if(tmpmusic==nullptr)
    {
        std::cout<<"Error occured in adding music"<<std::endl;
    }

    if (tmpmusic != nullptr)
    {
        music.push_back(tmpmusic);
       // std::cout << (music.size() - 1) << "sound_ready , path:" << path << std::endl;
    }

}
void soundclass::addeffects(const char* path)
{
    Mix_Chunk* tmpchunk = Mix_LoadWAV(path);
    if(tmpchunk==nullptr)
    {
        std::cout<<"Error in adding effects"<<std::endl;
    }

    if (tmpchunk != nullptr)
    {
        effects.push_back(tmpchunk);
       // std::cout << (effects.size() - 1) << "sound_ready , path:" << path << std::endl;
    }

}

void soundclass::playmusic(int num) const
{
    if (num > music.size() - 1)
    {
        std::cout << "sound out of range";

    }
    //std::cout << "invoked playsound function" << std::endl;
    if(num<music.size()){
    if(Mix_PlayMusic(music[num], -1)==-1){
        std::cout << "Error occured in playing music " << std::endl;
    }
    }
    //Mix_PlayMusic(msounds[num],-1);
    //usleep();

}
void soundclass::playeffects(int num) const
{
    if(num<effects.size())
    {
       Mix_PlayChannel(-1,effects[num],0);
    }

}
void soundclass::delete_all()
{
   // std::cout<<"Delete_all called"<<std::endl;
    Mix_HaltMusic();
    music.clear();
    effects.clear();
    Mix_CloseAudio();
    SDL_Quit();
    Mix_Quit();
    //std::cout<<"Delete_all called"<<std::endl;
    instance=nullptr;




}
void soundclass::play_cont_music(int num)
{
        playmusic(num);
}
void soundclass::play_cont_effects(int num)
{
        playeffects(num);
}

void soundclass::call_addsounds()
{
    //std::cout<<"reached call_addsounds"<<std::endl;
    soundclass* sd=sd->getinstance();
    sd->addmusic("sounds1/m1.mp3");
    sd->addeffects("sounds1/sci-fi-positive-notification-266.wav");
    sd->addeffects("sounds1/sci-fi-click-900.wav");
}
