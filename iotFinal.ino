#include "WiFi.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>

#ifndef certs_h
#define certs_h

// Amazon's root CA. This should be the same for everyone.
const char AWS_CERT_CA[] = "-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \ 
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\n"
"-----END CERTIFICATE-----\n";

// The private key for your device
const char AWS_CERT_PRIVATE[] = "-----BEGIN RSA PRIVATE KEY-----\n" \
"MIIEpQIBAAKCAQEAvDEJpnWx7SmF0dwew4lghnOYxw11BHOU+hj7ZrLXVtfNpYwG\n" \
"zfrXK91x60vxTSi4CtE8Edsj54TEZFklXBJr23h4TyNk+ErdcNrmUkWLR24u0CJU\n" \
"tm5uWqM6LosfCi49XuGZD5MtXoamHdnlZeenD3U4hPyq+spKQyUad9KQewiUt9Ib\n" \
"iw9Af6bjGGYGlHWjMIR7Y3290bvNgXwCgKGBKavPQ+Sz/XP5m4k9CFZjjNZE3r0a\n" \
"w035ImUtLOLPEjgr0bVDCL4ChY3gJr6ix6qkWKwH2rxDKOFYuVHiufGFc3MRt/x4\n" \
"ow6pk/c/b6C3dtBYAVR3sJdPM0YDs4ZBcoDb2QIDAQABAoIBAEZygO9MPafPFGYj\n" \
"5WxDP9v05+sTsYtSDSG2Ol4OcqfyruvayC1RSj0Eb4GqcxD0PjjmbHsusnkXbUE3\n" \
"UdHun2uP5FGTqVd9BvoZJ4ECwYmiyGlngJiuLCdH1R7ZO2xfNOAQyXBYIvKwqvyf\n" \
"tcz488PImLjHsOWi1jveZtMWArnbLxdA/7ZKr255fntxOwI1GA4Bk8LlQNvN1DCG\n" \
"hfz522ht6qXP0DHG5y2IVEVTkSxicK1e/NKA7RzOc+0THRWnvSo5fnNihFvqhDvl\n" \
"86uBD6At9gs0778wRNGKGKHDCcfqI5SJCiMsS3u90g0jWolSW1f1ZdfKdKXt806i\n" \
"nPHkCcUCgYEA4PFqbeGJHUPcK8SsnGthM68TAXtXZjwlqgO6lyTUkTmq3E2cG9kd\n" \ 
"G6nau2lh1ijApQ6lLSDnZ2MqPxzXelC8SZI1zQrVzqS9rHoi5ES+HZ/V13KYpTQ7\n" \ 
"bufU7S8KHbuZMlNtTCt6kM2lSTP0mRJm231QErdwiNRCh1uKux0Rbt8CgYEA1iyl\n" \ 
"O/3VgjCQjWPGtD5tuXejZji9ERXbF7o1QzXRq7NXlDnoUlYqQhVfzuUnGAelP/sB\n" \ 
"YFnOuWxhpXNyaoEs4gInj3xQ6MtcQgHsIQB9fKOt0GSvdLctAPm0iKUsDQSvKvHv\n" \ 
"gyiCMawKtt9nCvyV7qZMcHBzajIIaJWR/YQkZEcCgYEA2TFg0S32hXJTcVNaU0H/\n" \
"Pbcqw8CDOCyVNV6aWHvwXzTuO/8X32+4glBz6YcsN2tr7zN/214s8Q+35+6CRBEW\n" \
"bHcnSY7PuNIqbhIUBJI3e0UsZfW5W7JePIzOdCF6RBEyL3yMSQKmOpDFqjPnVbGF\n" \
"7SJHIXtLxmIkxqtl/ZtojMMCgYEAr8uLgPdz5d24+OUZ9156r85cp44Q2lJHOG2W\n" \ 
"RGmLhVS6oSb644JoQz/KGUeMVDQKVr7PvWdZwGcOq0BcfME0tvovwJ24x6wMOP3c\n" \ 
"9KWzWrf69l9+iN3FqdRMdBCnXLQol6ZoAw8f9meRj9NFgAYdhvqnKW+TvGn+7uE+\n" \ 
"KInrWQcCgYEAxk7jmlwsGJqVWMnGJmGjcPTXcr/eZR+mfdxEQNFuWEsZ2BDjke4Y\n" \ 
"L9ZUyw016sJYHlVSPPFdYzj8adv0TNFr9gpZ/QUbelJ2YeKeE263BrYI+yzZLHjx\n" \ 
"39S/ifzN+ujVuqacKMEyw5tvMeCxOthdJwdf+Kn9X5iRup47R0cgrbA=\n" \ 
"-----END RSA PRIVATE KEY-----\n";

