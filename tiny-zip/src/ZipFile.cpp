#include "ZipFile.hpp"

using namespace Zip;

void ZipFile::open(const std::string& _path, OpenMode _mode) {
	this->m_path = _path;
	this->m_mode = _mode;

	auto fstreamMode = _mode == OpenMode::in ? std::ios::ios_base::in : std::ios::ios_base::out;
	fstreamMode |= std::ios_base::binary;

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

	if (size <= sizeof(LOCAL_FILE_HEADER)) {
		return false;
	}

	while (this->m_fileStream.eof() == false) {
		LOCAL_FILE_HEADER header = {};

		this->m_fileStream.read((char*)&header, sizeof(header));

		if (header.signature == 0x04034b50) {
			std::string fileNameStr;
			std::vector<uint8_t> extFields;
			std::vector<uint8_t> data;

			fileNameStr.resize(header.fileNameLen);
			this->m_fileStream.read(fileNameStr.data(), header.fileNameLen);
			
			extFields.resize(header.extraFieldLen);
			this->m_fileStream.read((char*)extFields.data(), header.extraFieldLen);

			data.resize(header.compressedSize);
			this->m_fileStream.read((char*)data.data(), header.compressedSize);

			auto entry = ZipEntry(header, fileNameStr, extFields, data);
			this->m_entries.push_back(entry);
		}
		else {
			break;
		}
	}

	return m_entries.size() != 0;
}