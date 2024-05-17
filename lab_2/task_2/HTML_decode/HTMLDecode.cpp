#include "HTMLDecode.h"

namespace HTML
{
	using HTMLToStringTable = std::map<std::string, std::string>;
	
	const HTMLToStringTable htmlDecoder = {
		{ "&quot;", "\"" },
		{ "&apos;", "'" },
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&amp;", "&" }
	};

	size_t GetDecoderMaxKeyLength()
	{
		size_t maxKeyLength = 0;
		for (const auto& record : htmlDecoder)
		{
			if (record.first.length() > maxKeyLength)
			{
				maxKeyLength = record.first.length();
			}
		}
		return maxKeyLength;
	}

	const size_t MAX_DECODER_KEY_LENGTH = GetDecoderMaxKeyLength();

	std::string HtmlDecode(const std::string& html)
	{
		std::string result;

		for (size_t i = 0; i < html.size(); ++i)
		{
			if (html[i] != '&')
			{
				result += html[i];
				continue;
			}
			bool isFound = false;
			for (const auto& record : htmlDecoder)
			{
				if (!html.compare(i, record.first.size(), record.first))
				{
					result += record.second;
					i += record.first.size() - 1;
					isFound = true;
					break;
				}
			}
			if (!isFound) 
				result += html[i];
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
		if (!input.eof())
		{
			throw std::ios_base::failure("Error: stream is not fully read");
		}
		return decodedText;
	}
}
