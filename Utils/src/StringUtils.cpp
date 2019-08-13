#include  "Utils/StringUtils.hpp"
#include <algorithm>

namespace Utils
{
	namespace StringUtils
	{
		std::string lowerCaseExceptFirstLetter(const std::string& str)
		{
			std::string strModified{ str };
			std::transform(strModified.begin(), strModified.end(), strModified.begin(), ::tolower);
			strModified[0] = toupper(strModified[0]);
			return strModified;
		}
	} // namespace StringUtils
} // namespace Utils

