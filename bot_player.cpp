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

#include"bot_player.h"
#define HAND_THRESHOLD 5
bot_player::bot_player()
{
    legal_set.reserve(100);
}

bool bot_player::checkForcingMoves(QVector<card>* current_hand, users* h)
{
    /* checks the most recently played cards for whether its a draw card
     * that forces you to pick up from draw pile, also tests for skip
     * returns true if the player was forced into an action
     * will be called by botMove()
     */

        if(bot_player::last_card.get_number_string()=="DRAW-FOUR-WILD"&&bot_player::last_card.get_power()==true)
        {
            for(int i=0;i<4;i++)
            {
                current_hand->append(h->get_game_deck().takeFirst());
            }
            return true;
        }
        else if(bot_player::last_card.get_number_string()=="DRAW-TWO"&&bot_player::last_card.get_power()==true)
        {
            for(int i=0;i<2;i++)
            {
                current_hand->append(h->get_game_deck().takeFirst());
            }
            return true;
        }
        else if(last_card.get_number_string()=="SKIP"&&last_card.get_power()==true)
        {
            return true;
        }
        return false;

}
int bot_player::checkForUno(QVector<card>* current_hand, int player_id, int number_players, users* h, game* g)
{

    int x=g->is_clock_wise?1:-1;

    bool nextHasUno=h->get_player((player_id-1+x)%number_players+1>0?(player_id-1+x)%number_players+1:number_players+x+player_id).size()==1;//player id starts from 1
    if(nextHasUno)
    {
        if(current_hand->contains(new card(color_t::NO_COLOR, number_t::DRAW_FOUR_WILD)))
        {
            return current_hand->indexOf(new card(color_t::NO_COLOR, number_t::DRAW_FOUR_WILD));
        }
        else if(current_hand->contains(new card(last_card.get_color(), number_t::DRAW_TWO)))
        {
            return current_hand->indexOf(new card(last_card.get_color(), number_t::DRAW_TWO));
        }
        else if(current_hand->contains(new card(last_card.get_color(), number_t::SKIP)))
        {
            return current_hand->indexOf(new card(last_card.get_color(), number_t::SKIP));
        }
        else if(current_hand->contains(new card(last_card.get_color(), number_t::REVERSE)))
        {
            return current_hand->indexOf(new card(last_card.get_color(), number_t::REVERSE));
        }
        else if(current_hand->contains(new card(color_t::NO_COLOR, number_t::WILD)))
        {
            return current_hand->indexOf(new card(color_t::NO_COLOR, number_t::WILD));
        }
        
    }
    if(h->get_num_user()!=2)//!if there are only 2 players then no reason to check yourself for Uno you would already be able to play or not
    {
        x=g->is_clock_wise?2:-2;
        bool secondNextHasUno=h->get_player((player_id+x-1)%number_players+1>0?(player_id+x-1)%number_players+1:player_id+number_players+x).size()==1;
        if(secondNextHasUno)
        {
            return nonSpecialMove();
        }
    }
    return -1;

}
int bot_player::lookForSpecial()
{
    if(legal_set.contains(new card(color_t::NO_COLOR, number_t::DRAW_FOUR_WILD)))
    {
        return legal_set.indexOf(new card(color_t::NO_COLOR, number_t::DRAW_FOUR_WILD));
    }
    if(legal_set.contains(new card(color_t::NO_COLOR, number_t::WILD)))
    {
        return legal_set.indexOf(new card(color_t::NO_COLOR, number_t::WILD));
    }
    for(int i=0;i<legal_set.size();i++)
    {
        if(legal_set.at(i).get_number()==number_t::DRAW_TWO)
        {
            return i;
        }
        else if(legal_set.at(i).get_number()==number_t::SKIP)
        {
            return i;
        }
        else if(legal_set.at(i).get_number()==number_t::REVERSE)
        {
            return i;
        }
    }
    return -1;

}
int bot_player::nonSpecialMove()
{
    for(int i=0;i<legal_set.size();i++)
    {
        if(legal_set.at(i).color_string==last_card.get_color_string())
        {
            return i;
        }
        else if(legal_set.at(i).number_string==last_card.get_number_string())
        {
            return i;
        }
    }
    return -1;
}
void bot_player::generateLegalSet(QVector<card>* current_hand)
{

    for(int i=0;i<current_hand->size();i++)
    {
        if(last_card.get_color()==current_hand->at(i).get_color())
        {
            legal_set.emplace_back(new card(current_hand->at(i).get_color(), current_hand->at(i).get_number()));
        }
        else if(last_card.get_number()==current_hand->at(i).get_number())
        {           
            legal_set.emplace_back(new card(current_hand->at(i).get_color(), current_hand->at(i).get_number()));
        }
        else if(current_hand->at(i).get_number()==number_t::DRAW_FOUR_WILD)
        {
            legal_set.emplace_back(new card(current_hand->at(i).get_color(), current_hand->at(i).get_number()));
        }
        else if(current_hand->at(i).get_number()==number_t::WILD)
        {
            legal_set.emplace_back(new card(current_hand->at(i).get_color(), current_hand->at(i).get_number()));
        }
    }
}
int bot_player::botMove(game* g, users* h, QVector<card>* current_hand, int player_id)
{
    last_card=h->get_game_deck().back();
    legal_set.clear();
    generateLegalSet(current_hand);

    bool move_forced=checkForcingMoves(current_hand, h);
    if(move_forced)
    {
        return -1;
    }
    if(legal_set.size()==0)
    {
        int lastindex=current_hand->size();//!one card added right after so this is the last position
        current_hand->append(h->get_game_deck().takeFirst());
        if(last_card.get_color()==current_hand->at(lastindex).get_color())
        {
            return lastindex;

        }
        else if(last_card.get_number()==current_hand->at(lastindex).get_number())
        {
            return lastindex;

        }
        else if(current_hand->at(lastindex).get_number()==number_t::DRAW_FOUR_WILD)
        {
            return lastindex;

        }
        else if(current_hand->at(lastindex).get_number()==number_t::WILD)
        {
            return lastindex;

        }//special cards can be added here
        else
        {
            return -1;
        }


    }
    int other_Uno=checkForUno(current_hand, player_id, h->get_num_user(), h, g);
    if(other_Uno!=-1)
    {
        return other_Uno;
    }
    int x=lookForSpecial();
    int t=nonSpecialMove();
    if(current_hand->size()<=HAND_THRESHOLD)//!this is to prioritise playing special moves when the card count of the hand is low
    {

        if(x!=-1)
        {
            return current_hand->indexOf(legal_set.at(x));
        }
        else{

            if(t!=-1)
            {
                return current_hand->indexOf(legal_set.at(t));

            }
            else
            {
                current_hand->append(h->get_game_deck().takeFirst());
                return -1;
            }
        }
    }
    else//!to prioritise using special cards when the hand size is lower
    {
       if(t!=-1)
       {
           return current_hand->indexOf(legal_set.at(t));
       }
       else
       {
           if(x!=-1)
           {
               return current_hand->indexOf(legal_set.at(x));
           }
           else
           {
               current_hand->append(h->get_game_deck().takeFirst());
               return -1;
           }
       }
    }
}
