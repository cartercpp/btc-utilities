#pragma once

#include <array>
#include <cstdint>

struct bitcoin_block
{
	std::uint32_t m_version; // 4 bytes
	std::array<std::uint8_t, 32> m_prevBlock; // 32 bytes
	std::array<std::uint8_t, 32> m_merkleRoot; // 32 bytes
	std::uint32_t m_timestamp; // 4 bytes
	std::uint32_t m_bits; // 4 bytes
	std::uint32_t m_nonce; // 4 bytes
};
