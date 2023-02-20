#include "main.hpp"
#include "SettingsViewController/SettingsViewController.hpp"
#include "ModConfig.hpp"
#include "assets.hpp"

#include "bsml/shared/BSML.hpp"

DEFINE_TYPE(ParticleTuner, SettingsViewController);

namespace ParticleTuner {

    void SettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        getLogger().info("Parsing BSML to ViewController...");
        BSML::parse_and_construct(IncludedAssets::ModSettings_bsml, get_transform(), this);
        getLogger().info("Parsed BSML!");
    }

    float SettingsViewController::get_SparklesMultiplier() { return getModConfig().SparkleMultiplier.GetValue(); }
    void SettingsViewController::set_SparklesMultiplier(float value) { getModConfig().SparkleMultiplier.SetValue(value); }
    float SettingsViewController::get_ExplosionsMultiplier() { return getModConfig().ExplosionMultiplier.GetValue(); }
    void SettingsViewController::set_ExplosionsMultiplier(float value) { getModConfig().ExplosionMultiplier.GetValue(); }
    float SettingsViewController::get_LifetimeMultiplier() { return getModConfig().SparkleLifetimeMultiplier.GetValue(); }
    void SettingsViewController::set_LifetimeMultiplier(float value) { getModConfig().SparkleLifetimeMultiplier.SetValue(value); }
    float SettingsViewController::get_ParticleOpacity() { return getModConfig().ParticleOpacity.GetValue(); }
    void SettingsViewController::set_ParticleOpacity(float value) { getModConfig().ParticleOpacity.SetValue(value); }
}