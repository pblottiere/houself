//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
// global include
#include <Arduino.h>
#include <SoftwareSerial/SoftwareSerial.h>

// dominus include
#include <libdht11/DHT11.hpp>
#include <libesp8266/ESP8266.hpp>
#include <config.h>

//------------------------------------------------------------------------------
// global var
//------------------------------------------------------------------------------
SoftwareSerial dbg_serial(10, 11); // RX, TX

int32_t pin_rst(12);
int32_t pin_led(13);
int32_t pin_dht11(5);

libesp8266::ESP8266 wifi;
bool wifi_ready(false);

unsigned long period_msec(60000L);

//==============================================================================
//
// Custom functions
//
//==============================================================================
//------------------------------------------------------------------------------
// build_json_msg
//------------------------------------------------------------------------------
String build_json_msg(uint8_t value1)
{
    // String msg = "GET /json.htm?type=command&param=udevice&hid=1&did=4000&dunit=4&dtype=82&dsubtype=1&nvalue=0&svalue=";
    String msg = "GET /json.htm?type=command&param=udevice&idx=7&nvalue=0&svalue=";
    msg += value1;
    msg += ";1 HTTP/1.0\r\n\r\n";

    return msg;
}

//------------------------------------------------------------------------------
// update_temperature
//------------------------------------------------------------------------------
void update_temperature()
{
    // read data from sensor
    uint8_t temperature = 0x00;
    uint8_t humidity = 0x00;
    libdht11::DHT11 dht11(pin_dht11);
    LIB_DHT11_ERROR err = dht11.get_data(temperature, humidity);

    if (err == LIB_DHT11_ERROR_NO_ERROR)
    {
        String msg = build_json_msg(temperature);
        dbg_serial.println("Send TCP message: ");
        dbg_serial.println(msg);
        wifi.send_tcp_msg(SERVER_IP, (int32_t) SERVER_PORT, msg);
    }
}

//==============================================================================
//
// Arduino builtin functions
//
//==============================================================================
//------------------------------------------------------------------------------
// setup
//------------------------------------------------------------------------------
void setup()
{
    // init led status
    pinMode(pin_led, OUTPUT);

    // init dbg serial
    dbg_serial.begin(9600);
    dbg_serial.println("WIFI ESP8266 init...");

    // init wifi
    wifi.set_dbg_serial(dbg_serial);
    LIB_ESP8266_ERROR err = wifi.connect(ESSID, PASSWORD);

    if (err == LIB_ESP8266_ERROR_NO_ERROR)
    {
        wifi_ready = true;
        digitalWrite(pin_led, HIGH);
    }
    else
    {
        // reboot
        pinMode(pin_rst, OUTPUT);
        digitalWrite(pin_rst, HIGH);
        dbg_serial.println("Wifi connection failed. Reboot...");
    }
}

//------------------------------------------------------------------------------
// loop
//------------------------------------------------------------------------------
void loop()
{
    if (wifi_ready)
    {
        update_temperature();
        delay(period_msec);
    }
}
