#pragma once

#include "StandartImports.h"

namespace HTML
{
	using HTMLToStringTable = std::unordered_map<std::string, std::string>;

	std::string ReadStreamWithDecode(std::istream& input);
	std::string HtmlDecode(const std::string& html);
}