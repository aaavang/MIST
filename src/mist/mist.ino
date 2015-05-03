#include <Rainbowduino.h>

#define MIN_MESSAGE_SIZE 9
#define NON_MASKED 0
#define MASKED 1
#define CUBE_SIZE 4

void setup() {
  Serial.begin(9600);
  Rb.init();
}

void loop() {

  int bytesToRead = Serial.available();

  if (Serial.available() >= MIN_MESSAGE_SIZE) {
    // enough bytes have come over for us to start doing some work
    
    int cubeID = (int) Serial.read();
    
    // determine what type of message this is, and whether or not it applies to me
    bool isBroadcast = cubeID == 255;
    bool isTarget = isBroadcast || cubeID == 0;
    
    int r = (int) Serial.read();
    int g = (int) Serial.read();
    int b = (int) Serial.read();
    int addressMode = (int) Serial.read();
    int numberOfLEDs = (int) Serial.read();

    // you only pass messages on if there is a broadcast, or this cube wasnt the target
    if (isBroadcast || !isTarget) {
      Serial.write(isBroadcast ? cubeID : --cubeID);
      Serial.write(r);
      Serial.write(g);
      Serial.write(b);
      Serial.write(addressMode);
      Serial.write(numberOfLEDs);
    }

    // TODO: handle malformed requests
    // wait for all the bytes in this packet to arrive
    while (Serial.available() < numberOfLEDs * 3);

    for (int i = 0; i < numberOfLEDs; ++i) {
      int x = (int) Serial.read();
      int y = (int) Serial.read();
      int z = (int) Serial.read();

      // you only pass messages on if there is a broadcast, or this cube wasnt the target
      if (isBroadcast || !isTarget) {
        Serial.write(x);
        Serial.write(y);
        Serial.write(z);
      }

      // only bother parsing the values if the are going to be changing your lights
      if (isTarget) {
        if (addressMode == NON_MASKED) {
          // treat XYZ values as actual points, with 255 being wildcard
          int minX = x == 255 ? 0 : x;
          int maxX = x == 255 ? CUBE_SIZE - 1 : x;

          int minY = y == 255 ? 0 : y;
          int maxY = y == 255 ? CUBE_SIZE - 1 : y;

          int minZ = z == 255 ? 0 : z;
          int maxZ = z == 255 ? CUBE_SIZE - 1 : z;

          for (int i = minX; i <= maxX; ++i)
            for (int j = minY; j <= maxY; ++j)
              for (int k = minZ; k <= maxZ; ++k)
                Rb.setPixelZXY(k, i, j, r, g, b);

        } else if (addressMode == MASKED) {
          // treat XYZ as bitmasks
          char xs[CUBE_SIZE];
          char ys[CUBE_SIZE];
          char zs[CUBE_SIZE];

          for (int i  = 0; i < CUBE_SIZE; ++i) {
            char mask = (1 << i);
            xs[i] = x & mask;
            ys[i] = y & mask;
            zs[i] = z & mask;
          }

          for (int x = 0; x < CUBE_SIZE; ++x)
            for (int y = 0; y < CUBE_SIZE; ++y)
              for (int z = 0; z < CUBE_SIZE; ++z)
                if (xs[x] && ys[y] && zs[z])
                  Rb.setPixelZXY(z, x, y, r, g, b);
        }
      }
    }
  }
}
