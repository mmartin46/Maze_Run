#include <gb/gb.h>
#include <stdio.h>
#include <gb/gb.h>

/*

 PLAYER.C

 Tile Source File.

 Info:
  Form                 : All tiles as one unit.
  Format               : Gameboy 4 color.
  Compression          : None.
  Counter              : None.
  Tile size            : 8 x 8
  Tiles                : 0 to 0

  Palette colors       : None.
  SGB Palette          : None.
  CGB Palette          : None.

  Convert to metatiles : No.

 This file was generated by GBTD v2.2

*/



// A less CPU expensive version
// of the delay() function.
void performant_delay(UINT8 n)
{
   UINT8 i;
   for (i=0; i < n/2; ++i)
   {
      wait_vbl_done();
   }
}

/******* PLAYER INITIALIZATION **********/

// Player coodinates
struct PlayerLocation {
   UINT8 x;
   UINT8 y;
};


/* Start of tile array. */
unsigned char player[] =
{
  0x00,0x00,0x7E,0x7E,0xBD,0xC3,0xBD,0xE7,
  0x7E,0x7E,0x42,0x42,0x42,0x42,0x42,0x42
};

/********* PLAYER CONTROLS *********/



// Allow smoother animation for the player
// rather than utilizing the move_sprite() function.
void animate_sprite(UINT8 sprite_idx, INT8 move_x, INT8 move_y)
{
   while (move_x != 0)
   {
      // Check if move-x is anything other than 0.
      scroll_sprite(sprite_idx, move_x < 0 ? -1 : 1, 0);
      move_x += (move_x < 0 ? 1: -1);
      wait_vbl_done();
   }
   while (move_y != 0)
   {
      // Check is move_y is anything other than 0.
      scroll_sprite(sprite_idx, 0, move_y < 0 ? -1 : 1, 1);
      move_y += (move_y < 0 ? 1 : -1);
      wait_vbl_done();      
   }
}





// Resets the player's location.
void reset_player(UINT8 player_id, struct PlayerLocation *playerLoc)
{
   playerLoc->x = 16;
   playerLoc->y = 24;

   move_sprite(player_id, playerLoc->x, playerLoc->y);
}

/* End of PLAYER.C */
