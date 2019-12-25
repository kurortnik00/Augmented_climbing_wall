#include <SFML/Graphics.hpp>
#include <iostream>

#include "Aerohockey_state.hpp"

using namespace Aerohockey;

void StatePreparation::processEvents()
{
    world.processEvents();
}

void StatePreparation::update(const float delta)
{
    State::update(delta);

    world.left.update();
    world.right.update();
    world.left_ready.update(world.left.paddles());
    world.right_ready.update(world.right.paddles());
}

void StatePreparation::render()
{
    world.mWindow.clear();

    world.left.render(world.mWindow);
    world.right.render(world.mWindow);
    world.mWindow.draw(world.left_border);
    world.mWindow.draw(world.right_border);
    world.mWindow.draw(world.left_ready.sprite());
    world.mWindow.draw(world.right_ready.sprite());

    world.mWindow.display();
}

States::Type StatePreparation::switchTo()
{
    if (world.left_ready.isActivated() && world.right_ready.isActivated())
    {
        return States::Type::Game;
    }
    return States::Type::Preparation;
}
