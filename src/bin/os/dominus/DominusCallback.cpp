//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <stdio.h>
#include <iostream>
#include <libtchat/TchatMsg.hpp>
#include <libtchat/TchatMsgTempHum.hpp>
#include <sstream>  

#include "DominusCallback.hpp"  

//==============================================================================
//
// Cst / Dst
//
//==============================================================================
//------------------------------------------------------------------------------
// cst
//------------------------------------------------------------------------------
DominusCallback::DominusCallback(SerialPort *dominus_port, 
				 const std::string & domoticz_address) :
    _dominus_port(dominus_port),
    ReactorCallback(dominus_port->get_fd())
{
}

//==============================================================================
//
// Public methods
//
//==============================================================================
//------------------------------------------------------------------------------
// cb
//------------------------------------------------------------------------------
void DominusCallback::cb()
{
  uint8_t buffer[256];
  uint32_t bytes =_dominus_port->read_data(buffer);

  bool rc(false);
  TchatMsg msg;

  for(size_t j=0; j<bytes; j++)
  {
    bool rc = _tchat_buffer.add_byte(buffer[j]);
    if(rc)
    {
      msg.set_buffer(_tchat_buffer);

      if(msg.get_type() == TCHAT_TYPE_ACK)
      {
	switch(msg.get_target())
	{
               
	case TCHAT_TARGET_TEMP_HUM:
	  {
	    recv_ack_temp_hum(&msg);
	    break;
	  }
	default:
	  perror("Target unknown");
	}
      }
    }
  }
}

//==============================================================================
//
// Private methods
//
//==============================================================================
//------------------------------------------------------------------------------
// get_date
//------------------------------------------------------------------------------
std::string DominusCallback::get_date()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "\033[1;37m[%X]\033[0m", &tstruct);

    return buf;
}


//------------------------------------------------------------------------------
// recv_ack_temp_hum
//------------------------------------------------------------------------------
void DominusCallback::recv_ack_temp_hum(TchatMsg *msg)
{
    TchatMsgTempHum *tmp = (TchatMsgTempHum*) msg;
    std::cout << get_date() << " TEMPERATURE: " << (int) tmp->get_temperature() 
              << "°" << std::endl;
    std::cout << get_date() << " HUMIDITY: " << (int) tmp->get_humidity() 
              << "°" << std::endl;

    //TODO : set server configurable
    //TO TEST ------------------------------------------------------------------
    std::string server = "localhost:8080";
    std::string hid = "1";
    std::string did = "4000";
    std::string dunit = "4";
    std::string dtype = "82";
    std::string dsubtype = "1";
    std::string nvalue = "0";
    //TODO : compute humidity confort : 
    // 0=Normal
    // 1=Comfortable
    // 2=Dry
    // 3=Wet
    std::string hum_stat = "1";

    //get temperature  
    std::ostringstream temp_stream;
    temp_stream << (int) tmp->get_temperature();
    std::string temp_str = temp_stream.str();
    // get humidity
    std::ostringstream hum_stream;
    hum_stream << (int) tmp->get_humidity();
    std::string hum_str = hum_stream.str();

    //value
    std::string svalue = temp_str + ";" + hum_str + ";" + hum_stat;

    std::string cmd =  "http://" + server + "/json.htm?"
      "type=command"
      "&param=udevice"
      "&hid=" + hid + 
      "&did=" + did + 
      "&dunit=" + dunit + 
      "&dtype=" + dtype + 
      "&dsubtype=" + dsubtype + 
      "&nvalue=" + nvalue + 
      "&svalue=" + svalue;
				
    std::ostringstream os;
    os << curlpp::options::Url(cmd);

    std::string response = os.str();
    std::cout << response << std::endl;
    //--------------------------------------------------------------------------



}
