#pragma once

#include "ubus.hpp"

typedef enum {
	FIELD_CLIENT_IP = 0,
	FIELD_CLIENT_LAT,
	FIELD_CLIENT_LON,
	FIELD_CLIENT_ISP,
	FIELD_SERVER_ID,
	FIELD_SERVER_NAME,
	FIELD_SERVER_SPONSOR,
	FIELD_SERVER_DISTANCE,
	FIELD_SERVER_LATENCY,
	FIELD_SERVER_HOST,
	FIELD_RESULT_PING,
	FIELD_RESULT_JITTER,
	FIELD_RESULT_DOWNLOAD,
	FIELD_RESULT_DOWNLOAD_MB,
	FIELD_RESULT_UPLOAD,
	FIELD_RESULT_UPLOAD_MB,
	FIELD_RESULT_STATUS,
	FIELD_STATE,
	__FIELD_MAX
} field_type;

extern const struct blobmsg_policy st_policy[];

int st_policy_size(void);

int ubus_st_get(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg);

int ubus_st_list(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg);

int ubus_st_trigger(struct ubus_context *ctx, struct ubus_object *obj,
		struct ubus_request_data *req, const char *method,
		struct blob_attr *msg);
