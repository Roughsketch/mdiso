#ifndef _ISO_ENTRY_H
#define _ISO_ENTRY_H

#include "iso.h"

#include "iso_date.h"

namespace EntryOffset
{
  enum
  {
    Size = 0,
    Extended = 1,
    ExtentLocation = 2,
    DataLength = 10,
    Date = 18,
    FileFlags = 25,
    FileUnitSize = 26,
    InterleaveGap = 27,
    VolumeSequenceNumber = 28,
    FileIdentifierLength = 32,
    FileIdentifier = 33
  };
}

namespace Attribute
{
  enum
  {
    Hidden = 1,       //  Hidden from the user
    Directory = 2,    //  Directory
    Associated = 4,   //  Normal file
    Extended = 8,     //  Extended information
    Permission = 16,  //  
    Incomplete = 32   //  Incomplete listing
  };
};

struct ISOEntry
{
  ISOEntry();
  ISOEntry(std::vector<uint8_t>& data, uint32_t offset = 0);

  void contents(std::ifstream& file, uint32_t blocksize = 0x800);

  uint8_t size;
  uint8_t extended_size;
  uint32_t location;
  uint32_t data_length;
  std::unique_ptr<DateTime> date;
  uint8_t flags;
  uint8_t file_unit_size;
  uint8_t interleave_gap;
  uint16_t volume_sequence_number;
  uint8_t file_id_length;
  std::string identifier;

  //  Extras
  std::string extension;
};

#endif
