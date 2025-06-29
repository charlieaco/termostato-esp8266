# Arquitectura Hexagonal - Termostato ESP8266

## 🏗️ Diagrama de Arquitectura

```
┌─────────────────────────────────────────────────────────────────┐
│                        INTERFACES LAYER                        │
├─────────────────────────────────────────────────────────────────┤
│  ThermostatController                                           │
│  ┌─────────────────────────────────────────────────────────────┐ │
│  │ • Orquesta todos los componentes                           │ │
│  │ • Coordina casos de uso                                    │ │
│  │ • Maneja la máquina de estados                             │ │
│  └─────────────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌─────────────────────────────────────────────────────────────────┐
│                      APPLICATION LAYER                         │
├─────────────────────────────────────────────────────────────────┤
│  GetTemperatureUseCase    ControlTemperatureUseCase            │
│  ┌─────────────────────┐  ┌─────────────────────────────────┐   │
│  │ • Obtiene token     │  │ • Evalúa temperatura           │   │
│  │ • Obtiene tiempo    │  │ • Ejecuta acciones de control  │   │
│  │ • Obtiene temp      │  │ • Activa/desactiva sistemas    │   │
│  └─────────────────────┘  └─────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌─────────────────────────────────────────────────────────────────┐
│                        DOMAIN LAYER                            │
├─────────────────────────────────────────────────────────────────┤
│  Entities:                    Services:                        │
│  ┌─────────────────────┐  ┌─────────────────────────────────┐   │
│  │ • ThermostatState   │  │ • TemperatureController        │   │
│  └─────────────────────┘  └─────────────────────────────────┘   │
│                                                               │
│  Repositories (Interfaces):                                   │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │ • ITemperatureRepository                               │   │
│  │ • ITimeRepository                                      │   │
│  │ • IWifiRepository                                      │   │
│  │ • IHardwareRepository                                  │   │
│  └─────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌─────────────────────────────────────────────────────────────────┐
│                     INFRASTRUCTURE LAYER                       │
├─────────────────────────────────────────────────────────────────┤
│  HTTP Adapters:              Hardware Adapters:                │
│  ┌─────────────────────┐  ┌─────────────────────────────────┐   │
│  │ • MeteoApiAdapter   │  │ • Esp8266HardwareAdapter       │   │
│  │ • WorldTimeApiAdapter│  │ • Esp8266WifiAdapter          │   │
│  └─────────────────────┘  └─────────────────────────────────┘   │
│                                                               │
│  Utilities:                                                   │
│  ┌─────────────────────────────────────────────────────────┐   │
│  │ • HttpClient                                           │   │
│  │ • JsonParser                                           │   │
│  │ • config.h                                             │   │
│  └─────────────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────────────┘
```

## 📁 Estructura de Directorios

```
termostato/
├── termostato_hexagonal.ino           # Archivo principal (Arquitectura Hexagonal)
├── termostato_refactorizado.ino       # Versión modular anterior
├── termostato.ino                     # Código original (legacy)
│
├── src/
│   ├── domain/                        # 🎯 Lógica de negocio
│   │   ├── entities/                  # Entidades del dominio
│   │   │   └── ThermostatState.h
│   │   ├── repositories/              # Interfaces (Puertos)
│   │   │   ├── ITemperatureRepository.h
│   │   │   ├── ITimeRepository.h
│   │   │   ├── IWifiRepository.h
│   │   │   └── IHardwareRepository.h
│   │   └── services/                  # Servicios del dominio
│   │       ├── TemperatureController.h
│   │       └── TemperatureController.cpp
│   │
│   ├── application/                   # 🔧 Casos de uso
│   │   └── use_cases/
│   │       ├── GetTemperatureUseCase.h
│   │       ├── GetTemperatureUseCase.cpp
│   │       ├── ControlTemperatureUseCase.h
│   │       └── ControlTemperatureUseCase.cpp
│   │
│   ├── infrastructure/                # 🔌 Implementaciones (Adaptadores)
│   │   ├── config.h                   # Configuración centralizada
│   │   ├── http/                      # Adaptadores HTTP
│   │   │   ├── HttpClient.h
│   │   │   ├── HttpClient.cpp
│   │   │   ├── JsonParser.h
│   │   │   ├── JsonParser.cpp
│   │   │   ├── MeteoApiAdapter.h
│   │   │   ├── MeteoApiAdapter.cpp
│   │   │   ├── WorldTimeApiAdapter.h
│   │   │   └── WorldTimeApiAdapter.cpp
│   │   └── hardware/                  # Adaptadores de hardware
│   │       ├── Esp8266HardwareAdapter.h
│   │       ├── Esp8266HardwareAdapter.cpp
│   │       ├── Esp8266WifiAdapter.h
│   │       └── Esp8266WifiAdapter.cpp
│   │
│   └── interfaces/                    # 🎮 Controladores
│       └── controllers/
│           ├── ThermostatController.h
│           └── ThermostatController.cpp
│
├── README.md                          # Documentación principal
├── REFACTORING_GUIDE.md               # Guía de refactoring
├── ARCHITECTURE_DIAGRAM.md            # Este archivo
├── LICENSE                            # Licencia MIT
└── .gitignore                         # Archivos a ignorar
```

