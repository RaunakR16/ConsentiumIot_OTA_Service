#include <ConsentiumThings.h>
#include <DHT.h>

// Define firmware version
#define FIRMWARE_VERSION "0.0"
#define DHT_PIN 23
#define DHT_TYP DHT11

// Create ConsentiumThings object with firmware version
ConsentiumThingsDalton board(FIRMWARE_VERSION);


// DHT11 SETUP
DHT dht(DHT_PIN, DHT_TYP);


// WiFi credentials
const char *ssid = "VENOM";       // Replace with your WiFi SSID
const char *pass = "RDrdRDrd!^16";   // Replace with your WiFi password

// API keys
const char *SendApiKey = "5e4fca227ad0dbfd7c507588cdc8567b";       // API key for sending data
const char *ReceiveApiKey = "e02849241ffd7355779ef91fcc522db5";    // API key for receiving OTA updates
const char *BoardApiKey = "b8488bb534718d60"; // API key for the board

// Data transmission and update intervals
constexpr int interval = 5000;        // Data transmission interval (5 seconds)
const int updateInterval = 5;        // Check for OTA updates every 100 cycles

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  
  // Consentium IoT branding message
  Serial.println("Consentium IoT - Edge Board Library");
  Serial.println("-----------------------------------------");
  Serial.println("Initializing ConsentiumThings Board...");

  // Begin WiFi connection
  board.connectWiFi(ssid, pass);

  // Initialize the board for sending data
  board.enableSend(SendApiKey, BoardApiKey);

  // Enable OTA updates
  board.enableAirUpdate(ReceiveApiKey, BoardApiKey);

  // Set the interval for checking OTA updates
  board.setSyncInterval(updateInterval);

  Serial.println("ConsentiumThings Board Initialized!");
  Serial.println("-----------------------------------------");
  Serial.println();
}

void loop() {
  float t = dht.readTemperature();
  
  if (isnan(t))
  {
    Serial.println("ERROE !");
    return;
  }

  // Sensor data
  vector<double> sensorValues = {t}; // Sensor data vector
  const char* sensorInfo[] = {"Temperature"}; // Sensor information array

  board.airSync(sensorValues, sensorInfo, LOW_PRE); // Send with low precision

  // Wait before the next data transmission
  delay(interval);
}
