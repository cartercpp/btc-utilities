#pragma once

#include <iostream>
#include <stdexcept>
#include <array>
#include <utility>
#include <algorithm>
#include <concepts>
#include <cstdint>
#include <cstddef>
#include "block.hpp"

namespace sha256
{
	constexpr char c_to_lower(char c) noexcept
	{
		return ((c >= 'A') && (c <= 'Z')) ? ('a' + (c - 'A')) : c;
	}

	constexpr char c_to_upper(char c) noexcept
	{
		return ((c >= 'a') && (c <= 'z')) ? ('A' + (c - 'a')) : c;
	}

	template <int HexSize> requires (HexSize - 1 <= 2)
		constexpr std::uint8_t big_endian_hex_to_decimal(const char(&hex)[HexSize])
	{
		constexpr int RealHexSize = HexSize - 1;

		std::uint8_t output = 0;
		std::uint8_t intValue = 1;

		for (int iter = 0; iter < RealHexSize; ++iter)
		{
			const int hexIndex = RealHexSize - iter - 1;
			const char hexChar = c_to_lower(hex[hexIndex]);
			int nibbleValue = 0;

			if ((hexChar >= '0') && (hexChar <= '9'))
				nibbleValue = hexChar - '0';
			else if ((hexChar >= 'a') && (hexChar <= 'f'))
				nibbleValue = 10 + (hexChar - 'a');
			else
				throw std::invalid_argument{ "Argument contains one or more invalid hexadecimal chars" };

			output += ((nibbleValue & 1) != 0) * intValue;
			intValue <<= 1;

			output += ((nibbleValue & 2) != 0) * intValue;
			intValue <<= 1;

			output += ((nibbleValue & 4) != 0) * intValue;
			intValue <<= 1;

			output += ((nibbleValue & 8) != 0) * intValue;
			intValue <<= 1;
		}

		return output;
	}

	template <int HexSize> requires ((HexSize - 1 >= 3) && (HexSize - 1 <= 4))
		constexpr std::uint16_t big_endian_hex_to_decimal(const char(&hex)[HexSize])
	{
		constexpr int RealHexSize = HexSize - 1;

		std::uint16_t output = 0;
		std::uint16_t intValue = 1;

		for (int iter = 0; iter < RealHexSize; ++iter)
		{
			const int hexIndex = RealHexSize - iter - 1;
			const char hexChar = c_to_lower(hex[hexIndex]);
			int nibbleValue = 0;

			if ((hexChar >= '0') && (hexChar <= '9'))
				nibbleValue = hexChar - '0';
			else if ((hexChar >= 'a') && (hexChar <= 'f'))
				nibbleValue = 10 + (hexChar - 'a');
			else
				throw std::invalid_argument{ "Argument contains one or more invalid hexadecimal chars" };

			output += ((nibbleValue & 1) != 0) * intValue;
			intValue <<= 1;

			output += ((nibbleValue & 2) != 0) * intValue;
			intValue <<= 1;

			output += ((nibbleValue & 4) != 0) * intValue;
			intValue <<= 1;

			output += ((nibbleValue & 8) != 0) * intValue;
			intValue <<= 1;
		}

		return output;
	}

	template <int HexSize> requires ((HexSize - 1 >= 5) && (HexSize - 1 <= 8))
		constexpr std::uint32_t big_endian_hex_to_decimal(const char(&hex)[HexSize])
	{
		constexpr int RealHexSize = HexSize - 1;

		std::uint32_t output = 0;
		std::uint32_t intValue = 1;

		for (int iter = 0; iter < RealHexSize; ++iter)
		{
			const int hexIndex = RealHexSize - iter - 1;
			const char hexChar = c_to_lower(hex[hexIndex]);
			int nibbleValue = 0;

			if ((hexChar >= '0') && (hexChar <= '9'))
				nibbleValue = hexChar - '0';
			else if ((hexChar >= 'a') && (hexChar <= 'f'))
				nibbleValue = 10 + (hexChar - 'a');
			else
				throw std::invalid_argument{ "Argument contains one or more invalid hexadecimal chars" };

			output += ((nibbleValue & 1) != 0) * intValue;
			intValue <<= 1;

			output += ((nibbleValue & 2) != 0) * intValue;
			intValue <<= 1;

			output += ((nibbleValue & 4) != 0) * intValue;
			intValue <<= 1;

			output += ((nibbleValue & 8) != 0) * intValue;
			intValue <<= 1;
		}

		return output;
	}

