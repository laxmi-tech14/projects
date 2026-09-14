
#include <DHT.h>

// ---------- PIN DEFINITIONS ----------
#define PIR_PIN 2
#define DHT_PIN 3
#define DHT_TYPE DHT22

#define ROOM_LIGHT 8
#define WARNING_LED 9
#define BUZZER 10

#define LDR_PIN A0

// ---------- DHT OBJECT ----------
DHT dht(DHT_PIN, DHT_TYPE);

// ---------- LDR THRESHOLD ----------
int darknessThreshold = 500;

void setup() {

  Serial.begin(9600);

  dht.begin();

  pinMode(PIR_PIN, INPUT);

  pinMode(ROOM_LIGHT, OUTPUT);
  pinMode(WARNING_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.println("SMART ROOM MONITOR STARTED");
}

void loop() {

  // Read PIR
  int motion = digitalRead(PIR_PIN);

  // Read LDR
  int lightValue = analogRead(LDR_PIN);

  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // ---------- DISPLAY READINGS ----------

  Serial.println("-------------------------");

  Serial.print("Motion: ");

  if (motion == HIGH) {
    Serial.println("DETECTED");
  } else {
    Serial.println("NO MOTION");
  }

  Serial.print("LDR: ");
  Serial.println(lightValue);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // ---------- SMART LIGHT ----------

  if (motion == HIGH && lightValue > darknessThreshold) {

    digitalWrite(ROOM_LIGHT, HIGH);

    Serial.println("Room Light: ON");

  } else {

    digitalWrite(ROOM_LIGHT, LOW);

    Serial.println("Room Light: OFF");
  }

  // ---------- HIGH TEMPERATURE ALERT ----------

  if (temperature > 30) {

    digitalWrite(WARNING_LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    Serial.println("WARNING: HIGH TEMPERATURE!");

  } else {

    digitalWrite(WARNING_LED, LOW);
    digitalWrite(BUZZER, LOW);
  }

  delay(2000);
}

