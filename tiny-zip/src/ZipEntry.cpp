#include "ZipEntry.hpp"

using namespace Zip;

bool ZipEntry::uncompress() {
	return true;
}

bool ZipEntry::compress() {
	return true;
}

uint32_t ZipEntry::checksum()
{
	return 0;
}