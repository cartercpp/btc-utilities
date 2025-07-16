#include <iostream>
#include <string>
#include <string_view>
#include <stdexcept>
#include <array>
#include <cstdint>
#include "sha256.hpp"
#include "block.hpp"

std::uint32_t big_endian_hex_to_u32(std::string_view);
std::array<std::uint8_t, 32> big_endian_hex_to_u256(std::string_view);

int main()
{
	try
	{
		bitcoin_block block;
		std::string input;

		std::cout << "Input the following in big-endian hexadecimal:\n\n";
		
		std::cout << "Version (4 bytes)> ";
		std::getline(std::cin, input);
		block.m_version = big_endian_hex_to_u32(input);

		std::cout << "Previous block (32 bytes)> ";
		std::getline(std::cin, input);
		block.m_prevBlock = big_endian_hex_to_u256(input);

		std::cout << "Merkle root (32 bytes)> ";
		std::getline(std::cin, input);
		block.m_merkleRoot = big_endian_hex_to_u256(input);

		std::cout << "Timestamp (4 bytes)> ";
		std::getline(std::cin, input);
		block.m_timestamp = big_endian_hex_to_u32(input);

		std::cout << "Bits (4 bytes)> ";
		std::getline(std::cin, input);
		block.m_bits = big_endian_hex_to_u32(input);

		std::cout << "Nonce (4 bytes)> ";
		std::getline(std::cin, input);
		block.m_nonce = big_endian_hex_to_u32(input);
		std::cout << '\n';

		const auto blockHash = sha256::hash_block(block);
		for (const auto word : blockHash)
			sha256::display_as_big_endian_hex(word);
		std::cin.get();
	}
	catch (const std::exception& e)
	{
		std::cout << "Error> " << e.what() << '\n';
		return 1;
	}

	return 0;
}
