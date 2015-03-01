#include <sstream>       
#include <unistd.h>

/*** LIB CURL INCLUDES ***/
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>


int main(int argc, const char* argv[] )
{
  //RAII cleanup
  curlpp::Cleanup myCleanup;

  //construct cmd
  const double init_temp = 10;
  const int init_hum = 50;

  std::string server = "localhost:8080";
  std::string hid = "1";
  std::string did = "4000";
  std::string dunit = "4";
  std::string dtype = "82";
  std::string dsubtype = "1";
  std::string nvalue = "0";

  double temp = init_temp;
  int hum = init_hum;

  while (true)
  {
    //get temperature  
    std::ostringstream temp_stream;
    temp_stream << temp;
    std::string temp_str = temp_stream.str();
    // get humidity
    std::ostringstream hum_stream;
    hum_stream << hum;
    std::string hum_str = hum_stream.str();
    //TODO : compute humidity confort : 
    // 0=Normal
    // 1=Comfortable
    // 2=Dry
    // 3=Wet
    std::string hum_stat = "1";

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

    hum++;
    temp += 0.3;

    if (temp > 30)
      temp = init_temp;
    if (hum > 90)
      hum = init_hum;

    sleep(5);
  }


  
  return 0;
}
