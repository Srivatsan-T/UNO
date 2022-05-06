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


#include "client_greeting.h"
#include "ui_client_greeting.h"
#include "soundclass.h"

client_greeting::client_greeting(unsigned pn,unsigned n,QWidget *parent) :
    QMainWindow(parent),g(n),
    ui(new Ui::client_greeting)
{
    ui->setupUi(this);
    player_number = pn;
    game_over = false;
    socket = new QTcpSocket(this);
    ui->client_stack_widget->setCurrentIndex(0);
    g.start_game();
    ui->add_button_client->setEnabled(false);
    ui->drop_button_client->setEnabled(false);
    connect(this,&client_greeting::refresh_signal,this,&client_greeting::show_cards_refresh);
    is_first_message = true;
    ui->host_ip_input->setText("192.168.0.");
    ui->port_input->setText("1234");
}

client_greeting::~client_greeting()
{
    delete ui;
}


void client_greeting::start_client()
{

    QString ip = ui->host_ip_input->text();
    QString port = ui->port_input->text();
    player_number = ui->player_number_input->text().toInt();
    QString title = QString("Player- %1 - %2").arg(player_number).arg(Profilemanager::getInstance()->getName());
    connect(socket,&QTcpSocket::readyRead,this,&client_greeting::on_readyRead);
    connect(this,&client_greeting::deck_refresh_signal,this,&client_greeting::show_deck_refresh);
    connect(this,&client_greeting::refresh_signal,this,&client_greeting::show_cards_refresh);
    connect(socket,&QTcpSocket::errorOccurred,this,&client_greeting::connection_error);
    connect(socket,&QTcpSocket::connected,this,&client_greeting::server_connected);
    this->setWindowTitle(title);
    socket->connectToHost(ip,port.toUInt());
}

void client_greeting::connection_error()
{
    std::cout<<socket->errorString().toStdString();
    ui->info_label->setText("Sevrer not open");
}

void client_greeting::server_connected()
{
    ui->client_stack_widget->setCurrentIndex(ui->client_stack_widget->currentIndex() + 1);
}

void client_greeting::on_readyRead()
{

    socket_stream = new QDataStream(socket);
    socket_stream->setVersion(QDataStream::Qt_5_15);
    socket_stream->startTransaction();
    (*socket_stream) >> code >>g;
    if(!socket_stream->commitTransaction())
    {
        return;
    }
    if(code == 0)
    {
        if(is_first_message == true)
        {
            emit refresh_signal();
            is_first_message = false;
        }
        else
        {
            if(g.next_player == player_number)
            {
                index = -1;
                g.is_valid_move = false;
                ui->info_label_client->setText("");
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
                            pm->findNewStats(g.win_list[player_number-1]);
                            pm->fill_up_details();
                            pm->updateProfile();
                            pm->fill_win_det(g.win_list[player_number-1]);
                            pm->show();
                            toggle_cards(false);
                            this->close();
                            game_over = true;
                            return;
                        }
                    }
                }
                toggle_cards(res);
            }
            else
            {
                emit refresh_signal();
            }
        }
    }
    else if(code == 1)
    {

    }
}


bool client_greeting::check_func()
{
    for(uint i=0;i<g.win_list.size();i++)
    {
        if(g.h.get_player(i+1).size() == 0)
        {
            g.win_list[i] = true;
        }
    }
    if(g.is_move_available(player_number) == false)
    {
        ui->info_label_client->setText("No Moves Available");
        ui->drop_button_client->setEnabled(false);
    }

        if ((g.h.get_game_deck().back().get_number() == number_t::SKIP) && g.h.get_game_deck().back().get_power() == true)
        {
            ui->info_label_client->setText("You lost a turn");
            g.h.get_game_deck().back().set_power(false);
            return false;
        }

        if( (g.h.get_game_deck().back().get_number() == number_t::REVERSE) && g.h.get_game_deck().back().get_power() == true)
        {
            ui->info_label_client->setText("Game Reversed");
            g.h.get_game_deck().back().set_power(false);
        }

        if (g.h.get_game_deck().back().get_number() == number_t::DRAW_TWO && g.h.get_game_deck().back().get_power() == true)
        {
            ui->info_label_client->setText("2 Cards Added");
            g.player_add(player_number);
            g.player_add(player_number);
            g.h.get_game_deck().back().set_power(false);
            emit refresh_signal();
        }
        if (g.h.get_game_deck().back().get_number() == number_t::DRAW_FOUR_WILD && g.h.get_game_deck().back().get_power() == true)
        {
            ui->info_label_client->setText("4 Cards Added and color changed");
            for (int i = 0; i < 4; i++)
            {
                g.player_add(player_number);
            }
            g.h.get_game_deck().back().set_power(false);
            emit refresh_signal();
        }
        if (g.h.get_game_deck().back().get_number() == number_t::WILD || g.h.get_game_deck().back().get_number() == number_t::DRAW_FOUR_WILD)
        {
            QString str = QString("Color changed to %1").arg(g.h.get_game_deck().back().get_color_string());
            ui->info_label_client->setText(str);
        }
        return true;
}


