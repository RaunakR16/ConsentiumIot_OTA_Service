#include <ConsentiumThings.h>
#include <DHT.h>

// Define firmware version
#define FIRMWARE_VERSION "0.1"
#define DHT_PIN 13
#define DHT_TYP DHT11
// Create ConsentiumThings object with firmware version
ConsentiumThingsDalton board(FIRMWARE_VERSION);


// DHT11 SETUP
DHT dht(DHT_PIN, DHT_TYP);


// WiFi credentials
const char *ssid = "YOUR_WIFI_SSID";       // Replace with your WiFi SSID
const char *pass = "YOUR_WIFI_PASSWORD";   // Replace with your WiFi password

// API keys
const char *SendApiKey = "SEND_API KEY";       // API key for sending data
const char *ReceiveApiKey = "RECEIVE_API_KEY";    // API key for receiving OTA updates
const char *BoardApiKey = "BOARD_API_KEY"; // API key for the board

// Data transmission and update intervals
constexpr int interval = 5000;        // Data transmission interval (5 seconds)
const int updateInterval = 10;       // Check for OTA updates every 100 cycles

// Loop cycle counter
int loopCounter = 0;

void setup() {
  // Consentium IoT branding message
  Serial.println("Consentium IoT - Edge Board Library");
  Serial.println("-----------------------------------------");
  Serial.println("Initializing ConsentiumThings Board...");

  // Begin WiFi connection
  board.initWiFi(ssid, pass);

  // Initialize the board for sending data
  board.beginSend(SendApiKey, BoardApiKey);

  // Enable OTA updates
  board.beginOTA(ReceiveApiKey, BoardApiKey);
  dht.begin();

  Serial.println("ConsentiumThings Board Initialized!");
  Serial.println("-----------------------------------------");
  Serial.println();
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  if (isnan(t) || isnan(h))
  {
    Serial.println("ERROE !");
    return;
  }

  // Sensor data
  vector<double> sensorValues = {t, h}; // Sensor data vector
  const char* sensorInfo[] = {"Temperature", "Humidity"}; // Sensor information array

  board.sendData(sensorValues, sensorInfo, LOW_PRE); // Send with low precision

  // Increment the loop counter
  loopCounter++;

  // Check for OTA updates periodically
  if (loopCounter >= updateInterval) 
  {
    Serial.println("[Consentium IoT] Checking for OTA updates...");
    board.checkAndPerformUpdate(); // Check and perform OTA updates
    loopCounter = 0; // Reset the counter after checking for updates
  }

  // Wait before the next data transmission
  delay(interval);
}
