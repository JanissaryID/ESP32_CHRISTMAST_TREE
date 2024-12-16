int splitString(String input, char delimiter, String output[], int maxParts) {
  int startIndex = 0;
  int delimiterIndex;
  int count = 0;

  while ((delimiterIndex = input.indexOf(delimiter, startIndex)) != -1) {
    if (count < maxParts) {
      output[count++] = input.substring(startIndex, delimiterIndex);
      startIndex = delimiterIndex + 1;
    } else {
      break; // Prevent overflow
    }
  }

  if (startIndex < input.length() && count < maxParts) {
    output[count++] = input.substring(startIndex);
  }

  return count; // Return the number of parts found
}

void processData(String dataValue) {
   // Ensure array size matches maxParts in splitString
  const int maxParts = 10;

  count = splitString(dataValue, ';', parts, maxParts);

  Serial.println(count);
  Serial.println("-------");
  for (int i = 0; i < count; i++) {
    Serial.println(parts[i]);
  }
  Serial.println("-------");

  // Map string commands to unique integer values
  int commandHash = 0;
  if (parts[0] == "CTree") commandHash = 1;
  else if (parts[0] == "CStar") commandHash = 2;
  else if (parts[0] == "CAll") commandHash = 3;
  else if (parts[0] == "Done") commandHash = 4;
  else if (parts[0] == "Dna") commandHash = 5;
  else if (parts[0] == "DnaSpiral") commandHash = 6;
  else if (parts[0] == "Drift") commandHash = 7;
  else if (parts[0] == "Octopus") commandHash = 8;
  else if (parts[0] == "BlackHole") commandHash = 9;
  else if (parts[0] == "TwoChase") commandHash = 10;
  else if (parts[0] == "Rain") commandHash = 11;
  else if (parts[0] == "Fire") commandHash = 12;
  else if (parts[0] == "Lissajous") commandHash = 13;
  else if (parts[0] == "DistortionWaves") commandHash = 14;
  else if (parts[0] == "Solid") commandHash = 15;
  else if (parts[0] == "ThreeChase") commandHash = 16;
  else if (parts[0] == "AP") commandHash = 17;
  else if (parts[0] == "LSize") commandHash = 18;

  // Use switch to process commands
  switch (commandHash) {
    case 1: // CTree
      storeColorTree(parts, count);
      break;
    case 2: // CStar
      storeColorStar(parts, count);
      break;
    case 3: // CAll
      storeColorTree(parts, count);
      storeColorStar(parts, count);
      break;
    case 4: // Done
      animation = -1;
      break;
    case 5: // Dna
      animation = 0;
      break;
    case 6: // DnaSpiral
      animation = 1;
      break;
    case 7: // Drift
      animation = 2;
      break;
    case 8: // Octopus
      animation = 3;
      break;
    case 9: // BlackHole
      animation = 4;
      break;
    case 10: // ThreeChase
      animation = 5;
      break;
    case 11: // Rain
      animation = 6;
      break;
    case 12: // Fire
      animation = 7;
      break;
    case 13: // Lissajous
      animation = 8;
      break;
    case 14: // DistortionWaves
      animation = 9;
      break;
    case 15: // Solid
      animation = 10;
      break;
    case 16: // Three Color
      animation = 11;
      break;
    case 17: // Anim Param
      storeAnimParam(parts, count);
      break;
    case 18: // Anim Param
      // Serial.println(parts[0]);
      storeNumLed(parts, count);
      break;
    default:
      // Handle unknown command
      Serial.println("Unknown command: " + parts[0]);
      break;
  }
}

void storeColorTree(String* parts, int count){
  for (int i = 0; i < count; i++) {
    treeColor[i] = parts[i+1].toInt();
  }
  RgbColorTree();
}

void storeColorStar(String* parts, int count){
  for (int i = 0; i < count; i++) {
    starColor[i] = parts[i+1].toInt();
  }
  RgbColorStar();
}

void storeAnimParam(String* parts, int count){
  for (int i = 0; i < count-1; i++) {
    parameterAnimation[i] = parts[i+1].toInt();
  }
}

void storeTreeDim(String* parts, int count){
  for (int i = 0; i < count; i++) {
    dimensionTree[i] = parts[i+1].toInt();
  }
}

void storeStarLen(String* parts, int count){
  for (int i = 0; i < count; i++) {
    numLedStar[i] = parts[i+1].toInt();
  }
}