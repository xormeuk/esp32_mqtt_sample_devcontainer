#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";
const char* mqttServer = "yourMQTTServerAddress";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setupWifi() {
    delay(10);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }

    Serial.println("Connected to the WiFi network");
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);

    Serial.print("Message:");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }

    Serial.println();
    Serial.println("-----------------------");
}

void setup() {
    Serial.begin(115200);
    setupWifi();
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);

    while (!client.connected()) {
        Serial.println("Connecting to MQTT...");

        if (client.connect("ESP32Client")) {
            Serial.println("connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }

    client.publish("outTopic", "hello world");
    client.subscribe("inTopic");
}

void loop() {
    client.loop();
}
