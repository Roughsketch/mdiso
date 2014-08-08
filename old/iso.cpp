#include "iso.h"

ISO::ISO() { }

ISO::ISO(std::string filename)
{
  //  Open file for reading
  std::ifstream iso(filename, std::ios::binary);

  //  Vector to store header information
  std::vector<uint8_t> header(ISO::HeaderSize);

  //  If file didn't open correctly then throw an exception.
  if (!iso.good())
  {
    throw ISOOpenException();
  }

  //  Unset skipws to avoid vector eating spaces
  iso.unsetf(std::ios::skipws);


  try
  {
    //  Start at the default ISO header location
    iso.seekg(ISO::Start, std::ios::beg);

    //  Read header data directly into vector
    iso.read(reinterpret_cast<char *>(&header[0]), ISO::HeaderSize);

    //  Create PrimaryVolume out of header info
    this->primary = std::make_unique<PrimaryVolume>(ref(header));

    //  Print information
    std::cout << *primary;
    std::cin.get();
  }
  catch (std::exception e)
  {
    std::cout << e.what() << std::endl;
  }



  iso.close();
  this->iso_file = filename;
}

ISO::~ISO() { }


void ISO::directories()
{
  //  Root directory offset is provided by the directory in the 
  //  header times the logical block size (usually 2kb | 0x800)
  uint64_t root_dir = this->primary->root->location * this->primary->logical_block_size;

  std::cout << "Root Directory Listing:" << std::endl;

  uint32_t offset = 0;
  std::unique_ptr<ISOEntry> dir;
  std::vector<uint8_t> data(this->primary->root->data_length);

  std::ifstream iso(this->iso_file, std::ios::binary);

  if (!iso.good())
  {
    throw ISOOpenException();
  }
  std::cout << "Calling " << std::endl;
  this->primary->root->contents(iso, this->primary->logical_block_size);

  /*
  iso.seekg(root_dir, std::ios::beg);
  iso.read(reinterpret_cast<char *>(&data[0]), this->primary->root->data_length);

  while (offset < this->primary->root->data_length)
  {
    dir = std::make_unique<Directory>(ref(data), offset);
    offset += dir->size;

    if (dir->flags & FileFlag::Directory)
    {
      std::cout << "DIR: " << dir->identifier << std::endl;
    }
    else if (dir->flags & FileFlag::Associated)
    {
      std::cout << "FILE: " << dir->identifier << "     - " << dir->data_length << " bytes" << std::endl;

      if (dir->extension == "CNF")// || dir->extension == "CFG")
      {
        uint64_t location = dir->location * this->primary->logical_block_size;
        uint32_t size = dir->data_length;
        std::vector<uint8_t> file_data(size);

        iso.seekg(location, std::ios::beg);
        iso.read(reinterpret_cast<char *>(&file_data[0]), size);

        for (auto& byte : file_data)
        {
          std::cout << static_cast<char>(byte);
        }
      }
    }
    else
    {
      std::cout << "UNKNOWN: " << dir->identifier << " [F: " << static_cast<int>(dir->flags) << "]" << std::endl;
    }
  }
  */

  iso.close();
}

void ISO::files()
{

}

void ISO::contents()
{

}