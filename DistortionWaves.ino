uint8_t gamma8(uint8_t x) {
  const uint8_t PROGMEM gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 
  };
  return gamma8[x];
}

uint16_t mode_2DDistortionWaves(uint8_t speed, uint8_t intensity) {
  const int cols = dimensionTree[0];
  const int rows = dimensionTree[1];

  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate < 16) return 0; // FRAMETIME
  lastUpdate = now;

  FastLED.clear(true);

  uint8_t scale = intensity / 32;
  uint8_t w = 2;

  unsigned a = now / 32;
  unsigned a2 = a / 2;
  unsigned a3 = a / 3;

  unsigned cx = beatsin8(10 - speed / 32, 0, cols - 1) * scale;
  unsigned cy = beatsin8(12 - speed / 32, 0, rows - 1) * scale;
  unsigned cx1 = beatsin8(13 - speed / 32, 0, cols - 1) * scale;
  unsigned cy1 = beatsin8(15 - speed / 32, 0, rows - 1) * scale;
  unsigned cx2 = beatsin8(17 - speed / 32, 0, cols - 1) * scale;
  unsigned cy2 = beatsin8(14 - speed / 32, 0, rows - 1) * scale;

  for (int x = 0; x < cols; x++) {
    for (int y = 0; y < rows; y++) {
      byte rdistort = cos8((cos8((x << 3) + a) + cos8((y << 3) - a2) + a3) & 255) >> 1;
      byte gdistort = cos8((cos8((x << 3) - a2) + cos8((y << 3) + a3) + a + 32) & 255) >> 1;
      byte bdistort = cos8((cos8((x << 3) + a3) + cos8((y << 3) - a) + a2 + 64) & 255) >> 1;

      byte valueR = rdistort + w * (a - (((x - cx) * (x - cx) + (y - cy) * (y - cy)) >> 7));
      byte valueG = gdistort + w * (a2 - (((x - cx1) * (x - cx1) + (y - cy1) * (y - cy1)) >> 7));
      byte valueB = bdistort + w * (a3 - (((x - cx2) * (x - cx2) + (y - cy2) * (y - cy2)) >> 7));

      valueR = gamma8(cos8(valueR));
      valueG = gamma8(cos8(valueG));
      valueB = gamma8(cos8(valueB));

      if (XY(x, y) != -1) {
        ledsTree[XY(x, y)] = CRGB(valueR, valueG, valueB);
      }
    }
  }

  FastLED.show();
  return 16; // FRAMETIME
}

// mode_2DDistortionWaves(64, 128);