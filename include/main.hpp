#pragma once

// Include the modloader header, which allows us to tell the modloader which mod this is, and the version etc.
#include "scotland2/shared/loader.hpp"

// beatsaber-hook is a modding framework that lets us call functions and fetch field values from in the game
// It also allows creating objects, configuration, and importantly, hooking methods to modify their values
#include "beatsaber-hook/shared/api.hpp"
#include "beatsaber-hook/shared/hooking.hpp"
#include "paper2_scotland2/shared/logger.hpp"

static constexpr auto Logger = Paper::ConstLoggerContext("ParticleTuner");
#define INFO(message, ...) Logger.info(message, ## __VA_ARGS__)

void SetDustActive(bool value);