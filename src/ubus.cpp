#include "constants.hpp"
#include "logger.hpp"
#include "ubus_funcs.hpp"
#include "ubus.hpp"

std::string ubus_socket = "";
struct ubus_context *ctx;

#ifndef b
struct blob_buf b;
#endif

static const struct ubus_method st_methods[] = {
	{ .name = "get", .handler = ubus_st_get },
	{ .name = "list", .handler = ubus_st_list },
        { .name = "trigger", .handler = ubus_st_trigger },
};

static struct ubus_object_type st_object_type = {
        .name = "network.speedtest",
        .id = 0,
        .methods = st_methods,
        .n_methods = ARRAY_SIZE(st_methods),
};

static struct ubus_object st_object = {
        .name = "network.speedtest",
        .type = &st_object_type,
        .methods = st_methods,
        .n_methods = ARRAY_SIZE(st_methods),
};


int ubus_create(void) {

	if ( int ret = ubus_add_object(ctx, &st_object); ret != 0 ) {
		logger::error << "failed to register network.speedtest ubus object" << std::endl;
		logger::debug << "error: " << ubus_strerror(ret) << std::endl;
		return ret;
	}

	return 0;
}
