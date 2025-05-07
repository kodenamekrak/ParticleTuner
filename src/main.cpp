#include "main.hpp"

#include "scotland2/shared/modloader.h"
#include "autohooks/shared/hooks.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "bsml/shared/BSML.hpp"

#include "modInfo.hpp"
#include "ModConfig.hpp"
#include "SettingsViewController.hpp"

#include "UnityEngine/ParticleSystem.hpp"
#include "UnityEngine/Resources.hpp"

void SetDustActive(bool value) {
    for (auto particle : UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::ParticleSystem*>()) {
        if (particle->get_name() == "DustPS") {
            particle->get_emission().set_enabled(value);
        }
    }
}

/// @brief Called at the early stages of game loading
/// @param info The mod info.  Update this with your mod's info.
/// @return
MOD_EXPORT_FUNC void setup(CModInfo& info) {
    info = modInfo.to_c();

    Logger.info("Completed setup!");
}

/// @brief Called later on in the game loading - a good time to install function hooks
/// @return
MOD_EXPORT_FUNC void late_load() {
    il2cpp_functions::Init();

    getModConfig().Init(modInfo);

    custom_types::Register::AutoRegister();

    BSML::Init();
    BSML::Register::RegisterMainMenu<ParticleTuner::SettingsViewController*>("ParticleTuner", "ParticleTuner", "ParticleTuner mod settings");

    auto lateHookCount = LATE_HOOK_COUNT;
    if (lateHookCount > 0) {
        Logger.info("Installing {} late hook{}", lateHookCount, lateHookCount > 1 ? "s" : "");
        INSTALL_LATE_HOOKS();
        Logger.info("Finished installing late hook{}", lateHookCount == 0 || lateHookCount > 1 ? "s" : "");
    }
}
