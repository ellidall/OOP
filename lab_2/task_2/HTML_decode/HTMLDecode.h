#pragma once

#include "StandartImports.h"

namespace HTML
{
	std::string ReadStreamWithDecode(std::istream& input);
	std::string HtmlDecode(const std::string& html);
}