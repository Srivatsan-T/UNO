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


#include "server_greeting.h"
#include "ui_server_greeting.h"
#include "soundclass.h"

server_greeting::server_greeting(unsigned n,bool card_drop,QWidget *parent) :
    QMainWindow(parent),g(n,card_drop),
    ui(new Ui::server_greeting)
{
    ui->setupUi(this);
    g.start_game();
    is_first_move = true;
    game_over = false;
    server = new QTcpServer(this);
    ui->Submit_button->setEnabled(false);
    ui->server_stack_widget->setCurrentIndex(0);
    ui->add_button->setEnabled(false);
    ui->drop_button->setEnabled(false);
    ui->start_server_button->setEnabled(false);
    socket_stream = nullptr;
    ui->host_ip_input->setText("192.168.0.");
    ui->port_input->setText("1234");
    connect(this,&server_greeting::refresh_signal,this,&server_greeting::show_cards_refresh);
    connect(this,&server_greeting::deck_refresh_signal,this,&server_greeting::show_deck_refresh);
}

server_greeting::~server_greeting()
{
    delete ui;
}

void server_greeting::newConnection()
{

    while(server->hasPendingConnections())
    {
        appendtosockets(server->nextPendingConnection());
    }
}

void server_greeting::cards_count()
{
    ui->player_cards->clear();
    for(unsigned i=0;i<g.h.get_num_user();i++)
    {
        QString text = QString("Player-%1 : %2").arg(i+1).arg(g.h.get_player(i+1).size());
        QFont f("OCR A Extended",12);
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(text);
        item->setFont(f);
        item->setTextAlignment(4);
        ui->player_cards->addItem(item);
    }
}

void server_greeting::appendtosockets(QTcpSocket * s)
{
    socket_list.push_back(s);
    send_message(s);
    connect(s, &QTcpSocket::readyRead, this, &server_greeting::readyRead);
    ui->connections_list->addItem(QString("User with socket id %1 joined").arg(QString::number(s->socketDescriptor())));
    if(ui->connections_list->count() == (g.h.get_num_user()-1) )
    {
        ui->server_started_label->setText("Start Game Now!");
        ui->Submit_button->setEnabled(true);
    }
}

void server_greeting::start_server()
{
    QString title = QString("Server - Player - 1 - %1").arg(Profilemanager::getInstance()->getName());
    this->setWindowTitle(title);
    server->setMaxPendingConnections(g.h.get_num_user()-1);
    QHostAddress add;
    add.setAddress(add_string);
    if(server->listen(add, port_string.toUInt()))
    {
        ui->server_started_label->setText("Server Started");
        connect(server, &QTcpServer::newConnection, this, &server_greeting::newConnection);
    }
    else
    {
        ui->server_started_label->setText("Server could not start!");
    }
}


void server_greeting::readyRead()
{
    QTcpSocket * socket = reinterpret_cast<QTcpSocket *>(sender());
    socket_stream = new QDataStream(socket);
    socket_stream->startTransaction();
    socket_stream->setVersion(QDataStream::Qt_5_15);
    (*socket_stream) >>code>> g;
    if(!socket_stream->commitTransaction())
    {
        return;
    }

    if(code == 0)
    {
    if(g.next_player == 1)
    {
        index = -1;
        ui->info_label->setText("");
        g.is_valid_move = false;
        emit deck_refresh_signal();
        bool res = check_func();
        for(uint i=0;i<g.win_list.size();i++)
        {
            if(g.win_list[i] == true)
            {
                if(game_over == false)
                {
                    Profilemanager *pm = Profilemanager::getInstance();
                    pm->setupui();
                    pm->readStats();
                    pm->findNewStats(g.win_list[0]);
                    pm->fill_up_details();
                    pm->updateProfile();
                    pm->fill_win_det(g.win_list[0]);
                    pm->show();
                    game_over = true;
                    toggle_cards(false);
                    this->close();
                    return;
                }
            }
        }
        toggle_cards(res);
    }
    else
    {
        emit deck_refresh_signal();
        message_passer();
    }
    }
}

void server_greeting::send_all()
{
    for(int i=0;i< socket_list.size();i++)
    {
        send_message(socket_list[i]);
    }
}

void server_greeting::message_passer()
{
    for(int i=0;i<socket_list.size();i++)
    {
        if(socket_list[i]->isOpen())
        {
            QDataStream socket_stream(socket_list[i]);
            socket_stream.setVersion(QDataStream::Qt_5_15);
            int code = 0;
            socket_stream << code<<g;
            socket_list[i]->flush();
        }
        else
        {
            ui->info_label->setText("User not connected anymore!");
        }
    }
}

