# Red-Black-Knights
A open source implementation of the described in numberphile's video named "Red &amp; Black Knights". By default draws the standard version shown in the video, but this file includes intructions on how to change the code for new variations. Screenshots of some variations are included.

In order to change the ammount of players change the macro in line 5 of the main.c file to another number. This has to come accompained by
adding a player to the player list (both need to happen for it to actually add a player), which can be done by adding a player type to the hard coded array in line 36. The color must also be specified in line 20, otherwise it will read trash values from the stack.

The code by default contains the following piece types:
KNIGHT
ZEBRA
ANTELOPE
WAZIR
FERZ
whice were all specified in the extra contents video. Another piece type I created was also included, called PEACE, which doesn't attack any squares.

In order to add your own piece types simply add another macro similar to those in lines 29 to 34 to the list and include a list of squares the piece type attacks, formatted as a list of x offset, y offset subarrays. It must contain exactly 8 subarrays. If the piece you want to add attacks less than 8 squares, use 0, 0 as padding. If the piece you want to add attacks more than 8 squares, increase the value of MOVEMENT_COUNT in line 35 and add padding to all piece types accordingly, while making sure MOVEMENT_COUNT is exactly the biggest ammount of squares any piece type takes, and that all piece types have the correct ammount of padding.


The code by default contains the following colors:
black
white (note: white is used for the background, so any piece using white is effectively invisible)
red
green
blue
cyan
magenta
yellow
gray

In order to add another color please replace the color name with the following notation:
{.color = xxxx}
Where "xxxx" is the hex value of the color, including the 0x prefix. The alpha value is ignored.
