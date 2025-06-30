#ifndef CONTROL_TEMPERATURE_USE_CASE_TEST_H
#define CONTROL_TEMPERATURE_USE_CASE_TEST_H

#include "../../TestFramework.h"
#include "../../mocks/MockHardwareRepository.h"
#include "../../../src/application/use_cases/ControlTemperatureUseCase.h"

/**
 * @brief Tests para el caso de uso ControlTemperatureUseCase
 * 
 * Prueba la lógica de control de temperatura usando mocks
 * para simular el hardware.
 */
class ControlTemperatureUseCaseTest {
public:
    static void runAllTests();
    
private:
    static void testExecuteCriticalLowTemperature();
    static void testExecuteLowTemperature();
    static void testExecuteMediumTemperature();
    static void testExecuteHighTemperature();
    static void testExecuteWithDifferentTemperatures();
};

void ControlTemperatureUseCaseTest::runAllTests() {
    TestFramework::begin("ControlTemperatureUseCase Tests");
    
    TestFramework::test("Execute - Critical Low Temperature", testExecuteCriticalLowTemperature);
    TestFramework::test("Execute - Low Temperature", testExecuteLowTemperature);
    TestFramework::test("Execute - Medium Temperature", testExecuteMediumTemperature);
    TestFramework::test("Execute - High Temperature", testExecuteHighTemperature);
    TestFramework::test("Execute - With Different Temperatures", testExecuteWithDifferentTemperatures);
    
    TestFramework::end();
}

void ControlTemperatureUseCaseTest::testExecuteCriticalLowTemperature() {
    // Configurar mock de hardware
    MockHardwareRepository hwRepo;
    hwRepo.resetCallCounts();
    
    // Crear caso de uso
    ControlTemperatureUseCase useCase(hwRepo);
    
    // Ejecutar con temperatura crítica baja
    bool result = useCase.execute(3.0);
    
    // Verificar resultados
    TestFramework::assertTrue(result, "Use case should succeed");
    TestFramework::assertTrue(hwRepo.isEmergencyActive(), "Emergency should be activated");
    TestFramework::assertTrue(hwRepo.isHeatingActive(), "Heating should be activated");
    TestFramework::assertEquals(1, hwRepo.getEmergencyCallCount(), "Emergency should be called once");
    TestFramework::assertEquals(1, hwRepo.getHeatingCallCount(), "Heating should be called once");
}

void ControlTemperatureUseCaseTest::testExecuteLowTemperature() {
    // Configurar mock de hardware
    MockHardwareRepository hwRepo;
    hwRepo.resetCallCounts();
    
    // Crear caso de uso
    ControlTemperatureUseCase useCase(hwRepo);
    
    // Ejecutar con temperatura baja
    bool result = useCase.execute(7.5);
    
    // Verificar resultados
    TestFramework::assertTrue(result, "Use case should succeed");
    TestFramework::assertTrue(hwRepo.isHeatingActive(), "Heating should be activated");
    TestFramework::assertFalse(hwRepo.isCoolingActive(), "Cooling should not be activated");
    TestFramework::assertFalse(hwRepo.isEmergencyActive(), "Emergency should not be activated");
    TestFramework::assertEquals(1, hwRepo.getHeatingCallCount(), "Heating should be called once");
    TestFramework::assertEquals(1, hwRepo.getCoolingCallCount(), "Cooling should be called once (deactivate)");
}

void ControlTemperatureUseCaseTest::testExecuteMediumTemperature() {
    // Configurar mock de hardware
    MockHardwareRepository hwRepo;
    hwRepo.resetCallCounts();
    
    // Crear caso de uso
    ControlTemperatureUseCase useCase(hwRepo);
    
    // Ejecutar con temperatura media
    bool result = useCase.execute(13.0);
    
    // Verificar resultados
    TestFramework::assertTrue(result, "Use case should succeed");
    TestFramework::assertFalse(hwRepo.isHeatingActive(), "Heating should not be activated");
    TestFramework::assertFalse(hwRepo.isCoolingActive(), "Cooling should not be activated");
    TestFramework::assertFalse(hwRepo.isEmergencyActive(), "Emergency should not be activated");
    TestFramework::assertEquals(1, hwRepo.getHeatingCallCount(), "Heating should be called once (deactivate)");
    TestFramework::assertEquals(1, hwRepo.getCoolingCallCount(), "Cooling should be called once (deactivate)");
}

void ControlTemperatureUseCaseTest::testExecuteHighTemperature() {
    // Configurar mock de hardware
    MockHardwareRepository hwRepo;
    hwRepo.resetCallCounts();
    
    // Crear caso de uso
    ControlTemperatureUseCase useCase(hwRepo);
    
    // Ejecutar con temperatura alta
    bool result = useCase.execute(25.0);
    
    // Verificar resultados
    TestFramework::assertTrue(result, "Use case should succeed");
    TestFramework::assertTrue(hwRepo.isCoolingActive(), "Cooling should be activated");
    TestFramework::assertFalse(hwRepo.isHeatingActive(), "Heating should not be activated");
    TestFramework::assertFalse(hwRepo.isEmergencyActive(), "Emergency should not be activated");
    TestFramework::assertEquals(1, hwRepo.getCoolingCallCount(), "Cooling should be called once");
    TestFramework::assertEquals(1, hwRepo.getHeatingCallCount(), "Heating should be called once (deactivate)");
}

void ControlTemperatureUseCaseTest::testExecuteWithDifferentTemperatures() {
    // Configurar mock de hardware
    MockHardwareRepository hwRepo;
    
    // Crear caso de uso
    ControlTemperatureUseCase useCase(hwRepo);
    
    // Test múltiples temperaturas
    double temperatures[] = {-5.0, 2.0, 8.0, 12.0, 18.0, 30.0};
    int expectedHeatingCalls = 0;
    int expectedCoolingCalls = 0;
    int expectedEmergencyCalls = 0;
    
    for (double temp : temperatures) {
        hwRepo.resetCallCounts();
        bool result = useCase.execute(temp);
        TestFramework::assertTrue(result, "Use case should succeed for temperature " + String(temp));
        
        // Contar llamadas esperadas según el rango de temperatura
        if (temp < 5.0) {
            expectedEmergencyCalls++;
            expectedHeatingCalls++;
        } else if (temp < 10.0) {
            expectedHeatingCalls++;
            expectedCoolingCalls++; // deactivate
        } else if (temp < 16.0) {
            expectedHeatingCalls++; // deactivate
            expectedCoolingCalls++; // deactivate
        } else {
            expectedCoolingCalls++;
            expectedHeatingCalls++; // deactivate
        }
        
        // Verificar que se llamaron los métodos correctos
        TestFramework::assertTrue(
            hwRepo.getHeatingCallCount() > 0 || hwRepo.getCoolingCallCount() > 0 || hwRepo.getEmergencyCallCount() > 0,
            "At least one control method should be called for temperature " + String(temp)
        );
    }
}

#endif // CONTROL_TEMPERATURE_USE_CASE_TEST_H 