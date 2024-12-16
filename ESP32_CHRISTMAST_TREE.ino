#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include <FastLED.h>

#include <LittleFS.h>
#include <ArduinoJson.h>

#define FILE_PATH "/config.txt"
// //ESP32
// #define LED_TREE_PIN 2     // Define pin for tree LED (must be a constant)
// #define LED_STAR_PIN_1 4       // Define pin for star LED (must be a constant)
// #define LED_STAR_PIN_2 25      // Define pin for star LED (must be a constant)
// #define LED_STAR_PIN_3 33      // Define pin for star LED (must be a constant)
//ESP32S3
#define LED_TREE_PIN 48     // Define pin for tree LED (must be a constant)
#define LED_STAR_PIN_1 4       // Define pin for star LED (must be a constant)
#define LED_STAR_PIN_2 21      // Define pin for star LED (must be a constant)
#define LED_STAR_PIN_3 33      // Define pin for star LED (must be a constant)

#define SERVICE_UUID        "6e400001-b5a3-f393-e0a9-e50e24dcca9e"
#define CHARACTERISTIC_UUID "6e400002-b5a3-f393-e0a9-e50e24dcca9e"

BLEServer *pServer = nullptr;
BLECharacteristic *pCharacteristic = nullptr;

bool deviceConnected = false;
bool wasConnected = false;

String processDataValue;
volatile bool processFlag = false;

int animation = 10;

String parts[10];
int count = 0;

int dimensionTree[3] = {16, 16, 0}; //Width, Height

int numLedTree = dimensionTree[0]*dimensionTree[1];       // Number of tree LEDs
int numLedStar[4] = {55, 35, 15, 0}; // Edge, Middle, Center

int treeColor[4] = {255,128,255}; //Hue, Saturation, Brightness
int starColor[4] = {255,128,255}; //Hue, Saturation, Brightness

int dataFormat[3] = {-1, -1}; // Mode, NumData
CRGB colorChase[4] = {CRGB::Red, CRGB::Blue, CRGB::White};

int parameterAnimation[5] = {64,128,50,50};

char dataString[50];

CRGB* ledsTree;
CRGB* ledsStar_1;
CRGB* ledsStar_2;
CRGB* ledsStar_3;

byte** heat;
void heatSetup();

uint16_t mode_2DDNA(uint8_t speed, uint8_t intensity);
void mode_2DmatrixEffect(uint8_t speed, uint8_t fadeAmount);
void Fire2012();
uint16_t mode_2DLissajous(uint8_t speed, uint8_t intensity);
uint16_t mode_2Doctopus();
uint16_t mode_2DBlackHole(uint8_t speed, uint8_t fade, uint8_t intensity, uint8_t outerFreq, uint8_t innerFreq);
uint16_t twocolor_chase(CRGB color1, CRGB color2);
uint16_t tricolor_chase(CRGB color1, CRGB color2, CRGB color3);
uint16_t mode_2DDNASpiral(uint8_t speed, uint8_t intensity);
uint16_t mode_2DDistortionWaves(uint8_t speed, uint8_t intensity);
uint16_t mode_2DDrift(uint8_t speed, uint8_t intensity);
void writeEEPROM_NUM(int numLedStar[4], int dimensionTree[3]);

struct DataAnimation {
  int idAnimation;
  int parameterAnimation[5];
};

DataAnimation* dataAnim = nullptr;  // Will hold the data dynamically
int dataAnimSize = 0;  // To track the size of dataAnim array

void setup() {
  Serial.begin(115200);
  setupLittleFS();
  delay(1000);
  readAnimation();
  delay(1000);
  setupLED();
  setupBle();
}

void loop() {
  if (deviceConnected) {
    if (!wasConnected) {
      Serial.println("Device connected!");
      blinkLight();
      snprintf(dataString, sizeof(dataString), "Num;%d;%d;%d;%d;%d",
           dimensionTree[0], dimensionTree[1],
           numLedStar[0], numLedStar[1], numLedStar[2]);
      pCharacteristic->setValue(dataString);
      pCharacteristic->notify();
      wasConnected = true;
    }

    // Running loop when connected
    if(processFlag){
      processData(processDataValue);
      processFlag = false;
    }
  } else if (wasConnected) {
    Serial.println("Device disconnected!");
    wasConnected = false;

    // Restart advertising
    pServer->startAdvertising();
    Serial.println("Restarting advertising...");
  }
  switchAnimation();
  FastLED.show();
  delay(50);
}
