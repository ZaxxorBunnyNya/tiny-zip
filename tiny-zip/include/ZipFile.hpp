#ifndef ZIP_FILE_HPP__
#define ZIP_FILE_HPP__

#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

#include "ZipEntry.hpp"

namespace Zip {
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
			this->m_fileStream.close();
		}

		void openMemory(const std::vector<uint8_t> _data);
		void open(const std::string& _path, OpenMode _mode);
		bool is_open();
		bool parseEntries();
		std::vector<ZipEntry> getEntries() { return this->m_entries; }

	private:
		std::vector<ZipEntry> m_entries;
		std::string m_path;
		OpenMode m_mode;
		std::fstream m_fileStream;

		bool parseInMemoryEntries();
		bool parseInFileEntries();
	};
}

#endif // !ZIP_FILE_HPP__
