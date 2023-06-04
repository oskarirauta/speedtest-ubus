#pragma once

#include <string>

struct client_t {

	public:
		std::string ip, isp, country;
		float lat, lon;

};

struct server_t {

	public:
		std::string name, sponsor, host, country, country_code;
		float lat, lon, distance;
		int id = -1;
		long latency = -1;
		bool recommended;

};

struct results_t {

	public:
		int ping = -1;
		int jitter = -1;
		long latency = -1;
		double download = -1;
		double upload = -1;
		unsigned long received = 0;
		unsigned long sent = 0;

};

struct speedtest_t {

	public:
		client_t *client;
		server_t *server;
		results_t *results;

		speedtest_t() {

			this -> client = new client_t;
			this -> server = new server_t;
			this -> results = new results_t;
		}

		~speedtest_t() {

			delete this -> client;
			delete this -> server;
			delete this -> results;
		}

};
