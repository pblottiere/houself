//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <Arduino.h>
#include <SoftwareSerial/SoftwareSerial.h>

#include <libesp8266/LibESP8266.hpp>
#include <libdht11/LibDHT11.hpp>

#define ESSID               "PF"
#define PASS                "AZENORPF"
#define DOMINUS_SERVER      "192.168.1.33"
#define DOMINUS_PORT        8080
#define DHT11_PIN           5

LibESP8266 wifi;
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
    // wifi_ready = true;
    wifi.set_dbg_serial(dbg_serial);
    LIB_ESP8266_ERROR err = wifi.connect(ESSID, PASS);
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
        uint8_t temperature = 0x00;
        uint8_t humidity = 0x00;
        LibDHT11 dht11(DHT11_PIN);
        dht11.get_data(temperature, humidity);

        dbg_serial.println("TEMP/HUM");
        dbg_serial.println(temperature);
        dbg_serial.println(humidity);
        dbg_serial.println("DONE");

        String msg = "GET /json.htm?type=command&param=udevice&hid=1&did=4000&dunit=4&dtype=82&dsubtype=1&nvalue=0&svalue=";
        msg += temperature;
        msg += ";";
        msg += humidity;
        msg += ";1 HTTP/1.0\r\n\r\n";
        wifi.send_tcp_msg(DOMINUS_SERVER, (int32_t) DOMINUS_PORT, msg);

        delay(2000);
    }
}
