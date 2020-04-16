#include <stdio.h>
#include "plc4c.h"

int main() {
  bool loop = true;
  plc4c_system_handle system_handle = 0;
  plc4c_connection_handle connection_handle = 0;

  error_code error = plc4c_system_create(&system_handle);
  if (error != OK) {
    return -1;
  }

  error = plc4c_init(system_handle);
  if (error != OK) {
    return -1;
  }

  // Establish a connection to a remote device
  // you may or may not care about the connection handle
  error = plc4c_system_connect(system_handle,"s7://192.168.42.20", &connection_handle);
  if (error != OK) {
    return -1;
  }

  // Central program loop ...
  while(loop) {
    if (plc4c_system_loop(system_handle) != OK ) {
      break;
    }
  }

  // Make sure everything is cleaned up correctly.
  plc4c_system_shutdown(system_handle);

  return 0;
}
