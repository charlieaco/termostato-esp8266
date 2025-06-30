#ifndef JSON_PARSER_TEST_H
#define JSON_PARSER_TEST_H

#include "../../TestFramework.h"
#include "../../../src/infrastructure/json/JsonParser.h"

/**
 * @brief Tests para el parser JSON
 * 
 * Prueba la funcionalidad de parsing y extracción de datos JSON.
 */
class JsonParserTest {
public:
    static void runAllTests();
    
private:
    static void testExtractValueSuccess();
    static void testExtractValueFailure();
    static void testExtractTemperatureValueSuccess();
    static void testExtractTemperatureValueFailure();
    static void testIsValidJson();
    static void testPrintJsonStructure();
};

void JsonParserTest::runAllTests() {
    TestFramework::begin("JsonParser Tests");
    
    TestFramework::test("Extract Value - Success", testExtractValueSuccess);
    TestFramework::test("Extract Value - Failure", testExtractValueFailure);
    TestFramework::test("Extract Temperature Value - Success", testExtractTemperatureValueSuccess);
    TestFramework::test("Extract Temperature Value - Failure", testExtractTemperatureValueFailure);
    TestFramework::test("Is Valid JSON", testIsValidJson);
    TestFramework::test("Print JSON Structure", testPrintJsonStructure);
    
    TestFramework::end();
}

void JsonParserTest::testExtractValueSuccess() {
    // JSON válido con datos de prueba
    String jsonString = "{\"name\":\"test\",\"value\":42,\"active\":true}";
    String result;
    
    // Test extracción de string
    bool success1 = JsonParser::extractValue(jsonString, "name", result);
    TestFramework::assertTrue(success1, "Should extract string value successfully");
    TestFramework::assertEquals("test", result, "Extracted name should match");
    
    // Test extracción de número
    bool success2 = JsonParser::extractValue(jsonString, "value", result);
    TestFramework::assertTrue(success2, "Should extract numeric value successfully");
    TestFramework::assertEquals("42", result, "Extracted value should match");
    
    // Test extracción de boolean
    bool success3 = JsonParser::extractValue(jsonString, "active", result);
    TestFramework::assertTrue(success3, "Should extract boolean value successfully");
    TestFramework::assertEquals("true", result, "Extracted active should match");
}

void JsonParserTest::testExtractValueFailure() {
    // JSON válido pero sin la clave buscada
    String jsonString = "{\"name\":\"test\",\"value\":42}";
    String result;
    
    // Test extracción de clave inexistente
    bool success = JsonParser::extractValue(jsonString, "nonexistent", result);
    TestFramework::assertFalse(success, "Should fail when key doesn't exist");
    
    // Test JSON inválido
    String invalidJson = "{\"name\":\"test\",\"value\":42"; // JSON incompleto
    bool success2 = JsonParser::extractValue(invalidJson, "name", result);
    TestFramework::assertFalse(success2, "Should fail with invalid JSON");
}

void JsonParserTest::testExtractTemperatureValueSuccess() {
    // JSON válido con estructura de temperatura de Meteomatics
    String jsonData = R"({
        "data": [
            {
                "coordinates": [
                    {
                        "dates": [
                            {
                                "value": 22.5
                            }
                        ]
                    }
                ]
            }
        ]
    })";
    
    double temperature;
    bool success = JsonParser::extractTemperatureValue(jsonData, temperature);
    
    TestFramework::assertTrue(success, "Should extract temperature successfully");
    TestFramework::assertEquals(22.5, temperature, 0.1, "Extracted temperature should match");
}

void JsonParserTest::testExtractTemperatureValueFailure() {
    // JSON con estructura incorrecta
    String invalidJson = "{\"data\":[]}"; // Sin datos
    double temperature;
    
    bool success = JsonParser::extractTemperatureValue(invalidJson, temperature);
    TestFramework::assertFalse(success, "Should fail with empty data array");
    
    // JSON completamente inválido
    String malformedJson = "{\"data\":[{\"coordinates\":[{\"dates\":[{\"value\":";
    bool success2 = JsonParser::extractTemperatureValue(malformedJson, temperature);
    TestFramework::assertFalse(success2, "Should fail with malformed JSON");
}

void JsonParserTest::testIsValidJson() {
    // Test JSON válido
    JSONVar validJson = JSON.parse("{\"test\":\"value\"}");
    bool isValid = JsonParser::isValidJson(validJson);
    TestFramework::assertTrue(isValid, "Valid JSON should be recognized");
    
    // Test JSON inválido
    JSONVar invalidJson = JSON.parse("invalid json");
    bool isInvalid = JsonParser::isValidJson(invalidJson);
    TestFramework::assertFalse(isInvalid, "Invalid JSON should be recognized");
}

void JsonParserTest::testPrintJsonStructure() {
    // Test que la función no falle con JSON válido
    String jsonString = "{\"name\":\"test\",\"value\":42}";
    
    // Esta función solo imprime, no retorna valor
    // Solo verificamos que no cause errores
    try {
        JsonParser::printJsonStructure(jsonString);
        TestFramework::assertTrue(true, "Print JSON structure should not throw exception");
    } catch (const std::exception& e) {
        TestFramework::fail("Print JSON structure should not throw exception: " + String(e.what()));
    }
}

#endif // JSON_PARSER_TEST_H 