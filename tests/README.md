# Tests Unitarios - Termostato ESP8266

Este directorio contiene todos los tests unitarios para el proyecto del termostato ESP8266, organizados siguiendo la arquitectura hexagonal.

## 📁 Estructura de Tests

```
tests/
├── TestFramework.h                 # Framework de testing personalizado
├── README.md                       # Esta documentación
├── mocks/                          # Mocks para dependencias externas
│   ├── MockTemperatureRepository.h
│   ├── MockTimeRepository.h
│   └── MockHardwareRepository.h
├── domain/                         # Tests de la capa de dominio
│   └── services/
│       └── TemperatureControllerTest.h
├── application/                    # Tests de la capa de aplicación
│   └── use_cases/
│       ├── GetTemperatureUseCaseTest.h
│       └── ControlTemperatureUseCaseTest.h
└── infrastructure/                 # Tests de la capa de infraestructura
    └── json/
        └── JsonParserTest.h
```

## 🧪 Framework de Testing

### TestFramework.h

Framework de testing personalizado para Arduino/ESP8266 que proporciona:

- **Assertions**: `assertTrue()`, `assertFalse()`, `assertEquals()`, `assertNotNull()`
- **Test Execution**: `test()`, `begin()`, `end()`
- **Reporting**: Estadísticas de tests ejecutados, pasados y fallidos
- **Error Handling**: Manejo de excepciones y mensajes de error descriptivos

### Ejemplo de Uso

```cpp
#include "TestFramework.h"

void testExample() {
    TestFramework::begin("Mi Test Suite");
    
    TestFramework::test("Test de ejemplo", []() {
        int expected = 5;
        int actual = 2 + 3;
        TestFramework::assertEquals(expected, actual, "Suma básica");
    });
    
    TestFramework::end();
}
```

## 🎭 Mocks

### MockTemperatureRepository

Simula el repositorio de temperatura para testing sin dependencias externas:

```cpp
MockTemperatureRepository tempRepo;
tempRepo.setShouldSucceed(true);
tempRepo.setMockTemperature(22.5);
tempRepo.setMockToken("test_token");

double temperature;
bool result = tempRepo.getCurrentTemperature("2024-01-15T10:30:00Z", "test_token", temperature);
// result = true, temperature = 22.5
```

### MockTimeRepository

Simula el repositorio de tiempo:

```cpp
MockTimeRepository timeRepo;
timeRepo.setShouldSucceed(true);
timeRepo.setMockTime("2024-01-15T10:30:00Z");

String currentTime;
bool result = timeRepo.getCurrentTime(currentTime);
// result = true, currentTime = "2024-01-15T10:30:00Z"
```

### MockHardwareRepository

Simula el repositorio de hardware con contadores de llamadas:

```cpp
MockHardwareRepository hwRepo;
hwRepo.resetCallCounts();

ControlTemperatureUseCase useCase(hwRepo);
useCase.execute(15.0);

// Verificar estado
TestFramework::assertTrue(hwRepo.isHeatingActive());
TestFramework::assertEquals(1, hwRepo.getHeatingCallCount());
```

## 🎯 Tests por Capa

### Domain Layer Tests

**TemperatureControllerTest.h**
- ✅ Evaluación de rangos de temperatura (CRITICAL_LOW, LOW, MEDIUM, HIGH)
- ✅ Descripciones de rangos de temperatura
- ✅ Casos límite y valores extremos

### Application Layer Tests

**GetTemperatureUseCaseTest.h**
- ✅ Obtención exitosa de temperatura
- ✅ Manejo de fallos en token de autenticación
- ✅ Manejo de fallos en obtención de tiempo
- ✅ Manejo de fallos en obtención de temperatura
- ✅ Verificación de llamadas a repositorios

**ControlTemperatureUseCaseTest.h**
- ✅ Activación de calefacción para temperaturas bajas
- ✅ Activación de refrigeración para temperaturas altas
- ✅ Activación de emergencia para temperaturas críticas
- ✅ Desactivación de sistemas para temperaturas medias
- ✅ Verificación de estado del hardware

### Infrastructure Layer Tests

**JsonParserTest.h**
- ✅ Extracción exitosa de valores JSON
- ✅ Manejo de claves inexistentes
- ✅ Extracción de temperatura de respuesta de API
- ✅ Validación de JSON
- ✅ Manejo de JSON malformado

