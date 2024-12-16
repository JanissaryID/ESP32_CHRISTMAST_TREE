uint16_t mode_2DDNASpiral(uint8_t speed, uint8_t intensity) {
  const int cols = dimensionTree[0];
  const int rows = dimensionTree[1];

  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  if (now - lastUpdate < 16) return 0; // FRAMETIME
  lastUpdate = now;

  unsigned speeds = speed / 2 + 7;
  unsigned freq = intensity / 8;

  uint32_t ms = now / 20;

  // Fade out the current frame
  for (int i = 0; i < numLedTree; i++) {
    ledsTree[i].fadeToBlackBy(135);
  }

  for (int i = 0; i < rows; i++) {
    int x  = beatsin8(speeds, 0, cols - 1, 0, i * freq) + beatsin8(speeds - 7, 0, cols - 1, 0, i * freq + 128);
    int x1 = beatsin8(speeds, 0, cols - 1, 0, 128 + i * freq) + beatsin8(speeds - 7, 0, cols - 1, 0, 128 + 64 + i * freq);
    unsigned hue = (i * 128 / rows) + ms;

    // Skip every 4th row occasionally
    if ((i + ms / 8) & 3) {
      x = x / 2;
      x1 = x1 / 2;
      unsigned steps = abs(x - x1) + 1;
      bool positive = (x1 >= x); // Direction of drawing

      for (size_t k = 1; k <= steps; k++) {
        unsigned dx = positive ? (x + k - 1) : (x - k + 1);
        if (XY(dx, i) != -1) {
          ledsTree[XY(dx, i)] += CHSV(hue, 255, 255);
          ledsTree[XY(dx, i)].fadeLightBy(k * 255 / steps);
        }
      }

      if (XY(x, i) != -1) ledsTree[XY(x, i)] = CRGB::DarkSlateGray;
      if (XY(x1, i) != -1) ledsTree[XY(x1, i)] = CRGB::White;
    }
  }

  FastLED.show();
  return 16; // FRAMETIME
}

//mode_2DDNASpiral(64, 128);