void client_greeting::send_message(QTcpSocket* c)
{
    if(c->isOpen())
    {
        if(g.h.get_game_deck().back().get_number() == number_t::REVERSE && g.h.get_num_user() == 2)
        {
            g.next_player = player_number;
        }
        else
        {
        if(g.is_clock_wise == true)
        {
            if(player_number == g.h.get_num_user())
            {
                g.next_player = 1;
            }
            else
            {
                g.next_player = player_number +1;
            }
        }
        else
        {
             g.next_player = player_number -1;
        }
        }
        QDataStream socket_stream(c);
        socket_stream.setVersion(QDataStream::Qt_5_15);
        int code = 0;
        socket_stream <<code<< g;
        socket->flush();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Server not connected anymore!");
        msgBox.exec();
    }
}



void client_greeting::on_connect_button_clicked()
{
    soundclass *sd=sd->getinstance();
    sd->playeffects(1);
    if(ui->player_number_input->text().toUInt() <=1 || ui->player_number_input->text().toUInt() > g.h.get_num_user())
    {
       ui->info_label->setText("Player number invalid");
       return;
    }
    start_client();
    //ui->client_stack_widget->setCurrentIndex(ui->client_stack_widget->currentIndex() + 1);
}






void client_greeting::card_button_onclicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
    QPushButton *selected = static_cast<QPushButton *>(sender());
    auto it = std::find(g.button_vector.begin(), g.button_vector.end(), selected);
    index = it - g.button_vector.begin();
    std::cout<<index<<std::endl;
}

void client_greeting::show_deck_refresh()
{
    g.deck_back[0]->setVisible(false);
    ui->game_deck_layout_client->removeWidget(g.deck_back[0]);
    g.deck_back.clear();
    g.deck_back.push_back(g.h.get_game_deck().back().show_card());
    ui->game_deck_layout_client->addWidget(g.deck_back[0]);
    cards_count();
}


void client_greeting::show_cards_refresh()
{
    for(int i=0;i<g.button_vector.size();i++)
    {
        g.button_vector[i]->setVisible(false);
        ui->gridLayout_client->removeWidget(g.button_vector[i]);
    }
    g.append_buttons(player_number);
    for(int i=0;i<g.button_vector.size();i++)
    {
        connect(g.button_vector[i],&QPushButton::clicked,this,&client_greeting::card_button_onclicked);

    }

    for(unsigned  i=0;i<g.button_vector.size();i++)
    {
        ui->gridLayout_client->addWidget(g.button_vector[i]);
    }
    show_deck_refresh();
}

void client_greeting::cards_count()
{
    ui->player_cards_client->clear();
    for(unsigned i=0;i<g.h.get_num_user();i++)
    {
        QString text = QString("Player-%1 : %2").arg(i+1).arg(g.h.get_player(i+1).size());
        QFont f("OCR A Extended",12);
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(text);
        item->setFont(f);
        item->setTextAlignment(4);
        ui->player_cards_client->addItem(item);
    }
}


void client_greeting::player_drop(unsigned n)
{
    if(index == -1)
    {
        return;
    }
    else
    {
        if (g.card_drop(n, index+1) == false)
        {
            ui->info_label_client->setText("Invalid choice");
            return;
        }
        else
        {
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
                ui->info_label_client->setText("");
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
                ui->info_label_client->setText("");
                emit refresh_signal();
                toggle_cards(false);
                return;
            }
            else
            {
                g.h.get_game_deck().push_back(g.h.get_player(n)[index]);
                g.h.get_player(n).erase(g.h.get_player(n).begin() + index);
                g.is_valid_move = true;
                ui->info_label_client->setText("");
                emit refresh_signal();
                toggle_cards(false);
                return;
            }
        }
    }


}



void client_greeting::toggle_cards(bool choice)
{
    for(int i=0;i<g.button_vector.size();i++)
    {
        g.button_vector[i]->setEnabled(choice);
    }
    ui->add_button_client->setEnabled(choice);
    ui->drop_button_client->setEnabled(choice);
    if(choice == false)
    {
        send_message(socket);
    }
}



void client_greeting::on_add_button_client_clicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
    index = -1;
    ui->add_button_client->setEnabled(false);
    g.player_add(player_number);
    emit refresh_signal();
    if(g.is_move_available(player_number) == false)
    {
        ui->info_label_client->setText("No moves after adding");
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

void client_greeting::on_drop_button_client_clicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
    if(index == -1)
    {
        return;
    }
    else
    {
        player_drop(player_number);
    }
}
