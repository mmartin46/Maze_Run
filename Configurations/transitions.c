// Matthew 5:27
#include <gb/gb.h>

UINT8 fade_i;

// Manipulates the BGP_REG register.
// Shifts the number by two digits
// for a fade out effect.
//
// 00 : White
// 01 : Light Grey
// 10 : Dark Grey
// 11 : Black
//
// E4 = 11100100
// F9 = 11111001
// FE = 11111110
// FF = 11111111
void fadeout()
{
   for (fade_i = 0; fade_i < 4; fade_i++)
   {
      switch(fade_i)
      {
         case 0:
            BGP_REG = 0xE4;
            break;
         case 1:
            BGP_REG = 0xF9;
            break;
         case 2:
            BGP_REG = 0xFE;
            break;
         case 3:
            BGP_REG = 0xFF;
            break;
      }
      performant_delay(10);
   }
}

// Manipulates the BGP_REG register.
// Shifts the number by two digits
// for a fade in effect.
//
// 00 : White
// 01 : Light Grey
// 10 : Dark Grey
// 11 : Black
//
// E4 = 11100100
// F9 = 11111001
// FE = 11111110
// FF = 11111111
void fadein()
{
   for (fade_i = 0; fade_i < 3; fade_i++)
   {
      switch(fade_i)
      {
         case 0:
            BGP_REG = 0xFE;
            break;
         case 1:
            BGP_REG = 0xF9;
            break;
         case 2:
            BGP_REG = 0xE4;
            break;
      }
      performant_delay(10);
   }
}

