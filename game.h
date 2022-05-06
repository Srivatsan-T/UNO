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


#ifndef GAME_H
#define GAME_H

#include "users.h"
#include "card.h"
#include<QVector>
#include<string>
#include<stdlib.h>
#include<QDataStream>
#include<QString>
#include<QPushButton>

//! A Class to handle game variables common to both client and server.
class game: public QObject
{
    Q_OBJECT
    public:
    //! Variable to store if the game_direction is clock-wise or not. Comes in handy whenver a reverse card is played and to denote the next player in queue.
    bool is_clock_wise;
    //! Used to store the next player's number depending on is_clock_wise.
    unsigned next_player;
    //! Stores the result of card_drop() funtion.
    bool is_valid_move;
    //! Stores the result of the game in terms of bool win values for each players.
    //! The game ends when one of these becomes true.
    QVector<bool> win_list;
    QVector<QPushButton *> button_vector;
    QVector<QPushButton *> deck_back;
    //! This function moves the card present on the top of the game deck to the back of a player's deck
    /*! This function also disables the add button after adding a card to prevent multiple additions */
    void player_add(unsigned);
    game(unsigned,bool = false);
    users h;
    //! This function invokes the card generation function and fills up the player decks from the pool.
    void start_game();
    //! This function goes to the player's deck specified and check's in if the index specified is a valid move with respect to the discard pile
    /*!
     * \param t To denote the player number so that the function checks his deck of cards
     * \param n To denote the index of the card to be dropped.
     * \return Whether the chosen index's card can be dropped or not.
     */
    bool card_drop(unsigned t,unsigned n);
    //!  This function goes through the specified player's entire deck and returns if he has any valid moves to be played
    /*!
     * \param n Denotes the player_number
     * \return whether there is any move left to be played in n's deck.
     */
    bool is_move_available(unsigned n);
    //! This function clears the button vector for a player and fills it up with the card buttons returned by the get_card() function from card class
    void append_buttons(unsigned);
    //! equality operator used to compare game objects. It comes in handy since it is always getting transferred and knowing if 2 objects are same is crucial.
    void operator=(const game&);
};

QDataStream& operator<<(QDataStream& out, const game& g);
QDataStream& operator>>(QDataStream& in, game& g);
#endif
