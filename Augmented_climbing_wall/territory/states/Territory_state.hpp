#pragma once

#include <iostream>
#include "../objects/Territory_world.hpp"

namespace Territory
{
	namespace States
	{
		enum class Type
		{
			Preparation, Game, Result, Exiting
		};
	};

	struct State
	{
		State(States::Type type, World& world) : type(type), world(world) { }
		virtual ~State() { }

		virtual void processEvents() { }
		virtual void render() { }
		virtual States::Type switchTo() = 0;

		virtual void update(const float delta)
		{
			timeElapsed += delta;
		}

		virtual void reset()
		{
			timeElapsed = 0.f;
		}

		void log()
		{
			std::cout << "State " << static_cast<int>(type) << " " << timeElapsed << "\n";
		}

	protected:
		float timeElapsed = 0.f;
		States::Type type;
		World& world;
	};

	struct StatePreparation : public State
	{
		StatePreparation(States::Type type, World& world) : State(type, world) { }

		~StatePreparation() { }
		void processEvents() override;
		void update(const float delta) override;
		void render() override;
		States::Type switchTo() override;
	};

	struct StateGame : public State
	{
		StateGame(States::Type type, World& world) : State(type, world) { }

		~StateGame() { }
		void processEvents() override;
		void update(const float delta) override;
		void render() override;
		void reset() override;
		States::Type switchTo() override;
	};

	struct StateResult : public State
	{
		StateResult(States::Type type, World& world) : State(type, world) { }

		~StateResult() { }
		void update(const float delta) override;
		void render() override;
		States::Type switchTo() override;
	};

	struct StateExiting : public State
	{
		StateExiting(States::Type type, World& world) : State(type, world) { }

		~StateExiting() { }
		States::Type switchTo() override
		{
			return States::Type::Exiting;
		}
	};
}