## 🚀 Ejecutar Tests

### Opción 1: Test Suite Completo

1. Abrir `termostato_tests.ino` en Arduino IDE
2. Compilar y subir al ESP8266
3. Abrir el Monitor Serial (115200 baud)
4. Los tests se ejecutarán automáticamente

### Opción 2: Tests Específicos

Modificar `termostato_tests.ino` para ejecutar solo ciertos tests:

```cpp
void runAllTests() {
    // Solo tests de dominio
    TemperatureControllerTest::runAllTests();
    
    // Solo tests de aplicación
    // GetTemperatureUseCaseTest::runAllTests();
    // ControlTemperatureUseCaseTest::runAllTests();
    
    // Solo tests de infraestructura
    // JsonParserTest::runAllTests();
}
```

## 📊 Interpretar Resultados

### Output de Tests Exitosos

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

### Output de Tests Fallidos

```
🔍 Running test: Evaluate Temperature - Critical Low ... ❌ FAILED
   Test: Evaluate Temperature - Critical Low
   Error: Assertion failed: expected 0, got 1 - Temperature 4.9°C should be CRITICAL_LOW
```

## 🔧 Agregar Nuevos Tests

### 1. Crear Archivo de Test

```cpp
// tests/domain/services/MiNuevoTest.h
#ifndef MI_NUEVO_TEST_H
#define MI_NUEVO_TEST_H

#include "../../TestFramework.h"
#include "../../../src/domain/services/MiServicio.h"

class MiNuevoTest {
public:
    static void runAllTests();
    
private:
    static void testMiFuncionalidad();
};

void MiNuevoTest::runAllTests() {
    TestFramework::begin("Mi Nuevo Test");
    
    TestFramework::test("Mi Funcionalidad", testMiFuncionalidad);
    
    TestFramework::end();
}

void MiNuevoTest::testMiFuncionalidad() {
    // Lógica del test
    TestFramework::assertTrue(true, "Mi test funciona");
}

#endif
```

### 2. Incluir en Test Suite Principal

```cpp
// termostato_tests.ino
#include "tests/domain/services/MiNuevoTest.h"

void runDomainLayerTests() {
    // ... otros tests
    MiNuevoTest::runAllTests();
}
```

## 🎯 Mejores Prácticas

### 1. Nomenclatura
- Archivos de test: `NombreClaseTest.h`
- Métodos de test: `testNombreFuncionalidad()`
- Descripciones claras y específicas

### 2. Organización
- Un test por funcionalidad
- Tests independientes entre sí
- Setup y teardown cuando sea necesario

### 3. Assertions
- Usar assertions específicas (`assertEquals` vs `assertTrue`)
- Mensajes de error descriptivos
- Verificar tanto casos exitosos como fallidos

### 4. Mocks
- Configurar mocks antes de cada test
- Resetear contadores cuando sea necesario
- Verificar que los mocks fueron llamados correctamente

## 🐛 Debugging

### Tests que Fallan

1. **Revisar mensaje de error**: Proporciona información sobre qué falló
2. **Verificar valores esperados**: Comparar con valores reales
3. **Revisar configuración de mocks**: Asegurar que están configurados correctamente
4. **Verificar dependencias**: Asegurar que todas las dependencias están incluidas

### Tests que No Compilan

1. **Verificar includes**: Asegurar que todos los archivos necesarios están incluidos
2. **Verificar dependencias**: Asegurar que las clases mockadas existen
3. **Verificar sintaxis**: Revisar errores de compilación en Arduino IDE

## 📈 Métricas de Cobertura

Los tests cubren:

- ✅ **Domain Layer**: 100% de servicios
- ✅ **Application Layer**: 100% de casos de uso
- ✅ **Infrastructure Layer**: Utilidades JSON
- 🔄 **Interfaces Layer**: Pendiente de implementar

## 🔄 Próximos Pasos

1. **Tests de Interfaces**: Agregar tests para controladores
2. **Tests de Integración**: Tests que combinen múltiples capas
3. **Tests de Performance**: Medir tiempos de ejecución
4. **Tests de Stress**: Simular condiciones extremas
5. **Cobertura de Código**: Medir porcentaje de código cubierto

---

**Nota**: Los tests están diseñados para ejecutarse en el ESP8266 real, no en un emulador. Esto asegura que el código funciona en el entorno de producción. 