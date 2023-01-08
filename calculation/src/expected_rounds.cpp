#include <iostream>
#include <cmath>

constexpr auto p = 18.0 / 37.0;
constexpr auto q = 12.0 / 37.0;
constexpr auto c = 1.0 / (1.0 - (1.0 - p) * q);

#define pow_2(n) (1 << (n))
#define pow_4(n) std::pow(4, n)

double solve_one_chip(const int n, const int d)
{
	if ((n - d) < 0)
		return 0;
	return 1 + (1 - p) * solve_one_chip(n - d, 2 * d);
}

void one_chip(const int n, const int d)
{
	const auto budget = (pow_2(n) - 1) * d;
	std::cout << "The budget with one bet is $" << budget << std::endl; 
	const auto expected_rounds = solve_one_chip(budget, d);
	std::cout << "The expected rounds is " << expected_rounds << std::endl;
}

double solve_two_chips(const int n, const int d, const int d0)
{
	if ((n - 3 * d) < 0)
		return 0;
	const auto sub_solution = solve_two_chips(n - 3 * d, 4 * d, d0);
	if (d == d0)
		return 1 + (1 - p) * (1 - q) * sub_solution;
	else
		return c + (1.0 - p / c) * sub_solution;
}

void two_chips(const int n, const int d)
{
	const auto budget = (pow_4(n) - 1) * d;
	std::cout << "The budget with two bets is $" << budget << std::endl; 
	const auto expected_rounds = solve_two_chips(budget, d, d);
	std::cout << "The expected rounds is " << expected_rounds << std::endl;
}

int main()
{
	int n, d;
	do
	{
		std::cout << "Enter the number of maximum rounds you want to play (0 to quit): " << std::flush;
		std::cin >> n;
		if (n == 0)
			break;
		std::cout << "Enter the targeted profit: " << std::flush;
		std::cin >> d;
		one_chip(n , d);
		two_chips(n, d);
	} while(true);
}
