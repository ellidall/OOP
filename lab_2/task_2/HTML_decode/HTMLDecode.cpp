#include "HTMLDecode.h"

namespace HTML
{
	HTMLToStringTable htmlDecoder = {
		{ "&quot;", "\"" },
		{ "&apos;", "'" },
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&amp;", "&" }
	};

	std::string HtmlDecode(const std::string& html)
	{
		std::string result = html;
		size_t startPos = 0;
		size_t endPos = 0;
		while ((startPos = result.find('&', startPos)) != std::string::npos
			&& (endPos = result.find(';', startPos)) != std::string::npos)
		{
			std::string searchedString = result.substr(startPos, endPos - startPos + 1);
			auto record = htmlDecoder.find(searchedString);
			if (record != htmlDecoder.end())
			{
				result.replace(startPos, searchedString.length(), record->second);
				startPos += record->second.length();
			}
			else
			{
				++startPos;
			}
		}
		return result;
	}

	std::string ReadStreamWithDecode(std::istream& input)
	{
		std::string decodedText;
		std::string line;
		while (std::getline(input, line))
		{
			decodedText += HtmlDecode(line) + "\n";
		}
		if (decodedText.empty())
		{
			throw std::invalid_argument("Error: input string should not be empty");
		}
		if (!input.eof())
		{
			throw std::ios_base::failure("Error: stream is not fully read");
		}
		return decodedText;
	}
}
