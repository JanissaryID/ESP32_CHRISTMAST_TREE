uint16_t mode_2DDNA(uint8_t speed, uint8_t intensity) {
  const int cols = dimensionTree[0];
  const int rows = dimensionTree[1];

  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate < 16) return 0; // FRAMETIME
  lastUpdate = now;

  FastLED.clear(true);

  for (int i = 0; i < cols; i++) {
    int y1 = beatsin8(speed / 8, 0, rows - 1, 0, i * 4);
    int y2 = beatsin8(speed / 8, 0, rows - 1, 0, i * 4 + 128);

    if (XY(i, y1) != -1) {
      ledsTree[XY(i, y1)] = CHSV(i * 5 + now / 17, 255, beatsin8(5, 55, 255, 0, i * 10));
    }
    if (XY(i, y2) != -1) {
      ledsTree[XY(i, y2)] = CHSV(i * 5 + 128 + now / 17, 255, beatsin8(5, 55, 255, 0, i * 10 + 128));
    }
  }

  // Blur untuk efek halus
  for (int i = 0; i < numLedTree; i++) {
    ledsTree[i].nscale8(intensity);
  }

  FastLED.show();
  return 16; // FRAMETIME
}

//mode_2DDNA(64, 128);