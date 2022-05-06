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


#ifndef CARD_H
#define CARD_H


#include <vector>
#include <iostream>
#include <string>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<QDataStream>
#include<QVector>
#include<QColor>
#include<QPushButton>

//! Enum class to represent color of a UNO card
enum class color_t
{
    RED,
    BLUE,
    GREEN,
    YELLOW,
    NO_COLOR
};

//! Enum class to represent the number present in the UNO card
/*! After the number ten the enum class has numbers for special cards such as SKIP, REVERSE etc. */
enum class number_t
{
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    SKIP,
    REVERSE,
    DRAW_TWO,
    WILD,
    DRAW_FOUR_WILD,
    COLOR_DROP,
    NO_NUMBER
};

//! Fundamental class to define a card to be used extensively in the game.
//! Stores each card's data like its color and number and methods to create a QPushButton out of a card.
class card
{
    //! Enum class variable to denote color of a card
    color_t color;
    //! Enum class variable to denote number of a card
    number_t number;
    //! Denotes if a card has power. This is helpful to prevent a powerup card from affecting players more than once.
    bool power;
    QColor blue = QColor(Qt::blue);
    QColor red = QColor(Qt::red);
    QColor yellow = QColor(Qt::yellow);
    QColor green = QColor(Qt::green);
    QColor white = QColor(Qt::white);
public:
    //! Variable to store the card's color in string.
    QString color_string;
    //! Variable to store the card's number in string.
    QString number_string;
    //!
    //! \brief card constructor to create a card object out of given color and number
    //! \param c color_t enum object which denotes the color of the card
    //! \param n number_t enum object which denotes the number present on the card
    card(color_t c, number_t n);
    card();
    card(const card &);
    card(card*);
    //! A simple get function which returns the enum corresponding to the card's color
    color_t get_color() const;
    //! A simple get function which returns the enum corresponding to the card's number
    number_t get_number() const;
    //! A simple get function which returns the enum corresponding to the card's power state.
    /*! All cards have power values of true when they are created.
     *  They lose their power once they are played by any player.
     *  This is useful in case of power up cards so that they dont affect opponents more than once! */
    bool get_power() const;
    //! A method to change the power values of the card.
    void set_power(bool);
    //! This method sets an empty button's text as the card's number and color and returns the QPushButton Object
    QPushButton* show_card();
    //! This method returns the name of the card's color as string
    /*!This method is especially helpful in the show_card function to get the card's color as string
     * to set button's text */
    QString get_color_string();
    //! This method returns the name of the card's number as string
    /*!This method is especially helpful in the show_card function to get the card's number as string
     * to set button's text */
    QString get_number_string();
    void operator=(const card&);
    bool operator==(card) const;
    bool operator==(card*) const;//overloaded for safety
    //! This method is used to generate color_t and number_t enum objects from a set of strings
    /* This method is especially useful as enum objects can't be serialised to be sent over
     * the network. So they are converted to strings, sent to other users and are converted
     * back to enum using this function */
    void color_string_to_enum(QString color,QString number);
};

QDataStream& operator<<(QDataStream& out, const card& c);
QDataStream& operator>>(QDataStream& in, card& c);

#endif // CARD_H
