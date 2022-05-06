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


#ifndef INPUTS_H
#define INPUTS_H

#include <QMainWindow>
#include "server_greeting.h"
#include"client_greeting.h"
#include "bot_player.h"
#include<QListWidgetItem>
#include<stdlib.h>
#include<QString>

namespace Ui {
class inputs;
}

//! A GUI class to let the user enter the game settings like number of players and player_type.
class inputs : public QMainWindow
{
    Q_OBJECT
    unsigned num_players;
    unsigned player_type;
    unsigned player_number;
    //server - 1 client - 2
public:
    explicit inputs(QWidget *parent = nullptr);
    ~inputs();

private slots:
    //! This method is executed as input_button is clicked which processes the data and decides to open server_greeting
    //! , client_greeting or the bot instance
    void on_inputs_button_clicked();
    //! This method keeps track of the present highlighted item in player_type
    void on_player_type_list_itemActivated(QListWidgetItem *item);
    //! This method keeps track of the present highlighted item in player_number
    void on_num_players_list_itemActivated(QListWidgetItem *item);

    void on_player_type_list_itemClicked(QListWidgetItem *item);

    void on_num_players_list_itemClicked(QListWidgetItem *item);

private:
    Ui::inputs *ui;
    server_greeting *sg;
    client_greeting *cg;
};

#endif // INPUTS_H
