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


/********************************************************************************
** Form generated from reading UI file 'greeting.ui'
**
** Created by: Qt User Interface Compiler version 6.0.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef GREETINGS_H
#define GREETINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_greeting
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QFrame *frame;
    QPushButton *start_button;
    QPushButton *rules_button;
    QPushButton *exit_button;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *greeting)
    {
        if (greeting->objectName().isEmpty())
            greeting->setObjectName(QString::fromUtf8("greeting"));
        greeting->resize(800, 600);
        greeting->setStyleSheet(QString::fromUtf8("background:yellow"));
        centralwidget = new QWidget(greeting);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);
        label->setGeometry(QRect(80, 20, 624, 83));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("OCR A Extended"));
        font.setPointSize(48);
        font.setBold(false);
        label->setFont(font);
        label->setCursor(QCursor(Qt::CrossCursor));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setStyleSheet(QString::fromUtf8("background:white"));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(230, 200, 311, 251));
        frame->setStyleSheet(QString::fromUtf8("background-color:orange"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        start_button = new QPushButton(frame);
        start_button->setObjectName(QString::fromUtf8("start_button"));
        start_button->setGeometry(QRect(60, 30, 191, 51));
        start_button->setStyleSheet(QString::fromUtf8("background-color:white"));
        start_button->setCheckable(false);
        rules_button = new QPushButton(frame);
        rules_button->setObjectName(QString::fromUtf8("rules_button"));
        rules_button->setGeometry(QRect(60, 110, 191, 51));
        rules_button->setStyleSheet(QString::fromUtf8("background-color:white"));
        exit_button = new QPushButton(frame);
        exit_button->setObjectName(QString::fromUtf8("exit_button"));
        exit_button->setGeometry(QRect(60, 180, 191, 51));
        exit_button->setStyleSheet(QString::fromUtf8("background-color:white"));
        greeting->setCentralWidget(centralwidget);
        menubar = new QMenuBar(greeting);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        greeting->setMenuBar(menubar);
        statusbar = new QStatusBar(greeting);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        greeting->setStatusBar(statusbar);

        retranslateUi(greeting);

        QMetaObject::connectSlotsByName(greeting);
    } // setupUi

    void retranslateUi(QMainWindow *greeting)
    {
        greeting->setWindowTitle(QCoreApplication::translate("greeting", "UNO", nullptr));
        label->setText(QCoreApplication::translate("greeting", "You-Know-UNO?", nullptr));
        start_button->setText(QCoreApplication::translate("greeting", "Start", nullptr));
        rules_button->setText(QCoreApplication::translate("greeting", "Rules", nullptr));
        exit_button->setText(QCoreApplication::translate("greeting", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class greeting: public Ui_greeting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GREETINGS_H
