#include <iostream>
#include <thread>

#include "constants.hpp"
#include "speedtest_t.hpp"
#include "shared.hpp"
#include "signal.hpp"
#include "logger.hpp"
#include "loop.hpp"
#include "ubus.hpp"

speedtest_t *sp;

static void die_handler(int signum) {

	logger::info << "received " << Signal::string(signum == SIGINT ? SIGTERM : signum) << " signal" << std::endl;

	if ( !uloop_cancelled ) {
		logger::verbose << "stopping ubus service" << std::endl;
		uloop_end();
	}
}

int main(const int argc, const char **argv) {

	logger::output_level[logger::type::info] = true;
	logger::output_level[logger::type::error] = true;
	logger::output_level[logger::type::verbose] = true;
	logger::output_level[logger::type::vverbose] = true;
	logger::output_level[logger::type::debug] = true;

	sp = new speedtest_t;

	std::cout << "speedtest ubus" << std::endl;

	Signal::register_handler(die_handler);

	uloop_init();
	ctx = ubus_connect(ubus_socket == "" ? NULL : ubus_socket.c_str());

	if ( !ctx ) {
		logger::error << "failed to connect to ubus socket " << ubus_socket << std::endl;
		delete sp;
		return -1;
	}

	ubus_add_uloop(ctx);

	if ( int ret = ubus_create(); ret != 0 ) {
		ubus_free(ctx);
		delete sp;
		return(ret);
	}

	logger::verbose << "starting main loop" << std::endl;
	std::thread loop_thread(run_main_loop);

	logger::verbose << "starting ubus service" << std::endl;
	uloop_run();

	uloop_done();
	ubus_free(ctx);

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
