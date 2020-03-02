#ifndef UTILS_TCHAR_TSTRING_HPP
#define UTILS_TCHAR_TSTRING_HPP

#include <tchar.h>
#include <type_traits>
#include <string>
#include <string_view>

namespace jhack
{
	/*
	* Tstring: A simple wrapper for std::basic_string<TCHAR>
	* 
	* The purpose of this class is only to provide automatic conversion of the initial string,
	* according to the current TCHAR type. It means that you can construct a Tstring
	* from either a std::string or a std::wstring (or the corresponding litteral string).
	*/
	template <typename CharT = TCHAR, class = std::enable_if_t<std::is_same_v<CharT, TCHAR>>>
	class Tstring : public std::basic_string<CharT>
	{
	public:
		Tstring()
			: std::basic_string<CharT>()
		{}

		Tstring(std::wstring data)
		{
			if constexpr (std::is_same<CharT, wchar_t>::value)
				*dynamic_cast<std::basic_string<CharT>*>(this) = std::move(data);
			else if constexpr (std::is_same<CharT, char>::value)
			{
				this->resize(data.size());
				wcstombs(this->data(), data.c_str(), data.size());
			}
		}

		Tstring(std::string data)
		{
			if constexpr (std::is_same<CharT, wchar_t>::value)
			{
				this->resize(data.size());
				mbstowcs(this->data(), data.c_str(), data.size());
			}
			else if constexpr (std::is_same<CharT, char>::value)
				*dynamic_cast<std::basic_string<CharT>*>(this) = std::move(data);
		}

		Tstring(const wchar_t* data)
			: Tstring(std::wstring(data))
		{}
		Tstring(const char* data)
			: Tstring(std::string(data))
		{}


		friend std::basic_ostream<CharT>	&operator<<(std::basic_ostream<CharT> &os, const Tstring &str)
		{
			return os << dynamic_cast<const std::basic_string<CharT>&>(str);
		}

		friend std::basic_istream<CharT>	&operator>>(std::basic_istream<CharT> &is, Tstring &str)
		{
			return is >> dynamic_cast<std::basic_string<CharT>&>(str);
		}
	};


	// Tstring_view: a string_view with the TCHAR type.
	using Tstring_view = std::basic_string_view<TCHAR>;
}

#endif //UTILS_TCHAR_TSTRING_HPP