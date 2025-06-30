/**
 * Termostato ESP8266 - Test Suite
 * 
 * Archivo principal para ejecutar todos los tests unitarios
 * de la arquitectura hexagonal del termostato.
 * 
 * Tests organizados por capas:
 * - Domain Layer: Lógica de negocio
 * - Application Layer: Casos de uso
 * - Infrastructure Layer: Adaptadores y utilidades
 * - Interfaces Layer: Controladores
 */

// Framework de testing
#include "tests/TestFramework.h"

// Mocks
#include "tests/mocks/MockTemperatureRepository.h"
#include "tests/mocks/MockTimeRepository.h"
#include "tests/mocks/MockHardwareRepository.h"

// Tests de Domain Layer
#include "tests/domain/services/TemperatureControllerTest.h"

// Tests de Application Layer
#include "tests/application/use_cases/GetTemperatureUseCaseTest.h"
#include "tests/application/use_cases/ControlTemperatureUseCaseTest.h"

// Tests de Infrastructure Layer
#include "tests/infrastructure/json/JsonParserTest.h"

// Variables globales para tests
bool testsCompleted = false;
unsigned long testStartTime = 0;
const unsigned long TEST_TIMEOUT = 30000; // 30 segundos

void setup() {
    Serial.begin(115200);
    delay(1000); // Esperar a que Serial esté listo
    
    Serial.println("\n" + String(60, '='));
    Serial.println("🧪 TERMOSTATO ESP8266 - TEST SUITE");
    Serial.println("Arquitectura Hexagonal - Tests Unitarios");
    Serial.println(String(60, '='));
    
    testStartTime = millis();
}

void loop() {
    if (!testsCompleted) {
        runAllTests();
        testsCompleted = true;
    }
    
    // Verificar timeout
    if (millis() - testStartTime > TEST_TIMEOUT) {
        Serial.println("⚠️  TEST TIMEOUT - Tests taking too long");
        testsCompleted = true;
    }
    
    // Mantener el loop activo
    delay(1000);
}

void runAllTests() {
    Serial.println("\n🚀 Starting Test Suite...\n");
    
    // Ejecutar tests por capas
    runDomainLayerTests();
    runApplicationLayerTests();
    runInfrastructureLayerTests();
    
    // Resumen final
    printTestSummary();
}

void runDomainLayerTests() {
    Serial.println("🎯 DOMAIN LAYER TESTS");
    Serial.println(String(40, '-'));
    
    // Tests de servicios del dominio
    TemperatureControllerTest::runAllTests();
    
    Serial.println();
}

void runApplicationLayerTests() {
    Serial.println("🔧 APPLICATION LAYER TESTS");
    Serial.println(String(40, '-'));
    
    // Tests de casos de uso
    GetTemperatureUseCaseTest::runAllTests();
    ControlTemperatureUseCaseTest::runAllTests();
    
    Serial.println();
}

void runInfrastructureLayerTests() {
    Serial.println("🔌 INFRASTRUCTURE LAYER TESTS");
    Serial.println(String(40, '-'));
    
    // Tests de utilidades de infraestructura
    JsonParserTest::runAllTests();
    
    Serial.println();
}

void printTestSummary() {
    Serial.println(String(60, '='));
    Serial.println("📊 FINAL TEST SUMMARY");
    Serial.println(String(60, '='));
    
    int totalTests = TestFramework::getTotalTests();
    int passedTests = TestFramework::getPassedTests();
    int failedTests = TestFramework::getFailedTests();
    
    Serial.println("Total Tests Executed: " + String(totalTests));
    Serial.println("✅ Tests Passed: " + String(passedTests));
    Serial.println("❌ Tests Failed: " + String(failedTests));
    
    if (failedTests == 0) {
        Serial.println("\n🎉 ALL TESTS PASSED! 🎉");
        Serial.println("✅ The system is working correctly");
    } else {
        Serial.println("\n⚠️  SOME TESTS FAILED!");
        Serial.println("🔧 Please review the failed tests above");
    }
    
    // Estadísticas adicionales
    float passRate = (totalTests > 0) ? (float)passedTests / totalTests * 100 : 0;
    Serial.println("📈 Pass Rate: " + String(passRate, 1) + "%");
    
    Serial.println(String(60, '='));
    Serial.println("🏁 Test Suite Completed");
    Serial.println(String(60, '='));
}

/**
 * @brief Función auxiliar para ejecutar tests específicos
 * 
 * Útil para debugging o ejecutar solo ciertos tests
 */
void runSpecificTests() {
    // Ejemplo: ejecutar solo tests de dominio
    // TemperatureControllerTest::runAllTests();
    
    // Ejemplo: ejecutar solo tests de aplicación
    // GetTemperatureUseCaseTest::runAllTests();
    
    // Ejemplo: ejecutar solo tests de infraestructura
    // JsonParserTest::runAllTests();
} 