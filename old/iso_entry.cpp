#include "iso_entry.h"

ISOEntry::ISOEntry()
{

}

ISOEntry::ISOEntry(std::vector<uint8_t>& data, uint32_t offset)
{
  size = Util::read<uint8_t>(data, offset + EntryOffset::Size);
  extended_size = Util::read<uint8_t>(data, offset + EntryOffset::Extended);
  location = Util::read<uint32_t>(data, offset + EntryOffset::ExtentLocation);
  data_length = Util::read<uint32_t>(data, offset + EntryOffset::DataLength);
  date = std::make_unique<DateTime>(data, offset + EntryOffset::Date);
  flags = Util::read<uint8_t>(data, offset + EntryOffset::FileFlags);
  file_unit_size = Util::read<uint8_t>(data, offset + EntryOffset::FileUnitSize);
  interleave_gap = Util::read<uint8_t>(data, offset + EntryOffset::InterleaveGap);
  volume_sequence_number = Util::read<uint16_t>(data, offset + EntryOffset::VolumeSequenceNumber);
  file_id_length = Util::read<uint8_t>(data, offset + EntryOffset::FileIdentifierLength);
  identifier = Util::read(data, offset + EntryOffset::FileIdentifier, file_id_length);

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
    flags |= Attribute::Associated;

    extension = identifier.substr(identifier.find_last_of(".") + 1);
    extension = extension.substr(0, extension.length() - 2);
  }
}

void ISOEntry::contents(std::ifstream& file, uint32_t blocksize)
{
  uint32_t offset = 0;
  std::vector<uint8_t> data(this->data_length);
  std::unique_ptr<ISOEntry> dir;

  auto fpos = file.tellg();

  file.seekg(this->location * blocksize, std::ios::beg);

  file.read(reinterpret_cast<char *>(&data[0]), this->data_length);

  while (offset < this->data_length)
  {
    dir = std::make_unique<ISOEntry>(ref(data), offset);
    offset += dir->size;

    if (dir->flags & Attribute::Directory)
    {
      std::cout << "DIR: " << dir->identifier << std::endl;
      
      if (dir->identifier != "." && dir->identifier != "..")
      {
        dir->contents(file, blocksize);
      }
    }
    else if (dir->flags & Attribute::Associated)
    {
      std::cout << "FILE: " << dir->identifier << "     - " << dir->data_length << " bytes" << std::endl;

      if (dir->extension == "CNF" || dir->extension == "CFG")
      {
        uint64_t location = dir->location * blocksize;
        uint32_t size = dir->data_length;
        std::vector<uint8_t> file_data(size);

        file.seekg(location, std::ios::beg);
        file.read(reinterpret_cast<char *>(&file_data[0]), size);

        std::cout << std::string(file_data.begin(), file_data.end());
      }
    }
    else
    {
      std::cout << "UNKNOWN: " << dir->identifier << " [F: " << static_cast<int>(dir->flags) << "]" << std::endl;
    }
  }

  file.seekg(fpos, std::ios::beg);
}