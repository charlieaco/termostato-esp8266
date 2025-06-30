#ifndef MOCK_TIME_REPOSITORY_H
#define MOCK_TIME_REPOSITORY_H

#include "../../src/domain/repositories/ITimeRepository.h"
#include <Arduino.h>

/**
 * @brief Mock del repositorio de tiempo para testing
 * 
 * Implementa ITimeRepository para permitir testing
 * sin dependencias externas reales.
 */
class MockTimeRepository : public ITimeRepository {
private:
    bool shouldSucceed;
    String mockTime;
    int callCount;
    
public:
    MockTimeRepository() 
        : shouldSucceed(true), mockTime("2024-01-15T10:30:00Z"), callCount(0) {}
    
    /**
     * @brief Configura si el mock debe simular éxito o fallo
     * @param succeed true para simular éxito, false para simular fallo
     */
    void setShouldSucceed(bool succeed) { shouldSucceed = succeed; }
    
    /**
     * @brief Configura el tiempo mock que se devolverá
     * @param time Tiempo mock
     */
    void setMockTime(const String& time) { mockTime = time; }
    
    /**
     * @brief Obtiene el número de veces que se llamó getCurrentTime
     */
    int getCallCount() const { return callCount; }
    
    /**
     * @brief Resetea el contador de llamadas
     */
    void resetCallCount() { callCount = 0; }
    
    // Implementación de ITimeRepository
    bool getCurrentTime(String& currentTime) override {
        callCount++;
        
        if (!shouldSucceed) {
            return false;
        }
        
        currentTime = mockTime;
        return true;
    }
};

#endif // MOCK_TIME_REPOSITORY_H 