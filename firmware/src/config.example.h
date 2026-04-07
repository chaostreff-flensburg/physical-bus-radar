#pragma once

// Copy this file to config.h and fill in your values. config.h is gitignored.

#define WIFI_SSID "your-ssid"
#define WIFI_PASS "your-password"

#define URL_BASE   "https://www.busradar-flensburg.de"
#define URL_DETAIL "https://www.busradar-flensburg.de/json/busradar/vehiclepos"

// WS281x data pin. GPIO18 is taken by VSPI-SCK on most ESP32 boards, so 5 is a
// safer default. Adjust to your wiring.
#define LED_PIN 5

// Poll interval against the upstream API. Don't go below ~1s — be polite.
#define POLL_INTERVAL_MS 2000

// Background dim level for unused LEDs (mirrors busradar.py:44-46).
#define BG_DIM 4
