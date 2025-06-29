/**
 * Termostato Inteligente ESP8266 - Arquitectura Hexagonal
 * 
 * Sistema de control de temperatura inteligente que implementa la arquitectura hexagonal
 * (también conocida como arquitectura de puertos y adaptadores).
 * 
 * Arquitectura:
 * - Domain: Lógica de negocio y entidades
 * - Application: Casos de uso y servicios de aplicación
 * - Infrastructure: Implementaciones concretas (adaptadores)
 * - Interfaces: Controladores y orquestación
 */

// Incluir todas las dependencias necesarias
#include "src/infrastructure/config.h"

// Domain Layer
#include "src/domain/entities/ThermostatState.h"
#include "src/domain/repositories/ITemperatureRepository.h"
#include "src/domain/repositories/ITimeRepository.h"
#include "src/domain/repositories/IWifiRepository.h"
#include "src/domain/repositories/IHardwareRepository.h"
#include "src/domain/services/TemperatureController.h"

// Application Layer
#include "src/application/use_cases/GetTemperatureUseCase.h"
#include "src/application/use_cases/ControlTemperatureUseCase.h"

// Infrastructure Layer
#include "src/infrastructure/http/HttpClient.h"
#include "src/infrastructure/http/JsonParser.h"
#include "src/infrastructure/http/MeteoApiAdapter.h"
#include "src/infrastructure/http/WorldTimeApiAdapter.h"
#include "src/infrastructure/hardware/Esp8266HardwareAdapter.h"
#include "src/infrastructure/hardware/Esp8266WifiAdapter.h"

// Interfaces Layer
#include "src/interfaces/controllers/ThermostatController.h"

// Instancias de adaptadores (Infrastructure Layer)
MeteoApiAdapter meteoApiAdapter;
WorldTimeApiAdapter worldTimeApiAdapter;
Esp8266HardwareAdapter hardwareAdapter;
Esp8266WifiAdapter wifiAdapter;

// Instancias de casos de uso (Application Layer)
GetTemperatureUseCase getTemperatureUseCase(meteoApiAdapter, worldTimeApiAdapter);
ControlTemperatureUseCase controlTemperatureUseCase(hardwareAdapter);

// Instancia del controlador principal (Interfaces Layer)
ThermostatController thermostatController(
    wifiAdapter,
    getTemperatureUseCase,
    controlTemperatureUseCase,
    hardwareAdapter
);

void setup() {
    thermostatController.initialize();
}

void loop() {
    thermostatController.run();
} 