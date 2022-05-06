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


#ifndef USERS_H
#define USERS_H


#include "card.h"
#include<random>
#include<chrono>
#include<algorithm>
#include<iostream>
//#include<vector>
#include<QDataStream>
#include<QVector>

//! A class to generate decks of cards and store each player's decks and game_deck.
class users
{
    //! Variable to identify is the special power_up_card is enabled or not. Used to generate such cards and add them to the pile.
    bool color_drop_card;
    //! Vector of Vector of card objects to store each player's deck of cards.
    QVector<QVector<card>> player_list;
    //! Variable to store number of players
    unsigned number_players;
public:
    //! Variable to store the remaining generated cards after distributing to playerss
    QVector<card> game_deck;
    //! The initial container to store all the generated cards before they are split into player and game_deck cards.
    QVector<card> deck;
    users() = default;
    users(unsigned,bool);
    //! This function is used to fill up the players with initial cards from the deck
    /*! This function takes in the number of players as parameter and creates that many objects in the player_list vector and
     *  fills them with cards from a shuffled deck */
    void fill_up_players(unsigned);
    //! This is a simple get method to return the number of players
    unsigned get_num_user() const;
    //! This method returns the vector of a vector of card objects representing each user's deck of cards
    QVector<QVector<card>> get_player_list() const;
    //! This method is used to set the player_list vector
    void set_player_list(QVector<QVector<card>>&);
    //! This method is used to set the number of players
    void set_num_user(unsigned n);
    //! This method generates the entire deck of cards and invokes the fill_up_players method
    /*! The deck is generated in a pre-defined fashion and is shuffled using a time based seed. Then the player
     *  \param n denotes the number of players to be set to number_players.
     *  decks are filled up linearly from the shuffled deck */
    QVector<card> generate_deck();
    //! This method returns a specific player's card deck taking in the index according to player_list vector
    QVector<card>& get_player(unsigned p);
    /*! This method returns the game_deck which is basically the remaining cards left in the generated pool of cards after
     * distributing to players
     * \param p denotes the player number(starts from 1 being server) to be picked from the player's list. Note that it is player number and not player index.
     */
    QVector<card>& get_game_deck();
    void operator=(const users&);
};


QDataStream& operator<<(QDataStream& out, const users& u);
QDataStream& operator>>(QDataStream& in, users& u);


#endif // USERS_H
