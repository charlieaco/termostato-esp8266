#ifndef MOCK_HARDWARE_REPOSITORY_H
#define MOCK_HARDWARE_REPOSITORY_H

#include "../../src/domain/repositories/IHardwareRepository.h"
#include <Arduino.h>

/**
 * @brief Mock del repositorio de hardware para testing
 * 
 * Implementa IHardwareRepository para permitir testing
 * sin dependencias de hardware reales.
 */
class MockHardwareRepository : public IHardwareRepository {
private:
    bool heatingActive;
    bool coolingActive;
    bool emergencyActive;
    bool ledsStatus;
    int heatingCallCount;
    int coolingCallCount;
    int emergencyCallCount;
    int ledCallCount;
    
public:
    MockHardwareRepository() 
        : heatingActive(false), coolingActive(false), emergencyActive(false), 
          ledsStatus(false), heatingCallCount(0), coolingCallCount(0), 
          emergencyCallCount(0), ledCallCount(0) {}
    
    // Getters para verificar estado
    bool isHeatingActive() const { return heatingActive; }
    bool isCoolingActive() const { return coolingActive; }
    bool isEmergencyActive() const { return emergencyActive; }
    bool getLedsStatus() const { return ledsStatus; }
    
    // Getters para contadores
    int getHeatingCallCount() const { return heatingCallCount; }
    int getCoolingCallCount() const { return coolingCallCount; }
    int getEmergencyCallCount() const { return emergencyCallCount; }
    int getLedCallCount() const { return ledCallCount; }
    
    // Reset de contadores
    void resetCallCounts() {
        heatingCallCount = 0;
        coolingCallCount = 0;
        emergencyCallCount = 0;
        ledCallCount = 0;
    }
    
    // Implementación de IHardwareRepository
    void initialize() override {
        // No hace nada en el mock
    }
    
    void updateLeds(bool status) override {
        ledsStatus = status;
        ledCallCount++;
    }
    
    void delayWithLedUpdate(unsigned long milliseconds) override {
        // Simula delay sin realmente esperar
        ledCallCount++;
    }
    
    void activateHeating() override {
        heatingActive = true;
        heatingCallCount++;
    }
    
    void deactivateHeating() override {
        heatingActive = false;
        heatingCallCount++;
    }
    
    void activateCooling() override {
        coolingActive = true;
        coolingCallCount++;
    }
    
    void deactivateCooling() override {
        coolingActive = false;
        coolingCallCount++;
    }
    
    void activateEmergency() override {
        emergencyActive = true;
        emergencyCallCount++;
    }
    
    void deactivateEmergency() override {
        emergencyActive = false;
        emergencyCallCount++;
    }
};

#endif // MOCK_HARDWARE_REPOSITORY_H 