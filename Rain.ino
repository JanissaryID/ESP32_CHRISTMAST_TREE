void mode_2DmatrixEffect(uint8_t speed, uint8_t fadeAmount) {
  uint8_t trailMap[dimensionTree[0]][dimensionTree[1]] = {0};
  // Fade the entire matrix
  for (uint16_t i = 0; i < numLedTree; i++) {
    ledsTree[i].fadeToBlackBy(fadeAmount);
  }

  // Update trails
  for (uint8_t x = 0; x < dimensionTree[0]; x++) {
    for (uint8_t y = dimensionTree[1] - 1; y > 0; y--) {
      trailMap[x][y] = trailMap[x][y - 1];
      if (trailMap[x][y]) {
        ledsTree[XY(x, y)] = CHSV(96, 255, trailMap[x][y]); // Green hue
        trailMap[x][y] = max(0, trailMap[x][y] - fadeAmount / 32); // Reduce brightness
      }
    }
  }

  // Spawn new trail heads
  for (uint8_t x = 0; x < dimensionTree[0]; x++) {
    if (random8() < 64) { // Adjust spawn rate by changing threshold
      trailMap[x][0] = 255; // Full brightness
      ledsTree[XY(x, 0)] = CHSV(96, 255, 255); // Green hue
    }
  }
}