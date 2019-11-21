#include <SFML/Graphics.hpp>
#include <iostream>

#include "puck.hpp"

Puck::Puck (float radius, sf::Color color, sf::Vector2f position, sf::Vector2f velocity)
    : radius_ (radius), color_ (color), position_ (position), velocity_ (velocity)
{
    shape_.setRadius(radius_);
    shape_.setFillColor(color_);
    shape_.setOrigin(radius_, radius_);
    shape_.setPosition(position_);
}


void Puck::moveTo (sf::Vector2f position)
{
    position_ = position;
    shape_.setPosition(position_);
}

void Puck::update (float delta)
{
    //std::cout << shape_.getPosition().x << " " << shape_.getPosition().y << "\n";
    //std::cout << delta << " " << velocity_.x * delta << " " << velocity_.y * delta << "\n";
    position_ += velocity_ * delta;
    shape_.move(velocity_ * delta);
    //std::cout << "Update (" << position_.x << ", " << position_.y << ") - (" << velocity_.x << ", " << velocity_.y << ")\n";
    //std::cout << "Update collide (" << position_.x << ", " << position_.y << ") - (" << velocity_.x << ", " << velocity_.y << ")\n";
}


void Puck::reset(sf::Vector2f position, sf::Vector2f velocity)
{
    moveTo(position);
    velocity_ = velocity;
}


sf::CircleShape Puck::shape()
{
    return shape_;
}


float Puck::radius()
{
    return radius_;
}


sf::Vector2f & Puck::position()
{
    return position_;
}


sf::Vector2f & Puck::velocity()
{
    return velocity_;
}


void Puck::walls_collide (float width, float height)
{
    if ((position_.y <= radius_) || (position_.y >= height - radius_))
    {
        // std::cout << "\nCollide with wall (" << position_.x << ", " << position_.y << ") - (" << velocity_.x << ", " << velocity_.y << ")\n";

        velocity_.y *= -1;
        if (position_.y <= radius_)
        {
            position_.y = radius_ + 1.f;
        }
        else
        {
            position_.y = height - radius_ - 1.f;
        }
        shape_.setPosition(position_);
        // std::cout << "After wall collide (" << position_.x << ", " << position_.y << ") - (" << velocity_.x << ", " << velocity_.y << ")\n";
    }
}
