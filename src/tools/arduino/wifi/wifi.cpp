//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <Arduino.h>
#include <SoftwareSerial/SoftwareSerial.h>

#include <libesp8266/ESP8266.hpp>
#include <libdht11/DHT11.hpp>

#include <config.h>

#define DHT11_PIN           5

libesp8266::ESP8266 wifi;
bool wifi_ready = false;

SoftwareSerial dbg_serial(10, 11); // RX, TX

//------------------------------------------------------------------------------
// setup
//------------------------------------------------------------------------------
void setup()
{
    // init dbg serial line
    dbg_serial.begin(9600);
    dbg_serial.println("WIFI ESP8266 tools");

    // init wifi
    wifi.set_dbg_serial(dbg_serial);
    LIB_ESP8266_ERROR err = wifi.connect(ESSID, PASSWORD);
    if (err == LIB_ESP8266_ERROR_NO_ERROR)
        wifi_ready = true;
    else
        dbg_serial.println("FALSE");
}

//------------------------------------------------------------------------------
// loop
//------------------------------------------------------------------------------
void loop()
{
    if (wifi_ready)
    {
        // read data from sensor
        uint8_t temperature = 0.0;
        uint8_t humidity = 0.0;
        libdht11::DHT11 dht11(DHT11_PIN);
        dht11.get_data(temperature, humidity);

        // float to string
        String temperature_str, humidity_str;

        // dbg
        dbg_serial.println("TEMP/HUM");
        dbg_serial.println(temperature);
        dbg_serial.println(humidity);
        dbg_serial.println("DONE");

        // build json
        String msg = "json.htm?type=command&param=udevice&hid=1&did=4000&dunit=4&dtype=82&dsubtype=1&nvalue=0&svalue=";
        msg += temperature_str;
        msg += ";";
        msg += humidity_str;
        wifi.send_http_request(SERVER_IP, (int32_t) SERVER_PORT, msg);

        delay(2000);
    }
}
