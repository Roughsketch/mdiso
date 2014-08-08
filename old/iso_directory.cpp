#include "iso_directory.h"

Directory::Directory()
{

}

Directory::Directory(std::vector<uint8_t>& data, uint32_t offset)
{
  size = Util::read<uint8_t>(data, offset + DirectoryOffset::Size);
  extended_size = Util::read<uint8_t>(data, offset + DirectoryOffset::Extended);
  location = Util::read<uint32_t>(data, offset + DirectoryOffset::ExtentLocation);
  data_length = Util::read<uint32_t>(data, offset + DirectoryOffset::DataLength);
  date = std::make_unique<DateTime>(data, offset + DirectoryOffset::Date);
  flags = Util::read<uint8_t>(data, offset + DirectoryOffset::FileFlags);
  file_unit_size = Util::read<uint8_t>(data, offset + DirectoryOffset::FileUnitSize);
  interleave_gap = Util::read<uint8_t>(data, offset + DirectoryOffset::InterleaveGap);
  volume_sequence_number = Util::read<uint16_t>(data, offset + DirectoryOffset::VolumeSequenceNumber);
  file_id_length = Util::read<uint8_t>(data, offset + DirectoryOffset::FileIdentifierLength);
  identifier = Util::read(data, offset + DirectoryOffset::FileIdentifier, file_id_length);

  if (identifier.length() == 1 && identifier[0] == 1)
  {
    identifier = "..";
  }
  else if (identifier.length() == 1 && identifier[0] == 0)
  {
    identifier = ".";
  }

  if (identifier.length() > 2 && identifier.substr(identifier.length() - 2) == ";1")
  {
    flags |= FileFlag::Associated;

    extension = identifier.substr(identifier.find_last_of(".") + 1);
    extension = extension.substr(0, extension.length() - 2);
  }
}

void Directory::contents()
{

}