#include "iso.h"

namespace iso
{
  void files(std::string disc)
  {

  }

  ISO::ISO(std::string disc)
  {
    std::ifstream ifs(disc, std::ios::binary);

    std::vector<uint8_t> data = util::read_file(disc, 12);

    if (util::read<uint32_t>(data, 0) == 0xFFFFFF00 && util::read<uint32_t>(data, 4) == 0xFFFFFFFF && util::read<uint32_t>(data, 8) == 0xFFFFFF00)
    {
      m_has_padding = true;
    }

    if (m_has_padding)
    {
      m_header_offset = 0x9300;
    }
    else
    {
      m_header_offset = 0x8000;
    }

    m_header = std::make_shared<Header>(disc, m_header_offset);
  }
}