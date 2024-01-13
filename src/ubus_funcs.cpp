#include "json.hpp"
#include "logger.hpp"

#include "ubus_funcs.hpp"

int ubus_get(const std::string& method, const std::string& msg, std::string& result) {

	std::cout << "called ubus_get with method " << method << std::endl;

	if ( !msg.empty()) {
		std::cout << "received message: " << msg << std::endl;

		json::JSON json_msg = json::JSON::Load(msg);
		if ( json_msg.size() != 0 )
			std::cout << "received json: " << json_msg << std::endl;
	}

	json::JSON answer;
	answer["ping"] = "pong";
	result = answer.dumpMinified();

	std::cout << "replying: " << answer << std::endl;

	return 0;
}

int ubus_list(const std::string& method, const std::string& msg, std::string& result) {
	std::cout << "called ubus_list with method " << method << std::endl;
	result = "{\"list\":[1,2,3,4,5]}";
	return 0;
}

int ubus_test(const std::string& method, const std::string& msg, std::string& result) {

	logger::vverbose << "called ubus_test with method " << method << std::endl;

	if ( !msg.empty()) {

		json::JSON json_msg = json::JSON::Load(msg);
		if ( json_msg.size() != 0 ) {
			std::cout << "received json: " << json_msg << std::endl;
			result = "{\"test\":" + json_msg.dumpMinified() + "}";
		} else result = "{\"test\":\"failed to get args\"}";
	} else result = "{\"test\":\"args missing\"}";

	std::cout << "replying: " << result << std::endl;

	return 0;
}
