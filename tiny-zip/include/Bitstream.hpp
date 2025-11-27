#ifndef BITSTREAM_HPP__
#define BITSTREAM_HPP__

#include <string>
#include <vector>
#include <cstdint>

namespace Zip {
	class Bitstream {
	public:

		void reset() { m_bitPos = 0; }

		uint64_t getBitPos() { return m_bitPos; }

		Bitstream(const uint8_t* _src, size_t n) {
			m_beg = _src;
			m_end = _src + n;
			m_bitPos = 0;
			m_bitPosEnd = n * 8;
		}

		uint64_t get64_t() {

			if (m_bitPos > m_bitPosEnd)
				return 0;
			m_bitPos += 8;
			return read64le(&m_beg[m_bitPos]);
		}

		uint32_t get32_t() {

			if (m_bitPos > m_bitPosEnd)
				return 0;
			m_bitPos += 4;
			return read32le(&m_beg[m_bitPos]);
		}

		uint16_t get16_t() {

			if (m_bitPos > m_bitPosEnd)
				return 0;
			m_bitPos += 2;
			return read16le(&m_beg[m_bitPos]);
		}


		uint8_t get8_t() {

			if (m_bitPos > m_bitPosEnd)
				return 0;
			m_bitPos++;
			return read8le(&m_beg[m_bitPos]);
		}
	private:

		const uint8_t* m_beg;
		const uint8_t* m_end;

		size_t m_bitPos;
		size_t m_bitPosEnd;

		uint64_t read64le(const uint8_t* src) {
			return
				((uint64_t)src[0] << 0) |
				((uint64_t)src[1] << 8) |
				((uint64_t)src[2] << 16) |
				((uint64_t)src[3] << 24) |
				((uint64_t)src[4] << 32) |
				((uint64_t)src[5] << 40) |
				((uint64_t)src[6] << 48) |
				((uint64_t)src[7] << 56);
		}

		uint32_t read32le(const uint8_t* src) {
			return
				((uint32_t)src[0] << 0) |
				((uint32_t)src[1] << 8) |
				((uint32_t)src[2] << 16) |
				((uint32_t)src[3] << 24);
		}


		uint16_t read16le(const uint8_t* src) {
			return
				((uint16_t)src[0] << 0) |
				((uint16_t)src[1] << 8);
		}


		uint8_t read8le(const uint8_t* src) {
			return
				((uint16_t)src[0] << 0);
		}
	};
}

#endif // !BITSTREAM_HPP__
