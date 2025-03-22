#include <iostream>
#include "httplib.h"

int main()
{

	httplib::Client cli("localhost", 8090);

	auto res = cli.Get("/chat/getAllMessages");

	if (res) {
		std::cout << "Status Code: " << res->status << std::endl;
		std::cout << "Response Body: " << res->body << std::endl;
	}
	else {
		std::cout << "Request Failed" << std::endl;
	}

	return 0;
}