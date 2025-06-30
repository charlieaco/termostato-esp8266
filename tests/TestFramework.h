#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <Arduino.h>

/**
 * @brief Framework de testing simple para Arduino
 * 
 * Proporciona funcionalidades básicas para ejecutar tests unitarios
 * en el entorno de Arduino/ESP8266.
 */
class TestFramework {
private:
    static int totalTests;
    static int passedTests;
    static int failedTests;
    static String currentTestName;
    
public:
    /**
     * @brief Inicializa el framework de testing
     */
    static void begin(const String& testSuiteName);
    
    /**
     * @brief Finaliza el framework y muestra resultados
     */
    static void end();
    
    /**
     * @brief Ejecuta un test individual
     * @param testName Nombre del test
     * @param testFunction Función que contiene la lógica del test
     */
    static void test(const String& testName, void (*testFunction)());
    
    /**
     * @brief Verifica que una condición sea verdadera
     * @param condition Condición a verificar
     * @param message Mensaje de error si la condición es falsa
     */
    static void assertTrue(bool condition, const String& message = "");
    
    /**
     * @brief Verifica que una condición sea falsa
     * @param condition Condición a verificar
     * @param message Mensaje de error si la condición es verdadera
     */
    static void assertFalse(bool condition, const String& message = "");
    
    /**
     * @brief Verifica que dos valores sean iguales
     * @param expected Valor esperado
     * @param actual Valor actual
     * @param message Mensaje de error si no son iguales
     */
    template<typename T>
    static void assertEquals(T expected, T actual, const String& message = "");
    
    /**
     * @brief Verifica que dos strings sean iguales
     * @param expected String esperado
     * @param actual String actual
     * @param message Mensaje de error si no son iguales
     */
    static void assertEquals(const String& expected, const String& actual, const String& message = "");
    
    /**
     * @brief Verifica que dos valores double sean iguales con tolerancia
     * @param expected Valor esperado
     * @param actual Valor actual
     * @param tolerance Tolerancia para la comparación
     * @param message Mensaje de error si no son iguales
     */
    static void assertEquals(double expected, double actual, double tolerance, const String& message = "");
    
    /**
     * @brief Verifica que un valor no sea null
     * @param value Valor a verificar
     * @param message Mensaje de error si es null
     */
    template<typename T>
    static void assertNotNull(T* value, const String& message = "");
    
    /**
     * @brief Falla el test con un mensaje específico
     * @param message Mensaje de error
     */
    static void fail(const String& message);
    
    /**
     * @brief Obtiene el número total de tests ejecutados
     */
    static int getTotalTests() { return totalTests; }
    
    /**
     * @brief Obtiene el número de tests que pasaron
     */
    static int getPassedTests() { return passedTests; }
    
    /**
     * @brief Obtiene el número de tests que fallaron
     */
    static int getFailedTests() { return failedTests; }
};

// Inicialización de variables estáticas
int TestFramework::totalTests = 0;
int TestFramework::passedTests = 0;
int TestFramework::failedTests = 0;
String TestFramework::currentTestName = "";

void TestFramework::begin(const String& testSuiteName) {
    Serial.println("\n" + String(50, '='));
    Serial.println("🧪 TEST SUITE: " + testSuiteName);
    Serial.println(String(50, '='));
    totalTests = 0;
    passedTests = 0;
    failedTests = 0;
}

void TestFramework::end() {
    Serial.println(String(50, '='));
    Serial.println("📊 TEST RESULTS:");
    Serial.println("Total Tests: " + String(totalTests));
    Serial.println("✅ Passed: " + String(passedTests));
    Serial.println("❌ Failed: " + String(failedTests));
    
    if (failedTests == 0) {
        Serial.println("🎉 ALL TESTS PASSED!");
    } else {
        Serial.println("⚠️  SOME TESTS FAILED!");
    }
    Serial.println(String(50, '='));
}

void TestFramework::test(const String& testName, void (*testFunction)()) {
    currentTestName = testName;
    totalTests++;
    
    Serial.print("🔍 Running test: " + testName + " ... ");
    
    try {
        testFunction();
        Serial.println("✅ PASSED");
        passedTests++;
    } catch (const std::exception& e) {
        Serial.println("❌ FAILED");
        Serial.println("   Error: " + String(e.what()));
        failedTests++;
    }
}

void TestFramework::assertTrue(bool condition, const String& message) {
    if (!condition) {
        String errorMsg = "Assertion failed: expected true, got false";
        if (message.length() > 0) {
            errorMsg += " - " + message;
        }
        fail(errorMsg);
    }
}

void TestFramework::assertFalse(bool condition, const String& message) {
    if (condition) {
        String errorMsg = "Assertion failed: expected false, got true";
        if (message.length() > 0) {
            errorMsg += " - " + message;
        }
        fail(errorMsg);
    }
}

template<typename T>
void TestFramework::assertEquals(T expected, T actual, const String& message) {
    if (expected != actual) {
        String errorMsg = "Assertion failed: expected " + String(expected) + ", got " + String(actual);
        if (message.length() > 0) {
            errorMsg += " - " + message;
        }
        fail(errorMsg);
    }
}

void TestFramework::assertEquals(const String& expected, const String& actual, const String& message) {
    if (expected != actual) {
        String errorMsg = "Assertion failed: expected '" + expected + "', got '" + actual + "'";
        if (message.length() > 0) {
            errorMsg += " - " + message;
        }
        fail(errorMsg);
    }
}

void TestFramework::assertEquals(double expected, double actual, double tolerance, const String& message) {
    if (abs(expected - actual) > tolerance) {
        String errorMsg = "Assertion failed: expected " + String(expected, 6) + 
                         ", got " + String(actual, 6) + 
                         " (tolerance: " + String(tolerance, 6) + ")";
        if (message.length() > 0) {
            errorMsg += " - " + message;
        }
        fail(errorMsg);
    }
}

template<typename T>
void TestFramework::assertNotNull(T* value, const String& message) {
    if (value == nullptr) {
        String errorMsg = "Assertion failed: expected non-null value";
        if (message.length() > 0) {
            errorMsg += " - " + message;
        }
        fail(errorMsg);
    }
}

void TestFramework::fail(const String& message) {
    Serial.println("❌ FAILED");
    Serial.println("   Test: " + currentTestName);
    Serial.println("   Error: " + message);
    throw std::runtime_error(message.c_str());
}

#endif // TEST_FRAMEWORK_H 