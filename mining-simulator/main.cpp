#include <iostream>
#include <format>
#include "block.hpp"
#include "sha256.hpp"

/*
	This simple program re-mines the Bitcoin Genesis Block!
*/

int main()
{
	bitcoin_block block{
		.m_version = 0x00000001,
		.m_prevBlock = {}, // all zero
		.m_merkleRoot = {
			0x4a, 0x5e, 0x1e, 0x4b, 0xaa, 0xb8, 0x9f, 0x3a,
			0x32, 0x51, 0x8a, 0x88, 0xc3, 0x1b, 0xc8, 0x7f,
			0x61, 0x8f, 0x76, 0x67, 0x3e, 0x2c, 0xc7, 0x7a,
			0xb2, 0x12, 0x7b, 0x7a, 0xfd, 0xed, 0xa3, 0x3b
		},
		.m_timestamp = 0x495fab29,
		.m_bits = 0x1d00ffff,
		.m_nonce = 0x7c2bac1d - 5'000 // 5,000 away from the solution
	};

	while (true)
	{
		const auto blockHash = sha256::hash_block(block);

		std::cout << std::format("Nonce {} -> ", block.m_nonce);
		sha256::display_as_big_endian_hex(blockHash[0]);
		sha256::display_as_big_endian_hex(blockHash[1]);
		sha256::display_as_big_endian_hex(blockHash[2]);
		sha256::display_as_big_endian_hex(blockHash[3]);
		sha256::display_as_big_endian_hex(blockHash[4]);
		sha256::display_as_big_endian_hex(blockHash[5]);
		sha256::display_as_big_endian_hex(blockHash[6]);
		sha256::display_as_big_endian_hex(blockHash[7]);
		std::cout << '\n';

		const bool blockSolved
			= (blockHash[0] == sha256::big_endian_hex_to_decimal("00000000"))
			&& (blockHash[1] == sha256::big_endian_hex_to_decimal("0019d668"))
			&& (blockHash[2] == sha256::big_endian_hex_to_decimal("9c085ae1"))
			&& (blockHash[3] == sha256::big_endian_hex_to_decimal("65831e93"))
			&& (blockHash[4] == sha256::big_endian_hex_to_decimal("4ff763ae"))
			&& (blockHash[5] == sha256::big_endian_hex_to_decimal("46a2a6c1"))
			&& (blockHash[6] == sha256::big_endian_hex_to_decimal("72b3f1b6"))
			&& (blockHash[7] == sha256::big_endian_hex_to_decimal("0a8ce26f"));

		if (blockSolved)
		{
			std::cout << "Solved!\n";
			break;
		}
		else
			++block.m_nonce;
	}

	std::cin.get();

	return 0;
}