	template <int HexSize> requires ((HexSize - 1 >= 9) && (HexSize - 1 <= 16))
		constexpr std::uint64_t big_endian_hex_to_decimal(const char(&hex)[HexSize])
	{
		constexpr int RealHexSize = HexSize - 1;

		std::uint64_t output = 0;
		std::uint64_t intValue = 1;

		for (int iter = 0; iter < RealHexSize; ++iter)
		{
			const int hexIndex = RealHexSize - iter - 1;
			const char hexChar = c_to_lower(hex[hexIndex]);
			int nibbleValue = 0;

			if ((hexChar >= '0') && (hexChar <= '9'))
				nibbleValue = hexChar - '0';
			else if ((hexChar >= 'a') && (hexChar <= 'f'))
				nibbleValue = 10 + (hexChar - 'a');
			else
				throw std::invalid_argument{ "Argument contains one or more invalid hexadecimal chars" };

			output += ((nibbleValue & 1) != 0) * intValue;
			intValue <<= 1;

			output += ((nibbleValue & 2) != 0) * intValue;
			intValue <<= 1;

			output += ((nibbleValue & 4) != 0) * intValue;
			intValue <<= 1;

			output += ((nibbleValue & 8) != 0) * intValue;
			intValue <<= 1;
		}

		return output;
	}

	template <std::unsigned_integral numType>
	constexpr void display_as_big_endian_binary(numType num) noexcept
	{
		constexpr int numTypeBits = sizeof(numType) * 8;
		numType intValue = 1;
		intValue <<= numTypeBits - 1;

		for (int i = 0; i < numTypeBits; ++i)
		{
			std::cout << (((num & intValue) != 0) ? '1' : '0');
			intValue >>= 1;
		}
	}

	template <std::unsigned_integral numType>
	constexpr void display_as_big_endian_hex(numType num) noexcept
	{
		constexpr int numTypeBits = sizeof(numType) * 8;
		numType intValue = 1;
		intValue <<= numTypeBits - 1;

		for (int i = 0; i < numTypeBits; i += 4)
		{
			int nibbleValue = 0;

			nibbleValue += ((num & intValue) != 0) * 8;
			intValue >>= 1;

			nibbleValue += ((num & intValue) != 0) * 4;
			intValue >>= 1;

			nibbleValue += ((num & intValue) != 0) * 2;
			intValue >>= 1;

			nibbleValue += ((num & intValue) != 0) * 1;
			intValue >>= 1;

			if ((nibbleValue >= 0) && (nibbleValue <= 9))
				std::cout << char('0' + nibbleValue);
			else
				std::cout << char('a' + (nibbleValue - 10));
		}
	}

	template <std::unsigned_integral numType>
	constexpr bool get_bit(numType num, std::size_t bitIndex)
	{
		constexpr std::size_t numTypeBits = sizeof(numType) * 8;

		if (bitIndex >= numTypeBits)
			throw std::invalid_argument{ "Out of bounds" };

		numType intValue = 1;
		intValue <<= numTypeBits - bitIndex - 1;

		return (num & intValue) != 0;
	}

	template <std::unsigned_integral numType>
	constexpr void set_bit(numType& numRef, std::size_t bitIndex, bool setValue)
	{
		constexpr std::size_t numTypeBits = sizeof(numType) * 8;

		if (bitIndex >= numTypeBits)
			throw std::invalid_argument{ "Out of bounds" };

		numType intValue = 1;
		intValue <<= numTypeBits - bitIndex - 1;

		const bool bitValue = (numRef & intValue) != 0;

		if (bitValue != setValue)
		{
			if (setValue)
				numRef += intValue;
			else
				numRef -= intValue;
		}
	}

	template <std::unsigned_integral numType, std::size_t ArraySize>
	constexpr void set_bit(std::array<numType, ArraySize>& arrRef, std::size_t bitIndex,
		bool setValue)
	{
		constexpr std::size_t numTypeBits = sizeof(numType) * 8;
		constexpr std::size_t bitsInArray = numTypeBits * ArraySize;

		if (bitIndex >= bitsInArray)
			throw std::invalid_argument{ "Out of bounds" };

		set_bit(arrRef[bitIndex / numTypeBits], bitIndex % numTypeBits, setValue);
	}

	template <std::unsigned_integral numType>
	constexpr numType left_rotate(numType num, int count) noexcept
	{
		constexpr int numTypeBits = sizeof(numType) * 8;
		count %= numTypeBits;
		return (num << count) | (num >> (numTypeBits - count));
	}