// The certificate for your device
const char AWS_CERT_CRT[] = "-----BEGIN CERTIFICATE----- \n"
"MIIDWjCCAkKgAwIBAgIVAIal6/Zp2xHP39dOfwTNAMthY/VxMA0GCSqGSIb3DQEB\n" \
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n" \
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xOTEyMDcxNzA3\n" \
"MjJaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n" \
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC8MQmmdbHtKYXR3B7D\n" \
"iWCGc5jHDXUEc5T6GPtmstdW182ljAbN+tcr3XHrS/FNKLgK0TwR2yPnhMRkWSVc\n" \
"EmvbeHhPI2T4St1w2uZSRYtHbi7QIlS2bm5aozouix8KLj1e4ZkPky1ehqYd2eVl\n" \
"56cPdTiE/Kr6ykpDJRp30pB7CJS30huLD0B/puMYZgaUdaMwhHtjfb3Ru82BfAKA\n" \
"oYEpq89D5LP9c/mbiT0IVmOM1kTevRrDTfkiZS0s4s8SOCvRtUMIvgKFjeAmvqLH\n" \
"qqRYrAfavEMo4Vi5UeK58YVzcxG3/HijDqmT9z9voLd20FgBVHewl08zRgOzhkFy\n" \
"gNvZAgMBAAGjYDBeMB8GA1UdIwQYMBaAFIawQYRWXXbZzGzcFzkVKhevk7UJMB0G\n" \
"A1UdDgQWBBQu9eIheRtvIwqxGnx40T5WE/pJYzAMBgNVHRMBAf8EAjAAMA4GA1Ud\n" \
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAD04Gal+XoEtAU1KLZgRWwOP4\n" \
"Wu1R1ShhpXWsE7epCeHq2Kl3NSUJkRwPHARDroZksKM5K2W+qvxD6KBx9JgYul5h\n" \
"NOwQVMKbeJ5HxeRYekbWTmY0JCtyA6hFGR1sMnkOSEds0MuPk/p8F1nTWlNuGNVP\n" \
"oQq3avcdg4QDsb6sOam4wzorvU80eOxr6gjXWlFOMWrjfylbod6F+x7sEToB+RrS\n" \
"iN/vyVyOdwCRGdkdXPokxkEAyUCT2QJ7GDpn0zyML+HuyD4P4HUGGiQF2gwnIMPE\n" \
"/UOp3DDcl0VYqAKIATUG3rynfTEVZUfqt+3XHrcYdN0eQERJWnN7X67S3bZPXA==\n" \
"-----END CERTIFICATE-----\n";

#endif

// The name of the device. This MUST match up with the name defined in the AWS console
#define DEVICE_NAME "IoT-ESPDUINO32"

// The MQTTT endpoint for the device (unique for each AWS account but shared amongst devices within the account)
#define AWS_IOT_ENDPOINT "a32h7zcf87exln-ats.iot.us-east-2.amazonaws.com"

// The MQTT topic that this device should publish to
#define AWS_IOT_TOPIC "$aws/things/" DEVICE_NAME "/shadow/update"

// How many times we should attempt to connect to AWS
#define AWS_MAX_RECONNECT_TRIES 75

// Wifi credentials
const char *WIFI_SSID = "FLIA ROJAS";
const char *WIFI_PASSWORD = "PIRULOBENJAMIN";
WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(512);

void connectToWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Only try 15 times to connect to the WiFi
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 15){
    delay(500);
    Serial.print(".");
    retries++;
  }

  // If we still couldn't connect to the WiFi, go to deep sleep for a minute and try again.
  if(WiFi.status() != WL_CONNECTED){
    esp_sleep_enable_timer_wakeup(1 * 60L * 1000000L);
    esp_deep_sleep_start();
  }
}

void connectToAWS()
{
    // Configure WiFiClientSecure to use the AWS certificates we generated
    net.setCACert(AWS_CERT_CA);
    net.setCertificate(AWS_CERT_CRT);
    net.setPrivateKey(AWS_CERT_PRIVATE);

    // Connect to the MQTT broker on the AWS endpoint we defined earlier
    client.begin(AWS_IOT_ENDPOINT, 8883, net);

    // Try to connect to AWS and count how many times we retried.
    int retries = 0;
    Serial.print("Connecting to AWS IOT");

    while (!client.connect(DEVICE_NAME) && retries < AWS_MAX_RECONNECT_TRIES) {
        Serial.print(".");
        delay(100);
        retries++;
    }

    // Make sure that we did indeed successfully connect to the MQTT broker
    // If not we just end the function and wait for the next loop.
    if(!client.connected()){
        Serial.println(" Timeout!");
        return;
    }

    // If we land here, we have successfully connected to AWS!
    // And we can subscribe to topics and send messages.
    Serial.println("Connected!");
}

void sendJsonToAWS()
{
  StaticJsonDocument<512> jsonDoc;
  JsonObject stateObj = jsonDoc.createNestedObject("state");
  JsonObject reportedObj = stateObj.createNestedObject("reported");

  // Write the temperature & humidity. Here you can use any C++ type (and you can refer to variables)
  reportedObj["alv"] = 77;
  reportedObj["wifi_strength"] = WiFi.RSSI();

  // Create a nested object "location"
  JsonObject locationObj = reportedObj.createNestedObject("location");
  locationObj["name"] = "Soliduspoilers";

  // Publish the message to AWS
  char jsonBuffer[512];
  serializeJson(jsonDoc, jsonBuffer);
  
  client.publish(AWS_IOT_TOPIC, jsonBuffer);
}



void setup() {
  Serial.begin(9600);
  connectToWiFi();
  connectToAWS();
}

void loop() {
 sendJsonToAWS();
  client.loop();
  delay(1000);
}