## 🔄 Flujo de Dependencias

### Principio de Inversión de Dependencias

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Controller    │───▶│   Use Cases     │───▶│   Repositories  │
│   (Interfaces)  │    │   (Application) │    │   (Domain)      │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
         ▼                       ▼                       ▼
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Adapters      │    │   Adapters      │    │   Adapters      │
│ (Infrastructure)│    │(Infrastructure) │    │(Infrastructure) │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

### Reglas de Dependencia

1. **Domain Layer**: No depende de ninguna otra capa
2. **Application Layer**: Solo depende de Domain Layer
3. **Infrastructure Layer**: Implementa interfaces de Domain Layer
4. **Interfaces Layer**: Orquesta Application e Infrastructure

## 🎯 Beneficios de la Arquitectura Hexagonal

### ✅ **Separación de Responsabilidades**
- **Domain**: Lógica de negocio pura
- **Application**: Casos de uso específicos
- **Infrastructure**: Implementaciones técnicas
- **Interfaces**: Orquestación y control

### ✅ **Testabilidad**
- Cada capa puede ser testeada independientemente
- Fácil mock de dependencias externas
- Tests unitarios aislados

### ✅ **Mantenibilidad**
- Cambios localizados en capas específicas
- Fácil agregar nuevas funcionalidades
- Código organizado y predecible

### ✅ **Flexibilidad**
- Fácil cambiar proveedores de API
- Fácil cambiar hardware
- Fácil agregar nuevos casos de uso

### ✅ **Escalabilidad**
- Estructura preparada para crecimiento
- Fácil agregar nuevas entidades
- Fácil agregar nuevos repositorios

## 🔧 Configuración de Inyección de Dependencias

```cpp
// En termostato_hexagonal.ino

// 1. Crear instancias de adaptadores (Infrastructure)
MeteoApiAdapter meteoApiAdapter;
WorldTimeApiAdapter worldTimeApiAdapter;
Esp8266HardwareAdapter hardwareAdapter;
Esp8266WifiAdapter wifiAdapter;

// 2. Crear instancias de casos de uso (Application)
GetTemperatureUseCase getTemperatureUseCase(meteoApiAdapter, worldTimeApiAdapter);
ControlTemperatureUseCase controlTemperatureUseCase(hardwareAdapter);

// 3. Crear instancia del controlador (Interfaces)
ThermostatController thermostatController(
    wifiAdapter,
    getTemperatureUseCase,
    controlTemperatureUseCase,
    hardwareAdapter
);
```

## 🚀 Ventajas sobre la Arquitectura Anterior

| Aspecto | Arquitectura Modular | Arquitectura Hexagonal |
|---------|---------------------|------------------------|
| **Separación** | Por funcionalidad | Por capas de responsabilidad |
| **Dependencias** | Directas | Invertidas (DIP) |
| **Testabilidad** | Moderada | Alta |
| **Flexibilidad** | Media | Alta |
| **Escalabilidad** | Media | Alta |
| **Mantenibilidad** | Buena | Excelente |

## 📈 Próximos Pasos

1. **Implementar tests unitarios** para cada capa
2. **Agregar logging estructurado** por capa
3. **Implementar configuración dinámica** (Web interface)
4. **Agregar persistencia de datos** (EEPROM/SPIFFS)
5. **Implementar OTA updates** (Over-the-Air)
6. **Agregar más casos de uso** (configuración, monitoreo)
7. **Implementar patrones adicionales** (Factory, Observer, etc.)

## 📚 Referencias

- [Clean Architecture by Robert C. Martin](https://blog.cleancoder.com/uncle-bob/2012/08/13/the-clean-architecture.html)
- [Hexagonal Architecture (Ports and Adapters)](https://alistair.cockburn.us/hexagonal-architecture/)
- [SOLID Principles](https://en.wikipedia.org/wiki/SOLID)
- [Dependency Inversion Principle](https://en.wikipedia.org/wiki/Dependency_inversion_principle) 