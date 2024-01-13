#include <thread>

#include "config.hpp"
#include "logger.hpp"
#include "ubus.hpp"
#include "loop.hpp"

#include <iostream>

const std::chrono::seconds get_seconds() {

	return std::chrono::duration_cast<std::chrono::seconds>
		(std::chrono::system_clock::now().time_since_epoch());
}

bool Loop::sig_exit(void) {

	std::lock_guard<std::mutex> guard(this -> sig_mutex);
	return this -> _sig_exit;
}

bool Loop::running(void) {

	std::lock_guard<std::mutex> guard(this -> sig_mutex);
	return this -> _running;
}

int Loop::delay(void) {

	std::lock_guard<std::mutex> guard(this -> sig_mutex);
	return this -> _delay;
}

void Loop::set_sig_exit(bool state) {

	std::lock_guard<std::mutex> guard(this -> sig_mutex);
	this -> _sig_exit = state;
}

void Loop::set_running(bool state) {

	std::lock_guard<std::mutex> guard(this -> sig_mutex);
	this -> _running = state;
}

void Loop::set_delay(int delay) {

	std::lock_guard<std::mutex> guard(this -> sig_mutex);
	this -> _delay = delay;
}

void Loop::sleep(int ms) {

	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void Loop::run(void) {

	if ( this -> running())
		return;

	this -> set_running(true);
	int __delay = this -> delay();
	//int counter = 0;

	this -> sleep((int)(__delay * 0.5));

	this -> _next_cycle = get_seconds() + std::chrono::seconds(config::initial_cycle == 0 ?
						config::cycle_interval : config::initial_cycle);
	config::initial_cycle = 0;

	this -> sleep((int)(__delay * 0.5));

	while ( !this -> sig_exit()) {

		if ( get_seconds() > this -> _next_cycle ) {
//		if ( ++counter == 20000 ) {

			logger::vverbose << "cycle counter triggered" << std::endl;
//			counter = 0;

			if ( !this -> trigger_speedtest ) {

				logger::vverbose << "reachability test begins" << std::endl;

				this -> trigger_speedtest = true;
				this -> _next_cycle = get_seconds() + std::chrono::seconds(3);

			} else {

				logger::vverbose << "speedtest begins" << std::endl;

				this -> trigger_speedtest = false;
				this -> _next_cycle = get_seconds() + std::chrono::seconds(config::cycle_interval);
			}
		}

		this -> sleep(__delay);
	}

	this -> set_running(false);

}

Loop main_loop;

void run_main_loop(void) {
	main_loop.run();
}
