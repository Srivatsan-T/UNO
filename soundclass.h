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


#pragma once
#include <SDL_mixer.h>
#include <vector>

class soundclass
{
public:
    static soundclass* getinstance() {
        if (!instance) {
            instance = new soundclass;
            instance->call_addsounds();
        }
        instance->call_function();
        return instance;
    }

    void call_function()
    {
        initilisation();

    }
    ~soundclass();
    void addmusic(const char* path);
    void addeffects(const char* path);
    void playmusic(int num) const;
    void playeffects(int num) const;
    void delete_all();
    void play_cont_music(int num);
    void play_cont_effects(int num);
    void call_addsounds();




private:
    soundclass() {};
    void initilisation();
    static soundclass* instance;

    std::vector<Mix_Music*> music;  //stores music files (.mp3 files etc)
    std::vector<Mix_Chunk*> effects; //stores sound effects files( .wav files etc)
};


