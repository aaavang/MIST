#include <Rainbowduino.h>

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  Rb.init();
}

void loop() {

  delay(2000);
  int bytesToRead = Serial.available();
  Serial.print(bytesToRead);
  Serial.println(" bytes to read");

  if (Serial.available() >= 7) {
    int cubeID = (int) Serial.read();
    Serial.print("cube ID:");
    Serial.println(cubeID);
    int r = (int) Serial.read();
    int g = (int) Serial.read();
    int b = (int) Serial.read();
    Serial.print("r:");
    Serial.println(r);
    Serial.print("g:");
    Serial.println(g);
    Serial.print("b:");
    Serial.println(b);
    while ((int) Serial.peek() != 255) {
      int x = (int) Serial.read();
      while (!Serial.available());
      int y = (int) Serial.read();
      while (!Serial.available());
      int z = (int) Serial.read();
      Serial.print("(");
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      Serial.print(",");
      Serial.print(z);
      Serial.println(")");

      int minX = x == 254 ? 0 : x;
      int maxX = x == 254 ? 3 : x;

      int minY = y == 254 ? 0 : y;
      int maxY = y == 254 ? 3 : y;

      int minZ = z == 254 ? 0 : z;
      int maxZ = z == 254 ? 3 : z;

      for (int i = minX; i <= maxX; ++i)
        for (int j = minY; j <= maxY; ++j)
          for (int k = minZ; k <= maxZ; ++k)
            Rb.setPixelZXY(k, i, j, r,  g, b);

      while (!Serial.available());
    }

    if (Serial.available() && (int) Serial.peek() == 255) {
      Serial.read();
      Serial.println("cleaning end token");
    }
  }
}
