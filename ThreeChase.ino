uint16_t twocolor_chase(CRGB color1, CRGB color2) {
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  // Define the speed of the chase
  uint32_t cycleTime = 50 + ((255 - 128) << 1);  // Adjust speed as needed
  if (now - lastUpdate < cycleTime) return 0;  // No update yet
  lastUpdate = now;

  unsigned width = dimensionTree[0];  // Set each color's width to 16 LEDs (1-16 range)
  unsigned index = (now / cycleTime) % (width * 3);  // Update index based on time

  for (int i = 0; i < numLedTree; i++, index++) {
    if (index > (width * 3) - 1) index = 0;

    CRGB color = color1;
    if (index > (width << 1) - 1) {
      color = CHSV(i * 8, 255, 255);
    } else if (index > width - 1) {
      color = color2;
    }

    ledsTree[i] = color;
  }

  FastLED.show();
  return 16;  // FRAMETIME
}

uint16_t tricolor_chase(CRGB color1, CRGB color2, CRGB color3) {
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();

  // Define the speed of the chase
  uint32_t cycleTime = 50; // Adjust speed as needed
  if (now - lastUpdate < cycleTime) return 0; // No update yet
  lastUpdate = now;

  unsigned width = dimensionTree[0]; // Set each color's width to 16 LEDs
  unsigned index = (now / cycleTime) % (width * 3); // Update index based on time

  for (int i = 0; i < numLedTree; i++, index++) {
    if (index >= (width * 3)) index = 0;

    if (index < width) {
      ledsTree[i] = color1; // First color segment
    } else if (index < (width * 2)) {
      ledsTree[i] = color2; // Second color segment
    } else {
      ledsTree[i] = color3; // Third color segment
    }
  }

  FastLED.show();
  return cycleTime; // Frame time
}

//tricolorChase(64, 5, CRGB::Red, CRGB::Blue);