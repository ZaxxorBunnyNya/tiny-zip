#include "ZipEntry.hpp"
#include <cstring>

using namespace Zip;

bool ZipEntry::uncompress() {

	switch (this->m_method) {
	case CompressMethod::NoCompression:
		return true;
	case CompressMethod::LZMA:
		return this->uncompressLZMA();
	}

	return false;
}

bool ZipEntry::compress() {
	return false;
}

uint32_t ZipEntry::checksum()
{
	return 0;
}

bool ZipEntry::uncompressLZMA() {
	if (this->m_dataCompressed.size() < 13) {
		return false;
	}

	std::vector<uint8_t> properties;
	uint16_t version = 0;
	uint16_t propertiesSize = 0;
	uint32_t dictSize = 0;
	uint64_t uncompressedSize = 0;


	memcpy(&version, &this->m_dataCompressed[0], sizeof(version));
	memcpy(&propertiesSize, &this->m_dataCompressed[2], sizeof(propertiesSize));
	properties.resize(propertiesSize);

	memcpy(properties.data(), &this->m_dataCompressed[4], propertiesSize);

	size_t startOfData = propertiesSize + 4;

	uint8_t d = 0;
	memcpy(&d, &properties[0], sizeof(d));
	memcpy(&dictSize, &properties[1], sizeof(dictSize));
	//memcpy(&uncompressedSize, &properties[5], sizeof(uncompressedSize));

	if (d >= (9 * 5 * 5)) {
		return false;
	}

	uint8_t lc = d % 9;
	d /= 9;
	uint8_t  pb = d / 5;
	uint8_t lp = d % 5;

	if (dictSize < (1 << 12)) {
		return false;
	}


	return true;
}