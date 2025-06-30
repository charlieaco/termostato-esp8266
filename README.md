# Termostato Inteligente ESP8266

Un sistema de termostato inteligente basado en ESP8266 que obtiene datos meteorológicos en tiempo real y toma decisiones automáticas de control de temperatura.

## 🏗️ Arquitectura Modular

El proyecto ha sido refactorizado siguiendo principios de **Clean Code** y **Separación de Responsabilidades**:

### Estructura del Proyecto

```
termostato/
├── termostato_refactorizado.ino    # Archivo principal (versión limpia)
├── termostato_hexagonal.ino        # Versión con arquitectura hexagonal
├── termostato_tests.ino            # Suite de tests unitarios
├── termostato.ino                  # Código original (legacy)
├── config.h                        # Configuración centralizada
├── ThermostatState.h               # Definición de estados
├── JsonParser.h/.cpp               # Manejo de JSON
├── HttpClient.h/.cpp               # Operaciones HTTP/HTTPS
├── TemperatureController.h/.cpp    # Lógica de control de temperatura
├── ThermostatStateMachine.h/.cpp   # Máquina de estados principal
├── src/                            # Arquitectura hexagonal
│   ├── domain/                     # Lógica de negocio
│   ├── application/                # Casos de uso
│   ├── infrastructure/             # Adaptadores externos
│   └── interfaces/                 # Controladores
├── tests/                          # Tests unitarios
│   ├── TestFramework.h             # Framework de testing
│   ├── mocks/                      # Mocks para testing
│   ├── domain/                     # Tests de dominio
│   ├── application/                # Tests de aplicación
│   └── infrastructure/             # Tests de infraestructura
├── run_tests.sh                    # Script para ejecutar tests
├── tests_config.json               # Configuración de tests
├── README.md                       # Documentación
├── LICENSE                         # Licencia MIT
└── .gitignore                      # Archivos a ignorar
```

### Módulos del Sistema

#### 🔧 **Configuración (`config.h`)**
- Todas las constantes y configuraciones centralizadas
- Credenciales WiFi y API
- Umbrales de temperatura
- Configuración de hardware

#### 🔄 **Estados (`ThermostatState.h`)**
- Enumeración clara de estados del sistema
- Nombres descriptivos en lugar de códigos

#### 📊 **Parser JSON (`JsonParser.h/.cpp`)**
- Manejo robusto de respuestas JSON
- Extracción de datos meteorológicos
- Validación de datos

#### 🌐 **Cliente HTTP (`HttpClient.h/.cpp`)**
- Operaciones HTTP/HTTPS seguras
- Manejo de autenticación
- Construcción de URLs dinámicas

#### 🌡️ **Control de Temperatura (`TemperatureController.h/.cpp`)**
- Evaluación de rangos de temperatura
- Lógica de control automático
- Acciones específicas por rango

#### 🎛️ **Máquina de Estados (`ThermostatStateMachine.h/.cpp`)**
- Coordinación de todos los módulos
- Transiciones de estado claras
- Manejo de errores y reintentos

## ✨ Características

- **Control de temperatura automático**: Obtiene datos meteorológicos de Meteomatics API
- **Máquina de estados robusta**: Sistema con estados bien definidos y transiciones claras
- **Conexión WiFi**: Configuración automática de red WiFi
- **Indicadores LED**: Feedback visual del estado del sistema
- **Geolocalización**: Configurado para Buenos Aires, Argentina (-34.396944, -58.694444)
- **Código limpio**: Arquitectura modular siguiendo principios de Clean Code

## 🛠️ Hardware Requerido

- ESP8266 (NodeMCU, Wemos D1 Mini, etc.)
- LEDs para indicadores (pines 4 y 5)
- Fuente de alimentación estable

## ⚙️ Configuración

### Credenciales WiFi
Edita las siguientes líneas en `config.h`:
```cpp
#define WIFI_SSID "tu_red_wifi"
#define WIFI_PASSWORD "tu_password_wifi"
```

### API Meteomatics
El proyecto utiliza la API de Meteomatics para obtener datos meteorológicos. Necesitarás:
- Cuenta en Meteomatics
- Credenciales de acceso (codificadas en Base64)

### Ubicación
El sistema está configurado para Buenos Aires. Para cambiar la ubicación, modifica las coordenadas en `config.h`:
```cpp
#define LOCATION_LATITUDE "-34.396944"
#define LOCATION_LONGITUDE "-58.694444"
```

## 🔄 Estados del Sistema

1. **IDLE**: Estado de espera inicial
2. **INITIALIZING**: Inicialización del sistema
3. **GETTING_AUTH_TOKEN**: Obtención del token de autenticación
4. **GETTING_CURRENT_TIME**: Obtención de la hora actual
5. **GETTING_TEMPERATURE**: Obtención de datos de temperatura
6. **EVALUATING_DECISION**: Evaluación y toma de decisiones
7. **WAITING**: Tiempo de espera entre ciclos

## 🌡️ Funcionalidades

### Obtención de Datos Meteorológicos
- Temperatura actual en grados Celsius
- Hora local sincronizada
- Datos de la API Meteomatics

### Lógica de Control
El sistema evalúa la temperatura en diferentes rangos:
- **CRITICAL_LOW** (< 5°C): Activa calefacción de emergencia
- **LOW** (5-10°C): Activa sistema de calefacción
- **MEDIUM** (10-16°C): Mantiene configuración actual
- **HIGH** (> 16°C): Activa sistema de refrigeración