bool server_greeting::check_func()
{
        for(uint i=0;i<g.win_list.size();i++)
        {
            if(g.h.get_player(i+1).size() == 0)
            {
                g.win_list[i] = true;
            }
        }

        if(g.is_move_available(1) == false)
        {
            ui->info_label->setText("No Moves Available");
            ui->drop_button->setEnabled(false);
        }

        if ((g.h.get_game_deck().back().get_number() == number_t::SKIP) && g.h.get_game_deck().back().get_power() == true)
        {
            ui->info_label->setText("You lost a turn");
            g.h.get_game_deck().back().set_power(false);
            return false;
        }

        if( (g.h.get_game_deck().back().get_number() == number_t::REVERSE) && g.h.get_game_deck().back().get_power() == true)
        {
            ui->info_label->setText("Game Reversed");
            g.h.get_game_deck().back().set_power(false);
         }
        if (g.h.get_game_deck().back().get_number() == number_t::DRAW_TWO && g.h.get_game_deck().back().get_power() == true)
        {
            ui->info_label->setText("2 Cards Added");
            g.player_add(1);
            g.player_add(1);
            g.h.get_game_deck().back().set_power(false);
            emit refresh_signal();
        }
        if (g.h.get_game_deck().back().get_number() == number_t::DRAW_FOUR_WILD && g.h.get_game_deck().back().get_power() == true)
        {
            ui->info_label->setText("4 Cards Added and color changed");
            for (int i = 0; i < 4; i++)
            {
                g.player_add(1);
            }
            g.h.get_game_deck().back().set_power(false);
            emit refresh_signal();
        }
        if (g.h.get_game_deck().back().get_number() == number_t::WILD || g.h.get_game_deck().back().get_number() == number_t::DRAW_FOUR_WILD || g.h.get_game_deck().back().get_number() == number_t::COLOR_DROP)
        {
            QString str = QString("Color changed to %1").arg(g.h.get_game_deck().back().get_color_string());
            ui->info_label->setText(str);
        }
        return true;
}

void server_greeting::send_message(QTcpSocket * c)
{
    if(c->isOpen())
    {
        if(g.h.get_game_deck().back().get_number() == number_t::REVERSE && g.h.get_num_user() == 2)
        {
            g.next_player = 1;
            index = -1;
            ui->info_label->setText("");
            g.is_valid_move = false;
            emit deck_refresh_signal();
            bool res = check_func();
            for(uint i=0;i<g.win_list.size();i++)
            {
                if(g.win_list[i] == true)
                {
                    if(game_over == false)
                    {
                        Profilemanager *pm = Profilemanager::getInstance();
                        pm->setupui();
                        pm->readStats();
                        pm->findNewStats(g.win_list[0]);
                        pm->fill_up_details();
                        pm->updateProfile();
                        pm->fill_win_det(g.win_list[0]);
                        pm->show();
                        game_over = true;
                        toggle_cards(false);
                        this->close();
                        return;
                    }
                }
            }
            toggle_cards(res);
            return;
        }
    else
        {
        if(g.is_clock_wise == true)
        {
            g.next_player = 2;
        }
        else
        {
            g.next_player = g.h.get_num_user();
        }
        }
        QDataStream socket_stream(c);
        socket_stream.setVersion(QDataStream::Qt_5_15);
        int code = 0;
        socket_stream << code<<g;
        c->flush();

    }
    else
    {
        ui->info_label->setText("User not connected anymore!");
    }
}


void server_greeting::on_start_server_button_clicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
    start_server();
}


void server_greeting::card_button_onclicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
    QPushButton *selected = static_cast<QPushButton *>(sender());
    auto it = std::find(g.button_vector.begin(), g.button_vector.end(), selected);
    index = it - g.button_vector.begin();
    std::cout<<index<<std::endl;
}

void server_greeting::show_deck_refresh()
{
    if(!is_first_move)
    {
        g.deck_back[0]->setVisible(false);
        ui->game_deck_layout->removeWidget(g.deck_back[0]);
        g.deck_back.clear();
        g.deck_back.append(g.h.get_game_deck().back().show_card());
        ui->game_deck_layout->addWidget(g.deck_back[0]);
        cards_count();
    }
}


void server_greeting::show_cards_refresh()
{
    for(int i=0;i<g.button_vector.size();i++)
    {
        g.button_vector[i]->setVisible(false);
        ui->gridLayout->removeWidget(g.button_vector[i]);
    }
    g.append_buttons(1);
    for(int i=0;i<g.button_vector.size();i++)
    {
        connect(g.button_vector[i],&QPushButton::clicked,this,&server_greeting::card_button_onclicked);

    }
    for(unsigned  i=0;i<g.button_vector.size();i++)
    {
        ui->gridLayout->addWidget(g.button_vector[i]);
    }
      show_deck_refresh();
}

