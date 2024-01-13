#include <iostream>
#include <thread>

#include "constants.hpp"
#include "speedtest_t.hpp"
#include "shared.hpp"
#include "signal.hpp"
#include "logger.hpp"
#include "loop.hpp"
#include "ubus.hpp"
#include "ubus_funcs.hpp"

speedtest_t *sp;
std::mutex sp_mutex;

static void die_handler(int signum) {

	if ( logger::log_level >= logger::verbose.id())
		logger::info << "received " << Signal::string(signum) << " signal" << std::endl;
	else logger::info << "received TERM signal" << std::endl;

	if ( !uloop_cancelled ) {
		logger::verbose << "stopping ubus service" << std::endl;
		uloop_end();
	}
}

int main(const int argc, const char **argv) {

	logger::loglevel(logger::debug);

	sp = new speedtest_t;

	std::cout << "speedtest ubus" << std::endl;

	Signal::register_handler(die_handler);

	uloop_init();
	ubus::service *srv;

	try {
		srv = new ubus::service;
	} catch ( ubus::exception &e ) {
		logger::error << e.what() << std::endl;
		delete sp;
		return e.code();
	}

	try {
		srv -> add_object("network.speedtest", {

			UBUS_HANDLER("test", ubus_test),
			UBUS_HANDLER("get", ubus_get),
			UBUS_HANDLER("list", ubus_list),
		});

	} catch ( ubus::exception &e ) {
		logger::error << "failed to add ubus object: " <<
				e.what() << " (code " << e.code() << ")" << std::endl;
		delete sp;
		return e.code();
	}

	logger::verbose << "starting main loop" << std::endl;
	std::thread loop_thread(run_main_loop);

	logger::verbose << "starting ubus service" << std::endl;
	uloop_run();

	uloop_done();
	delete srv;

	logger::verbose << "ubus service has stopped" << std::endl;
	logger::vverbose << "exiting main loop" << std::endl;

	main_loop.set_sig_exit(true);

	while ( main_loop.running())
		std::this_thread::sleep_for(std::chrono::milliseconds(SIG_DELAY));

	logger::vverbose << "main loop stopped" << std::endl;

	loop_thread.join();

	delete sp;
	logger::vverbose << "exiting" << std::endl;

	return 0;
}
