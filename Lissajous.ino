uint16_t mode_2DLissajous(uint8_t speed, uint8_t intensity) {
  const int cols = dimensionTree[0];
  const int rows = dimensionTree[1];

  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate < 16) return 0; // FRAMETIME
  lastUpdate = now;

  FastLED.clear(true);

  uint_fast16_t phase = (now * speed) / 32;

  for (int i = 0; i < 256; i++) {
    uint_fast8_t xlocn = sin8(phase / 2 + (i * intensity) / 32);
    uint_fast8_t ylocn = cos8(phase / 2 + i * 2);

    xlocn = (cols < 2) ? 1 : (map(2 * xlocn, 0, 511, 0, 2 * (cols - 1)) + 1) / 2;
    ylocn = (rows < 2) ? 1 : (map(2 * ylocn, 0, 511, 0, 2 * (rows - 1)) + 1) / 2;

    if (XY(xlocn, ylocn) != -1) {
      ledsTree[XY(xlocn, ylocn)] = CHSV(now / 100 + i, 255, 255);
    }
  }

  FastLED.show();
  return 16; // FRAMETIME
}

// mode_2DLissajous(64, 128);