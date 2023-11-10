#include "game.h"

#define BOARD_SQUARE_WIDTH (game->width / 8)
#define BOARD_SQUARE_HEIGHT (game->height / 8)

enum img_index{
  img_white_pawn,
  img_white_rook,
  img_white_knight,
  img_white_bishop,
  img_white_queen,
  img_white_king,
  img_black_pawn,
  img_black_rook,
  img_black_knight,
  img_black_bishop,
  img_black_queen,
  img_black_king
};

void update(Game* game);
void render(Game* game);
void render_pieces(Game* game);
void init_textures(Game* game);
u64 set_bit(u64 number, int x, int y, bool set);
u64 move_piece(u64 number, int xFrom, int yFrom, int xTo, int yTo);
void cleanup(Game* game);

void game_init(Game* game, SDL_Window* window, SDL_Renderer* renderer, int width, int height)
{
  // Sets all game variables
  game->width = width;
  game->height = height;
  game->running = true;
  game->window = window;
  game->renderer = renderer;
  // init textures
  init_textures(game);
  board_init(game->board);
}

void game_mainloop(Game* game)
{
  while(game->running)
  {
    update(game);
    render(game);
  }
}

void update(Game* game)
{
  while(SDL_PollEvent(&game->event))
  {
    // Checks for User closing window
    if(game->event.type == SDL_QUIT)
    {
      cleanup(game);
      game->running = false;
    } else if(game->event.type == SDL_MOUSEBUTTONDOWN)
    {
      int x = game->event.motion.x;
      int y = game->event.motion.y;
      x /= BOARD_SQUARE_WIDTH;
      y /= BOARD_SQUARE_HEIGHT;
      printf("Mouse pressed on x:%d | y:%d\n", x, y);
      int square = y * 8 + x;
      uint64_t mask = 1ULL << square;
      game->board->bb_piece[bb_piece_white_queen] = move_piece(game->board->bb_piece[bb_piece_white_queen], 4, 7, x, y);
    }
  }
}

void render(Game* game)
{
  SDL_RenderClear(game->renderer);

  // Draws chess board
  for(int x = 0; x < 8; x++)
  {
    for(int y = 0; y < 8; y++)
    {
      SDL_Rect rect = (SDL_Rect){ x * BOARD_SQUARE_WIDTH, y * BOARD_SQUARE_HEIGHT, BOARD_SQUARE_WIDTH, BOARD_SQUARE_HEIGHT };
      if(x % 2 - y % 2 != 0)
      {
        SDL_SetRenderDrawColor(game->renderer, 181, 136, 99, 255);
      } else 
      {
        SDL_SetRenderDrawColor(game->renderer, 240, 217, 181, 255);
      }

      SDL_RenderFillRect(game->renderer, &rect);
    }
  }

  render_pieces(game);

  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  SDL_RenderPresent(game->renderer);
}

void render_pieces(Game* game)
{
    for (int rank = 0; rank < 8; rank++) {
      for (int file = 0; file < 8; file++) {
        int square = rank * 8 + file;
        uint64_t mask = 1ULL << square;
        SDL_Rect rect = (SDL_Rect){ file * BOARD_SQUARE_WIDTH, rank * BOARD_SQUARE_HEIGHT,
          BOARD_SQUARE_WIDTH, BOARD_SQUARE_HEIGHT };
        
        if (game->board->bb_piece[bb_piece_white_pawn] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_white_pawn], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_white_rook] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_white_rook], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_white_knight] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_white_knight], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_white_bishop] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_white_bishop], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_white_queen] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_white_queen], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_white_king] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_white_king], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_black_pawn] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_black_pawn], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_black_rook] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_black_rook], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_black_knight] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_black_knight], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_black_bishop] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_black_bishop], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_black_queen] & mask) 
        {
          SDL_RenderCopy(game->renderer, game->img[img_black_queen], NULL, &rect);
        } 

        else if (game->board->bb_piece[bb_piece_black_king] & mask) 
        {
         SDL_RenderCopy(game->renderer, game->img[img_black_king], NULL, &rect);
        } 
      }
    }
}

void init_textures(Game* game)
{
  game->img[img_white_pawn] = IMG_LoadTexture(game->renderer, "assets/pawn/white.png");
  game->img[img_white_rook] = IMG_LoadTexture(game->renderer, "assets/rook/white.png");
  game->img[img_white_knight] = IMG_LoadTexture(game->renderer, "assets/knight/white.png");
  game->img[img_white_bishop] = IMG_LoadTexture(game->renderer, "assets/bishop/white.png");
  game->img[img_white_queen] = IMG_LoadTexture(game->renderer, "assets/queen/white.png");
  game->img[img_white_king] = IMG_LoadTexture(game->renderer, "assets/king/white.png");
  game->img[img_black_pawn] = IMG_LoadTexture(game->renderer, "assets/pawn/black.png");
  game->img[img_black_rook] = IMG_LoadTexture(game->renderer, "assets/rook/black.png");
  game->img[img_black_knight] = IMG_LoadTexture(game->renderer, "assets/knight/black.png");
  game->img[img_black_bishop] = IMG_LoadTexture(game->renderer, "assets/bishop/black.png");
  game->img[img_black_queen] = IMG_LoadTexture(game->renderer, "assets/queen/black.png");
  game->img[img_black_king] = IMG_LoadTexture(game->renderer, "assets/king/black.png");
}

u64 set_bit(u64 number, int x, int y, bool set) {
  if(set) 
  {
    // Set the bit to 1
    return number | (1ULL << (y * 8 + x));
  } else {
    // Set the bit to 0
    return number & ~(1ULL << (y * 8 + x));
  }
}

u64 move_piece(u64 number, int xFrom, int yFrom, int xTo, int yTo)
{
  u64 ret = set_bit(number, xFrom, yFrom, 0);
  return set_bit(ret, xTo, yTo, 1);
}

void cleanup(Game* game)
{
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
}
