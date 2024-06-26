#include "main.hpp"
#include "SettingsViewController.hpp"
#include "ModConfig.hpp"
#include "assets.hpp"

#include "bsml/shared/BSML.hpp"

DEFINE_TYPE(ParticleTuner, SettingsViewController);

#define DEFINE_BSML_PROPERTY(type, name) \
type SettingsViewController::get_##name() { return getModConfig().name.GetValue(); } \
void SettingsViewController::set_##name(type value) { getModConfig().name.SetValue(value); }

namespace ParticleTuner {

    void SettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if(!firstActivation)
            return;
        BSML::parse_and_construct(IncludedAssets::ModSettings_bsml, get_transform(), this);
    }

    void SettingsViewController::ApplyConfig(bool reducedNoteParticles, bool reducedBombEffects, bool reducedClashEffects, bool reducedDustParticles, bool rainbowParticles, float sparklesMultiplier, float sparklesLifetimeMultiplier, float explosionsMultiplier, float explosionsLifetimeMultiplier, float particleOpacity)
    {
        getModConfig().ReducedNoteParticles.SetValue(reducedNoteParticles);
        getModConfig().ReducedBombCutEffects.SetValue(reducedBombEffects);
        getModConfig().ReducedClashEffects.SetValue(reducedClashEffects);
        getModConfig().ReducedDustParticles.SetValue(reducedDustParticles);
        getModConfig().RainbowParticles.SetValue(rainbowParticles);
        getModConfig().SparklesMultiplier.SetValue(sparklesMultiplier);
        getModConfig().SparklesLifetimeMultiplier.SetValue(sparklesLifetimeMultiplier);
        getModConfig().ExplosionsMultiplier.SetValue(explosionsMultiplier);
        getModConfig().ExplosionsLifetimeMultiplier.SetValue(explosionsLifetimeMultiplier);
        getModConfig().ParticleOpacity.SetValue(particleOpacity);

        ReduceCoreToggle->set_Value(reducedNoteParticles);
        ReduceBombToggle->set_Value(reducedBombEffects);
        ReduceClashToggle->set_Value(reducedClashEffects);
        ReduceDustToggle->set_Value(reducedDustParticles);
        SetDustActive(!reducedDustParticles);
        RainbowToggle->set_Value(rainbowParticles);
        SparklesIncrement->set_Value(sparklesMultiplier);
        SparklesLifetimeIncrement->set_Value(sparklesLifetimeMultiplier);
        ExplosionsIncrement->set_Value(explosionsMultiplier);
        ExplosionsLifetimeIncrement->set_Value(explosionsLifetimeMultiplier);
        OpacityIncrement->set_Value(particleOpacity);
    }

    void SettingsViewController::ApplyNone()
    {
        INFO("Applying config 'None'");
        ApplyConfig(true, true, true, true, false, 0, 0, 0, 0, 0);
    }

    void SettingsViewController::ApplyNormal()
    {
        INFO("Applying config 'Normal'");
        ApplyConfig(false, false, false, false, false, 1, 1, 1, 1, 1);
    }

    void SettingsViewController::ApplyFantasy()
    {
        INFO("Applying config 'Fantasy'");
        ApplyConfig(false, false, false, true, true, 12, 2, 0.1f, 1, 1);
    }

    void SettingsViewController::ApplyInsane()
    {
        INFO("Applying config 'Insane'");
        ApplyConfig(false, false, false, false, true, 100, 10, 10, 10, 1);
    }

    DEFINE_BSML_PROPERTY(bool, ReducedNoteParticles);
    DEFINE_BSML_PROPERTY(bool, ReducedBombCutEffects);
    DEFINE_BSML_PROPERTY(bool, ReducedClashEffects);
    DEFINE_BSML_PROPERTY(bool, RainbowParticles);

    bool SettingsViewController::get_ReducedDustParticles() { return getModConfig().ReducedDustParticles.GetValue(); }
    void SettingsViewController::set_ReducedDustParticles(bool value) { getModConfig().ReducedDustParticles.SetValue(value); SetDustActive(!value); }

    DEFINE_BSML_PROPERTY(float, SparklesMultiplier);
    DEFINE_BSML_PROPERTY(float, SparklesLifetimeMultiplier);
    DEFINE_BSML_PROPERTY(float, ParticleOpacity);
    DEFINE_BSML_PROPERTY(float, ExplosionsMultiplier);
    DEFINE_BSML_PROPERTY(float, ExplosionsLifetimeMultiplier);
}