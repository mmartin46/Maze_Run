// Psalms 2:8
#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include "level_setup.c"
#include "Assets/main_screen_data.c"
#include "Assets/main_screen_map.c"

void load_start_up()
{
      // Main Screen
   set_bkg_data(0, 243, main_screen_data);
   set_bkg_tiles(0, 0, 20, 18, main_screen_map);

   SHOW_BKG;
   DISPLAY_ON;

   // Pauses until the user presses start
   waitpad(J_START);
   play_sound();


   fadeout();
}

void main()
{
   // Set Volume
   set_volume();

   // Main Screen
   load_start_up();

   // Setting up the level
   generate_level();
   set_level_attributes();
   fadein();

   // Player Sprite
   set_sprite_data(0, 1, player);
   set_sprite_tile(0, 0);

   // Player Location
   reset_player(P1, &playerlocation);


   // Setting background flags.
   SHOW_SPRITES;
   SHOW_BKG;
   DISPLAY_ON;

   while (1)
   {
      if (joypad() & J_A)
      {
         debug = 1;
      }

      switch (level_num)
      {
         case 1:
            player_control(P1, &playerlocation, &level_1);
            break;
         case 2:
            player_control(P1, &playerlocation, &level_2);
            break;
         case 3:
            player_control(P1, &playerlocation, &level_3);
            break;
         default:
            HIDE_SPRITES;
            fadeout();
            printf("\n \n \n \n \n \n \n \n \n   YOU WON THE GAME!"); 
      }
   }
}
