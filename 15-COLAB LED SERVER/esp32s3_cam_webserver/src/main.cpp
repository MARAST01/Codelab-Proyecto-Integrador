#include <Arduino.h>
#include <WiFi.h>
#include "esp_camera.h"

// ⚙️ Configuración WiFi
const char* ssid = "jj";
const char* password = "123456789JJG";
WiFiServer server(80);

// 📸 Pines para ESP32S3-CAM con OV2640
#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM     15
#define SIOD_GPIO_NUM     4
#define SIOC_GPIO_NUM     5

#define Y9_GPIO_NUM       16
#define Y8_GPIO_NUM       17
#define Y7_GPIO_NUM       18
#define Y6_GPIO_NUM       12
#define Y5_GPIO_NUM       10
#define Y4_GPIO_NUM       8
#define Y3_GPIO_NUM       9
#define Y2_GPIO_NUM       11
#define VSYNC_GPIO_NUM    6
#define HREF_GPIO_NUM     7
#define PCLK_GPIO_NUM     13



// 🧠 Inicializar cámara
void iniciarCamara() {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 10000000;
    config.pixel_format = PIXFORMAT_JPEG;   
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 10;
    config.fb_count = 1;    
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Error al iniciar la cámara: 0x%x\n", err);
    } else {
        Serial.println("Cámara inicializada correctamente");
    }
}

// 📡 Conexión WiFi
void conectarRedWifi() {
    WiFi.begin(ssid, password);
    Serial.print("Conectando a WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConectado a la red WiFi");
}

// 🔐 Tipo de cifrado
String getTipoCrifrado(wifi_auth_mode_t tipoCifrado) {
switch (tipoCifrado) {
    case WIFI_AUTH_OPEN: return "Abierta";
    case WIFI_AUTH_WEP: return "WEP";
    case WIFI_AUTH_WPA_PSK: return "WPA_PSK";
    case WIFI_AUTH_WPA2_PSK: return "WPA2_PSK";
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA_WPA2_PSK";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2_ENTERPRISE";
    case WIFI_AUTH_MAX: return "WPA_MAX";
    default: return "Desconocido";
}
}

// 📶 Escaneo de redes
void escanearRedes() {
    int n = WiFi.scanNetworks();
    Serial.println("Redes encontradas: " + String(n));
    for (int i = 0; i < n; i++) {
        Serial.println("SSID: " + WiFi.SSID(i));
        Serial.println("RSSI: " + String(WiFi.RSSI(i)));
        Serial.println("MAC: " + WiFi.BSSIDstr(i));
        Serial.println("Cifrado: " + getTipoCrifrado(WiFi.encryptionType(i)));
        Serial.println("-----------------------");
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(2, OUTPUT); // LED
    escanearRedes();
    conectarRedWifi();
    iniciarCamara();
    Serial.println("IP local: " + WiFi.localIP().toString());
    server.begin();
}

void loop() {
    WiFiClient cliente = server.available();
    if (cliente) {
        String mensaje = "";
        Serial.println("Cliente conectado");
        while (cliente.connected()) {
            if (cliente.available()) {
                char letra = cliente.read();
                Serial.write(letra);
                if (letra == '\n') {
                    if (mensaje.length() == 0) {
                        cliente.println("HTTP/1.1 200 OK");
                        cliente.println("Content-type:text/html");
                        cliente.println();
                        cliente.println("<html><body>");
                        cliente.println("<h2>Control de LED y Cámara</h2>");
                        cliente.println("<a href=\"/H\">Encender LED</a><br>");
                        cliente.println("<a href=\"/L\">Apagar LED</a><br>");
                        cliente.println("<a href=\"/cam\">Ver imagen de la cámara</a><br>");
                        cliente.println("</body></html>");
                        cliente.println();