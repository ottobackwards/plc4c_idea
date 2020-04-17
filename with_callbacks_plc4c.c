/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#include <stdio.h>
#include "plc4c.h"

void default_on_driver_loaded(plc4c_driver *driver);

void default_driver_load_error(const char *driver_name, error_code error);

void default_on_connection(plc4c_connection *connection);

void default_connection_error(const char *connection_string, error_code error);

void default_on_disconnection(plc4c_connection *connection);

void default_disconnection_error(plc4c_connection *connection, error_code error);

void default_loop_error(plc4c_driver *driver, plc4c_connection *connection, error_code error);

int main() {
  bool loop = true;
  plc4c_system *system = NULL;
  plc4c_connection *connection = NULL;
  plc4c_connection *connection2 = NULL;

  error_code error = plc4c_system_create(&system);
  if (error != OK) {
    return -1;
  }

  /* setup our callbacks */

  plc4c_system_set_on_driver_loaded(system, &default_on_driver_loaded);
  plc4c_system_set_on_driver_load_error(system, &default_driver_load_error);
  plc4c_system_set_on_connection(system, &default_on_connection);
  plc4c_system_set_on_connection_error(system, &default_connection_error);
  plc4c_system_set_on_loop_error(system, &default_connection_error);

  error = plc4c_init(system);
  if (error != OK) {
    return -1;
  }

  // Establish a connection to remote devices
  // you may or may not care about the connection handle
  error = plc4c_system_connect(system, "s7://192.168.42.20", &connection);
  if (error != OK) {
    return -1;
  }
  error = plc4c_system_connect(system, "s7://192.168.42.22", &connection2);
  if (error != OK) {
    return -1;
  }

  // Central program loop ...
  while (loop) {
    if (plc4c_system_loop(system) != OK) {
      break;
    }
  }

  // Make sure everything is cleaned up correctly.
  plc4c_system_shutdown(system);
  plc4c_system_destroy(system);

  return 0;
}

void default_on_driver_loaded(plc4c_driver *driver) {}

void default_driver_load_error(const char *driver_name, error_code error) {}

void default_on_connection(plc4c_connection *connection) {}

void default_connection_error(const char *connection_string, error_code error) {}

void default_on_disconnection(plc4c_connection *connection) {}

void default_disconnection_error(plc4c_connection *connection, error_code error) {}

void default_loop_error(plc4c_driver *driver, plc4c_connection *connection, error_code error) {}
