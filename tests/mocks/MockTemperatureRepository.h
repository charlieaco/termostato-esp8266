#ifndef MOCK_TEMPERATURE_REPOSITORY_H
#define MOCK_TEMPERATURE_REPOSITORY_H

#include "../../src/domain/repositories/ITemperatureRepository.h"
#include <Arduino.h>

/**
 * @brief Mock del repositorio de temperatura para testing
 * 
 * Implementa ITemperatureRepository para permitir testing
 * sin dependencias externas reales.
 */
class MockTemperatureRepository : public ITemperatureRepository {
private:
    bool shouldSucceed;
    String mockToken;
    double mockTemperature;
    int callCount;
    
public:
    MockTemperatureRepository() 
        : shouldSucceed(true), mockToken("mock_token_123"), mockTemperature(20.5), callCount(0) {}
    
    /**
     * @brief Configura si el mock debe simular éxito o fallo
     * @param succeed true para simular éxito, false para simular fallo
     */
    void setShouldSucceed(bool succeed) { shouldSucceed = succeed; }
    
    /**
     * @brief Configura el token mock que se devolverá
     * @param token Token mock
     */
    void setMockToken(const String& token) { mockToken = token; }
    
    /**
     * @brief Configura la temperatura mock que se devolverá
     * @param temperature Temperatura mock
     */
    void setMockTemperature(double temperature) { mockTemperature = temperature; }
    
    /**
     * @brief Obtiene el número de veces que se llamó getCurrentTemperature
     */
    int getCallCount() const { return callCount; }
    
    /**
     * @brief Resetea el contador de llamadas
     */
    void resetCallCount() { callCount = 0; }
    
    // Implementación de ITemperatureRepository
    bool getCurrentTemperature(const String& timestamp, const String& authToken, double& temperature) override {
        callCount++;
        
        if (!shouldSucceed) {
            return false;
        }
        
        temperature = mockTemperature;
        return true;
    }
    
    bool getAuthToken(String& token) override {
        if (!shouldSucceed) {
            return false;
        }
        
        token = mockToken;
        return true;
    }
};

#endif // MOCK_TEMPERATURE_REPOSITORY_H 