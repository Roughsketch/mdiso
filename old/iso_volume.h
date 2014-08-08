#ifndef _ISO_VOLUME_H
#define _ISO_VOLUME_H

#include "iso.h"

#include "iso_date.h"
#include "iso_entry.h"

namespace VolumeOffset
{
  enum
  {
    Type = 0,
    Identifier = 1,
    Version = 6,
    SystemIdentifier = 8,
    VolumeIdentifier = 40,
    VolumeSpaceSize = 80,
    VolumeSetSize = 120,
    VolumeSequenceNumber = 124,
    LogicalBlockSize = 128,
    PathTableSize = 132,
    PathTableLocationLSB = 140,
    PathTableOptionalLSB = 144,
    PathTableLocationMSB = 148,
    PathTableOptionalMSB = 152,
    RootDirectory = 156,
    VolumeSetIdentifier = 190,
    PublisherIdentifier = 318,
    DataPreparerIdentifier = 446,
    ApplicationIdentifier = 574,
    CopyrightIdentifier = 702,
    AbstractIdentifier = 740,
    BibliographicIdentifier = 776,
    VolumeCreationDate = 813,
    VolumeModificationDate = 830,
    VolumeExpirationDate = 847,
    VolumeEffectiveDate = 864,
    FileStructureVersion = 881
  };
};

struct BootVolume
{
  uint8_t type;
  std::string identifier;
  uint8_t version;
  std::string boot_system_identifier;
  std::string boot_volume_identifier;
};

struct PrimaryVolume
{
  PrimaryVolume();
  PrimaryVolume(std::vector<uint8_t>& data);

  friend std::ostream& operator<<(std::ostream& os, const PrimaryVolume& pv);

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

#endif
