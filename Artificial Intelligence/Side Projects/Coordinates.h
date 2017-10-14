#ifndef COORDINATES_H
#define COORDINATES_H

class GameState;

#include <map>
#include <deque>
#include <iostream>

using namespace std;

class Coordinates
{
	private:
		int value;

		int x;
		int y;

	public:
		Coordinates()
		{
			this->x = 0;
			this->y = 0;
		}

		Coordinates(int v, int x, int y)
		{
			this->value = v;

			this->x = x;
			this->y = y;
		}

		~Coordinates()
		{}

		// setters and getters
		int get_x() const
		{
			return this->x;
		}

		void set_x(int x)
		{
			this->x = x;
		}

		int get_y() const
		{
			return this->y;
		}

		void set_y(int y)
		{
			this->y = y;
		}

		int get_value() const
		{
			return this->value;
		}

		void set_value(int v)
		{
			this->value = v;
		}

		// prototypes: see .c file for details
		static deque<Coordinates> zero_list(const GameState, int);

		bool is_up(Coordinates);
		bool is_down(Coordinates);
		bool is_left(Coordinates);
		bool is_right(Coordinates);
};

#endif
