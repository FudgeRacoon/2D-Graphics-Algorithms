#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#define round(x) (int)((x)+0.5)

class DDA_APP
{
private:		
	struct Point 
	{			
		int x;
		int y;
    };

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	bool isRunning;

public:
	DDA_APP()
	{
		SDL_Init(SDL_INIT_VIDEO);

		window = SDL_CreateWindow("DDA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, NULL);

		isRunning = true;
	}

public:
	bool IsRunning()
	{
		return isRunning;
	}		
	
public:
	void Draw()
	{
		Point p1, p2;

		printf("Enter the values of x1 and y1:\n");
		scanf("%d %d", &p1.x, &p1.y);

		printf("Enter the values of x2 and y2:\n");
		scanf("%d %d", &p2.x, &p2.y);
		
		SDL_Color color;
		color.r = rand() % 255;
		color.g = rand() % 255;
		color.b = rand() % 255;
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		DDA(p1, p2, color);

		SDL_RenderPresent(renderer);

		printf("Press esc to quit\nPress any key to draw again\n");
	}
	
	void DDA(const Point& p1, const Point& p2, SDL_Color color) 
	{
		//Calculate delta-x and delta-y
		int dx = p2.x - p1.x;
		int dy = p2.y - p1.y;

		//If slope is less than 1 then calcualte y step per x else calculate x step per y
		int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
		float xInc = (float) dx / steps;
		float yInc = (float) dy / steps;
		
		float x = p1.x;
		float y = p1.y;
		
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

		for(int i = 0; i < steps; i++)
		{
			SDL_RenderDrawPoint(renderer, round(x), round(y));
			x += xInc;
			y += yInc;
		}
	}
};

int main(int argc, char* argv[])
{
	DDA_APP app;

	while(app.IsRunning())
		app.Draw();

	return 0;
}

