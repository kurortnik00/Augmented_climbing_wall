#include <iostream>

#include "Aerohockey_state.hpp"
#include "../../util.hpp"

using namespace Aerohockey;

void StateResult::reset()
{
    State::reset();
    
    // Important: align_center after setString!
    world.left_score.setString(std::to_string(world.left.score()));
    align_center(world.left_score, world.left_result_rect);

    // Important: align_center after setString!
    world.right_score.setString(std::to_string(world.right.score()));
    align_center(world.right_score, world.right_result_rect);

    std::string sign = "=";
    if (world.left.score() != world.right.score())
    {
        if (world.left.score() > world.right.score())
        {
            sign = ">";
        }
        else
        {
            sign = "<";
        }
    }
    world.sign.setString(sign);

    // Important: align_center after setString!
    sf::RectangleShape window_border;
    window_border.setSize(sf::Vector2f(world.width_, world.height_));
    align_center(world.sign, window_border);
}

void StateResult::update(const float delta)
{
    State::update(delta);

    float direction = 0.f;
    if (world.left.score() != world.right.score())
    {
        if (world.left.score() > world.right.score())
        {
            direction = 1.f;
        }
        else
        {
            direction = -1.f;
        }
    }
    world.result_border_position += world.result_border_velocity * direction * delta;

    world.left_result_rect.setPosition(0, 0);
    world.left_result_rect.setSize(sf::Vector2f(world.result_border_position, world.height_));
    world.right_result_rect.setPosition(world.result_border_position, 0);
    world.right_result_rect.setSize(sf::Vector2f(world.width_ - world.result_border_position, world.height_));
}

void StateResult::render()
{
    world.mWindow.clear();

    world.mWindow.draw(world.left_result_rect);
    world.mWindow.draw(world.right_result_rect);
    world.mWindow.draw(world.left_score);
    world.mWindow.draw(world.right_score);
    if (timeElapsed > Config::result_sign_delay)
    {
        world.mWindow.draw(world.sign);
    }

    world.mWindow.display();
}

States::Type StateResult::switchTo()
{
    if (timeElapsed > Config::result_demonstration_time)
    {
        return States::Type::Exiting;
    }
    return States::Type::Result;
}
