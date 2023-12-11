#ifndef SPELLCASTERUTILS_H
#define SPELLCASTERUTILS_H

//#include <boost/beast/root_certificates.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>

#include "Constants.h"

class SpellcasterUtils
{
public:
	// http
	static std::string httpsGetRequest(std::string host, std::string path);

	// pasing
	static std::string getStringFromData(const std::string& data, const std::string search, const std::string& valueBegin, const std::string& valueEnd, int& pos, bool noChangePos = false);
	static int getIntFromPlayerData(const std::string& data, const std::string search, const std::string& valueBegin, const std::string& valueEnd, int& pos, bool noChangePos = false);

	// login
	static bool isAI(const std::string& warlock);
};

#endif 
