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


#include "game.h"

game::game(unsigned n,bool color_drop):h(n,color_drop)
{
    next_player = 0;
    is_clock_wise = true;
    is_valid_move = false;
    for(uint i=0;i<n;i++)
    {
        win_list.append(false);
    }
}

void game::start_game()
{
    h.generate_deck();
    h.fill_up_players(h.get_num_user());
    deck_back.append(h.get_game_deck().back().show_card());
}


bool game::is_move_available(unsigned n)
{
    for (int i = 0; i < h.get_player(n).size(); i++)
    {
        if (h.get_player(n)[i].get_number() == number_t::WILD || h.get_player(n)[i].get_number() == number_t::DRAW_FOUR_WILD || h.get_player(n)[i].get_number() == number_t::COLOR_DROP)
        {
            return true;
        }
        else if ((h.get_game_deck().back().get_number() >= number_t::DRAW_TWO) && h.get_player(n)[i].get_color() == h.get_game_deck().back().get_color())
        {
            return true;
        }
        else if ((h.get_game_deck().back().get_number() == number_t::SKIP || h.get_game_deck().back().get_number() == number_t::REVERSE) && (h.get_player(n)[i].get_number() == h.get_game_deck().back().get_number() || h.get_player(n)[i].get_color() == h.get_game_deck().back().get_color()))
        {
            return true;
        }
        else if ((h.get_game_deck().back().get_number() < number_t::SKIP) && (h.get_player(n)[i].get_number() == h.get_game_deck().back().get_number() || h.get_player(n)[i].get_color() == h.get_game_deck().back().get_color()))
        {
            return true;
        }
    }
    return false;
}


bool game::card_drop(unsigned t, unsigned n)
{
    is_valid_move = false;
    if ( (h.get_player(t)[n - 1].get_number() == number_t::WILD) || (h.get_player(t)[n - 1].get_number() == number_t::DRAW_FOUR_WILD) || (h.get_player(t)[n - 1].get_number() == number_t::COLOR_DROP) )
    {
        is_valid_move = true;
    }
    else if ( (h.get_player(t)[n - 1].get_number() == number_t::DRAW_TWO) && (h.get_player(t)[n - 1].get_color() == h.get_game_deck().back().get_color()))
    {
        is_valid_move = true;
    }
    else if (( (h.get_player(t)[n - 1].get_number() == number_t::REVERSE) || (h.get_player(t)[n - 1].get_number() == number_t::SKIP) ) && ( (h.get_player(t)[n - 1].get_color() == h.get_game_deck().back().get_color()) || (h.get_player(t)[n - 1].get_number() == h.get_game_deck().back().get_number())))
    {
        is_valid_move = true;
    }
    else if ( (h.get_player(t)[n - 1].get_number() < number_t::SKIP) && ( (h.get_player(t)[n - 1].get_number() == h.get_game_deck().back().get_number()) || (h.get_player(t)[n - 1].get_color() == h.get_game_deck().back().get_color())))
    {
        is_valid_move = true;
    }
    else if ((h.get_game_deck().back().get_number() >= number_t::DRAW_TWO) && (h.get_player(t)[n - 1].get_color() == h.get_game_deck().back().get_color()) )
    {
        is_valid_move = true;
    }
    else if (( (h.get_game_deck().back().get_number() == number_t::SKIP) || (h.get_game_deck().back().get_number() == number_t::REVERSE )) && ( (h.get_player(t)[n - 1].get_number() == h.get_game_deck().back().get_number() ) || (h.get_player(t)[n - 1].get_color() == h.get_game_deck().back().get_color())))
    {
        is_valid_move = true;
    }
    else if ((h.get_game_deck().back().get_number() < number_t::SKIP) && ( (h.get_player(t)[n - 1].get_number() == h.get_game_deck().back().get_number() ) || ( h.get_player(t)[n - 1].get_color() == h.get_game_deck().back().get_color() ) ))
    {
        is_valid_move = true;
    }
    return is_valid_move;
}


void game::append_buttons(unsigned n)
{
    button_vector.clear();
    for (int i = 0; i < h.get_player(n).size(); i++)
    {
        button_vector.append(h.get_player(n)[i].show_card());
        button_vector[i]->setEnabled(false);
    }
}

void game::player_add(unsigned n)
{
    h.get_player(n).push_back(h.get_game_deck().front());
    h.get_player(n).back().set_power(true);
    h.get_game_deck().erase(h.get_game_deck().begin());
}

void game::operator=(const game& g)
{
    is_valid_move = g.is_valid_move;
    win_list = g.win_list;
    is_clock_wise = g.is_clock_wise;
    h = g.h;
    next_player = g.next_player;
}

QDataStream& operator<<(QDataStream& out, const game& g)
{
    out<<g.is_valid_move;
    out<<g.win_list;
    out<<g.next_player;
    out<<g.is_clock_wise;
    out<<g.h;
    return out;
}
QDataStream& operator>>(QDataStream& in, game& g)
{
    in>>g.is_valid_move;
    in>>g.win_list;
    in>>g.next_player;
    in>>g.is_clock_wise;
    in>>g.h;
    return in;
}
