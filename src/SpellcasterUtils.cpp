#include "SpellcasterUtils.h"

std::string SpellcasterUtils::httpsGetRequest(std::string host, std::string path) {
    namespace http = boost::beast::http;
    
    boost::asio::io_context ioc;
    boost::asio::ssl::context ssl_ioc(boost::asio::ssl::context::sslv23_client);
    boost::asio::ip::tcp::resolver resolver(ioc);
    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket(ioc, ssl_ioc);
    boost::asio::ip::tcp::resolver::query query(host, "https");
    boost::asio::connect(socket.lowest_layer(), resolver.resolve(query));
    socket.lowest_layer().set_option(boost::asio::ip::tcp::no_delay(true));
    socket.handshake(boost::asio::ssl::stream_base::client);
    http::request<http::string_body> req(http::verb::get, path, 11);
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    http::write(socket, req);
    boost::beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(socket, buffer, res);
    std::cout << res << std::endl;
    //socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    //socket.close(boost::beast::websocket::close_code::normal);
    boost::system::error_code ec;
    socket.shutdown(ec);
    socket.lowest_layer().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    socket.lowest_layer().cancel(ec);
    socket.lowest_layer().close();
}

std::string SpellcasterUtils::getStringFromData(const std::string& data, const std::string search, const std::string& valueBegin, const std::string& valueEnd, int& pos, bool noChangePos) {
    //qDebug() << "QWarlockUtils::getStringFromData" << (Data.length() > 60 ? Data.left(60) : Data) << Search << ValueBegin << ValueEnd << Pos << NoChangePos;
    int old_pos = pos, idx1 = 0, idx2 = 0, idx3 = -1;
    if (pos == -1) {
        pos = 0;
    }
    do {
        idx1 = data.find_first_of(search, pos);
        if (idx1 == -1) {
            break;
        }
        idx1 += search.length();

        idx2 = valueBegin.empty() ? idx1 : data.find_first_of(valueBegin, idx1);
        if (idx2 == -1) {
            break;
        }

        idx2 += valueBegin.length();

        idx3 = -1;
        std::vector<std::string> ve;
        boost::split(ve, valueEnd, boost::is_any_of("#;#"));
        // QStringList ve = valueEnd.split("#;#");
        for(std::string v : ve) {
            int idx = data.find_first_of(v, idx2);
            if (idx == -1) {
                continue;
            }
            if ((idx3 == -1) || (idx < idx3)) {
                idx3 = idx;
            }
        }
        if (idx3 == -1) {
            idx3 = data.length();
        }
    } while (false);
    if (noChangePos) {
        pos = old_pos;
    }
    else {
        pos = idx3;
    }
    if (idx3 != -1) {
        std::string res = data.substr(idx2, idx3 - idx2);
        //qDebug() << "QWarlockUtils::getStringFromData" << idx1 << idx2 << idx3 << res;
        return res;
    }
    else {
        //qDebug() << "QWarlockUtils::getStringFromData not found" << idx1 << idx2 << idx3;
        return "";
    }
}

int SpellcasterUtils::getIntFromPlayerData(const std::string& data, const std::string search, const std::string& valueBegin, const std::string& valueEnd, int& pos, bool noChangePos) {
    return std::stoi(getStringFromData(data, search, valueBegin, valueEnd, pos, noChangePos));
}


bool SpellcasterUtils::isAI(const std::string& warlock) {
    std::string uppName = warlock;
    boost::to_upper(uppName);
    for (std::string s : _lstAI) {
        if (s.compare(uppName) == 0) {
            return true;
        }
    }

    return false;
}