	template <std::unsigned_integral numType>
	constexpr numType right_rotate(numType num, int count) noexcept
	{
		constexpr int numTypeBits = sizeof(numType) * 8;
		count %= numTypeBits;
		return (num >> count) | (num << (numTypeBits - count));
	}

	template <std::unsigned_integral numType>
	constexpr numType reverse_endian_as_num(numType num) noexcept
	{
		numType result = 0;

		for (std::size_t i = 0; i < sizeof(numType); ++i)
		{
			result <<= 8;
			result |= (num & 0xFF);
			num >>= 8;
		}
		
		return result;
	}

	template <std::unsigned_integral numType>
	constexpr auto reverse_endian_as_bytes(numType num) noexcept
	{
		std::array<std::uint8_t, sizeof(numType)> bytes{};

		for (std::size_t byteNumber = 0; byteNumber < sizeof(numType); ++byteNumber)
		{
			set_bit(bytes[bytes.size() - byteNumber - 1], 0, get_bit(num, byteNumber * 8));
			set_bit(bytes[bytes.size() - byteNumber - 1], 1, get_bit(num, byteNumber * 8 + 1));
			set_bit(bytes[bytes.size() - byteNumber - 1], 2, get_bit(num, byteNumber * 8 + 2));
			set_bit(bytes[bytes.size() - byteNumber - 1], 3, get_bit(num, byteNumber * 8 + 3));
			set_bit(bytes[bytes.size() - byteNumber - 1], 4, get_bit(num, byteNumber * 8 + 4));
			set_bit(bytes[bytes.size() - byteNumber - 1], 5, get_bit(num, byteNumber * 8 + 5));
			set_bit(bytes[bytes.size() - byteNumber - 1], 6, get_bit(num, byteNumber * 8 + 6));
			set_bit(bytes[bytes.size() - byteNumber - 1], 7, get_bit(num, byteNumber * 8 + 7));
		}

		return bytes;
	}

	template <std::unsigned_integral numType, std::size_t ArraySize>
	constexpr auto reverse_endian_as_bytes(const std::array<numType, ArraySize>& numbers) noexcept
	{
		constexpr std::size_t OutputSize = sizeof(numType) * ArraySize;
		std::array<std::uint8_t, OutputSize> bytes{};

		for (std::size_t i = 0; i < ArraySize; ++i)
		{
			numType num = numbers[ArraySize - i - 1];

			for (std::size_t byteNumber = 0; byteNumber < sizeof(numType); ++byteNumber)
			{
				bytes[i * sizeof(numType) + byteNumber] = num & 0xff;
				num >>= 8;
			}
		}

		return bytes;
	}

	template <std::unsigned_integral lArgType, std::unsigned_integral rArgType>
	constexpr auto concat_as_num(lArgType lArg, rArgType rArg)
	{
		constexpr int lArgBits = sizeof(lArgType) * 8,
			rArgBits = sizeof(rArgType) * 8,
			outputBits = lArgBits + rArgBits;

		if constexpr (outputBits == 16)
		{
			std::uint16_t output = 0;
			int writeIndex = 0;

			for (int i = 0; i < lArgBits; ++i)
			{
				set_bit(output, writeIndex, get_bit(lArg, i));
				++writeIndex;
			}

			for (int i = 0; i < rArgBits; ++i)
			{
				set_bit(output, writeIndex, get_bit(rArg, i));
				++writeIndex;
			}

			return output;
		}
		else if constexpr (outputBits == 32)
		{
			std::uint32_t output = 0;
			int writeIndex = 0;

			for (int i = 0; i < lArgBits; ++i)
			{
				set_bit(output, writeIndex, get_bit(lArg, i));
				++writeIndex;
			}

			for (int i = 0; i < rArgBits; ++i)
			{
				set_bit(output, writeIndex, get_bit(rArg, i));
				++writeIndex;
			}

			return output;
		}
		else if constexpr (outputBits == 64)
		{
			std::uint64_t output = 0;
			int writeIndex = 0;

			for (int i = 0; i < lArgBits; ++i)
			{
				set_bit(output, writeIndex, get_bit(lArg, i));
				++writeIndex;
			}

			for (int i = 0; i < rArgBits; ++i)
			{
				set_bit(output, writeIndex, get_bit(rArg, i));
				++writeIndex;
			}

			return output;
		}
		else
			throw std::runtime_error{ "Could not concatenate the arguments" };
	}

