int XY(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return -1;

  // Adjust for serpentine wiring
  if (y % 2 == 0) {
    // Even rows go left-to-right
    return (y * WIDTH) + x;
  } else {
    // Odd rows go right-to-left
    return (y * WIDTH) + (WIDTH - 1 - x);
  }
}

void switchAnimation() {
  // Default parameter values if dataAnim is null or no data
  int defaultParameter[5] = {64, 128, 50, 50, 0}; // Default values
  
  // Check if dataAnim is null or no animations are loaded
  if (dataAnim == nullptr || dataAnimSize == 0) {
    Serial.println("No animation data found. Using default parameters.");
    // Use default parameters
    int* parameterAnimation = defaultParameter;
    
    // You may want to set animation = 0 as default animation if no data
    animation = 0; // Assuming you want to run the first animation when no data
  } else {
    // Use parameters from dataAnim for the current animation
    int* parameterAnimation = dataAnim[animation].parameterAnimation;
  }

  // Switch animation based on the current animation index
  switch (animation) {
    case 0:
      Serial.println("DNA");
      mode_2DDNA(parameterAnimation[0], parameterAnimation[1]);
      break;
    case 1:
      Serial.println("DNA SPIRAL");
      mode_2DDNASpiral(parameterAnimation[0], parameterAnimation[1]);
      break;
    case 2:
      Serial.println("DRIFT");
      mode_2DDrift(parameterAnimation[0], parameterAnimation[1]);
      break;
    case 3:
      Serial.println("OCTOPUS");
      mode_2Doctopus();
      break;
    case 4:
      Serial.println("BLACK HOLE");
      mode_2DBlackHole(parameterAnimation[0], parameterAnimation[1], parameterAnimation[2], parameterAnimation[3], parameterAnimation[4]);
      break;
    case 5:
      Serial.println("TWO COLOR");
      twocolor_chase(colorChase[0], colorChase[1]);
      break;
    case 6:
      Serial.println("RAIN");
      mode_2DmatrixEffect(parameterAnimation[0], parameterAnimation[1]);
      break;
    case 7:
      Serial.println("FIRE");
      Fire2012();
      break;
    case 8:
      Serial.println("LISSAJOUS");
      mode_2DLissajous(parameterAnimation[0], parameterAnimation[1]);
      break;
    case 9:
      Serial.println("DISTORTION");
      mode_2DDistortionWaves(parameterAnimation[0], parameterAnimation[1]);
      break;
    case 10:
      Serial.println("RGB ALL");
      RgbColorAll();
      break;
    case 11:
      Serial.println("TRI COLOR");
      tricolor_chase(colorChase[0], colorChase[1], colorChase[3]);
      break;
    default:
      Serial.println("Unknown animation.");
      break;
  }
}