void server_greeting::player_drop(unsigned n)
{
    if(index == -1)
    {
        return;
    }
    if(is_first_move == true)
    {
        is_first_move = false;
        goto droplabel;
    }
    else{
        if (g.card_drop(n, index+1) == false)
        {
            ui->info_label->setText("Invalid choice");
            return;
        }
        else
        {
droplabel:
            if (g.h.get_player(n)[index].get_number() == number_t::WILD || g.h.get_player(n)[index].get_number() == number_t::DRAW_FOUR_WILD || g.h.get_player(n)[index].get_number() == number_t::COLOR_DROP)
            {
                QMessageBox choice_box;
                choice_box.setText("Select Your Card Color Change");
                QPushButton *redButton = choice_box.addButton(tr("RED"), QMessageBox::ActionRole);
                QPushButton *blueButton = choice_box.addButton(tr("BLUE"),QMessageBox::ActionRole);
                QPushButton *greenButton = choice_box.addButton(tr("GREEN"),QMessageBox::ActionRole);
                QPushButton *yellowButton = choice_box.addButton(tr("YELLOW"),QMessageBox::ActionRole);
                choice_box.exec();
                if(choice_box.clickedButton() == redButton)
                {
                    changed_color = color_t::RED;
                }
                else if(choice_box.clickedButton() == blueButton)
                {
                    changed_color = color_t::BLUE;
                }
                else if(choice_box.clickedButton() == greenButton)
                {
                    changed_color = color_t::GREEN;
                }
                else if(choice_box.clickedButton() == yellowButton)
                {
                    changed_color = color_t::YELLOW;
                }
                if(g.h.get_player(n)[index].get_number() == number_t::COLOR_DROP)
                {
                    for(int i=0;i<g.h.get_player(n).size();i++)
                    {
                        if(g.h.get_player(n)[i].get_color() == changed_color)
                        {
                            g.h.get_game_deck().push_back(g.h.get_player(n)[i]);
                        }
                    }
                }
                g.h.get_player(n)[index] = card(changed_color, g.h.get_player(n)[index].get_number());
                g.h.get_game_deck().push_back(g.h.get_player(n)[index]);
                g.h.get_player(n).erase(g.h.get_player(n).begin() + index);

                if(g.h.get_game_deck().back().get_number() == number_t::COLOR_DROP)
                {
                    QVector<card> temp_vector;
                    for(int i=0;i<g.h.get_player(n).size();i++)
                    {
                        if(g.h.get_player(n)[i].get_color() != g.h.get_game_deck().back().get_color())
                        {
                            temp_vector.push_back(g.h.get_player(n)[i]);
                        }
                    }
                    g.h.get_player(n) = temp_vector;
                }

                g.is_valid_move = true;
                ui->info_label->setText("");
                emit refresh_signal();
                toggle_cards(false);
                return;
            }
            else if(g.h.get_player(n)[index].get_number() == number_t::REVERSE)
            {
                g.is_clock_wise = !g.is_clock_wise;
                g.h.get_game_deck().push_back(g.h.get_player(n)[index]);
                g.h.get_player(n).erase(g.h.get_player(n).begin() + index);
                g.is_valid_move = true;
                ui->info_label->setText("");
                emit refresh_signal();
                toggle_cards(false);
                return;
            }
            else
            {
                g.h.get_game_deck().push_back(g.h.get_player(n)[index]);
                g.h.get_player(n).erase(g.h.get_player(n).begin() + index);
                g.is_valid_move = true;
                ui->info_label->setText("");
                emit refresh_signal();
                toggle_cards(false);
                return;
            }
        }
    }
}



void server_greeting::toggle_cards(bool choice)
{
    for(int i=0;i<g.button_vector.size();i++)
    {
        g.button_vector[i]->setEnabled(choice);
    }
    ui->add_button->setEnabled(choice);
    ui->drop_button->setEnabled(choice);
    if(choice == false)
    {
        send_all();
    }
}


void server_greeting::on_Submit_button_clicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
    ui->server_stack_widget->setCurrentIndex(ui->server_stack_widget->currentIndex() +1);
    g.is_valid_move = false;
    emit refresh_signal();
    toggle_cards(true);
}

void server_greeting::on_add_button_clicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
    index = -1;
    ui->add_button->setEnabled(false);
    g.player_add(1);
    emit refresh_signal();
    if(g.is_move_available(1) == false)
    {
        ui->info_label->setText("No moves after adding");
        toggle_cards(false);
        return;
    }
    else
    {
        QMessageBox choice_box;
        choice_box.setText("Do you want to drop a card now?");
        QPushButton *yesButton = choice_box.addButton(tr("Yes"), QMessageBox::ActionRole);
        QPushButton *noButton = choice_box.addButton(tr("No"),QMessageBox::ActionRole);
        choice_box.exec();
        if(choice_box.clickedButton() == yesButton)
        {
            for(int i=0;i<g.button_vector.size();i++)
            {
                g.button_vector[i]->setEnabled(true);
            }
        }
        else if(choice_box.clickedButton() == noButton)
        {
            toggle_cards(false);
        }
    }

}

void server_greeting::on_drop_button_clicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
    if(index == -1)
    {
        return;
    }
    else
    {
        player_drop(1);
        return;
    }
}

void server_greeting::on_host_ip_button_clicked()
{
    soundclass *sd=sd->getinstance();
    sd->playeffects(1);
    add_string = ui->host_ip_input->text();
    port_string = ui->port_input->text();
    ui->start_server_button->setEnabled(true);
}
