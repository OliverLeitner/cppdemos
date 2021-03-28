/**
 * http server
 */
#include <httpserver.hpp>
#include "mysql_select.hpp" // mysql functionality

using namespace httpserver;

class hello_world_resource : public http_resource {
public:
    /*const std::shared_ptr<http_response> render(const http_request&) {
        return std::shared_ptr<http_response>(new string_response("Hello, World!"));
    }*/
    const std::shared_ptr<http_response> render_GET(const http_request&) {
        return std::shared_ptr<http_response>(new string_response(getCustomerData(), 200, "application/json;charset=latin1"));
    }
    const std::shared_ptr<http_response> render(const http_request&) {
        return std::shared_ptr<http_response>(new string_response("OTHER: Hello, World!"));
    }
};

int main(int argc, char** argv) {
    webserver ws = create_webserver(8080)
        .no_ssl()
        .no_ipv6()
        // .no_debug()
        .no_pedantic()
        // .no_basic_auth()
        // .no_digest_auth()
        .no_regex_checking()
        .no_ban_system()
        .no_post_process();

    hello_world_resource hwr;
    ws.register_resource("/hello", &hwr); // basic routing
    ws.start(true);

    return 0;
}
