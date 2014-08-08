#include "iso_volume.h"

PrimaryVolume::PrimaryVolume() { }

PrimaryVolume::PrimaryVolume(std::vector<uint8_t>& data)
{
  type = Util::read<uint8_t>(data, VolumeOffset::Type);
  identifier = Util::read(data, VolumeOffset::Identifier, 5);
  version = Util::read<uint8_t>(data, VolumeOffset::Version);
  system_identifier = Util::read(data, VolumeOffset::SystemIdentifier, 32);
  volume_identifier = Util::read(data, VolumeOffset::VolumeIdentifier, 32);

  volume_space_size = Util::read<uint32_t>(data, VolumeOffset::VolumeSpaceSize);
  volume_set_size = Util::read<uint16_t>(data, VolumeOffset::VolumeSetSize);
  volume_sequence_number = Util::read<uint16_t>(data, VolumeOffset::VolumeSequenceNumber);
  logical_block_size = Util::read<uint16_t>(data, VolumeOffset::LogicalBlockSize);
  path_table_size = Util::read<uint32_t>(data, VolumeOffset::PathTableSize);
  path_table_location = Util::read<uint32_t>(data, VolumeOffset::PathTableLocationLSB);
  path_table_optional = Util::read<uint32_t>(data, VolumeOffset::PathTableOptionalLSB);

  root = std::make_unique<ISOEntry>(data, VolumeOffset::RootDirectory);

  volume_set_identifier = Util::read(data, VolumeOffset::VolumeSetIdentifier, 128);
  publisher_identifier = Util::read(data, VolumeOffset::PublisherIdentifier, 128);
  data_preparer_identifier = Util::read(data, VolumeOffset::DataPreparerIdentifier, 128);
  application_identifier = Util::read(data, VolumeOffset::ApplicationIdentifier, 128);
  copyright_identifier = Util::read(data, VolumeOffset::CopyrightIdentifier, 38);
  abstract_identifier = Util::read(data, VolumeOffset::AbstractIdentifier, 36);
  bibliographic_identifier = Util::read(data, VolumeOffset::BibliographicIdentifier, 37);

  volume_creation = std::make_unique<DateTime>(Util::read(data, VolumeOffset::VolumeCreationDate, 17));
  volume_modification = std::make_unique<DateTime>(Util::read(data, VolumeOffset::VolumeModificationDate, 17));
  volume_expiration = std::make_unique<DateTime>(Util::read(data, VolumeOffset::VolumeExpirationDate, 17));
  volume_effective = std::make_unique<DateTime>(Util::read(data, VolumeOffset::VolumeEffectiveDate, 17));

  file_structure_version = Util::read<uint8_t>(data, VolumeOffset::FileStructureVersion);
}

std::ostream& operator<<(std::ostream& os, const PrimaryVolume& pv)
{
  os << std::hex;

  os << "Type:                      " << static_cast<int>(pv.type) << std::endl;
  os << "Identifier:                " << pv.identifier << std::endl;
  os << "Version:                   " << static_cast<int>(pv.version) << std::endl;
  os << "System Identifier:         " << pv.system_identifier << std::endl;
  os << "Volume Identifier:         " << pv.volume_identifier << std::endl;

  os << "Volume Space Size:         " << static_cast<int>(pv.volume_space_size) << std::endl;
  os << "Volume Set Size:           " << static_cast<int>(pv.volume_set_size) << std::endl;
  os << "Volume Sequence Number:    " << static_cast<int>(pv.volume_sequence_number) << std::endl;
  os << "Logical Block Size:        " << static_cast<int>(pv.logical_block_size) << std::endl;

  os << "Path Table Size:           " << pv.path_table_size << std::endl;
  os << "Path Table Location:       " << pv.path_table_location << std::endl;
  os << "Path Table Optional:       " << pv.path_table_optional << std::endl;

  os << "Root Directory Location:   " << pv.root->location << std::endl;

  os << "Volume Set Identifier:     " << pv.volume_set_identifier << std::endl;
  os << "Publisher Identifier:      " << pv.publisher_identifier << std::endl;
  os << "Data Preparer Identifier:  " << pv.data_preparer_identifier << std::endl;
  os << "Application Identifier:    " << pv.application_identifier << std::endl;
  os << "Copyright Identifier:      " << pv.copyright_identifier << std::endl;
  os << "Abstract Identifier:       " << pv.abstract_identifier << std::endl;
  os << "Bibliographic Identifier:  " << pv.bibliographic_identifier << std::endl;

  os << "Volume Creation Date:      " << pv.volume_creation->to_string() << std::endl;
  os << "Volume Modification Date:  " << pv.volume_modification->to_string() << std::endl;
  os << "Volume Expiration Date:    " << pv.volume_expiration->to_string() << std::endl;
  os << "Volume Effective Date:     " << pv.volume_effective->to_string() << std::endl;

  os << "File Structure Version:    " << static_cast<int>(pv.file_structure_version) << std::endl;

  os << std::dec;

  return os;
}