### Indicadores LED
- LEDs en pines 4 y 5 proporcionan feedback visual del estado del sistema
- Parpadeo durante operaciones
- Indicación de estado de conexión

## 📦 Instalación

1. Instala el IDE de Arduino
2. Agrega el soporte para ESP8266
3. Instala las siguientes librerías:
   - ESP8266WiFi
   - ESP8266HTTPClient
   - Arduino_JSON
   - WiFiClientSecureBearSSL

4. Configura las credenciales WiFi y API en `config.h`
5. Compila y sube `termostato_refactorizado.ino` al ESP8266

## 🔧 Dependencias

- ESP8266WiFi
- ESP8266WiFiMulti
- ESP8266HTTPClient
- WiFiClient
- Arduino_JSON
- WiFiClientSecureBearSSL

## 🧹 Principios de Clean Code Aplicados

### ✅ **Separación de Responsabilidades**
- Cada clase tiene una responsabilidad específica
- Configuración separada de lógica de negocio

### ✅ **Nombres Descriptivos**
- `ThermostatStateMachine` en lugar de `stateMachine`
- `GETTING_AUTH_TOKEN` en lugar de `_GET_TOKEN_`
- `evaluateTemperature` en lugar de `evaluateTemperature`

### ✅ **Funciones Pequeñas y Enfocadas**
- Cada función hace una sola cosa
- Métodos privados para lógica interna
- Funciones estáticas para utilidades

### ✅ **Configuración Centralizada**
- Todas las constantes en `config.h`
- Fácil modificación de parámetros
- Sin valores hardcodeados

### ✅ **Manejo de Errores Mejorado**
- Validación de respuestas JSON
- Reintentos automáticos
- Logging detallado

### ✅ **Código Reutilizable**
- Clases modulares
- Métodos estáticos para utilidades
- Interfaces claras entre módulos

## 📈 Mejoras Implementadas

1. **Eliminación de variables globales**: Datos encapsulados en clases
2. **Manejo de errores robusto**: Validación y reintentos automáticos
3. **Logging mejorado**: Mensajes descriptivos y estructurados
4. **Configuración flexible**: Fácil modificación de parámetros
5. **Código mantenible**: Estructura clara y documentada

## 🚀 Uso

### Versión Refactorizada (Recomendada)
```cpp
// termostato_refactorizado.ino
#include "config.h"
#include "ThermostatStateMachine.h"

ThermostatStateMachine thermostat;

void setup() {
    thermostat.initialize();
}

void loop() {
    thermostat.run();
}
```

### Versión Original (Legacy)
```cpp
// termostato.ino - Código original
// Mantenido para compatibilidad
```

## 📄 Licencia

Este proyecto está bajo licencia MIT. Ver el archivo LICENSE para más detalles.

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor, abre un issue o pull request para sugerencias y mejoras.

## 👨‍💻 Autor

Desarrollado para control de temperatura inteligente con ESP8266, aplicando principios de Clean Code y arquitectura modular.

## 🧪 Tests Unitarios

El proyecto incluye una suite completa de tests unitarios organizados por capas de la arquitectura hexagonal.

### 🎯 Cobertura de Tests

- ✅ **Domain Layer**: Tests de lógica de negocio (100%)
- ✅ **Application Layer**: Tests de casos de uso (100%)
- ✅ **Infrastructure Layer**: Tests de adaptadores (JSON parser)
- 🔄 **Interfaces Layer**: Tests de controladores (pendiente)

### 🚀 Ejecutar Tests

#### Opción 1: Arduino IDE
1. Abrir `termostato_tests.ino` en Arduino IDE
2. Compilar y subir al ESP8266
3. Abrir Monitor Serial (115200 baud)
4. Los tests se ejecutarán automáticamente

#### Opción 2: Script Automatizado
```bash
# Ejecutar todos los tests
./run_tests.sh

# Solo compilar
./run_tests.sh -c

# Solo subir (asume compilado)
./run_tests.sh -u

# Solo ejecutar tests (asume subido)
./run_tests.sh -t

# Usar puerto específico
./run_tests.sh -p /dev/ttyUSB1
```

### 📊 Ejemplo de Output

```
==================================================
🧪 TEST SUITE: TemperatureController Tests
==================================================
🔍 Running test: Evaluate Temperature - Critical Low ... ✅ PASSED
🔍 Running test: Evaluate Temperature - Low ... ✅ PASSED
🔍 Running test: Evaluate Temperature - Medium ... ✅ PASSED
🔍 Running test: Evaluate Temperature - High ... ✅ PASSED
🔍 Running test: Get Temperature Range Description ... ✅ PASSED
==================================================
📊 TEST RESULTS:
Total Tests: 5
✅ Passed: 5
❌ Failed: 0
🎉 ALL TESTS PASSED!
==================================================
```

### 🎭 Mocks Disponibles

- **MockTemperatureRepository**: Simula API de temperatura
- **MockTimeRepository**: Simula API de tiempo
- **MockHardwareRepository**: Simula control de hardware

### 📖 Documentación de Tests

Ver [tests/README.md](tests/README.md) para documentación detallada sobre:
- Framework de testing
- Cómo agregar nuevos tests
- Mejores prácticas
- Debugging de tests 