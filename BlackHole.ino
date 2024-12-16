// Efek Black Hole
uint16_t mode_2DBlackHole(uint8_t speed, uint8_t fade, uint8_t intensity, uint8_t outerFreq, uint8_t innerFreq) {
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  // Periksa apakah saatnya memperbarui frame berdasarkan kecepatan
  if (now - lastUpdate < 16) return 0; // FRAMETIME
  lastUpdate = now;

  // Fading trails
  for (int i = 0; i < numLedTree; i++) {
    ledsTree[i].fadeToBlackBy(fade);
  }

  // Waktu berbasis frame
  unsigned long t = now / 128;

  // Outer stars
  for (size_t i = 0; i < 8; i++) {
    int x = beatsin8(outerFreq, 0, dimensionTree[0] - 1, 0, ((i % 2) ? 128 : 0) + t * i);
    int y = beatsin8(intensity, 0, dimensionTree[1] - 1, 0, ((i % 2) ? 192 : 64) + t * i);
    if (XY(x, y) != -1) {
      ledsTree[XY(x, y)] += CHSV(i * 32, 255, 255);
    }
  }

  // Inner stars
  for (size_t i = 0; i < 4; i++) {
    int x = beatsin8(innerFreq, dimensionTree[0] / 4, dimensionTree[0] - 1 - dimensionTree[0] / 4, 0, ((i % 2) ? 128 : 0) + t * i);
    int y = beatsin8(innerFreq, dimensionTree[1] / 4, dimensionTree[1] - 1 - dimensionTree[1] / 4, 0, ((i % 2) ? 192 : 64) + t * i);
    if (XY(x, y) != -1) {
      ledsTree[XY(x, y)] += CHSV(255 - i * 64, 255, 255);
    }
  }

  // Central white dot
  ledsTree[XY(dimensionTree[0] / 2, dimensionTree[1] / 2)] = CRGB::White;

  FastLED.show();
  return 16; // FRAMETIME
}

//mode_2DBlackHole(64, 32, 128, 16, 32);