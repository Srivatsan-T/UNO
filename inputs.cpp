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


#include "inputs.h"
#include "ui_inputs.h"
#include "soundclass.h"

inputs::inputs(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::inputs)
{
    ui->setupUi(this);
    player_type = 0;
    num_players = 0;
    player_number = 2;
    ui->inputs_button->setEnabled(false);
    ui->check_box_frame->hide();
    ui->game_option_label->hide();
    this->setWindowTitle("Inputs");
}

inputs::~inputs()
{
    delete ui;
}



void inputs::on_inputs_button_clicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
    if(player_type == 1)
    {
        sg = new server_greeting(num_players,ui->color_drop_card_checkbox->isChecked());
        sg->show();
        this->close();
    }
    else if(player_type == 2)
    {
        cg = new client_greeting(player_number,num_players);
        cg->show();
        this->close();
    }
}

void inputs::on_player_type_list_itemActivated(QListWidgetItem *item)
{
    if(ui->player_type_list->item(0) == item)
    {
        ui->check_box_frame->show();
        ui->game_option_label->show();
        player_type = 1;
    }
    else if(ui->player_type_list->item(1) == item)
    {
        ui->check_box_frame->hide();
        ui->game_option_label->hide();
        player_type = 2;
    }
    if(player_type > 0 && num_players > 0)
    {
        ui->inputs_button->setEnabled(true);
    }
}

void inputs::on_num_players_list_itemActivated(QListWidgetItem *item)
{
    if(ui->num_players_list->item(0) == item)
    {
        num_players = 2;
    }
    else if(ui->num_players_list->item(1) == item)
    {
        num_players = 3;
    }
    else if(ui->num_players_list->item(2) == item)
    {
        num_players = 4;
    }
    else if(ui->num_players_list->item(3) == item)
    {
        num_players = 5;
    }
    else if(ui->num_players_list->item(4) == item)
    {
        num_players = 6;
    }

    if(player_type > 0 && num_players > 0)
    {
        ui->inputs_button->setEnabled(true);
    }
}

void inputs::on_player_type_list_itemClicked(QListWidgetItem *item)
{
    if(ui->player_type_list->item(0) == item)
    {
        ui->check_box_frame->show();
        ui->game_option_label->show();
        player_type = 1;
    }
    else if(ui->player_type_list->item(1) == item)
    {
        ui->check_box_frame->hide();
        ui->game_option_label->hide();
        player_type = 2;
    }
    if(player_type > 0 && num_players > 0)
    {
        ui->inputs_button->setEnabled(true);
    }
}



void inputs::on_num_players_list_itemClicked(QListWidgetItem *item)
{
    if(ui->num_players_list->item(0) == item)
    {
        num_players = 2;
    }
    else if(ui->num_players_list->item(1) == item)
    {
        num_players = 3;
    }
    else if(ui->num_players_list->item(2) == item)
    {
        num_players = 4;
    }
    else if(ui->num_players_list->item(3) == item)
    {
        num_players = 5;
    }
    else if(ui->num_players_list->item(4) == item)
    {
        num_players = 6;
    }

    if(player_type > 0 && num_players > 0)
    {
        ui->inputs_button->setEnabled(true);
    }
}

