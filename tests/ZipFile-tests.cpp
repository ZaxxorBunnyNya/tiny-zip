#include <gtest/gtest.h>
#include "ZipFile.hpp"
#include <filesystem>


TEST(ZipFileTest, can_open_not_existing_file) {
	auto zip = Zip::ZipFile("not-exists.zip", Zip::OpenMode::in);

	EXPECT_FALSE(zip.is_open());
}

TEST(ZipFileTest, can_open_existing_file) {
	auto zip = Zip::ZipFile("tests-data/simple-data-no-compressed.zip", Zip::OpenMode::in);

	EXPECT_TRUE(zip.is_open());
}

TEST(ZipFileTest, can_parse_file_entries) {
	auto zip = Zip::ZipFile("tests-data/simple-data-no-compressed.zip", Zip::OpenMode::in);

	EXPECT_TRUE(zip.parseEntries());
}

TEST(ZipFileTest, can_return_error_on_empty_file) {
	auto zip = Zip::ZipFile("tests-data/empty.zip", Zip::OpenMode::in);

	EXPECT_FALSE(zip.parseEntries());
}

TEST(ZipFileTest, can_return_error_on_corrupt_header) {
	auto zip = Zip::ZipFile("tests-data/corrupt_zip_header.zip", Zip::OpenMode::in);

	EXPECT_FALSE(zip.parseEntries());
}

TEST(ZipFileTest, can_uncompress_simple_archive) {
	auto zip = Zip::ZipFile("tests-data/simple-data-no-compressed.zip", Zip::OpenMode::in);

	EXPECT_TRUE(zip.parseEntries());

	auto entries = zip.getEntries();

	EXPECT_EQ(entries.size(), 1);

	auto entry = entries[0];
	std::vector<uint8_t> data;

	std::fstream inFs("tests-data/simple-data.txt", std::ios::ios_base::in|std::ios_base::binary);
	inFs.seekg(0, std::ios_base::end);
	auto size = inFs.tellg();
	inFs.seekg(0);

	data.resize(size);
	inFs.read((char*)data.data(), size);

	EXPECT_EQ(entry.data().size(), size);
	EXPECT_EQ(memcmp(data.data(), entry.data().data(), size), 0);
}

