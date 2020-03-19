#ifndef EASY_INPUT_H_
#define EASY_INPUT_H_

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <limits>
#include <type_traits>

template <typename T0, typename ... Ts>
std::ostream& operator<< (std::ostream& s, std::variant<T0, Ts...> const& v)
{
	std::visit([&](auto&& arg) { s << arg; }, v); return s;
	//https://stackoverflow.com/a/47168851/8964221
}

template <typename T0, typename ... Ts>
void assign(T0& s, std::variant<Ts...> const& v)
{
	s = std::get<T0>(v);
}

template <typename TInput>
class easy_input final {
private:

	template <typename T, typename lambda>
	T input_getter(lambda t) {
		T ret_val;
		do {
			if (std::cin.fail())
				std::cout << "Wrong Input Try Again!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			ret_val = t();
		} while (std::cin.fail());
		return ret_val;
	}

public:
	TInput user_input;
	std::vector<std::variant<
		int, float, bool,
		double, char, std::string,
		short int, unsigned short int, unsigned int,
		long int, unsigned long int, long long int,
		unsigned long long int, unsigned char, long double
		>> values;
	const std::string output;

	easy_input(std::string _output) : output(_output) { }

	template<typename T>
	easy_input<TInput> operator+ (easy_input<T> source)
	{
		std::string temp;

		std::cout << "Input type: " << typeid(source.user_input).name() << std::endl
			<< source.output << std::endl;
		auto s = static_cast<T>(source.user_input);

		if constexpr (std::is_same<T, bool>::value) {
			s = input_getter<T>([]() { T s; std::cin >> std::boolalpha >> s; return s; });
			std::cout << "Eingabe: " << std::boolalpha << s << std::endl;
		}
		else if constexpr ( std::is_same<T, std::string>::value) {
			s = input_getter<std::string>([]() { std::string var; std::getline(std::cin, var); return var; });
			std::cout << "Eingabe: " << s << std::endl;
		}
		else {
			s = input_getter<T>([]() { T s; std::cin >> s; return s; });
			std::cout << "Eingabe: " << s << std::endl;
		}

		if (std::is_same<T, std::string>::value)
			source.values.push_back(temp);
		else
			source.values.push_back(s);


		this->values.insert(this->values.end(), source.values.begin(), source.values.end());

		return *this;
	}

	void print() {
		for (auto& print : this->values) {
			std::cout << print << std::endl;
		}
	}

	template <typename T>
	void assign_var(size_t index, T& var) {
		assign(var, this->values[index]);
	}
};

#define input(type,console_output) easy_input<type>(console_output)
#define sum(name) easy_input<int> name = easy_input<int>("empty") //UGLY

#endif