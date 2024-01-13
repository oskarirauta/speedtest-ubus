#pragma once

#include <mutex>

#include "speedtest_t.hpp"

extern speedtest_t *sp;
extern std::mutex sp_mutex;

void st_update(void);
