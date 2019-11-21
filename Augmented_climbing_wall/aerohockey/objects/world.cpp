#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>

#include "world.hpp"
#include "../util.hpp"

using namespace std;


World::World(float width, float height, float update_time, BodyTracker & kinect, bool kinectControl)
    : width_(width)
    , height_(height)
    , score_changed(false)
    , paused(false)
    , use_paddle_velocity(false)
    , kinectControl (kinectControl)
    , puck_velocity (sf::Vector2f(400.f, 400.f))
    , update_time (update_time)
    , mWindow(sf::VideoMode(width, height), "Aerohockey", sf::Style::None)
    , puck (height / 20, sf::Color::White, sf::Vector2f(width / 2, height / 2), puck_velocity)
    , left (height / 20, sf::Color(204, 0, 0), update_time, kinect, true, kinectControl)
    , right (height / 20, sf::Color(0, 102, 0), update_time, kinect, false, kinectControl)
    , board (&left, &right, 0.5)
    , left_ready (sf::Vector2f(width / 4, height / 2), sf::Vector2f(width / 10, width / 10))
    , right_ready (sf::Vector2f(width * 3 / 4, height / 2), sf::Vector2f(width / 10, width / 10))
{
    mWindow.setFramerateLimit(60);
    mWindow.setVerticalSyncEnabled(true);

    left_border.setPosition(0.f, 0.f);
    left_border.setSize(sf::Vector2f(2.f, height_ - 60.f));
    left_border.setFillColor(sf::Color(204, 0, 0));

    right_border.setPosition(798.f, 0.f);
    right_border.setSize(sf::Vector2f(2.f, height_ - 60.f));
    right_border.setFillColor(sf::Color(0, 102, 0));

    left_border.setPosition(0.f, 0.f);
    left_border.setSize(sf::Vector2f(800.f, 2.f));
    left_border.setFillColor(sf::Color::White);
}


void World::processEvents()
{
    if (!kinectControl)
    {
        left.handleInput();
        right.handleInput();
    }
}


void World::update()
{
    left.update();
    right.update();
    puck.update(update_time);

    for (int i = 0; i < left.n_limbs; i++)
    {
        collide_objects(left.paddles()[i], puck);
    }
    for (int i = 0; i < right.n_limbs; i++)
    {
        collide_objects(right.paddles()[i], puck);
    }
    puck.walls_collide(width_, height_);

    score_changed = goal_scored();
    board.update(update_time, score_changed);
}


void World::collide_objects(Paddle & first, Puck & second)
{
    float r1 = first.radius();
    float r2 = second.radius();
    float threshold = (r1 + r2) * (r1 + r2);
    sf::Vector2f x1 = first.position(), x2 = second.position();

    float dist = dist2(x1, x2);
    if (dist2(x1, x2) <= threshold)
    {
        sf::Vector2f v1 = sf::Vector2f(0.f, 0.f), v2 = second.velocity();
        if (use_paddle_velocity)
        {
            v1 = first.velocity();
        }

        float rewind_time = 0.f;
        if (dist < threshold)
        {
            sf::Vector2f dv = v1 - v2;
            rewind_time = (r1 + r2 - sqrt(dist)) / sqrt(len2(dv));

            first.moveTo(x1 - rewind_time * v1);
            second.moveTo(x2 - rewind_time * v2);
        }

        sf::Vector2f x1 = first.position(), x2 = second.position();
        second.velocity() = v2 - 2.f * (x2 - x1) * dot(v2 - v1, x2 - x1) / len2(x2 - x1);

        // first.update(width, height, rewind_time);
        second.update(rewind_time);
    }
}


void World::collide_objects(Puck * first, Puck * second, int width, int height)
{
    float r1 = first->radius();
    float r2 = second->radius();
    float threshold = (r1 + r2) * (r1 + r2);
    sf::Vector2f x1 = first->position(), x2 = second->position();

    float dist = dist2(x1, x2);
    if (dist <= threshold)
    {
        sf::Vector2f v1 = first->velocity(), v2 = second->velocity();

        float rewind_time = 0.f;
        if (dist < threshold)
        {
            sf::Vector2f dv = v1 - v2;
            rewind_time = (r1 + r2 - sqrt(dist)) / sqrt(len2(dv));
            std::cout << r1 + r2 << " " << sqrt(dist) << " " << dv.x << " " << dv.y << " " << rewind_time << "\n";
            first->moveTo(x1 - rewind_time * v1);
            second->moveTo(x2 - rewind_time * v2);
        }

        sf::Vector2f x1 = first->position(), x2 = second->position();
        first->velocity() = v1 - (x1 - x2) * dot(v1 - v2, x1 - x2) / len2(x1 - x2);
        second->velocity() = v2 - (x2 - x1) * dot(v2 - v1, x2 - x1) / len2(x2 - x1);

        first->update(rewind_time);
        second->update(rewind_time);
    }
}

bool World::goal_scored()
{
    sf::Vector2f velocity = puck_velocity;

    if ((puck.position().x < 0) || (puck.position().x > width_))
    {
        if (puck.position().x < 0)
        {
            right.scored();
            velocity.x *= -1;
        }
        else
        {
            left.scored();
        }
        puck.reset(sf::Vector2f(width_ / 2, height_ / 2), velocity);
        return true;
    }
    return false;
}

void World::render()
{
    mWindow.clear();

    mWindow.draw(left_border);
    mWindow.draw(right_border);
    mWindow.draw(top_border);

    mWindow.draw(puck.shape());
    for (int i = 0; i < left.n_limbs; i++)
    {
        mWindow.draw(left.paddles()[i].shape());
    }
    for (int i = 0; i < right.n_limbs; i++)
    {
        mWindow.draw(right.paddles()[i].shape());
    }

    board.render(mWindow);

    mWindow.display();
}


void World::reset()
{
    left.reset();
    right.reset();
    puck.reset(sf::Vector2f(width_ / 2, height_ / 2), puck_velocity);
    board.reset();
}
