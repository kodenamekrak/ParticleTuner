#pragma once

#include "paper2_scotland2/shared/logger.hpp"

#define MOD_EXPORT __attribute__((visibility("default")))
#ifdef __cplusplus
#define MOD_EXPORT_FUNC extern "C" MOD_EXPORT
#else
#define MOD_EXPORT_FUNC MOD_EXPORT
#endif

inline constexpr auto Logger = Paper::ConstLoggerContext(MOD_ID "_" VERSION);
void SetDustActive(bool value);
