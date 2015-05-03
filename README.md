# MIST
This project is to experiment with controlling multiple chained Rainbow Cubes over a serial interface

Currently only the unlimited message length is implemented

Message Format:
IRGBMNXYZXYZ...

I = 1 byte cube ID (0-254, 255 is wildcard)

R = 1 byte red value (0-255)

G = 1 byte green value (0-255)

B = 1 byte blue value (0-255)

M = 1 byte address mode (0 = non-masked, 1 = masked)

N = 1 byte number of XYZ pairs

X = 1 byte (see below for usage)

Y = 1 byte (see below for usage)

Z = 1 byte (see below for usage)


Address Modes:

Non-masked: This mode treats the XYZ values as literal points, with 255 being a wildcard.  This mode supports up to 254x254x254 sized cubes.

Example: (0,0,255) = selects the column of leds at x=0,y=0


Masked:  This mode treats the XYZ values as bitmasks.  An LED is selected if its position in the bit mask is 1 for X, Y, and Z.  This mode supports up to 8x8x8 sized cubes.

Example: (9,9,9) = (1001,1001,1001) = selects the corner LEDs

Example: (15,15,15) = (1111,1111,1111) = selects the entire cube
