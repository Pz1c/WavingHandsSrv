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
#include <iostream>

class SpellcasterUtils
{
public:
	static std::string httpsGetRequest(std::string host, std::string path);
};

#endif 
