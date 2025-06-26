# Termostato Inteligente ESP8266

Un sistema de termostato inteligente basado en ESP8266 que obtiene datos meteorológicos en tiempo real y toma decisiones automáticas de control de temperatura.

## Características

- **Control de temperatura automático**: Obtiene datos meteorológicos de Meteomatics API
- **Máquina de estados**: Sistema robusto con estados bien definidos
- **Conexión WiFi**: Configuración automática de red WiFi
- **Indicadores LED**: Feedback visual del estado del sistema
- **Geolocalización**: Configurado para Buenos Aires, Argentina (-34.396944, -58.694444)

## Hardware Requerido

- ESP8266 (NodeMCU, Wemos D1 Mini, etc.)
- LEDs para indicadores (pines 4 y 5)
- Fuente de alimentación estable

## Configuración

### Credenciales WiFi
Edita las siguientes líneas en el código:
```cpp
#define STASSID "tu_red_wifi"
#define STAPSK "tu_password_wifi"
```

### API Meteomatics
El proyecto utiliza la API de Meteomatics para obtener datos meteorológicos. Necesitarás:
- Cuenta en Meteomatics
- Credenciales de acceso (codificadas en Base64)

### Ubicación
El sistema está configurado para Buenos Aires. Para cambiar la ubicación, modifica las coordenadas:
```cpp
// Coordenadas actuales: Buenos Aires
// -34.396944,-58.694444
```

## Estados del Sistema

1. **IDLE**: Estado de espera inicial
2. **INITIALIZE**: Inicialización del sistema
3. **GET_TOKEN**: Obtención del token de autenticación
4. **GET_CURRENT_TIME**: Obtención de la hora actual
5. **GET_TEMPERATURE**: Obtención de datos de temperatura
6. **TAKE_DECISION**: Evaluación y toma de decisiones
7. **SPENDING_TIME**: Tiempo de espera entre ciclos

## Funcionalidades

### Obtención de Datos Meteorológicos
- Temperatura actual en grados Celsius
- Hora local sincronizada
- Datos de la API Meteomatics

### Lógica de Control
El sistema evalúa la temperatura en diferentes rangos:
- > 16°C: Rango alto
- 10-16°C: Rango medio
- 5-10°C: Rango bajo
- < 5°C: Rango crítico

### Indicadores LED
- LEDs en pines 4 y 5 proporcionan feedback visual del estado del sistema

## Instalación

1. Instala el IDE de Arduino
2. Agrega el soporte para ESP8266
3. Instala las siguientes librerías:
   - ESP8266WiFi
   - ESP8266HTTPClient
   - Arduino_JSON
   - WiFiClientSecureBearSSL

4. Configura las credenciales WiFi y API
5. Compila y sube el código al ESP8266

## Estructura del Proyecto

```
termostato/
├── termostato.ino    # Código principal
├── README.md         # Documentación
└── .gitignore        # Archivos a ignorar
```

## Dependencias

- ESP8266WiFi
- ESP8266WiFiMulti
- ESP8266HTTPClient
- WiFiClient
- Arduino_JSON
- WiFiClientSecureBearSSL

## Licencia

Este proyecto está bajo licencia MIT. Ver el archivo LICENSE para más detalles.

## Contribuciones

Las contribuciones son bienvenidas. Por favor, abre un issue o pull request para sugerencias y mejoras.

## Autor

Desarrollado para control de temperatura inteligente con ESP8266. 