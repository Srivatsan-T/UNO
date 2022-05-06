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


#ifndef GREETING_H
#define GREETING_H

#include <QMainWindow>
#include "rules.h"
#include "inputs.h"
#include "profilemanager.h"

namespace Ui {
class greeting;
}

//! A GUI class to display the user with navigations for start, rules, profile and exit options.
class greeting : public QMainWindow
{
    Q_OBJECT

public:
    explicit greeting(QWidget *parent = nullptr);
    ~greeting();

private slots:
    //! This method is invoked when user presses the start button and it leads to inputs page
    void on_start_button_clicked();
    //! This method closes the game when exit button is pressed
    void on_exit_button_clicked();
    //! This button opens up the rules page when the rules button is pressed
    void on_rules_button_clicked();
    //! This button opens up the profile manager page when the corresponding button is pressed
    void on_profile_button_clicked();

private:
    Ui::greeting *ui;
    rules *r;
    inputs *i;
    Profilemanager *pm;
};

#endif // GREETING_H
