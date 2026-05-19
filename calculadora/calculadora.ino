#include <Arduino.h>
#include <WiFi.h>
#include <NetworkClient.h>
#include <WiFiAP.h>

#include "operacoes.h"  
const char index_html[] PROGMEM = 
#include "index.h"       
;

const char *ssid = "yourAP";
const char *password = "yourPassword";

NetworkServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(LED_BIT0, OUTPUT);
  pinMode(LED_BIT1, OUTPUT);
  pinMode(LED_BIT2, OUTPUT);
  pinMode(LED_BIT3, OUTPUT);

  if (!WiFi.softAP(ssid, password)) {
    while (1);
  }
  
  server.begin();
}

void loop() {
  NetworkClient client = server.accept();

  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print(index_html);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.startsWith("GET /calcula")) {
          int posA = currentLine.indexOf("a=") + 2;
          int fimA = currentLine.indexOf("&", posA);
          String paramA = currentLine.substring(posA, fimA);

          int posB = currentLine.indexOf("b=") + 2;
          int fimB = currentLine.indexOf("&", posB);
          String paramB = currentLine.substring(posB, fimB);

          int posOp = currentLine.indexOf("op=") + 3;
          int fimOp = currentLine.indexOf(" ", posOp);
          String op = currentLine.substring(posOp, fimOp);

          int resultadoFinal = processarCalculoHardware(paramA, paramB, op);

          if (resultadoFinal == -1) {
            client.println("HTTP/1.1 400 Bad Request");
            client.println("Content-type:text/plain");
            client.println();
            client.print("ERRO DE OVERFLOW: O resultado estourou os limites de 4 bits!");
          } else {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/plain");
            client.println();
            client.print(resultadoFinal); 
          }
          break;
        }
      }
    }
    client.stop();
  }
}