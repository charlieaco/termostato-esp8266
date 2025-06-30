#ifndef TEMPERATURE_CONTROLLER_TEST_H
#define TEMPERATURE_CONTROLLER_TEST_H

#include "../../TestFramework.h"
#include "../../../src/domain/services/TemperatureController.h"

/**
 * @brief Tests para el controlador de temperatura
 * 
 * Prueba la lógica de evaluación de temperatura y
 * clasificación en rangos.
 */
class TemperatureControllerTest {
public:
    static void runAllTests();
    
private:
    static void testEvaluateTemperatureCriticalLow();
    static void testEvaluateTemperatureLow();
    static void testEvaluateTemperatureMedium();
    static void testEvaluateTemperatureHigh();
    static void testGetTemperatureRangeDescription();
};

void TemperatureControllerTest::runAllTests() {
    TestFramework::begin("TemperatureController Tests");
    
    TestFramework::test("Evaluate Temperature - Critical Low", testEvaluateTemperatureCriticalLow);
    TestFramework::test("Evaluate Temperature - Low", testEvaluateTemperatureLow);
    TestFramework::test("Evaluate Temperature - Medium", testEvaluateTemperatureMedium);
    TestFramework::test("Evaluate Temperature - High", testEvaluateTemperatureHigh);
    TestFramework::test("Get Temperature Range Description", testGetTemperatureRangeDescription);
    
    TestFramework::end();
}

void TemperatureControllerTest::testEvaluateTemperatureCriticalLow() {
    // Test temperatura crítica baja (< 5°C)
    auto result1 = TemperatureController::evaluateTemperature(4.9);
    TestFramework::assertEquals(
        static_cast<int>(TemperatureController::TemperatureRange::CRITICAL_LOW),
        static_cast<int>(result1),
        "Temperature 4.9°C should be CRITICAL_LOW"
    );
    
    auto result2 = TemperatureController::evaluateTemperature(0.0);
    TestFramework::assertEquals(
        static_cast<int>(TemperatureController::TemperatureRange::CRITICAL_LOW),
        static_cast<int>(result2),
        "Temperature 0.0°C should be CRITICAL_LOW"
    );
    
    auto result3 = TemperatureController::evaluateTemperature(-10.0);
    TestFramework::assertEquals(
        static_cast<int>(TemperatureController::TemperatureRange::CRITICAL_LOW),
        static_cast<int>(result3),
        "Temperature -10.0°C should be CRITICAL_LOW"
    );
}

void TemperatureControllerTest::testEvaluateTemperatureLow() {
    // Test temperatura baja (5-10°C)
    auto result1 = TemperatureController::evaluateTemperature(5.0);
    TestFramework::assertEquals(
        static_cast<int>(TemperatureController::TemperatureRange::LOW),
        static_cast<int>(result1),
        "Temperature 5.0°C should be LOW"
    );
    
    auto result2 = TemperatureController::evaluateTemperature(7.5);
    TestFramework::assertEquals(
        static_cast<int>(TemperatureController::TemperatureRange::LOW),
        static_cast<int>(result2),
        "Temperature 7.5°C should be LOW"
    );
    
    auto result3 = TemperatureController::evaluateTemperature(9.9);
    TestFramework::assertEquals(
        static_cast<int>(TemperatureController::TemperatureRange::LOW),
        static_cast<int>(result3),
        "Temperature 9.9°C should be LOW"
    );
}

void TemperatureControllerTest::testEvaluateTemperatureMedium() {
    // Test temperatura media (10-16°C)
    auto result1 = TemperatureController::evaluateTemperature(10.0);
    TestFramework::assertEquals(
        static_cast<int>(TemperatureController::TemperatureRange::MEDIUM),
        static_cast<int>(result1),
        "Temperature 10.0°C should be MEDIUM"
    );
    
    auto result2 = TemperatureController::evaluateTemperature(13.0);
    TestFramework::assertEquals(
        static_cast<int>(TemperatureController::TemperatureRange::MEDIUM),
        static_cast<int>(result2),
        "Temperature 13.0°C should be MEDIUM"
    );
    
    auto result3 = TemperatureController::evaluateTemperature(15.9);
    TestFramework::assertEquals(
        static_cast<int>(TemperatureController::TemperatureRange::MEDIUM),
        static_cast<int>(result3),
        "Temperature 15.9°C should be MEDIUM"
    );
}

void TemperatureControllerTest::testEvaluateTemperatureHigh() {
    // Test temperatura alta (> 16°C)
    auto result1 = TemperatureController::evaluateTemperature(16.0);
    TestFramework::assertEquals(
        static_cast<int>(TemperatureController::TemperatureRange::HIGH),
        static_cast<int>(result1),
        "Temperature 16.0°C should be HIGH"
    );
    
    auto result2 = TemperatureController::evaluateTemperature(20.0);
    TestFramework::assertEquals(
        static_cast<int>(TemperatureController::TemperatureRange::HIGH),
        static_cast<int>(result2),
        "Temperature 20.0°C should be HIGH"
    );
    
    auto result3 = TemperatureController::evaluateTemperature(30.0);
    TestFramework::assertEquals(
        static_cast<int>(TemperatureController::TemperatureRange::HIGH),
        static_cast<int>(result3),
        "Temperature 30.0°C should be HIGH"
    );
}

void TemperatureControllerTest::testGetTemperatureRangeDescription() {
    // Test descripciones de rangos
    String desc1 = TemperatureController::getTemperatureRangeDescription(
        TemperatureController::TemperatureRange::CRITICAL_LOW
    );
    TestFramework::assertEquals("Critical Low (< 5°C)", desc1, "CRITICAL_LOW description");
    
    String desc2 = TemperatureController::getTemperatureRangeDescription(
        TemperatureController::TemperatureRange::LOW
    );
    TestFramework::assertEquals("Low (5-10°C)", desc2, "LOW description");
    
    String desc3 = TemperatureController::getTemperatureRangeDescription(
        TemperatureController::TemperatureRange::MEDIUM
    );
    TestFramework::assertEquals("Medium (10-16°C)", desc3, "MEDIUM description");
    
    String desc4 = TemperatureController::getTemperatureRangeDescription(
        TemperatureController::TemperatureRange::HIGH
    );
    TestFramework::assertEquals("High (> 16°C)", desc4, "HIGH description");
}

#endif // TEMPERATURE_CONTROLLER_TEST_H 