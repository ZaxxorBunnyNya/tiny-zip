#include "ZipFile.hpp"

using namespace Zip;

void ZipFile::open(const std::string& _path, OpenMode _mode) {
	this->m_path = _path;
	this->m_mode = _mode;

	auto fstreamMode = _mode == OpenMode::in ? std::ios::ios_base::in : std::ios::ios_base::out;

	this->m_fileStream.open(_path, fstreamMode);
}

bool ZipFile::is_open() {
	return this->m_fileStream.is_open();
}

bool ZipFile::parseEntries() {
	if (this->m_mode == OpenMode::in) {
		return this->parseInFileEntries();
	}
	else if (this->m_mode == OpenMode::out) {
		return this->parseInMemoryEntries();
	}

	return false;
}

bool ZipFile::parseInMemoryEntries() {
	return false;
}

bool ZipFile::parseInFileEntries() {
	this->m_fileStream.seekg(0, std::ios_base::end);
	size_t size = this->m_fileStream.tellp();
	this->m_fileStream.seekg(0);

	if (size <= sizeof(ZIP_HEADER)) {
		return false;
	}

	ZIP_HEADER header = {};

	this->m_fileStream.read((char*)&header, sizeof(header));

	if (header.signature != 0x04034b50) {
		return false;
	}

	return true;
}