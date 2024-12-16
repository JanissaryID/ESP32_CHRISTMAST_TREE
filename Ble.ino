class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
    }

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
    }
};

class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pCharacteristic) {
    String value = pCharacteristic->getValue();
    
    std::string valueStd = value.c_str();
    
    Serial.print("Written value: ");
    Serial.println(valueStd.c_str());

    //--------------------------------
    processDataValue = valueStd.c_str();
    processFlag = true;
  }
};

void setupBle() {
  BLEDevice::init("Christmast Tree GKJ Kudus");

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE_NR
  );

  pCharacteristic->setValue("Hello BLE");
  pCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // Minimum preferred connection interval
  pAdvertising->setMinPreferred(0x12); // Maximum preferred connection interval
  pAdvertising->start();
  Serial.println("BLE Advertising started...");
}
