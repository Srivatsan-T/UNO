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


#include "greeting.h"
#include "ui_greeting.h"
#include "soundclass.h"

greeting::greeting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::greeting)
{
    ui->setupUi(this);
    this->setWindowTitle("You-Know-UNO?");
}

greeting::~greeting()
{
    delete ui;
}



void greeting::on_start_button_clicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
    i = new inputs;
    i->show();
    this->close();
}

void greeting::on_exit_button_clicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
        sd->delete_all();
    this->close();
}

void greeting::on_rules_button_clicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
    r = new rules;
    r->show();
}

void greeting::on_profile_button_clicked()
{
    soundclass *sd=sd->getinstance();
        sd->playeffects(1);
    pm = pm->getInstance();
    pm->setupui();
    pm->fill_up_details();
    pm->show();
}
