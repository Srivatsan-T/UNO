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

#include "profilemanager.h"
#include "ui_profilemanager.h"
#include<fstream>
#include<QString>
#include "soundclass.h"
#include <QtWidgets>

Profilemanager* Profilemanager::instance = nullptr;
Profilemanager::Profilemanager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Profilemanager)
{
    ui->setupUi(this);
}

Profilemanager::~Profilemanager()
{
    delete ui;
}
Profilemanager::Profilemanager(int argument)//as of now, argument is only used to change the signature of the constructor beacuse of ambiguity
{
}
Profilemanager* Profilemanager::getInstance()
{
    if (!Profilemanager::instance){
        Profilemanager::instance = new Profilemanager(1);
    }
    Profilemanager::instance->readStats();
    return Profilemanager::instance;
}

void Profilemanager::fill_up_details()
{
    ui->win_info_label->hide();
    ui->profile_right->item(0)->setText(instance->name);
    ui->profile_right->item(1)->setText(QString::number(instance->level));
    ui->profile_right->item(2)->setText(QString::number(instance->xp));
    ui->profile_right->item(3)->setText(QString::number(instance->xp_left));
    ui->profile_right->item(4)->setText(QString::number(instance->games_played));
    ui->profile_right->item(5)->setText(QString::number(instance->games_won));
    ui->profile_right->item(6)->setText(QString::number(instance->winrate));
}

void Profilemanager::fill_win_det(bool win_det)
{
    ui->win_info_label->show();
    QString txt;
    if(win_det == true)
    {
        txt = "You Won!";
    }
    else
    {
        txt = "Sorry! You Lost";
    }
    ui->win_info_label->setText(txt);
}
void Profilemanager::setupui()
{
    ui = new Ui::Profilemanager;
    ui->setupUi(getInstance());
    this->setWindowTitle(QString("Profile- %1").arg(this->getName()));
    if(getInstance()->name != "<default_name>")
    {
        ui->label_2->hide();
        ui->lineEdit->hide();
    }
}
void Profilemanager::readStats()
{
    std::ifstream reader;
    reader.open("profiledata.txt");
    if(reader.fail())
    {
        Profilemanager::instance->resetProfile();
    }
    std::string temp_input;
    reader>>temp_input;
    name=QString::fromStdString(temp_input);
    reader>>level;
    reader>>xp;
    reader>>games_played;
    reader>>games_won;
    reader>>winrate;
    reader.close();
}
void Profilemanager::setName(QString name_input)
{
    Profilemanager::instance->name=name_input;
}
QString Profilemanager::getName()
{
    return Profilemanager::instance->name;
}
int Profilemanager::getLevel()
{
    return Profilemanager::instance->level;

}
int Profilemanager::getXP()
{
    return Profilemanager::instance->xp;
}
int Profilemanager::getPlayed()
{
    return Profilemanager::instance->games_played;

}
int Profilemanager::getWon()
{
    return Profilemanager::instance->games_won;

}
int Profilemanager::getXPLeft()
{
    //The system is 50xp*level no. is the total xp required to the next level with 50 for a win and 25 for a loss
    return Profilemanager::instance->getLevel()*50-Profilemanager::instance->getXP();
}
void Profilemanager::findNewStats(bool win_status)
{
    Profilemanager::instance->games_played+=1;
    if(win_status)
    {
        Profilemanager::instance->games_won+=1;
        Profilemanager::instance->xp+=50;
    }
    else
    {
        Profilemanager::instance->xp+=25;
    }
   Profilemanager::instance->winrate=Profilemanager::instance->games_won/Profilemanager::instance->games_played;
    if(Profilemanager::instance->xp>=Profilemanager::instance->level*50)
    {
        //some level up text too
        Profilemanager::instance->level+=1;
        Profilemanager::instance->xp-=(Profilemanager::instance->level-1)*50;
    }
}
void Profilemanager::updateProfile()
{
    std::ofstream writer;
    writer.open("profiledata.txt");
    writer<<Profilemanager::instance->name.toStdString()<<std::endl;//fix to work with qstring
    writer<<Profilemanager::instance->level<<std::endl;
    writer<<Profilemanager::instance->xp<<std::endl;
    writer<<Profilemanager::instance->games_played<<std::endl;
    writer<<Profilemanager::instance->games_won<<std::endl;
    writer<<Profilemanager::instance->winrate<<std::endl;
    writer.close();
}
void Profilemanager::resetProfile()
{
    std::ofstream writer;
    Profilemanager::instance->name="<default_name>";
    Profilemanager::instance->level=1;
    Profilemanager::instance->xp=0;
    Profilemanager::instance->games_played=0;
    Profilemanager::instance->games_won=0;
    Profilemanager::instance->winrate=0;
    writer.open("profiledata.txt");
    writer<<Profilemanager::instance->name.toStdString()<<std::endl;//fix to work with qstring
    writer<<Profilemanager::instance->level<<std::endl;
    writer<<Profilemanager::instance->xp<<std::endl;
    writer<<Profilemanager::instance->games_played<<std::endl;
    writer<<Profilemanager::instance->games_won<<std::endl;
    writer<<Profilemanager::instance->winrate<<std::endl;
    writer.close();
}

void Profilemanager::on_lineEdit_editingFinished()
{
    setName(ui->lineEdit->text());
    //ui->lineEdit->hide();
    //ui->label_2->hide();
    fill_up_details();
    updateProfile();
    this->setWindowTitle("Profile - "+ui->lineEdit->text());
    ui->lineEdit->clear();
}

//close event for profile manager window

void Profilemanager::closeEvent(QCloseEvent *event)
{
    soundclass* sd=sd->getinstance();
    sd->delete_all();
    event->accept();
}

