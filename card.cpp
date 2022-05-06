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

#include "card.h"

card::card(color_t c, number_t n)
{
    color = c;
    number = n;
    power = true;
    get_color_string();
    get_number_string();
}

card::card()
{
    color = color_t::NO_COLOR;
    number = number_t::NO_NUMBER;
    power = true;
    get_color_string();
    get_number_string();
}

card::card(const card &s)
{
    color = s.color;
    number = s.number;
    power = s.power;
    get_color_string();
    get_number_string();
}
card::card(card* s)
{
    color=s->color;
    number=s->number;
    power=s->power;
    get_color_string();
    get_number_string();

}
color_t card::get_color() const
{
    return color;
}

number_t card::get_number() const
{
    return number;
}

bool card::get_power() const
{
    return power;
}

void card::set_power(bool val)
{
    power = val;
}




 QString card::get_color_string()
{
    if (get_color() == color_t::RED)
    {
        color_string = "RED";
    }
    else if (get_color() == color_t::BLUE)
    {
        color_string = "BLUE";
    }
    else if (get_color() == color_t::GREEN)
    {
        color_string = "GREEN";
    }
    else if (get_color() == color_t::YELLOW)
    {
        color_string = "YELLOW";
    }
    else if (get_color() == color_t::NO_COLOR)
    {
        color_string = "BLACK";
    }
    return color_string;
}

 QString card::get_number_string()
{
    if (get_number() == number_t::ZERO)
    {
        number_string = "0";
    }
    else if (get_number() == number_t::ONE)
    {
        number_string = "1";
    }
    else if (get_number() == number_t::TWO)
    {
        number_string = "2";
    }
    else if (get_number() == number_t::THREE)
    {
        number_string = "3";
    }
    else if (get_number() == number_t::FOUR)
    {
        number_string = "4";
    }
    else if (get_number() == number_t::FIVE)
    {
        number_string = "5";
    }
    else if (get_number() == number_t::SIX)
    {
        number_string = "6";
    }
    else if (get_number() == number_t::SEVEN)
    {
        number_string = "7";
    }
    else if (get_number() == number_t::EIGHT)
    {
        number_string = "8";
    }
    else if (get_number() == number_t::NINE)
    {
        number_string = "9";
    }
    else if (get_number() == number_t::TEN)
    {
        number_string = "10";
    }

    if (get_number() == number_t::SKIP)
    {
        number_string = "SKIP";
    }

    else if (get_number() == number_t::REVERSE)
    {
        number_string = "REVERSE";
    }

    else if (get_number() == number_t::DRAW_TWO)
    {
        number_string = "DRAW-TWO";
    }

    else if (get_number() == number_t::WILD)
    {
        number_string = "WILD";
    }

    else if (get_number() == number_t::DRAW_FOUR_WILD)
    {
        number_string = "DRAW-FOUR-WILD";
    }
    else if(get_number() == number_t::COLOR_DROP)
    {
        number_string = "COLOR-DROP";
    }
    else if(get_number() == number_t::NO_NUMBER)
    {
        number_string = "NO-NUMBER";
    }
    return number_string;
}


void card::operator=(const card &c)
{
    color = c.color;
    number = c.number;
    power = c.power;
}
/*  overloaded for safety
 *
 */
bool card::operator==(card c) const
{
    if(color==c.color&&number==c.number)
    {
        return true;
    }
    return false;
}
bool card::operator==(card *c) const
{
    if(color==c->color&&number==c->number)
    {
        return true;
    }
    return false;
}

QDataStream& operator<<(QDataStream& out, const card& c)
{
    out<<c.color_string;
    out<<c.number_string;
    out<<c.get_power();
    return out;
}

QDataStream& operator>>(QDataStream &in, card& c)
{
    bool power;
    in>>c.color_string;
    in>>c.number_string;
    in>>power;
    c.set_power(power);
    c.color_string_to_enum(c.color_string,c.number_string);
    return in;
}

void card::color_string_to_enum(QString _color,QString _number)
{
    if(_color == "RED")
    {
        color = color_t::RED;
    }
    else if(_color == "BLUE")
    {
        color = color_t::BLUE;
    }
    else if(_color == "GREEN")
    {
        color = color_t::GREEN;
    }
    else if(_color == "YELLOW")
    {
        color = color_t::YELLOW;
    }
    else if(_color == "BLACK")
    {
        color = color_t::NO_COLOR;
    }
    else
    {
        color = color_t::NO_COLOR;
    }

    if(_number == "0")
    {
        number = number_t::ZERO;
    }
    else if(_number == "1")
    {
        number = number_t::ONE;
    }
    else if(_number == "2")
    {
        number = number_t::TWO;
    }
    else if(_number == "3")
    {
        number = number_t::THREE;
    }
    else if(_number == "4")
    {
        number = number_t::FOUR;
    }
    else if(_number == "5")
    {
        number = number_t::FIVE;
    }
    else if(_number == "6")
    {
        number = number_t::SIX;
    }
    else if(_number == "7")
    {
        number = number_t::SEVEN;
    }
    else if(_number == "8")
    {
        number = number_t::EIGHT;
    }
    else if(_number == "9")
    {
        number = number_t::NINE;
    }
    else if(_number == "10")
    {
        number = number_t::TEN;
    }

    else if(_number == "SKIP")
    {
        number = number_t::SKIP;
    }
    else if(_number == "REVERSE")
    {
        number = number_t::REVERSE;
    }
    else if(_number == "DRAW-TWO")
    {
        number = number_t::DRAW_TWO;
    }
    else if(_number == "WILD")
    {
        number = number_t::WILD;
    }
    else if(_number == "DRAW-FOUR-WILD")
    {
        number = number_t::DRAW_FOUR_WILD;
    }
    else if(_number == "NO-NUMBER")
    {
        number = number_t::NO_NUMBER;
    }
    else if(_number == "COLOR-DROP")
    {
        number = number_t::COLOR_DROP;
    }
}


QPushButton * card::show_card()
{
    QColor col;
    QPushButton *card_button = new QPushButton();
    //card_button->setFixedSize(QSize(70,100));
    if(get_color() == color_t::RED)
    {
        col = red;
    }
    else if(get_color() == color_t::BLUE)
    {
        col = blue;
    }
    else if(get_color() == color_t::GREEN)
    {
        col = green;
    }
    else if(get_color() == color_t::YELLOW)
    {
        col = yellow;
    }
    else if(get_color() == color_t::NO_COLOR)
    {
        col = white;
    }
    QString color = QString("background-color: %1").arg(col.name());
    card_button->setStyleSheet(color);
    /*
    if(get_number_string() == "DRAW-TWO")
    {
        card_button->setText(get_color_string() + "\n" + "DRAW\nTWO");
    }
    else if(get_number_string() == "DRAW-FOUR-WILD")
    {
        card_button->setText(get_color_string() + "\n" + "DRAW\nFOUR\nWILD");
    }
    else if(get_number_string() == "COLOR-DROP")
    {
        card_button->setText(get_color_string() + "\n" + "COLOR\nDROP");
    }
    else
    {
        card_button->setText(get_color_string() + "\n" +get_number_string());
    }
    */
    card_button->setText(get_color_string() + "-" +get_number_string());
    return card_button;
}

