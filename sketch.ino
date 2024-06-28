// Now turn this trash into treasure!
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define ONE_WIRE_BUS 2
#define REGULAR_LED_PIN 4

bool ledState = false;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  // put your setup code here, to run once:
  pinMode(REGULAR_LED_PIN, OUTPUT);
  digitalWrite(REGULAR_LED_PIN, LOW);

  Serial.begin(9600);
  Serial.println("Starting up...");

  sensors.begin();
  Serial.println("DS18B20 Temperature Sensor Setup Complete.");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);

  display.clearDisplay();
  display.display();
}

void loop() {
  // Request temperature from DS18B20 sensor
  digitalWrite(REGULAR_LED_PIN, ledState ? HIGH : LOW);

  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  // Print temperature to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  ledState = !ledState;

  if (temperatureC != DEVICE_DISCONNECTED_C) {
    // Print temperature to Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" °C");

    // Display temperature on OLED
    display.clearDisplay();
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.print("Temp: ");
    display.print(temperatureC);
    display.print(" C");
    display.display();
  } else {
    Serial.println("Error: Could not read temperature data");

    // Display error message on OLED
    display.clearDisplay();
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.print("Error");
    display.display();
  }

  delay(1000); // Wait for 1 second before next reading
}