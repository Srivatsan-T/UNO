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


#ifndef BOT_PLAYER_H
#define BOT_PLAYER_H


#include"card.h"
#include"game.h"
#include"users.h"
#include<QVector>
#include<QString>
class bot_player
{
    //!The set of legal cards playable by the bot in a scpeific turn, regenerated at the start of each turn
    QVector<card> legal_set;
    //!The most recent card played in the game
    card last_card;
public:

    bot_player();
    /* !
     *  The main method to generate a move from the QVector of cards given to it. Calls all the other methods based on implemented logic.
     *  \param  current_hand pointer to vector of the card hand,
     *  \param player_id the number of the player, used in checkForUno() to find the next and second next player.
     */
    int botMove(game* g, users* h, QVector<card>* current_hand, int player_id);
    //!Checks if there are any forced card pickups that have to be made from cards like +2 and +4
    bool checkForcingMoves(QVector<card>* current_hand, users* h);
    //!Checks to see if the next player has one card, and looks for the strongest special card to play
    int checkForUno(QVector<card>* current_hand, int player_id, int number_players, users* h, game* g);
    //!Looks for a move that isnt a special card
    int nonSpecialMove();
    //!Looks for a special move like a +2, +4, skip, etc.
    int lookForSpecial();
    //!Generates the set of legal moves playable by the bot player, regenerated each turn
    void generateLegalSet(QVector<card>* current_hand);//legal_set cleared everytime botMove() is called
};


#endif // BOT_PLAYER_H
