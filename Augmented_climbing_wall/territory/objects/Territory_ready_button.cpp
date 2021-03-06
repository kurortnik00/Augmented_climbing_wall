#include <SFML/Graphics.hpp>

#include "Territory_ready_button.hpp"

using namespace Territory;

ReadyButton::ReadyButton(sf::Vector2f position, sf::Vector2f size)
    : position_(position), size_(size)
{
    sprite_.setOrigin(size_ / 2.f);
    sprite_.setPosition(position);
    sprite_.setColor(sf::Color::Yellow);
}


bool ReadyButton::isActivated()
{
    return activated;
}


void ReadyButton::setTexture(sf::Texture& texture)
{
    sprite_.setTexture(texture);
    sprite_.setScale(size_.x / sprite_.getLocalBounds().width, size_.y / sprite_.getLocalBounds().height);
}

sf::Sprite& ReadyButton::sprite()
{
    return sprite_;
}


void ReadyButton::update(std::vector<Paddle> paddles)
{
    activated = false;
    for (int i = 0; i < paddles.size(); i++)
    {
        sf::Vector2f paddle_position = paddles[i].position();
        activated |= (paddle_position.x >= position_.x - size_.x / 2) &&
            (paddle_position.x <= position_.x + size_.x / 2) &&
            (paddle_position.y >= position_.y - size_.y / 2) &&
            (paddle_position.y <= position_.y + size_.y / 2);
    }

    if (activated)
    {
        sprite_.setColor(sf::Color::Green);
    }
    else {
        sprite_.setColor(sf::Color::Yellow);
    }
}
