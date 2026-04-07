#include "busradar_client.h"
#include "config.h"

#include <ArduinoJson.h>
#ifdef ESP8266
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
using WiFiClientSecure = BearSSL::WiFiClientSecure;
#else
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#endif

namespace {

// Extract the secId value from a Set-Cookie header line.
// Header looks like: "secId=abcdef; Path=/; HttpOnly"
String parse_sec_id(const String& set_cookie) {
    int key = set_cookie.indexOf("secId=");
    if (key < 0) return String();
    int start = key + 6;
    int end = set_cookie.indexOf(';', start);
    if (end < 0) end = set_cookie.length();
    return set_cookie.substring(start, end);
}

}  // namespace

bool BusradarClient::acquire_cookie() {
    WiFiClientSecure client;
    client.setInsecure();  // TODO: pin Let's Encrypt root CA

    HTTPClient http;
    if (!http.begin(client, URL_BASE)) {
        Serial.println("[busradar] http.begin(URL_BASE) failed");
        return false;
    }
    const char* collect[] = {"Set-Cookie"};
    http.collectHeaders(collect, 1);

    int code = http.GET();
    if (code <= 0) {
        Serial.printf("[busradar] cookie GET failed: %s\n", http.errorToString(code).c_str());
        http.end();
        return false;
    }
    String set_cookie = http.header("Set-Cookie");
    http.end();

    sec_id_ = parse_sec_id(set_cookie);
    if (sec_id_.length() == 0) {
        Serial.println("[busradar] no secId in Set-Cookie");
        return false;
    }
    Serial.printf("[busradar] secId acquired (%d chars)\n", sec_id_.length());
    return true;
}

bool BusradarClient::fetch_details(std::vector<BusPos>& out, bool& auth_failed) {
    auth_failed = false;
    out.clear();

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    if (!http.begin(client, URL_DETAIL)) {
        Serial.println("[busradar] http.begin(URL_DETAIL) failed");
        return false;
    }
    http.addHeader("Cookie", String("secId=") + sec_id_);
    http.addHeader("Referer", URL_BASE);
    http.addHeader("User-Agent", "busradar-esp32/1.0");

    int code = http.GET();
    if (code < 0) {
        Serial.printf("[busradar] details GET failed: %s\n", http.errorToString(code).c_str());
        http.end();
        return false;
    }
    if (code >= 400) {
        Serial.printf("[busradar] details GET HTTP %d -> auth refresh\n", code);
        auth_failed = true;
        http.end();
        return false;
    }

    // ~50 buses with lat/lon/line fits comfortably in 8 KiB.
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, http.getStream());
    http.end();

    if (err) {
        Serial.printf("[busradar] json parse error: %s\n", err.c_str());
        return false;
    }

    JsonArray result = doc["result"].as<JsonArray>();
    if (result.isNull()) {
        Serial.println("[busradar] missing 'result' array -> auth refresh");
        auth_failed = true;
        return false;
    }

    for (JsonObject bus : result) {
        BusPos b;
        // Upstream sends lat/lon as strings (see query.py:45) but be tolerant.
        if (bus["lat"].is<const char*>()) {
            b.lat = atof(bus["lat"].as<const char*>());
            b.lon = atof(bus["lon"].as<const char*>());
        } else {
            b.lat = bus["lat"].as<float>();
            b.lon = bus["lon"].as<float>();
        }
        if (bus["line"].is<const char*>()) {
            b.line = bus["line"].as<const char*>();
        } else {
            b.line = String(bus["line"].as<int>());
        }
        out.push_back(b);
    }
    return true;
}

bool BusradarClient::fetch(std::vector<BusPos>& out) {
    if (sec_id_.length() == 0) {
        if (!acquire_cookie()) return false;
    }

    bool auth_failed = false;
    if (fetch_details(out, auth_failed)) return true;

    if (auth_failed) {
        sec_id_ = "";
        if (!acquire_cookie()) return false;
        return fetch_details(out, auth_failed);
    }
    return false;
}
