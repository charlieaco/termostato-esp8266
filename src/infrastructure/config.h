#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
#ifndef WIFI_SSID
#define WIFI_SSID "acosta 2.4"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "casatonta01"
#endif

// Hardware Configuration
#define LED_PIN_1 4
#define LED_PIN_2 5
#define SERIAL_BAUD_RATE 115200

// Timing Configuration
#define ONE_SECOND 1000
#define SETUP_DELAY_SECONDS 4
#define WIFI_RETRY_DELAY_SECONDS 10
#define STATE_MACHINE_DELAY_SECONDS 30
#define TOKEN_RETRY_DELAY_SECONDS 120
#define TEMPERATURE_UPDATE_DELAY_SECONDS 120

// API Configuration
#define METEO_API_HOST "api.meteomatics.com"
#define METEO_LOGIN_HOST "login.meteomatics.com"
#define METEO_API_PORT 443
#define METEO_LOGIN_PORT 443

// SSL Configuration
const char FINGERPRINT_SNI_CLOUDFLARESSL_COM[] PROGMEM = "5D ED 5B 16 EA F6 52 87 A1 F2 6D 3B 45 C3 65 C2 1B 0A 4B 59";

// Authentication
const char METEO_LOGIN_CREDENTIALS[] PROGMEM = "bXljb19hY29zdGFfY2FybG9zOktDQlR1NTA5eXY=";

// Location Configuration (Buenos Aires, Argentina)
#define LOCATION_LATITUDE "-34.396944"
#define LOCATION_LONGITUDE "-58.694444"

// Time API Configuration
#define TIME_API_URL "http://worldtimeapi.org/api/timezone/America/Argentina/Salta"

// Temperature Thresholds
#define TEMPERATURE_HIGH_THRESHOLD 16.0
#define TEMPERATURE_MEDIUM_THRESHOLD 10.0
#define TEMPERATURE_LOW_THRESHOLD 5.0

#endif // CONFIG_H 