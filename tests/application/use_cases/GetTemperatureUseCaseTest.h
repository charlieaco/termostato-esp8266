#ifndef GET_TEMPERATURE_USE_CASE_TEST_H
#define GET_TEMPERATURE_USE_CASE_TEST_H

#include "../../TestFramework.h"
#include "../../mocks/MockTemperatureRepository.h"
#include "../../mocks/MockTimeRepository.h"
#include "../../../src/application/use_cases/GetTemperatureUseCase.h"

/**
 * @brief Tests para el caso de uso GetTemperatureUseCase
 * 
 * Prueba la lógica de obtención de temperatura usando mocks
 * para simular las dependencias externas.
 */
class GetTemperatureUseCaseTest {
public:
    static void runAllTests();
    
private:
    static void testExecuteSuccess();
    static void testExecuteFailureOnAuthToken();
    static void testExecuteFailureOnCurrentTime();
    static void testExecuteFailureOnTemperature();
    static void testExecuteWithMockData();
};

void GetTemperatureUseCaseTest::runAllTests() {
    TestFramework::begin("GetTemperatureUseCase Tests");
    
    TestFramework::test("Execute - Success", testExecuteSuccess);
    TestFramework::test("Execute - Failure on Auth Token", testExecuteFailureOnAuthToken);
    TestFramework::test("Execute - Failure on Current Time", testExecuteFailureOnCurrentTime);
    TestFramework::test("Execute - Failure on Temperature", testExecuteFailureOnTemperature);
    TestFramework::test("Execute - With Mock Data", testExecuteWithMockData);
    
    TestFramework::end();
}

void GetTemperatureUseCaseTest::testExecuteSuccess() {
    // Configurar mocks para éxito
    MockTemperatureRepository tempRepo;
    MockTimeRepository timeRepo;
    
    tempRepo.setShouldSucceed(true);
    tempRepo.setMockToken("test_token_123");
    tempRepo.setMockTemperature(22.5);
    
    timeRepo.setShouldSucceed(true);
    timeRepo.setMockTime("2024-01-15T10:30:00Z");
    
    // Crear caso de uso
    GetTemperatureUseCase useCase(tempRepo, timeRepo);
    
    // Ejecutar
    double temperature;
    bool result = useCase.execute(temperature);
    
    // Verificar resultados
    TestFramework::assertTrue(result, "Use case should succeed");
    TestFramework::assertEquals(22.5, temperature, 0.1, "Temperature should match mock");
    TestFramework::assertEquals(1, tempRepo.getCallCount(), "Temperature repository should be called once");
    TestFramework::assertEquals(1, timeRepo.getCallCount(), "Time repository should be called once");
}

void GetTemperatureUseCaseTest::testExecuteFailureOnAuthToken() {
    // Configurar mocks para fallo en token
    MockTemperatureRepository tempRepo;
    MockTimeRepository timeRepo;
    
    tempRepo.setShouldSucceed(false); // Simular fallo en getAuthToken
    timeRepo.setShouldSucceed(true);
    
    // Crear caso de uso
    GetTemperatureUseCase useCase(tempRepo, timeRepo);
    
    // Ejecutar
    double temperature;
    bool result = useCase.execute(temperature);
    
    // Verificar resultados
    TestFramework::assertFalse(result, "Use case should fail");
    TestFramework::assertEquals(0, tempRepo.getCallCount(), "Temperature repository should not be called");
    TestFramework::assertEquals(0, timeRepo.getCallCount(), "Time repository should not be called");
}

void GetTemperatureUseCaseTest::testExecuteFailureOnCurrentTime() {
    // Configurar mocks para fallo en tiempo
    MockTemperatureRepository tempRepo;
    MockTimeRepository timeRepo;
    
    tempRepo.setShouldSucceed(true);
    timeRepo.setShouldSucceed(false); // Simular fallo en getCurrentTime
    
    // Crear caso de uso
    GetTemperatureUseCase useCase(tempRepo, timeRepo);
    
    // Ejecutar
    double temperature;
    bool result = useCase.execute(temperature);
    
    // Verificar resultados
    TestFramework::assertFalse(result, "Use case should fail");
    TestFramework::assertEquals(0, tempRepo.getCallCount(), "Temperature repository should not be called");
    TestFramework::assertEquals(1, timeRepo.getCallCount(), "Time repository should be called once");
}

void GetTemperatureUseCaseTest::testExecuteFailureOnTemperature() {
    // Configurar mocks para fallo en temperatura
    MockTemperatureRepository tempRepo;
    MockTimeRepository timeRepo;
    
    tempRepo.setShouldSucceed(true);
    tempRepo.setMockToken("test_token_123");
    // getCurrentTemperature fallará porque shouldSucceed está true pero no hay temperatura configurada
    
    timeRepo.setShouldSucceed(true);
    timeRepo.setMockTime("2024-01-15T10:30:00Z");
    
    // Crear caso de uso
    GetTemperatureUseCase useCase(tempRepo, timeRepo);
    
    // Ejecutar
    double temperature;
    bool result = useCase.execute(temperature);
    
    // Verificar resultados
    TestFramework::assertFalse(result, "Use case should fail");
    TestFramework::assertEquals(1, tempRepo.getCallCount(), "Temperature repository should be called once");
    TestFramework::assertEquals(1, timeRepo.getCallCount(), "Time repository should be called once");
}

void GetTemperatureUseCaseTest::testExecuteWithMockData() {
    // Configurar mocks con datos específicos
    MockTemperatureRepository tempRepo;
    MockTimeRepository timeRepo;
    
    tempRepo.setShouldSucceed(true);
    tempRepo.setMockToken("mock_auth_token_456");
    tempRepo.setMockTemperature(18.7);
    
    timeRepo.setShouldSucceed(true);
    timeRepo.setMockTime("2024-01-15T14:45:30Z");
    
    // Crear caso de uso
    GetTemperatureUseCase useCase(tempRepo, timeRepo);
    
    // Ejecutar
    double temperature;
    bool result = useCase.execute(temperature);
    
    // Verificar resultados
    TestFramework::assertTrue(result, "Use case should succeed with mock data");
    TestFramework::assertEquals(18.7, temperature, 0.1, "Temperature should match mock data");
    
    // Verificar que los repositorios fueron llamados correctamente
    TestFramework::assertEquals(1, tempRepo.getCallCount(), "Temperature repository call count");
    TestFramework::assertEquals(1, timeRepo.getCallCount(), "Time repository call count");
}

#endif // GET_TEMPERATURE_USE_CASE_TEST_H 