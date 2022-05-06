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

#ifndef SERVER_GREETING_H
#define SERVER_GREETING_H

#include <QMainWindow>
#include "game.h"
#include<QVector>
#include<QTcpServer>
#include<QTcpSocket>
#include<QDataStream>
#include"QHostAddress"
#include <QString>
#include<QPushButton>
#include<QGridLayout>
#include<QColor>
#include <QListWidget>
#include<QMessageBox>
#include "profilemanager.h"
#include <algorithm>
#include <iterator>

namespace Ui {
class server_greeting;
}

//! A class to handle the gameplay for the server player.
class server_greeting : public QMainWindow
{
    Q_OBJECT
    //! Variable which comes in handy for the receiver of serialised bytes to know the kind of data being received.
    int code;
    //! Denotes if the game is over or not
    bool game_over;
    //! Used to send serialised bytes of data over the local network through sockets.
    QDataStream *socket_stream;
    //! Game variable for each player. The server and clients share their game states with each other through this object.
    game g;
    //! Denotes if the server is making his first move or not. True initially and false after the first move.
    //! Especially useful since the first move has no restrictions.
    bool is_first_move;
    //! Vector used to store the client sockets which are connected to the server
    QVector<QTcpSocket *> socket_list;
    //! Variable used to store the temporary index of card button clicked. Given default initial value as -1 which represents no card chosen.
    int index;
    //! Temporarily stores the changed color in case of WILD or DRAW_FOUR_WILD cards
    color_t changed_color;
    //! Stores the IP address of server as string
    QString add_string;
    //! Stores the port number as string
    QString port_string;
    Ui::server_greeting *ui;
    //! QTcpServer pointer used for all TCP operations
    QTcpServer *server;
public:
    //! This function is used to relay the modified game object that was sent to server by a client to all the
    //! other clients as that they can update their game objects.
    void message_passer();
    //! This function is used by the server to send the modified game object to all clients after making its move
    void send_all();
    //! This function counts each player's cards and displays it to the given player.
    void cards_count();
    explicit server_greeting(unsigned,bool,QWidget *parent = nullptr);
    //! This function changes the title of the window to given player's name from profilemanager and starts listening for potential clients
    void start_server();
    //! This function adds the clients to a vector of clients called sockets and enables start_game button if all clients have joined.
    /*!
      \param socket A QTcpSocket* object to denote the client socket.
     */
    void appendtosockets(QTcpSocket* socket);
    ~server_greeting();
    //! This function uses the card_drop() from game to check if a card is valid move and drop it.
    //! This function also asks for the color of choice if it's a special card.
    /*!
      \param toggle boolean value to denote whether to toggle the button on or off
    */
    void player_drop(unsigned);
    //! This function is used to enable or disable the card buttons for the players. The buttons are disabled when other players are making their moves.
    //! The function calls send_all() method when toggled false since it denotes the move is made.
    /*!
      \param toggle boolean value to denote whether to toggle the button on or off
    */
    void toggle_cards(bool);
    //! Check function is called whenever a player move starts to check for any pre-move conditions to implement
    //! This includes ending the move if last card was SKIP or adding cards as per power-up cards played.
    bool check_func();
signals:
    //! This signal is emitted whenever we want to refresh the player's deck of cards. This method internally uses game class's
    //! append_cards() function and also calls show_deck_refresh.
    void refresh_signal();
    //! This signal is emitted whenever there is a need to refresh the discard_pile alone.
    void deck_refresh_signal();
public slots:
    //! This function is called whenever deck_refresh_signal is emitted.
    void show_deck_refresh();
    //! This function is called whenever a new client connects to the server. This function internally calls appendtosockets(QTcpSocket*) function.
    void newConnection();
    //! This function is called whenever there is a new message in QDataStream. The function then decodes the message and updates its game object.
    void readyRead();
    //! This method serialises the user's game object and sends it via QDataStream to the QTcpSocket* fed as parameter to it.
    /*!
     * \param socket A QTcpSocket * object to denote the client socket.
     */
    void send_message(QTcpSocket *);
    //! This function is called whenever a player clicks on a card button. This function then finds it's index and stores it in index variable.
    void card_button_onclicked();
private slots:
    void on_start_server_button_clicked();
    void show_cards_refresh();
    void on_Submit_button_clicked();
    void on_add_button_clicked();
    void on_drop_button_clicked();
    void on_host_ip_button_clicked();

};

#endif // SERVER_GREETING_H
