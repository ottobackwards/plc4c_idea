cmake_minimum_required(VERSION 3.16)
project(plc4c_moc C)

set(CMAKE_C_STANDARD 11)

add_executable(simple simple_plc4c.c plc4c.h)
add_executable(with_callbackas with_callbacks_plc4c.c plc4c.h)
