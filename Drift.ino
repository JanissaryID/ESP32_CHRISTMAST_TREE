uint16_t mode_2DDrift(uint8_t speed, uint8_t intensity) {
  const int cols = dimensionTree[0];
  const int rows = dimensionTree[1];

  const int colsCenter = (cols >> 1) + (cols % 2);
  const int rowsCenter = (rows >> 1) + (rows % 2);

  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate < 16) return 0; // FRAMETIME
  lastUpdate = now;

  FastLED.clear(true);

  const float maxDim = max(cols, rows) / 2.0;
  unsigned long t = now / (32 - (speed >> 3));

  for (float i = 1.0f; i < maxDim; i += 0.25f) {
    float angle = radians(t * (maxDim - i));
    int mySin = sin8(angle) * i / 255.0;
    int myCos = cos8(angle) * i / 255.0;

    if (XY(colsCenter + mySin, rowsCenter + myCos) != -1) {
      ledsTree[XY(colsCenter + mySin, rowsCenter + myCos)] = CRGB::White;
    }
  }

  FastLED.show();
  return 16; // FRAMETIME
}

//  mode_2DDrift(64, 128);