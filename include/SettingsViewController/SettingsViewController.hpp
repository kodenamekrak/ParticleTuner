#pragma once
#include "custom-types/shared/macros.hpp"
#include "bsml/shared/macros.hpp"
#include "HMUI/ViewController.hpp"

DECLARE_CLASS_CODEGEN(ParticleTuner, SettingsViewController, HMUI::ViewController,
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
    
    DECLARE_BSML_PROPERTY(float, SparklesMultiplier);
    DECLARE_BSML_PROPERTY(float, ExplosionsMultiplier);
    DECLARE_BSML_PROPERTY(float, LifetimeMultiplier);
    DECLARE_BSML_PROPERTY(float, ParticleOpacity);
)