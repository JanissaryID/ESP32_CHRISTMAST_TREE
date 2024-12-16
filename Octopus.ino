typedef struct {
  uint8_t angle;
  uint8_t radius;
} map_t;

uint16_t mode_2Doctopus() {
  const int cols = dimensionTree[0];  // Get number of columns from dimensionTree
  const int rows = dimensionTree[1];  // Get number of rows from dimensionTree
  const uint8_t mapp = 180 / max(cols, rows);

  // Dynamically allocate memory for rMap based on the number of columns and rows
  static map_t* rMap = nullptr;
  if (rMap == nullptr) {
    rMap = (map_t*)malloc(cols * rows * sizeof(map_t));  // Allocate memory for the map
    if (rMap == nullptr) {
      Serial.println("Memory allocation failed!");
      return 0;
    }
  }

  static uint8_t offsX = 128;      // Offset X (initial value)
  static uint8_t offsY = 128;      // Offset Y (initial value)

  // Re-initialize if necessary
  static unsigned long lastUpdate = 0;
  unsigned long now = millis();
  if (now - lastUpdate > 100) {
    lastUpdate = now;
    const int C_X = (cols / 2) + ((offsX - 128) * cols) / 255;
    const int C_Y = (rows / 2) + ((offsY - 128) * rows) / 255;

    for (int x = 0; x < cols; x++) {
      for (int y = 0; y < rows; y++) {
        int dx = (x - C_X);
        int dy = (y - C_Y);
        rMap[x + y * cols].angle = int(40.7436f * atan2(dy, dx));  // Angle calculation
        rMap[x + y * cols].radius = sqrt(dx * dx + dy * dy) * mapp; // Radius calculation
      }
    }
  }

  static uint16_t step = 0;
  step += 1; // Increment step (simulate speed control)

  for (int x = 0; x < cols; x++) {
    for (int y = 0; y < rows; y++) {
      byte angle = rMap[x + y * cols].angle;
      byte radius = rMap[x + y * cols].radius;
      
      unsigned intensity = sin8(sin8((angle * 4 - radius) / 4 + step / 2) + radius - step + angle * 8);
      intensity = map((intensity * intensity) & 0xFFFF, 0, 65535, 0, 255); // Non-linear intensity

      // Using CHSV to generate colors dynamically based on step, radius, and angle
      CRGB c = CHSV(step / 2 - radius, 255, intensity);  // Color generated based on hue, saturation, and value
      ledsTree[x + y * cols] = c;  // Assign the color to the LED in the array
    }
  }

  FastLED.show();
  return 16;  // Frame time (adjust this to control speed)
}