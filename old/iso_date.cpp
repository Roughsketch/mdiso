#include "iso_date.h"

DateTime::DateTime() { }

DateTime::DateTime(std::vector<uint8_t>& data, uint32_t offset)
{
  //  DateTime format
  year = data[offset + 0] + 1900;
  month = data[offset + 1];
  day = data[offset + 2];
  hour = data[offset + 3];
  minute = data[offset + 4];
  second = data[offset + 5];
  gmt = data[offset + 6];
}

DateTime::DateTime(std::string& date)
{
  //  YYYYMMDDHHMMSSGG
  year = std::stoi(date.substr(0, 4));
  month = std::stoi(date.substr(4, 2));
  day = std::stoi(date.substr(6, 2));
  hour = std::stoi(date.substr(8, 2));
  minute = std::stoi(date.substr(10, 2));
  second = std::stoi(date.substr(12, 2));
  gmt = std::stoi(date.substr(14, 2));
}

std::string DateTime::to_string()
{
  std::string date;
  date = std::to_string(year);
  date += std::to_string(month);
  date += std::to_string(day);
  date += std::to_string(hour);
  date += std::to_string(minute);
  date += std::to_string(second);
  date += std::to_string(gmt);
  date += "$";
  return date;
}
