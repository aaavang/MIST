# MIST
This project is to experiment with controlling multiple chained Rainbow Cubes over a serial interface

Currently only the unlimited message length is implemented

Message Format:
IRGBXYZXYZ...E

I = 1 byte cube ID (0-253, 254 is wildcard, 255 is unused)

R = 1 byte red value (0-255)

G = 1 byte green value (0-255)

B = 1 byte blue value (0-255)

X = x coordinate (0-253, 254 is a wildcard)

Y = y coordinate (0-253, 254 is a wildcard)

Z = z coordinate (0-253, 254 is a wildcard)

E = end marker (255)

Examples:

Clear the entire cube
DEC: 0 0 0 0 254 254 254 255
HEX: 0 0 0 0 FE FE FE FF

Make the entire cube green
DEC: 0 0 255 0 254 254 254 255
HEX: 0 0 FF 0 FE FE FE FF

Make the top sheet blue
DEC: 0 0 0 255 254 254 3 255
HEX: 0 0 0 FF FE FE 03 FF

Make a single line red
DEC: 0 255 0 0 254 1 1 255
HEX: 0 FF 0 0 FE 01 01 FF

Make a single LED white
DEC: 0 255 255 255 1 1 1 255
HEX: 0 FF FF FF 1 1 1 FF
