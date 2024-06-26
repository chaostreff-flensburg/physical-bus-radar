import requests
import random
import time
from rpi_ws281x import PixelStrip, Color

# LED-Konfiguration
LED_COUNT = 65  # Anzahl der LEDs
LED_PIN = 18    # GPIO-Pin für den LED-Streifen
LED_FREQ_HZ = 800000  # Frequenz (Hz) für den LED-Streifen
LED_DMA = 10    # DMA-Kanal für den LED-Streifen
LED_BRIGHTNESS = 255  # Helligkeit (0-255) für den LED-Streifen
LED_INVERT = False    # 'True' um die Logik zu invertieren
LED_CHANNEL = 0    # 0 oder 1, je nachdem welcher PWM-Hardware-Chip verwendet wird

# Setzen Sie die URL Ihrer REST-Schnittstelle hier ein
REST_URL = "http://127.0.0.1:8000/busradar/v1/details"

# Funktion zum Abrufen von LED-Daten von der REST-Schnittstelle
def get_led_data():
    try:
        response = requests.get(REST_URL)
        response.raise_for_status()  # Wirft eine Exception für 4xx und 5xx Statuscodes
        return response.json()
    except requests.exceptions.RequestException as e:
        print("Fehler beim Abrufen der Daten von der REST-Schnittstelle:", e)
        return {}

# Funktion zum Steuern der LEDs
def control_leds(led_data):
    # Setup LED strip
    # Schleife durch die LED-Daten und setzen der Farben
    #print(led_data)
    for led_info in led_data:
        led_index = int(led_info['led'])
        color_str = led_info['color']
        color_int = Color(*(int(color_str[i:i+2], 16) for i in (1, 3, 5)))  # Umwandlung von Hexadezimalfarbe in Farbnummer
        strip.setPixelColor(led_index, color_int)

if __name__ == "__main__":
    strip = PixelStrip(LED_COUNT, LED_PIN, LED_FREQ_HZ, LED_DMA, LED_INVERT, LED_BRIGHTNESS, LED_CHANNEL)
    strip.begin()
    resetrange = range(0, LED_COUNT)
    while True:
        for ledi in resetrange:
            colorrandom = random.randint(4,10)
            strip.setPixelColor(ledi, Color(colorrandom,colorrandom,colorrandom))
        led_data = get_led_data()
        if led_data:
            control_leds(led_data)
        time.sleep(0.1)
        strip.show()
