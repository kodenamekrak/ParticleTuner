#pragma once

#include "custom-types/shared/macros.hpp"
#include "bsml/shared/macros.hpp"
#include "bsml/shared/BSML/Components/Settings/ToggleSetting.hpp"
#include "bsml/shared/BSML/Components/Settings/IncrementSetting.hpp"
#include "HMUI/ViewController.hpp"

DECLARE_CLASS_CODEGEN(ParticleTuner, SettingsViewController, HMUI::ViewController) {
    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::FindMethodUnsafe("HMUI", "ViewController", "DidActivate", 3), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, ReduceCoreToggle);
    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, ReduceBombToggle);
    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, ReduceClashToggle);
    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, ReduceDustToggle);
    DECLARE_INSTANCE_FIELD(BSML::ToggleSetting*, RainbowToggle);

    DECLARE_INSTANCE_FIELD(BSML::IncrementSetting*, SparklesIncrement);
    DECLARE_INSTANCE_FIELD(BSML::IncrementSetting*, SparklesLifetimeIncrement);
    DECLARE_INSTANCE_FIELD(BSML::IncrementSetting*, ExplosionsIncrement);
    DECLARE_INSTANCE_FIELD(BSML::IncrementSetting*, ExplosionsLifetimeIncrement);
    DECLARE_INSTANCE_FIELD(BSML::IncrementSetting*, OpacityIncrement);

    DECLARE_INSTANCE_METHOD(void, ApplyConfig, bool reducedNoteParticles, bool reducedBombEffects, bool reducedClashEffects, bool reducedDustParticles, bool rainbowParticles, float sparklesMultiplier, float sparklesLifetimeMultiplier, float explosionsMultiplier, float explosionsLifetimeMultiplier, float particleOpacity);
    DECLARE_INSTANCE_METHOD(void, ApplyNone);
    DECLARE_INSTANCE_METHOD(void, ApplyNormal);
    DECLARE_INSTANCE_METHOD(void, ApplyFantasy);
    DECLARE_INSTANCE_METHOD(void, ApplyInsane);

    DECLARE_BSML_PROPERTY(bool, ReducedNoteParticles);
    DECLARE_BSML_PROPERTY(bool, ReducedBombCutEffects);
    DECLARE_BSML_PROPERTY(bool, ReducedClashEffects);
    DECLARE_BSML_PROPERTY(bool, ReducedDustParticles);
    DECLARE_BSML_PROPERTY(bool, RainbowParticles);

    DECLARE_BSML_PROPERTY(float, SparklesMultiplier);
    DECLARE_BSML_PROPERTY(float, SparklesLifetimeMultiplier);
    DECLARE_BSML_PROPERTY(float, ParticleOpacity);
    DECLARE_BSML_PROPERTY(float, ExplosionsMultiplier);
    DECLARE_BSML_PROPERTY(float, ExplosionsLifetimeMultiplier);
};
