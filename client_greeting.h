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


#ifndef CLIENT_GREETING_H
#define CLIENT_GREETING_H

#include <QMainWindow>
#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include<iostream>
#include<QString>
#include<string>
#include"QByteArray"
#include<QHostAddress>
#include"QtGlobal"
#include"game.h"
#include<QDataStream>
#include<QMessageBox>
#include<QListWidget>
#include"profilemanager.h"

namespace Ui {
class client_greeting;
}

//! A class to handle the gameplay for client players.
class client_greeting : public QMainWindow
{
    Q_OBJECT
    //! Game variable for each player.
    game g;
    int code;
    //! Denotes if the game is over or not
    bool game_over;
    //! Used to send serialised bytes of data over the local network through sockets
    QDataStream *socket_stream;
    //! Denotes if the client is receiving first message from server.
    //! Especially useful since no move is made for this first message.
    bool is_first_message;
    //! Variable used to store the player_number of the client player. Do note that server is always assigned  player_number = 1.
    unsigned player_number;
    //! QTcpClient pointer used for all TCP operations.
    QTcpSocket *socket;
    //! Variable used to store the temporary index of card button clicked.
    int index;
    //! Temporarily stores the changed color in case of WILD or DRAW_FOUR_WILD cards
    color_t changed_color;
public:
    //! This function counts each player's cards and displays it to the given player.
    void cards_count();
    //! Check function is called whenever a player move starts to check for any pre-move conditions to implement
    //! This includes ending the move if last card was SKIP or adding cards as per power-up cards played.
    bool check_func();
    explicit client_greeting(unsigned,unsigned,QWidget *parent = nullptr);
    //! This function changes the title of the game window to the player's name and starts listening on the ip and port specified.
    void start_client();
    ~client_greeting();
    //! This function uses the card_drop() from game to check if a card is valid move and drop it.
    //! This function also asks for the color of choice if it's a special card.
    /*!
       \param a the index of card to be dropped
    */
    void player_drop(unsigned a);
    //! This function is used to enable or disable the card buttons for the players. The buttons are disabled when other players are making their moves.
    //! The function calls send_all() method when toggled false since it denotes the move is made.
    /*!
      \param toggle boolean value to denote whether to toggle the button on or off
    */
    void toggle_cards(bool toggle);
signals:
    //! This signal is emitted whenever there is a need to refresh the discard_pile alone.
    void deck_refresh_signal();
    //! This signal is emitted whenever we want to refresh the player's deck of cards. This method internally uses game class's
    //! append_cards() function and also calls show_deck_refresh.
    void refresh_signal();
public slots:
    //! This function is called whenever there is a new message in QDataStream. The function then decodes the message and updates its game object.
    void on_readyRead();
    //! This method serialises the user's game object and sends it via QDataStream to the QTcpSocket* fed as parameter to it.
    /*!
     * \param socket A QTcpSocket * object to denote the client socket.
     */
    void send_message(QTcpSocket * socket);
    //! This function is called whenever a player clicks on a card button. This function then finds it's index and stores it in index variable.
    void card_button_onclicked();
    void show_cards_refresh();
    //! This function is called whenever deck_refresh_signal is emitted.
    void show_deck_refresh();
    void connection_error();
    void server_connected();
private slots:
    void on_connect_button_clicked();
    void on_add_button_client_clicked();
    void on_drop_button_client_clicked();

private:
    Ui::client_greeting *ui;
};

#endif // CLIENT_GREETING_H
