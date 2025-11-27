#ifndef ZIP_ENTRY_HPP__
#define ZIP_ENTRY_HPP__

#include <iostream>
#include <vector>

#include "Zip.hpp"

namespace Zip {

	enum CompressMethod {
		NoCompression = 0,
		Shrink = 1,
		CompressFactor1 = 2,
		CompressFactor2 = 3,
		CompressFactor3 = 4,
		CompressFactor4 = 5,
		LZMA = 14,
	};

	class ZipEntry
	{
	public:
		ZipEntry(const LOCAL_FILE_HEADER& _header, std::string _fileName, std::vector<uint8_t> _extFields, std::vector<uint8_t> _data) {
			this->m_fileName = _fileName;

			if (_header.compressionMethod != CompressMethod::NoCompression) {
				this->m_dataCompressed = _data;
			}
			else {
				this->m_data = _data;
			}

			this->m_method = (CompressMethod)_header.compressionMethod;
		}

		~ZipEntry() {

		}

		ZipEntry(std::string _fileName) {
			this->m_fileName = _fileName;
		}

		bool uncompress();
		bool compress();

		size_t size() {
			return this->m_data.size();
		}

		size_t sizeCompressed() {
			return this->m_dataCompressed.size();
		}

		uint32_t checksum();
		std::string fileName() { return this->m_fileName; }

		std::vector<uint8_t> data() {
			return this->m_data;
		}

	private:
		std::string m_fileName = "";

		std::vector<uint8_t> m_dataCompressed;
		std::vector<uint8_t> m_data;
		CompressMethod m_method;

		bool uncompressLZMA();
	};
}

#endif // !ZIP_ENTRY_HPP__
