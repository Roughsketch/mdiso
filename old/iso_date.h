#ifndef _ISO_DATETIME_H
#define _ISO_DATETIME_H

#include "iso.h"

struct DateTime
{
  DateTime();
  DateTime(std::vector<uint8_t>& bytes, uint32_t offset = 0);
  DateTime(std::string& date);
  std::string to_string();

  uint32_t year;
  uint32_t month;
  uint32_t day;
  uint32_t hour;
  uint32_t minute;
  uint32_t second;
  uint32_t gmt;
};

#endif
