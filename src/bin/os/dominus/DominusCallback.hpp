#ifndef DOMINUS_CALLBACK_HPP
#define DOMINUS_CALLBACK_HPP

#include <libtchat/TchatBuffer.hpp>
#include <libtchat/TchatMsg.hpp>
#include <libserial/SerialPort.hpp>
#include <libreactor/ReactorCallback.hpp>

class DominusCallback : public ReactorCallback
{
public:
  DominusCallback(SerialPort * arduino_port,
		  const std::string & domoticz_ip);

  void cb();

private:
  std::string get_date(); 

  void recv_ack_led(TchatMsg *msg);
  void recv_ack_servo(TchatMsg *msg);
  void recv_ack_temp_hum(TchatMsg *msg);

  TchatBuffer _tchat_buffer;
  SerialPort *_dominus_port;
  const std::string _domoticz_ip;
};

#endif
