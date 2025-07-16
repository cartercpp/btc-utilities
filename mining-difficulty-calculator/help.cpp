#include <cmath>
#include <cstdint>

double bits_to_target(std::uint32_t bits) noexcept
{
	const auto exponent = bits >> 24;
	const auto coefficient = bits & 0x007fffff; // lower 3 bytes

	return coefficient * std::pow(256, exponent - 3);
}

double bits_to_difficulty(std::uint32_t bits) noexcept
{
	return bits_to_target(0x1d00ffffu) / bits_to_target(bits);
}