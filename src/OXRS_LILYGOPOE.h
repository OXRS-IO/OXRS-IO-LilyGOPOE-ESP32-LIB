/*
 * OXRS_LILYGOPOE.h
 */

#ifndef OXRS_LILYGOPOE_H
#define OXRS_LILYGOPOE_H

#include <OXRS_MQTT.h>                // For MQTT pub/sub
#include <OXRS_API.h>                 // For REST API

// I2C
#define       I2C_SDA                 33
#define       I2C_SCL                 32

// REST API
#define       REST_API_PORT           80

// Ethernet
#define ETH_CLOCK_MODE                ETH_CLOCK_GPIO17_OUT   // Version with not PSRAM
#define ETH_PHY_TYPE                  ETH_PHY_LAN8720        // Type of the Ethernet PHY (LAN8720 or TLK110)  
#define ETH_PHY_POWER                 -1                     // Pin# of the enable signal for the external crystal oscillator (-1 to disable for internal APLL source)
#define ETH_PHY_MDC                   23                     // Pin# of the I²C clock signal for the Ethernet PHY
#define ETH_PHY_MDIO                  18                     // Pin# of the I²C IO signal for the Ethernet PHY
#define ETH_PHY_ADDR                  0                      // I²C-address of Ethernet PHY (0 or 1 for LAN8720, 31 for TLK110)
#define ETH_RST_PIN                   5

class OXRS_LILYGOPOE : public Print
{
  public:
    void begin(jsonCallback config, jsonCallback command);
    void loop(void);

    // Firmware can define the config/commands it supports - for device discovery and adoption
    void setConfigSchema(JsonVariant json);
    void setCommandSchema(JsonVariant json);

    // Return a pointer to the MQTT library
    OXRS_MQTT * getMQTT(void);

    // Return a pointer to the API library
    OXRS_API * getAPI(void);

    // Helpers for publishing to stat/ and tele/ topics
    boolean publishStatus(JsonVariant json);
    boolean publishTelemetry(JsonVariant json);

    // Implement Print.h wrapper
    virtual size_t write(uint8_t);
    using Print::write;

  private:
    void _initialiseNetwork(void);
    
    boolean _isNetworkConnected(void);
};

#endif
