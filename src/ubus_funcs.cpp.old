#include "ubus_funcs.hpp"

const struct blobmsg_policy st_policy[] = {
	[FIELD_CLIENT_IP] = { .name = "ipaddr", .type = BLOBMSG_TYPE_STRING },
	[FIELD_CLIENT_LAT] = { .name = "lat", .type = BLOBMSG_TYPE_STRING },
	[FIELD_CLIENT_LON] = { .name = "lon", .type = BLOBMSG_TYPE_STRING },
	[FIELD_CLIENT_ISP] = { .name = "isp", .type = BLOBMSG_TYPE_STRING },
	[FIELD_SERVER_ID] = { .name = "server_id", .type = BLOBMSG_TYPE_INT16 },
	[FIELD_SERVER_NAME] = { .name = "server_name", .type = BLOBMSG_TYPE_STRING },
	[FIELD_SERVER_SPONSOR] = { .name = "server_sponsor", .type = BLOBMSG_TYPE_STRING },
	[FIELD_SERVER_DISTANCE] = { .name = "server_distance", .type = BLOBMSG_TYPE_INT16 },
	[FIELD_SERVER_LATENCY] = { .name = "server_latency", .type = BLOBMSG_TYPE_INT16 },
	[FIELD_SERVER_HOST] = { .name = "server_host", .type = BLOBMSG_TYPE_STRING },
	[FIELD_RESULT_PING] = { .name = "result_ping", .type = BLOBMSG_TYPE_INT16 },
	[FIELD_RESULT_JITTER] = { .name = "result_jitter", .type = BLOBMSG_TYPE_INT16 },
	[FIELD_RESULT_DOWNLOAD] = { .name = "result_download", .type = BLOBMSG_TYPE_INT16 },
	[FIELD_RESULT_DOWNLOAD_MB] = { .name = "result_download_mb", .type = BLOBMSG_TYPE_INT16 },
	[FIELD_RESULT_UPLOAD] = { .name = "result_upload", .type = BLOBMSG_TYPE_INT16 },
	[FIELD_RESULT_UPLOAD_MB] = { .name = "result_upload_mb", .type = BLOBMSG_TYPE_INT16 },
	[FIELD_RESULT_STATUS] = { .name = "result_status", .type = BLOBMSG_TYPE_STRING },
	[FIELD_STATE] = { .name = "state", .type = BLOBMSG_TYPE_STRING },	
};

int st_policy_size(void) {
	return ARRAY_SIZE(st_policy);
}

int ubus_st_get(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg) {

	return 0;
}

int ubus_st_list(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg) {

	return 0;
}

int ubus_st_trigger(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg) {

	return 0;
}
