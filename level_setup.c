// Mark 3:5
#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include "Player.c"
#include "Assets/MazeMap.c"
#include "Configurations/transitions.c"
#include "Assets/MazeSprites.c"

/** LEVEL ATTRIBUTES **/
struct LevelFeatures {
   UINT16 key_loc;
   UINT16 door_loc; 
   UINT16 key_coord[2];
   UINT16 door_coord[2];
};
struct LevelFeatures level_1;
struct LevelFeatures level_2;

unsigned char *levels[] = { maze_map, maze_map_two };


UINT8 level_num = 0;
const char reset_block[1] = {0x00};



/** For debugging **/
UBYTE debug = 0;


/** PLAYER ATTRIBUTES **/

const int P1 = 0;

// Player coodinates
struct PlayerLocation {
   UINT8 x;
   UINT8 y;
};

struct PlayerLocation playerlocation;




/** LEVEL ATTRIBUTES **/

// Generates the level specified
// in the parameter.
void generate(UINT8 level_num)
{
   set_bkg_data(0, 4, maze_sprites);
   set_bkg_tiles(0, 0, 20, 18, levels[level_num]);
}

// Generates a random level.
void generate_level()
{
   generate(level_num++);
}



// Sets the key and door locations.
void set_level_attributes()
{ 
   // Level 1 attributes
   level_1.key_loc = 74;
   level_1.door_loc = 4;
   level_1.key_coord[0] = 14;
   level_1.key_coord[1] = 3;
   level_1.door_coord[0] = 4;
   level_1.door_coord[1] = 0;

   // Level 2 attributes
   level_2.key_loc = 107;
   level_2.door_loc = 339;
   level_2.key_coord[0] = 7;
   level_2.key_coord[1] = 5;
   level_2.door_coord[0] = 19;
   level_2.door_coord[1] = 16;
}

void level_complete()
{
   if (level_num < 2)
   {
      fadeout();
      HIDE_SPRITES;
      printf("\n \n \n \n \n \n \n \n \n   LEVEL COMPLETED!");
      fadein();
      waitpad(J_START);
      fadeout();
      SHOW_SPRITES;

      generate_level();
      reset_player(P1, &playerlocation);
      fadein();
   }
   else
   {
      fadeout();
      HIDE_SPRITES;
      printf("\n \n \n \n \n \n \n \n \n   YOU COMPLETED THE GAME!");
      fadein();      
   }
}


// Determines the boundaries where the player can move.
UBYTE allow_player_move(UINT8 player_X, UINT8 player_Y, struct LevelFeatures *lvl, UINT8 index)
{
   UINT16 idx_TOP_LEFT_X, idx_TOP_LEFT_Y, idx_TILE_TOP_LEFT;
   UBYTE result;

   // How many sprites(8-bits) down is the player?
   idx_TOP_LEFT_X = (player_X - 8) / 8;
   idx_TOP_LEFT_Y = (player_Y - 16) / 8;

   // 20 sprites per row
   idx_TILE_TOP_LEFT = 20 * idx_TOP_LEFT_Y + idx_TOP_LEFT_X;

   if (debug)
   {
      printf("%u %u\n", (UINT16) player_X, (UINT16) player_Y);
      printf("%u %u %u\n", (UINT16) idx_TOP_LEFT_X, (UINT16) idx_TOP_LEFT_Y, (UINT16) idx_TILE_TOP_LEFT);
   }

   // Checks if we are on a blank block.
   result = levels[index][idx_TILE_TOP_LEFT] == reset_block[0];

   if (idx_TILE_TOP_LEFT==lvl->key_loc)
   {
      // collect the key
      set_bkg_tiles(lvl->key_coord[0], lvl->key_coord[1], 1, 1, reset_block[0]);
      result = 1;
   }
   else if (idx_TILE_TOP_LEFT==lvl->door_loc)
   {
      set_bkg_tiles(lvl->door_coord[0], lvl->door_coord[1], 1, 1, reset_block);
      level_complete();
   }
   return result;
}


// Controls of the player
void player_control(UINT8 player_id, struct PlayerLocation *playerLoc, const struct LevelFeatures *lvl)
{
   if (joypad() & J_LEFT)
   {
      if (allow_player_move(playerLoc->x - 8, playerLoc->y, lvl, level_num - 1))
      {
        playerLoc->x -= 8;
        animate_sprite(player_id, -8, 0);
      }
   }
   else if (joypad() & J_RIGHT)
   {
      if (allow_player_move(playerLoc->x + 8, playerLoc->y, lvl, level_num - 1))
      {
        playerLoc->x += 8;
        animate_sprite(player_id, 8, 0);      
      }
   }
   else if (joypad() & J_UP)
   {
      if (allow_player_move(playerLoc->x, playerLoc->y - 8, lvl, level_num - 1))
      {
        playerLoc->y -= 8;
        animate_sprite(player_id, 0, -8);      
      }
   }
   else if (joypad() & J_DOWN)
   {
      if (allow_player_move(playerLoc->x, playerLoc->y + 8, lvl, level_num - 1))
      {
        playerLoc->y += 8;
        animate_sprite(player_id, 0, 8);      
      }
   }
   performant_delay(5);
}