	template <std::unsigned_integral... Ts> requires (sizeof...(Ts) > 0)
	constexpr auto concat_as_bytes(Ts... args) noexcept
	{
		constexpr std::size_t ArraySize = []() constexpr {
			std::size_t bytes = 0;

			[[maybe_unused]] const char temp[] = {
				(bytes += sizeof(Ts), '\0')...
			};
			
			return bytes;
		}();
		std::array<std::uint8_t, ArraySize> bytes{};
		std::size_t writeBitIndex = 0;

		auto func = [&](std::unsigned_integral auto num) -> void {
			using numType = decltype(num);
			constexpr std::size_t numTypeBits = sizeof(numType) * 8;
			
			numType intValue = 1;
			intValue <<= numTypeBits - 1;

			for (std::size_t i = 0; i < numTypeBits; ++i)
			{
				set_bit(bytes[writeBitIndex / 8], i % 8, (num & intValue) != 0);
				intValue >>= 1;
				++writeBitIndex;
			}
		};

		[[maybe_unused]] const char temp[] = {
			(func(args), '\0')...
		};

		return bytes;
	}

	constexpr std::array<std::uint32_t, 64> K = {
		0x428a2f98u, 0x71374491u, 0xb5c0fbcfu, 0xe9b5dba5u,
		0x3956c25bu, 0x59f111f1u, 0x923f82a4u, 0xab1c5ed5u,
		0xd807aa98u, 0x12835b01u, 0x243185beu, 0x550c7dc3u,
		0x72be5d74u, 0x80deb1feu, 0x9bdc06a7u, 0xc19bf174u,
		0xe49b69c1u, 0xefbe4786u, 0x0fc19dc6u, 0x240ca1ccu,
		0x2de92c6fu, 0x4a7484aau, 0x5cb0a9dcu, 0x76f988dau,
		0x983e5152u, 0xa831c66du, 0xb00327c8u, 0xbf597fc7u,
		0xc6e00bf3u, 0xd5a79147u, 0x06ca6351u, 0x14292967u,
		0x27b70a85u, 0x2e1b2138u, 0x4d2c6dfcu, 0x53380d13u,
		0x650a7354u, 0x766a0abbu, 0x81c2c92eu, 0x92722c85u,
		0xa2bfe8a1u, 0xa81a664bu, 0xc24b8b70u, 0xc76c51a3u,
		0xd192e819u, 0xd6990624u, 0xf40e3585u, 0x106aa070u,
		0x19a4c116u, 0x1e376c08u, 0x2748774cu, 0x34b0bcb5u,
		0x391c0cb3u, 0x4ed8aa4au, 0x5b9cca4fu, 0x682e6ff3u,
		0x748f82eeu, 0x78a5636fu, 0x84c87814u, 0x8cc70208u,
		0x90befffau, 0xa4506cebu, 0xbef9a3f7u, 0xc67178f2u
	};

