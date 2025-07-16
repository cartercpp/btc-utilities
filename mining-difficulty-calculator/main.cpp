#include <iostream>
#include <format>
#include <limits>
#include <cstdint>

double bits_to_target(std::uint32_t) noexcept;
double bits_to_difficulty(std::uint32_t) noexcept;

int main()
{
	std::uint32_t bits;
	std::cout << "bits = ";
	std::cin >> bits;

	const double target = bits_to_target(bits),
		difficulty = bits_to_difficulty(bits);

	std::cout << std::format("target = {}\n", target);
	std::cout << std::format("difficulty = {}\n", difficulty);
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}
