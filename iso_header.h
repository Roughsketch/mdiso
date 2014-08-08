#ifndef _MDISO_HEADER_H
#define _MDISO_HEADER_H

namespace iso
{
  struct Header
  {
    Header(std::string file, uint32_t offset);

  private:
    uint8_t type;
    std::string identifier;
    uint8_t version;
    std::string system_identifier;
    std::string volume_identifier;
    uint32_t volume_space_size;
    uint16_t volume_set_size;
    uint16_t volume_sequence_number;
    uint16_t logical_block_size;
    uint32_t path_table_size;
    uint32_t path_table_location;
    uint32_t path_table_optional;
    std::unique_ptr<ISOEntry> root;
    std::string volume_set_identifier;
    std::string publisher_identifier;
    std::string data_preparer_identifier;
    std::string application_identifier;
    std::string copyright_identifier;
    std::string abstract_identifier;
    std::string bibliographic_identifier;

    std::unique_ptr<DateTime> volume_creation;
    std::unique_ptr<DateTime> volume_modification;
    std::unique_ptr<DateTime> volume_expiration;
    std::unique_ptr<DateTime> volume_effective;

    uint8_t file_structure_version;
  };
}

#endif
