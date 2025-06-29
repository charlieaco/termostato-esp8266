/**
 * Termostato Inteligente ESP8266 - Versión Refactorizada
 * 
 * Sistema de control de temperatura inteligente que obtiene datos meteorológicos
 * de Meteomatics API y toma decisiones automáticas de control.
 * 
 * Arquitectura modular siguiendo principios de Clean Code:
 * - Separación de responsabilidades
 * - Nombres descriptivos
 * - Funciones pequeñas y enfocadas
 * - Configuración centralizada
 * - Manejo de errores mejorado
 */

#include "config.h"
#include "ThermostatStateMachine.h"

// Instancia global de la máquina de estados
ThermostatStateMachine thermostat;

void setup() {
    thermostat.initialize();
}

void loop() {
    thermostat.run();
} 