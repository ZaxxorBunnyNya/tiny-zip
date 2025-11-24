#include <gtest/gtest.h>
#include "ZipFile.hpp"
#include <filesystem>


TEST(ZipFileTest, open_not_existing_file) {
	auto zip = Zip::ZipFile("not-exists.zip", Zip::OpenMode::in);

	EXPECT_FALSE(zip.is_open());
}

TEST(ZipFileTest, open_existing_file) {
	auto zip = Zip::ZipFile("tests-data/simple-data-no-compressed.zip", Zip::OpenMode::in);

	EXPECT_TRUE(zip.is_open());
}

