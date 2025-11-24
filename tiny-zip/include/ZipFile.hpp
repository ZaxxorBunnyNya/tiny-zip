#ifndef ZIP_FILE_HPP__
#define ZIP_FILE_HPP__

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

#include "./Packed.hpp"

namespace Zip {
	START_PACKED struct ZIP_HEADER{
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
	} END_PACKED;

	enum OpenMode {
		in,
		out,
		trunc,
	};

	class ZipFile
	{
	public:
		ZipFile() {
			this->m_mode = OpenMode::out;
		}

		ZipFile(const std::string& _path, OpenMode _mode) {
			this->open(_path, _mode);
		}

		~ZipFile() {

		}

		void openMemory(const std::vector<uint8_t> _data);
		void open(const std::string& _path, OpenMode _mode);
		bool is_open();
		bool parseEntries();

	private:
		std::string m_path;
		OpenMode m_mode;
		std::fstream m_fileStream;

		bool parseInMemoryEntries();
		bool parseInFileEntries();
	};
}

#endif // !ZIP_FILE_HPP__
