#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include <BleKeyboard.h>



BleKeyboard bleKeyboard("AirPods Pro");

const char ssid[] = "School-Student";//your ssid
const char pass[] = "";       // パスワードは8文字以上
const IPAddress ip(192, 168, 123, 45);//your decided ipaddress
const IPAddress subnet(255, 255, 255, 0);
AsyncWebServer server(80);            // ポート設定

// Jsonオブジェクトの初期化


#define LED_PIN 25

uint8_t led_status;  //LEDの状態制御用変数

void setup()
{
  Serial.begin(115200);
  bleKeyboard.begin();
  // SPIFFSのセットアップ
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.softAP(ssid, pass);           // SSIDとパスの設定
  delay(100);                        // このdelayを入れないと失敗する場合がある
  WiFi.softAPConfig(ip, ip, subnet); // IPアドレス、ゲートウェイ、サブネットマスクの設定

  IPAddress myIP = WiFi.softAPIP();  // WiFi.softAPIP()でWiFi起動

  // 各種情報を表示
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // GETリクエストに対するハンドラーを登録
  // rootにアクセスされた時のレスポンス
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });
  // style.cssにアクセスされた時のレスポンス
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });
  server.on("/conf.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    String names = request->arg("param");
    String gender = request->arg("gender");
    String blood = request->arg("blood");
    String opinion = request->arg("opinion");
    String confHTML = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>Confirmation Page</title></head><body>";
    confHTML += "<h1>Confirmation Page</h1>";
    confHTML += "<p>お名前：" + names + "</p>";
    confHTML += "<p>性別：" + gender + "</p>";
    confHTML += "<p>血液型：" + blood + "</p>";
    confHTML += "<p>ご意見：" + opinion + "</p>";
    confHTML += "</body></html>";

    // レスポンスとしてconf.htmlの内容を返す
    request->send(200, "text/html", confHTML);
  });

  // LED の制御変数の変更リクエスト


  // サーバースタート
  server.begin();

  Serial.println("Server start!");
}

void loop() {
  // LED状態変更
 if (bleKeyboard.isConnected()) {
    /* bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.write(116);*/
    //windows
    Serial.println("Sending 'Hello world'...");
    bleKeyboard.write(KEY_LEFT_GUI);
    Serial.println("Sending 'Hello world'...");
    bleKeyboard.print("cmd");
    delay(1000);
    Serial.println("Sending Enter key...");
    bleKeyboard.write(KEY_RETURN);

    delay(1000);

    Serial.println("Sending Play/Pause media key...");
    bleKeyboard.print("start https'//github.com/golderperson");
    bleKeyboard.write(KEY_RETURN);
    delay(500);
    bleKeyboard.write(KEY_RETURN);
    delay(500);
    Serial.println("Sending Play/Pause media key...");
    bleKeyboard.print("start https://github.com/golderperson");
    bleKeyboard.write(KEY_RETURN);
    delay(3000);

    Serial.println("Sending Enter key...");
    delay(3000);
    //android
    Serial.println("Sending Ctrl+Alt+Delete...");
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.press('b');
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.write(KEY_RETURN);
    delay(500);
    bleKeyboard.write(KEY_RETURN);
    delay(1000);
    Serial.println("Sending Enter key...");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press('t');
    delay(500);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press('l');
    delay(500);
    bleKeyboard.releaseAll();
    bleKeyboard.print("https'//github.com/golderperson");
    bleKeyboard.write(KEY_RETURN);
    delay(500);
    bleKeyboard.write(KEY_RETURN);
    delay(500);
    Serial.println("Sending Play/Pause media key...");
    bleKeyboard.print("https://github.com/golderperson");
    bleKeyboard.write(KEY_RETURN);
    delay(3000);
    //chromebook
    Serial.println("Sending Ctrl+Alt+Delete...");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press('t');
    delay(100);
    bleKeyboard.releaseAll();
    delay(500);
    bleKeyboard.print("https'//github.com/golderperson");
    bleKeyboard.write(KEY_RETURN);
    delay(500);
    bleKeyboard.write(KEY_RETURN);
    delay(500);
    Serial.println("Sending Play/Pause media key...");
    bleKeyboard.print("https://github.com/golderperson");
    bleKeyboard.write(KEY_RETURN);
    delay(3000);
  


  }
  
  Serial.println("Waiting 5 seconds...");
  delay(100);
}
