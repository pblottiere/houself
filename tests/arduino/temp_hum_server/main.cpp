#include "server.hpp"

int main()
{
  setup_server();

  while(1)
    loop_server();
}
