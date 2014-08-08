#ifndef _MDISO_H
#define _MDISO_H

#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <memory>

#include "util.h"

#include "iso_header.h"

namespace iso
{
  void extract(std::string disc, std::string dir);
  void build(std::string dir, std::string disc);
  void files(std::string disc);
  bool valid_directory(std::string dir);


  class ISO
  {
  public:
    ISO(std::string disc);

  private:
    std::shared_ptr<Header> m_header;
    uint32_t m_block_size;
    uint32_t m_header_offset;
    bool m_has_padding;
    bool m_pad_size;
  };
}


#endif
