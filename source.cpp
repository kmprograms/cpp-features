#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>


// ---------------------------------------------------------------------------
// FOLD EXPRESSIONS
// https://en.cppreference.com/w/cpp/language/fold
// zapewnia wygodny syntax do operacji przeprowadzanych na elementach zawartych
// w parameter pack

// ---------------------------------------------------------------------------
// PARAMETER PACK
// https://en.cppreference.com/w/cpp/language/parameter_pack
// pozwala przechowac zero lub wiecej argumentow szablonowych (template arguments)
// ---------------------------------------------------------------------------

// ... op pack			redukcja od lewej do prawej
// pack ... op			redukcja od prawej do lewej
// init op ... op pack  redukcja od lewej do prawej z wartoscia poczatkowa
// pack op ... op init  redukcja od prawej do lewej z wartoscia poczatkowa

template<typename ...Args> 
auto sum(Args ...args)
{
	// std::cout << sum(1, 2, 3, 4) << std::endl;
	// return (args + ... + 0);
	// return (0 + ... + args);
	return (... + args);
}

template<typename T, typename ...Args>
auto add_all(std::vector<T>& v, Args ...args)
{
	(v.emplace_back(args), ...);
}

template <typename ...Args>
void print(Args&& ...args)
{
	(std::cout << ... << std::forward<Args>(args)) << std::endl;
}

struct Person
{
	std::string name;
	int age;

	operator int() const {
		return age;
	}
};

template<typename... Args>
bool all(Args... args) { return (... && args); }

void test_fold_expressions()
{
	std::cout << "-------------------" << std::endl;
	std::cout << sum(1, 2, 3, 4) << std::endl;
	std::cout << sum(11, 22.3) << std::endl;
	std::cout << sum(11, "ala") << std::endl;
	std::cout << sum(11, Person{"A", 10}) << std::endl;
	std::cout << "-------------------" << std::endl;

	std::vector<Person> people;
	Person p1{ "A", 10 };
	Person p2{ "B", 20 };
	Person p3{ "C", 30 };

	add_all(people, p1, p2, p3);
	std::for_each(
		people.begin(), 
		people.end(), 
		[](const auto& p) {std::cout << p.name << " " << p.age << std::endl; });

	print("A", ",", "B", ",", "C");

	std::cout << std::boolalpha << all(true, true, true) << std::endl;

}

// ----------------------------------------------------------------------------
// STD::FORWARD
// http://www.cplusplus.com/reference/utility/forward/
// ----------------------------------------------------------------------------
void forward_fun(const int& x)
{
	std::cout << "LV" << std::endl;
}

void forward_fun(int&& x)
{
	std::cout << "RV" << std::endl;
}

template <class T> 
void fun(T&& x)
{
	// forward_fun(x);

	// jezeli x jest referencja do lvalue to funkcja zwraca ta referencje
	// jezeli x jest referencja do rvalue zwraca argument, ktory bedzie przeazany jako rwartosc
	forward_fun(std::forward<T>(x));
}

void test_forward()
{
	int value;
	
	std::cout << "Call with lvalue:" << std::endl;
	fun(value);

	std::cout << "Call with rvalue:" << std::endl;
	fun(0);
}

int main()
{
	test_fold_expressions();
	// test_forward();
	return 0;
}