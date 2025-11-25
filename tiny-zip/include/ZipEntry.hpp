#ifndef ZIP_ENTRY_HPP__
#define ZIP_ENTRY_HPP__

#include <iostream>
#include <vector>

#include "Zip.hpp"

namespace Zip {

	enum CompressAlgo {
		NoCompression = 0,
		Shrink = 1,
		CompressFactor1 = 2,
		CompressFactor2 = 3,
		CompressFactor3 = 4,
		CompressFactor4 = 5,
	};

	class ZipEntry
	{
	public:
		ZipEntry(const LOCAL_FILE_HEADER &_header, std::string _fileName, std::vector<uint8_t> _extFields, std::vector<uint8_t> _data) {
			this->m_fileName = _fileName;
			
			if (_header.compressionMethod != CompressAlgo::NoCompression) {
				this->m_dataCompressed = _data;
			}
			else {
				this->m_data = _data;
			}
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

		std::vector<uint8_t> data() {
			return this->m_data;
		}

	private:
		std::string m_fileName = "";

		std::vector<uint8_t> m_dataCompressed;
		std::vector<uint8_t> m_data;

	};
}

#endif // !ZIP_ENTRY_HPP__
