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