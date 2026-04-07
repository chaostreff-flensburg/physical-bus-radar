#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <vector>

#include "busradar_client.h"
#include "config.h"
#include "led_map.h"
#include "lines.h"
#include "nearest.h"

static Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
static BusradarClient client;
static unsigned long last_poll_ms = 0;

static void startup_rainbow_wipe() {
    // Fill strip left-to-right with a rainbow, then fade back to black.
    strip.clear();
    strip.show();
    for (size_t i = 0; i < LED_COUNT; ++i) {
        uint16_t hue = (uint32_t)i * 65535UL / LED_COUNT;
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(hue)));
        strip.show();
        delay(20);
    }
    delay(300);
    for (uint8_t b = 255; b > 0; b -= 5) {
        strip.setBrightness(b);
        strip.show();
        delay(15);
    }
    strip.clear();
    strip.setBrightness(255);
    strip.show();
}

static void set_status_leds(uint32_t color) {
    for (size_t i = 0; i < 3 && i < LED_COUNT; ++i) {
        strip.setPixelColor(i, color);
    }
    strip.show();
}

static void connect_wifi() {
    Serial.printf("WiFi connecting to %s", WIFI_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    const unsigned long timeout_ms = 30000;
    unsigned long start = millis();
    unsigned long last_log = start;
    while (WiFi.status() != WL_CONNECTED) {
        // Blue pulse via sine over time.
        float phase = (millis() - start) / 800.0f;
        float s = (sinf(phase * 2.0f * PI) + 1.0f) * 0.5f;  // 0..1
        uint8_t b = (uint8_t)(s * 200.0f) + 10;
        set_status_leds(strip.Color(0, 0, b));

        if (millis() - last_log >= 500) {
            Serial.print('.');
            last_log = millis();
        }
        if (millis() - start > timeout_ms) {
            Serial.println(" FAILED");
            set_status_leds(strip.Color(180, 0, 0));
            delay(2000);
            return;
        }
        delay(30);
    }
    Serial.printf(" ok, ip=%s\n", WiFi.localIP().toString().c_str());
    set_status_leds(strip.Color(0, 120, 0));
    delay(400);
    // Clear status pixels so draw_frame starts from a clean state.
    for (size_t i = 0; i < 3 && i < LED_COUNT; ++i) {
        strip.setPixelColor(i, 0);
    }
    strip.show();
}

static void draw_frame(const std::vector<BusPos>& buses) {
    // Background dim white over the whole strip.
    for (size_t i = 0; i < LED_COUNT; ++i) {
        strip.setPixelColor(i, strip.Color(BG_DIM, BG_DIM, BG_DIM));
    }

    int drawn = 0, off_map = 0, skipped = 0;
    for (const BusPos& b : buses) {
        if (!line_is_active(b.line.c_str())) { ++skipped; continue; }
        size_t idx = nearest_route_point(b.lat, b.lon);
        if (idx >= LED_COUNT) { ++off_map; continue; }
        uint32_t rgb = color_for_line(b.line.c_str());
        strip.setPixelColor(idx, strip.Color((rgb >> 16) & 0xff,
                                             (rgb >> 8) & 0xff,
                                             rgb & 0xff));
        ++drawn;
    }
    strip.show();
    Serial.printf("[frame] buses=%u drawn=%d off_map=%d skipped=%d\n",
                  (unsigned)buses.size(), drawn, off_map, skipped);
}

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("\nbusradar-esp32 boot");

    strip.begin();
    strip.setBrightness(255);
    strip.clear();
    strip.show();

    startup_rainbow_wipe();

    connect_wifi();
}

void loop() {
    unsigned long now = millis();
    if (now - last_poll_ms < POLL_INTERVAL_MS && last_poll_ms != 0) {
        delay(10);
        return;
    }
    last_poll_ms = now;

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi lost, reconnecting");
        connect_wifi();
    }

    std::vector<BusPos> buses;
    if (client.fetch(buses)) {
        draw_frame(buses);
    } else {
        Serial.println("[loop] fetch failed");
    }
}
