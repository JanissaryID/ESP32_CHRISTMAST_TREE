void cleanupLED() {
  delete[] ledsTree;
  delete[] ledsStar_1;
  delete[] ledsStar_2;
  delete[] ledsStar_3;
}

void RgbColorTree() {
  for (int i = 0; i < numLedTree; i++) { //
    ledsTree[i] = CHSV(treeColor[0], treeColor[1], treeColor[2]); // Set tree color
  }
  FastLED.show(); // Update tree LEDs
}

void RgbColorStar() {
  for (int i = 0; i < numLedStar[0]; i++) {
    ledsStar_1[i] = CHSV(starColor[0], starColor[1], starColor[2]); // Set star color
  }
  for (int i = 0; i < numLedStar[1]; i++) {
    ledsStar_2[i] = CHSV(starColor[0], starColor[1], starColor[2]); // Set star color
  }
  for (int i = 0; i < numLedStar[2]; i++) {
    ledsStar_3[i] = CHSV(starColor[0], starColor[1], starColor[2]); // Set star color
  }
  FastLED.show(); // Update star LEDs
}

void RgbColorAll() {
  RgbColorTree();
  RgbColorStar();
  FastLED.show(); // Update star LEDs
}

void setAllBrightness(int bValue = 0) {
  treeColor[2] = bValue;
  starColor[2] = bValue;
  FastLED.setBrightness(treeColor[2]);
  FastLED.setBrightness(starColor[2]);
}

void setBrightnessTree(int bValue = 0) {
  treeColor[2] = bValue;
  FastLED.setBrightness(treeColor[2]);
}

void setBrightnessStar(int bValue = 0) {
  starColor[2] = bValue;
  FastLED.setBrightness(starColor[2]);
}

void blinkLight() {
  setAllBrightness(255);
  RgbColorAll();
  delay(300);
  setAllBrightness(0);
  RgbColorAll();
  delay(300);
  setAllBrightness(255);
  RgbColorAll();
}

void setupLED() {
  ledsTree = new CRGB[numLedTree];
  ledsStar_1 = new CRGB[numLedStar[0]];
  ledsStar_2 = new CRGB[numLedStar[1]];
  ledsStar_3 = new CRGB[numLedStar[2]];

  FastLED.addLeds<WS2812, LED_TREE_PIN, GRB>(ledsTree, numLedTree);
  FastLED.addLeds<WS2812, LED_STAR_PIN_1, GRB>(ledsStar_1, numLedStar[0]);
  FastLED.addLeds<WS2812, LED_STAR_PIN_2, GRB>(ledsStar_2, numLedStar[1]);
  FastLED.addLeds<WS2812, LED_STAR_PIN_3, GRB>(ledsStar_3, numLedStar[2]);
  FastLED.clear();

  setAllBrightness(255);
  RgbColorAll();

  heatSetup();
}