	template <std::size_t ArraySize>
	constexpr auto hash_bytes(const std::array<std::uint8_t, ArraySize>& bytes) noexcept
	{
		constexpr std::uint64_t BinarySize = ArraySize * 8;

		std::array<std::uint32_t, 8> H{
			0x6a09e667u, 0xbb67ae85u, 0x3c6ef372u, 0xa54ff53au, 0x510e527fu, 0x9b05688cu,
			0x1f83d9abu, 0x5be0cd19u
		};

		constexpr std::size_t pBinarySize = []() constexpr {
			std::size_t size = BinarySize + 1;
			while ((size % 512) != 0)
				++size;
			return size;
		}();

		std::array<std::uint8_t, pBinarySize / 8> preprocessedBytes{};
		
		for (std::size_t i = 0; i < ArraySize; ++i)
			preprocessedBytes[i] = bytes[i];
		set_bit(preprocessedBytes[ArraySize], 0, true);

		int readIndex = 0;

		for (std::size_t offset = 8; offset > 0; --offset)
			for (int i = 0; i < 8; ++i)
			{
				set_bit(preprocessedBytes[preprocessedBytes.size() - offset], i,
					get_bit(BinarySize, readIndex));
				++readIndex;
			}

		for (std::size_t pIndex = 0; pIndex < pBinarySize; pIndex += 512)
		{
			std::array<std::uint32_t, 64> W{};

			for (std::size_t i = 0; i < 16; ++i)
			{
				const std::uint8_t byte1 = preprocessedBytes[pIndex / 8 + i * 4],
					byte2 = preprocessedBytes[pIndex / 8 + i * 4 + 1],
					byte3 = preprocessedBytes[pIndex / 8 + i * 4 + 2],
					byte4 = preprocessedBytes[pIndex / 8 + i * 4 + 3];

				W[i] = concat_as_num(
					concat_as_num(byte1, byte2),
					concat_as_num(byte3, byte4)
				);
			}

			for (std::size_t i = 16; i < 64; ++i)
			{
				const std::uint32_t s0 = right_rotate(W[i - 15], 7) ^ right_rotate(W[i - 15], 18)
					^ (W[i - 15] >> 3);

				const std::uint32_t s1 = right_rotate(W[i - 2], 17) ^ right_rotate(W[i - 2], 19)
					^ (W[i - 2] >> 10);

				W[i] = W[i - 16] + s0 + W[i - 7] + s1;
			}

			std::uint32_t a = H[0],
				b = H[1],
				c = H[2],
				d = H[3],
				e = H[4],
				f = H[5],
				g = H[6],
				h = H[7];

			for (std::size_t i = 0; i < 64; ++i)
			{
				const std::uint32_t S1 = right_rotate(e, 6) ^ right_rotate(e, 11)
					^ right_rotate(e, 25);

				const std::uint32_t ch = (e & f) ^ (~e & g);
				const std::uint32_t temp1 = h + S1 + ch + K[i] + W[i];

				const std::uint32_t S0 = right_rotate(a, 2) ^ right_rotate(a, 13)
					^ right_rotate(a, 22);

				const std::uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
				const std::uint32_t temp2 = S0 + maj;

				h = g;
				g = f;
				f = e;
				e = d + temp1;
				d = c;
				c = b;
				b = a;
				a = temp1 + temp2;
			}

			H[0] += a;
			H[1] += b;
			H[2] += c;
			H[3] += d;
			H[4] += e;
			H[5] += f;
			H[6] += g;
			H[7] += h;
		}

		return H;
	}

	constexpr auto serialize_block_header(const bitcoin_block& block) noexcept
	{
		std::array<std::uint8_t, 80> bytes{};
		std::size_t writeIndex = 0;

		const auto versionBytes = reverse_endian_as_bytes(block.m_version);
		for (std::size_t i = 0; i < versionBytes.size(); ++i)
		{
			bytes[writeIndex] = versionBytes[i];
			++writeIndex;
		}

		for (std::size_t i = 0; i < block.m_prevBlock.size(); ++i)
		{
			bytes[writeIndex] = block.m_prevBlock[block.m_prevBlock.size() - i - 1];
			++writeIndex;
		}

		for (std::size_t i = 0; i < block.m_merkleRoot.size(); ++i)
		{
			bytes[writeIndex] = block.m_merkleRoot[block.m_merkleRoot.size() - i - 1];
			++writeIndex;
		}

		const auto timestampBytes = reverse_endian_as_bytes(block.m_timestamp);
		for (std::size_t i = 0; i < timestampBytes.size(); ++i)
		{
			bytes[writeIndex] = timestampBytes[i];
			++writeIndex;
		}

		const auto bitsBytes = reverse_endian_as_bytes(block.m_bits);
		for (std::size_t i = 0; i < bitsBytes.size(); ++i)
		{
			bytes[writeIndex] = bitsBytes[i];
			++writeIndex;
		}

		const auto nonceBytes = reverse_endian_as_bytes(block.m_nonce);
		for (std::size_t i = 0; i < nonceBytes.size(); ++i)
		{
			bytes[writeIndex] = nonceBytes[i];
			++writeIndex;
		}

		return bytes;
	}

	constexpr auto hash_block(const bitcoin_block& block) noexcept
	{
		const auto header1 = serialize_block_header(block);
		const auto hash1 = hash_bytes(header1);
		const auto header2 = concat_as_bytes(
			hash1[0], hash1[1], hash1[2], hash1[3], hash1[4], hash1[5], hash1[6], hash1[7]
		);
		const auto hash2 = hash_bytes(header2);

		const auto temp = reverse_endian_as_bytes(hash2);
		std::array<std::uint32_t, 8> output{};

		for (std::size_t i = 0; i < temp.size(); i += 4)
		{
			const std::uint8_t byte1 = temp[i],
				byte2 = temp[i + 1],
				byte3 = temp[i + 2],
				byte4 = temp[i + 3];

			output[i / 4] = concat_as_num(
				concat_as_num(byte1, byte2),
				concat_as_num(byte3, byte4)
			);
		}

		return output;
	}
}