#include "server.hpp"

//-----------------------------------------------------------------------------
// global var
//-----------------------------------------------------------------------------
int32_t pin_rx_log(10);
int32_t pin_tx_log(11);
dominus::core::DmnLogger logger(pin_rx_log, pin_tx_log);

int32_t pin_rst(12);
int32_t pin_led(13);
int32_t pin_dht11(5);

libesp8266::ESP8266 wifi;
bool wifi_ready(false);

unsigned long period_msec(60000L);

//=============================================================================
//
// Custom functions
//
//=============================================================================
//-----------------------------------------------------------------------------
// arduino_reset
//-----------------------------------------------------------------------------
void arduino_reset()
{
  pinMode(pin_rst, OUTPUT);
  digitalWrite(pin_rst, HIGH);
}

//-----------------------------------------------------------------------------
// build_json_msg
//-----------------------------------------------------------------------------
String float_to_str(const float f)
{
  char val[10];
  dtostrf(f, 4, 2, val);

  return val;
}

//-----------------------------------------------------------------------------
// build_json_msg
//-----------------------------------------------------------------------------
String build_json_msg(String value1)
{
  String msg = "json.htm?type=command&param=udevice&idx=7&nvalue=0&svalue=";
  msg += value1;

  return msg;
}

//-----------------------------------------------------------------------------
// update_temperature
//-----------------------------------------------------------------------------
void update_temperature()
{
  // read data from sensor
  uint8_t temperature = 0.0;
  uint8_t humidity = 0.0;
  libdht11::DHT11 dht11(pin_dht11);
  LIB_DHT11_ERROR err = dht11.get_data(temperature, humidity);

  String temperature_str = float_to_str(temperature);
  String humidity_str = float_to_str(humidity);

  logger.log("[DHT11] Temperature : " + temperature_str
          + " / humidity : " + humidity_str);

  if (err == LIB_DHT11_ERROR_NO_ERROR)
  {
    String msg = build_json_msg(temperature_str);
    wifi.send_http_request(SERVER_IP, (int32_t) SERVER_PORT, msg);
  }
}

//=============================================================================
//
// Arduino builtin functions
//
//=============================================================================
//-----------------------------------------------------------------------------
// setup_server
//-----------------------------------------------------------------------------
void setup_server()
{
  // init led status
  pinMode(pin_led, OUTPUT);

  // init dbg serial
  logger.log("");
  logger.log("");
  logger.log("[SERVER] Init ESP8266 wifi...");

  // init wifi
  //wifi.set_dbg_serial(dbg_serial);
  LIB_ESP8266_ERROR err = wifi.connect(ESSID, PASSWORD);

  if (err == LIB_ESP8266_ERROR_NO_ERROR)
  {
    logger.log("[SERVER] Wifi connection ready");
    wifi_ready = true;
    digitalWrite(pin_led, HIGH);
  }
  else
  {
    // reboot wifi and arduino
    logger.log("[SERVER] Wifi connection failed. Reboot...");
    wifi.reset();
    arduino_reset();
  }
}

//-----------------------------------------------------------------------------
// loop_server
//-----------------------------------------------------------------------------
void loop_server()
{
  if (wifi_ready)
  {
    update_temperature();
    delay(period_msec);
  }
}
