#include "game.h"

#define WIDTH 512
#define HEIGHT 512

int init(SDL_Window** window, SDL_Renderer** renderer);
void cleanup(SDL_Window* window, SDL_Renderer* renderer);

int main(int argc, char** argv)
{
  SDL_Window* window;
  SDL_Renderer* renderer;
  Game game;

  if(init(&window, &renderer))
  {
    return -1;
  }
  
  game_init(&game, window, renderer, WIDTH, HEIGHT);
  game_mainloop(&game);

  cleanup(game.window, game.renderer);
  return 0;
}

int init(SDL_Window** window, SDL_Renderer** renderer)
{
  if(SDL_Init(SDL_INIT_EVERYTHING))
  {
    printf("SDL Initialize Error! Error Code: %s\n", SDL_GetError());
    return -1;
  }

  *window = SDL_CreateWindow("Chess Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
  if(!*window)
  {
    printf("SDL Window Error! Error Code: %s\n", SDL_GetError());
    return -1;
  }
  //SDL_SetWindowBordered(*window, false);

  *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);
  if(!*renderer)
  {
    printf("SDL Renderer Error! Error Code: %s\n", SDL_GetError());
    return -1;
  }

  return 0;
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer)
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}
