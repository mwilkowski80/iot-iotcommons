//
// Created by mw on 22.02.2020.
//

#include "iotcommons_utils.h"

#include <sstream>
#include <iomanip>


String bytes_to_hex_str(unsigned char *buf, size_t len) {
  std::stringstream ss;
  ss << std::hex;

  for( int i(0) ; i < len; ++i )
    ss << std::setw(2) << std::setfill('0') << (int)buf[i];

  return String(ss.str().c_str());
}
