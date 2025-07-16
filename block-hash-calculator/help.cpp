#include <array>
#include <string_view>
#include <stdexcept>
#include <cstdint>
#include <cctype>
#include <cstddef>

std::uint32_t big_endian_hex_to_u32(std::string_view hex)
{
	if (hex.size() != 8)
		throw std::invalid_argument{ "8 hexadecimal characters = 32 bits" };

	std::uint32_t output = 0;
	std::uint32_t coeff = 1;

	for (auto it = hex.rbegin(); it != hex.rend(); ++it)
	{
		const char hexChar = std::tolower(*it);
		int hexCharValue = 0;
		
		if ((hexChar >= '0') && (hexChar <= '9'))
			hexCharValue = hexChar - '0';
		else if ((hexChar >= 'a') && (hexChar <= 'f'))
			hexCharValue = 10 + (hexChar - 'a');
		else
			throw std::invalid_argument{ "Valid hexadecimal characters: 0-9/a-f" };

		output += coeff * hexCharValue;
		coeff *= 16;
	}

	return output;
}

std::array<std::uint8_t, 32> big_endian_hex_to_u256(std::string_view hex)
{
	if (hex.size() != 64)
		throw std::invalid_argument{ "64 hexadecimal characters = 256 bits" };

	std::array<std::uint8_t, 32> output{};

	for (std::size_t index = 0; index < hex.size(); index += 2)
	{
		const char hexChar1 = std::tolower(hex[index]),
			hexChar2 = std::tolower(hex[index + 1]);
		std::uint8_t byteValue = 0;

		if ((hexChar1 >= '0') && (hexChar1 <= '9'))
			byteValue += 16 * (hexChar1 - '0');
		else if ((hexChar1 >= 'a') && (hexChar1 <= 'f'))
			byteValue += 16 * (10 + (hexChar1 - 'a'));
		else
			throw std::invalid_argument{ "Valid hexadecimal characters: 0-9/a-f" };

		if ((hexChar2 >= '0') && (hexChar2 <= '9'))
			byteValue += hexChar2 - '0';
		else if ((hexChar2 >= 'a') && (hexChar2 <= 'f'))
			byteValue += 10 + (hexChar2 - 'a');
		else
			throw std::invalid_argument{ "Valid hexadecimal characters: 0-9/a-f" };

		output[index / 2] = byteValue;
	}

	return output;
}