#ifndef _ISO_DIRECTORY_H
#define _ISO_DIRECTORY_H

#include "iso.h"

#include "iso_date.h"
#include "iso_file.h"

namespace DirectoryOffset
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

struct Directory
{
  Directory();
  Directory(std::vector<uint8_t>& data, uint32_t offset = 0);

  void contents();

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
