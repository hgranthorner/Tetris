#define SDL_MAIN_HANDLED

#include <algorithm>
#include <iostream>
#include <iterator>
#include <array>
#include "SDL.h"
#include "SDL_ttf.h"

constexpr unsigned int width = 800;
constexpr unsigned int height = 800;
constexpr unsigned int cols = 10;
constexpr unsigned int rows = 20;
constexpr unsigned int col_width = 40;
constexpr unsigned int row_height = 30;
constexpr unsigned int playable_width = cols * col_width;
constexpr unsigned int playable_height = rows * row_height;
constexpr unsigned int playable_x = (width / 2) - (playable_width / 2);
constexpr unsigned int playable_y = (height / 2) - (playable_height / 2);

struct Tile
{
	unsigned int x;
	unsigned int y;

	[[nodiscard]] SDL_Rect to_rect() const
	{
		return SDL_Rect{
				.x = static_cast<int>(playable_x + this->x * col_width),
				.y = static_cast<int>(playable_y + this->y * row_height),
				.w = col_width,
				.h = row_height
		};
	}
};

enum Direction
{
	Left,
	Right
};

class Tetromino
{
public:
	Tetromino(unsigned int x, unsigned int y, std::array<Tile, 4> tiles) : x(x), y(y), tiles(tiles)
	{}

	unsigned int x;
	unsigned int y;
	std::array<Tile, 4> tiles{};

//	virtual void rotate(SDL_Renderer& renderer) = 0;

//	virtual void move(SDL_Renderer& renderer, Direction direction) = 0;

  void draw(SDL_Renderer *renderer)
	{
		for (const auto& tile: this->tiles)
		{
			SDL_Rect rect = tile.to_rect();
			SDL_RenderFillRect(renderer, &rect);
		}
	};
};

class StraightTetromino : public Tetromino
{
public:
	StraightTetromino() : Tetromino(0, 0,
	                                std::array<Tile, 4>{
			                                Tile{.x = 0, .y = 0},
			                                {.x = 1, .y = 0},
			                                {.x = 2, .y = 0},
			                                {.x = 3, .y = 0}})
	{}
};


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	SDL_SetMainReady();
	const auto window = SDL_CreateWindow("Tetris",
	                                     SDL_WINDOWPOS_CENTERED,
	                                     SDL_WINDOWPOS_CENTERED,
	                                     width,
	                                     height,
	                                     SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cerr << "Could not create window!\n";
		exit(1);
	}
	const auto renderer = SDL_CreateRenderer(window,
	                                         -1,
	                                         SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) exit(1);
	if (TTF_Init() != 0) exit(1);

	bool running = true;

	StraightTetromino tet;

	while (running)
	{
		// Handle Input
		SDL_Event event;

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
		}

		// Render
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 100, 0, 100, 100);
		SDL_Rect playable_background{
				.x=static_cast<int>((width / 2) - (playable_width / 2)),
				.y=static_cast<int>((height / 2) - (playable_height / 2)),
				.w=playable_width,
				.h=playable_height
		};
		SDL_RenderFillRect(renderer, &playable_background);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_Rect playable_background_outline{
				.x=playable_background.x - 1,
				.y=playable_background.y - 1,
				.w=playable_background.w + 2,
				.h=playable_background.h + 2
		};

		SDL_RenderDrawRect(renderer, &playable_background_outline);

		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		tet.draw(renderer);

		SDL_RenderPresent(renderer);
	}

	return 0;
}
