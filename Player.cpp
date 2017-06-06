/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbamping <kbamping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 17:29:07 by dmather           #+#    #+#             */
/*   Updated: 2017/05/28 09:32:57 by kbamping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"


Player::Player(void)
{
    return;
}

Player::Player(WINDOW * win) : GameObject::GameObject(win, '>')
{

}

Player::Player(Player const & src)
{
    *this = src;
    return;
}

Player& Player::operator=(Player const & rhs)
{
    if (this != &rhs)
    {
		this->setLocation(rhs.getLocation('x'), rhs.getLocation('y'));
		this->setMax('x', rhs.getMax('x'));
		this->setMax('y', rhs.getMax('y'));
        this->setWindow(rhs.getWindow());
        this->setCharacter(rhs.getCharacter());
        this->setAlive(rhs.isAlive());
    }

    return *this;
}

Player::~Player(void)
{
    return;
}
