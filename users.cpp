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


#include "users.h"

users::users(unsigned n,bool color_drop)
{
    number_players = n;
    color_drop_card = color_drop;
    QVector<card> card_list;
    for(unsigned i=0;i<n;i++)
    {
        player_list.push_back(card_list);
    }
}

unsigned users::get_num_user() const
{
    return number_players;
}


void users::fill_up_players(unsigned num)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle (users::deck.begin(), users::deck.end(),e);

    for(int i=0;i<10;i++)
    {
        player_list[0].emplace_back(deck[i]);
    }

    for(int i=10;i<20;i++)
    {
        player_list[1].emplace_back(deck[i]);
    }
    if(num == 3)
    {

        for(int i=20;i<30;i++)
        {
            player_list[2].emplace_back(deck[i]);
        }
    }
    else if(num == 4)
    {

        for(int i=20;i<30;i++)
        {
            player_list[2].emplace_back(deck[i]);
        }

        for(int i=30;i<40;i++)
        {
            player_list[3].emplace_back(deck[i]);
        }
    }

    else if(num == 5)
    {
        for(int i=20;i<30;i++)
        {
            player_list[2].emplace_back(deck[i]);
        }

        for(int i=30;i<40;i++)
        {
            player_list[3].emplace_back(deck[i]);
        }
        for(int i=40;i<50;i++)
        {
            player_list[4].emplace_back(deck[i]);
        }
    }
    else if(num == 6)
    {
        for(int i=20;i<30;i++)
        {
            player_list[2].emplace_back(deck[i]);
        }

        for(int i=30;i<40;i++)
        {
            player_list[3].emplace_back(deck[i]);
        }
        for(int i=40;i<50;i++)
        {
            player_list[4].emplace_back(deck[i]);
        }

        for(int i=50;i<60;i++)
        {
            player_list[5].emplace_back(deck[i]);
        }
    }

    for(int i=num*10;i<deck.size();i++)
    {
        game_deck.emplace_back(deck[i]);
    }

}

QVector<card> users::generate_deck()
{
    for(int i = 0;i<10;i++)
    {
        deck.push_back(card(color_t::BLUE, static_cast<number_t>(i) ));
    }
    for(int i=10;i<19;i++)
    {
        deck.push_back(card(color_t::BLUE,static_cast<number_t>(i-9)));
    }
    deck.push_back(card(color_t::BLUE,number_t::SKIP));
    deck.push_back(card(color_t::BLUE,number_t::SKIP));
    deck.push_back(card(color_t::BLUE,number_t::REVERSE));
    deck.push_back(card(color_t::BLUE,number_t::REVERSE));
    deck.push_back(card(color_t::BLUE,number_t::DRAW_TWO));
    deck.push_back(card(color_t::BLUE,number_t::DRAW_TWO));

    for(int i = 0;i<10;i++)
    {
        deck.push_back(card(color_t::RED,static_cast<number_t>(i)));
    }
    for(int i=10;i<19;i++)
    {
        deck.push_back(card(color_t::RED,static_cast<number_t>(i-9)));
    }
    deck.push_back(card(color_t::RED,number_t::SKIP));
    deck.push_back(card(color_t::RED,number_t::SKIP));
    deck.push_back(card(color_t::RED,number_t::REVERSE));
    deck.push_back(card(color_t::RED,number_t::REVERSE));
    deck.push_back(card(color_t::RED,number_t::DRAW_TWO));
    deck.push_back(card(color_t::RED,number_t::DRAW_TWO));

    for(int i = 0;i<10;i++)
    {
        deck.push_back(card(color_t::GREEN,static_cast<number_t>(i)));
    }
    for(int i=10;i<19;i++)
    {
        deck.push_back(card(color_t::GREEN,static_cast<number_t>(i-9)));
    }

    deck.push_back(card(color_t::GREEN,number_t::SKIP));
    deck.push_back(card(color_t::GREEN,number_t::SKIP));
    deck.push_back(card(color_t::GREEN,number_t::REVERSE));
    deck.push_back(card(color_t::GREEN,number_t::REVERSE));
    deck.push_back(card(color_t::GREEN,number_t::DRAW_TWO));
    deck.push_back(card(color_t::GREEN,number_t::DRAW_TWO));

    for(int i = 0;i<10;i++)
    {
        deck.push_back(card(color_t::YELLOW,static_cast<number_t>(i)));
    }
    for(int i=10;i<19;i++)
    {
        deck.push_back(card(color_t::YELLOW,static_cast<number_t>(i-9)));
    }

    deck.push_back(card(color_t::YELLOW,number_t::SKIP));
    deck.push_back(card(color_t::YELLOW,number_t::SKIP));
    deck.push_back(card(color_t::YELLOW,number_t::REVERSE));
    deck.push_back(card(color_t::YELLOW,number_t::REVERSE));
    deck.push_back(card(color_t::YELLOW,number_t::DRAW_TWO));
    deck.push_back(card(color_t::YELLOW,number_t::DRAW_TWO));

    for(int i=100;i<104;i++)
    {
        deck.push_back(card(color_t::NO_COLOR,number_t::WILD));
    }

    for(int i=104;i<108;i++)
    {
        deck.push_back(card(color_t::NO_COLOR,number_t::DRAW_FOUR_WILD));
    }

    if(color_drop_card == true)
    {
        for(unsigned i=108;i<108+number_players;i++)
        {
            deck.push_back(card(color_t::NO_COLOR,number_t::COLOR_DROP));
        }
    }

    for(int i=0;i<deck.size();i++)
    {
        deck[i].set_power(true);
    }
    return deck;
}

QVector<card>& users::get_player(unsigned n)
{
    return player_list[n-1];
}


 QVector<card>& users::get_game_deck()
{
    return game_deck;
}

void users::operator=(const users& u)
{
    player_list = u.player_list;
    game_deck = u.game_deck;
    deck = u.deck;
    number_players = u.number_players;
}


QDataStream& operator<<(QDataStream& out, const users& u)
{
    out<<u.get_num_user();
    out<<u.get_player_list();
    out<<u.game_deck;
    out<<u.deck;
    return out;
}
QDataStream& operator>>(QDataStream& in, users& u)
{
    unsigned num;
    QVector<QVector<card>> list;
    in>>num;
    in>>list;
    in>>u.get_game_deck();
    in>>u.deck;
    u.set_player_list(list);
    u.set_num_user(num);
    return in;
}

void users::set_num_user(unsigned int num)
{
    number_players = num;
}

QVector<QVector<card>>users::get_player_list() const
{
    return player_list;
}

void users::set_player_list(QVector<QVector<card>>& list)
{
    player_list = list;
}
