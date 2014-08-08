#ifndef _ISO_H
#define _ISO_H

/*
  This class is designed to read data from a standard
  ISO9660 disk.
*/

#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <memory>
#include <vector>

#include "patch.h"

#include "iso_except.h"

//  Need to forward declare all the structures due to circular references
struct DateTime;
struct PrimaryVolume;
struct BootVolume;
struct ISOEntry;

#include "iso_date.h"
#include "iso_entry.h"
#include "iso_volume.h"

#include "helpers.h"

struct PathTable
{
  uint8_t identifier_length;
  uint8_t extended_length;
  uint32_t extent_location;
  uint16_t parent_index;
  std::string identifier;
};



class ISO {
public:
  static const uint64_t Start = 0x8000;
  static const uint64_t HeaderSize = 0x372;
  
  ISO();
  ISO(std::string filename);
  ~ISO();

  void directories();
  void files();
  void contents();
private:
  std::unique_ptr<PrimaryVolume> primary;
  std::unique_ptr<ISOEntry> iso_files;
  std::string iso_file;
};

#endif
