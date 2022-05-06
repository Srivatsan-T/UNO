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


#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H
#include<fstream>
#include<QString>
#include <QDialog>

namespace Ui {
class Profilemanager;
}

class Profilemanager : public QDialog
{
    Q_OBJECT
private:
    Ui::Profilemanager *ui;
    static Profilemanager* instance;
    QString name;
    int level; int xp; int games_played; int games_won; int xp_left;
    double winrate;
    Profilemanager(int argument);//for now, to create a different signature
    explicit Profilemanager(QWidget *parent = nullptr);

public:

    ~Profilemanager();
    void setupui();
    void fill_up_details();
    void fill_win_det(bool);
    static Profilemanager* getInstance();
    void readStats();
    QString getName();
    void setName(QString name_input);
    int getLevel();
    int getXP();
    int getXPLeft();
    int getPlayed();
    int getWon();
    void findNewStats(bool win_status);
    void updateProfile();
    void resetProfile();


private slots:
    void on_lineEdit_editingFinished();


protected:
    void closeEvent(QCloseEvent *event) override;

};

#endif // PROFILEMANAGER_H
