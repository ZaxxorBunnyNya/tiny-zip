#ifndef ZIP_H__
#define ZIP_H__

#include "Packed.hpp"
#include <cstdint>

PACK( struct  LOCAL_FILE_HEADER {
	uint32_t signature;
	uint16_t version_needed;
	uint16_t flags;
	uint16_t compressionMethod;
	uint16_t modificationTime;
	uint16_t modificationDate;
	uint32_t crc32;
	uint32_t compressedSize;
	uint32_t uncompressedSize;
	uint16_t fileNameLen;
	uint16_t extraFieldLen;
});

PACK (struct FILE_DESCRIPTOR {
	uint32_t crc32;
	uint32_t compressedSize;
	uint32_t uncomressedSize;
});


#endif // !ZIP_H__
