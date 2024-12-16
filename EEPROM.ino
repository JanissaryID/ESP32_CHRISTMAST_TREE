void writeEEPROM_NUM(int numLedStar[4], int dimensionTree[3]) {
  // Create a JSON document
  StaticJsonDocument<200> doc;

  // Add numLedStar array to the JSON
  JsonArray numLedArray = doc.createNestedArray("numLedStar");
  for (int i = 0; i < 4; i++) {
    numLedArray.add(numLedStar[i]);
  }

  // Add dimensionTree array to the JSON
  JsonArray dimensionArray = doc.createNestedArray("dimensionTree");
  for (int i = 0; i < 3; i++) {
    dimensionArray.add(dimensionTree[i]);
  }

  // Open file for writing
  File file = LittleFS.open("/config.json", "w");
  if (!file) {
    Serial.println("Failed to open file for writing!");
    return;
  }

  // Serialize JSON and write it to the file
  if (serializeJson(doc, file) == 0) {
    Serial.println("Failed to write JSON to file!");
  } else {
    Serial.println("JSON written to file successfully!");
  }

  file.close();  // Close the file
}

void readEEPROM_NUM() {
  // Open file for reading
  File file = LittleFS.open("/config.json", "r");
  if (!file) {
    Serial.println("Failed to open file for reading!");
    return;
  }

  // Create a JSON document for reading
  StaticJsonDocument<200> doc;
  
  // Deserialize the JSON from the file
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.println("Failed to parse JSON!");
    file.close();
    return;
  }

  // Read numLedStar from the JSON
  JsonArray numLedArray = doc["numLedStar"].as<JsonArray>();
  for (int i = 0; i < 4; i++) {
    numLedStar[i] = numLedArray[i];
  }

  // Read dimensionTree from the JSON
  JsonArray dimensionArray = doc["dimensionTree"].as<JsonArray>();
  for (int i = 0; i < 3; i++) {
    dimensionTree[i] = dimensionArray[i];
  }

  // Print the read values
  Serial.println("Read JSON from file:");
  Serial.print("numLedStar: ");
  for (int i = 0; i < 4; i++) {
    Serial.print(numLedStar[i]);
    Serial.print(" ");
  }
  Serial.println();

  Serial.print("dimensionTree: ");
  for (int i = 0; i < 3; i++) {
    Serial.print(dimensionTree[i]);
    Serial.print(" ");
  }
  Serial.println();

  file.close();  // Close the file
}

void storeNumLed(String* parts, int count) {
  if (count < 6) return; // Ensure enough parts for both arrays

  dimensionTree[0] = parts[1].toInt();
  dimensionTree[1] = parts[2].toInt();
  numLedStar[0] = parts[3].toInt();
  numLedStar[1] = parts[4].toInt();
  numLedStar[2] = parts[5].toInt();

  writeEEPROM_NUM(numLedStar, dimensionTree);
}

void setupLittleFS() {
  if (!LittleFS.begin(false)) {
    Serial.println("Failed to initialize LittleFS! Formatting...");
    LittleFS.format(); // Format if mount fails
    if (!LittleFS.begin()) {
      Serial.println("Failed to format and mount LittleFS!");
      while (true); // Halt execution
    }
  }
  Serial.println("LittleFS mounted successfully!");
  readEEPROM_NUM();
}

// Function to write the animation data to LittleFS
void writeAnimation() {
  // Create a JSON document
  StaticJsonDocument<1024> doc;

  // Add dataAnimSize to JSON
  doc["dataAnimSize"] = dataAnimSize;

  // Add dataAnim array to the JSON
  JsonArray dataAnimArray = doc.createNestedArray("dataAnim");
  for (int i = 0; i < dataAnimSize; i++) {
    JsonObject animationObject = dataAnimArray.createNestedObject();
    animationObject["idAnimation"] = dataAnim[i].idAnimation;

    // Add parameterAnimation array for each animation
    JsonArray paramsArray = animationObject.createNestedArray("parameterAnimation");
    for (int j = 0; j < 5; j++) {
      paramsArray.add(dataAnim[i].parameterAnimation[j]);
    }
  }

  // Open file for writing
  File file = LittleFS.open("/animations.json", "w");
  if (!file) {
    Serial.println("Failed to open file for writing!");
    return;
  }

  // Serialize JSON and write it to the file
  if (serializeJson(doc, file) == 0) {
    Serial.println("Failed to write JSON to file!");
  } else {
    Serial.println("Animation data written to file successfully!");
  }

  file.close();  // Close the file
}

// Function to read the animation data from LittleFS
void readAnimation() {
  // Open file for reading
  File file = LittleFS.open("/animations.json", "r");
  if (!file) {
    Serial.println("Failed to open file for reading!");
    return;
  }

  // Create a JSON document for reading
  StaticJsonDocument<1024> doc;

  // Deserialize the JSON from the file
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.println("Failed to parse JSON!");
    file.close();
    return;
  }

  // Read dataAnimSize from the JSON to determine the number of animations
  dataAnimSize = doc["dataAnimSize"];

  // Dynamically allocate memory for dataAnim array based on the size
  if (dataAnimSize > 0) {
    dataAnim = new DataAnimation[dataAnimSize];
  }

  // Read dataAnim array from the JSON
  JsonArray dataAnimArray = doc["dataAnim"].as<JsonArray>();
  for (int i = 0; i < dataAnimSize; i++) {
    JsonObject animationObject = dataAnimArray[i].as<JsonObject>();
    dataAnim[i].idAnimation = animationObject["idAnimation"];
    
    // Read parameterAnimation array for each animation
    JsonArray paramsArray = animationObject["parameterAnimation"].as<JsonArray>();
    for (int j = 0; j < 5; j++) {
      dataAnim[i].parameterAnimation[j] = paramsArray[j];
    }
  }

  // Print the read values
  Serial.println("Read animation data from file:");
  for (int i = 0; i < dataAnimSize; i++) {
    Serial.print("Animation ");
    Serial.print(i);
    Serial.print(" ID: ");
    Serial.print(dataAnim[i].idAnimation);
    Serial.print(" Parameters: ");
    for (int j = 0; j < 5; j++) {
      Serial.print(dataAnim[i].parameterAnimation[j]);
      Serial.print(" ");
    }
    Serial.println();
  }

  file.close();  // Close the file
}

void printDataAnim() {
  // Function to print dataAnim content
  for (int i = 0; i < dataAnimSize; i++) {
    Serial.print("Animation ");
    Serial.print(i);
    Serial.print(" ID: ");
    Serial.print(dataAnim[i].idAnimation);
    Serial.print(" Parameters: ");
    for (int j = 0; j < 5; j++) {
      Serial.print(dataAnim[i].parameterAnimation[j]);
      Serial.print(" ");
    }
    Serial.println();
  }
}