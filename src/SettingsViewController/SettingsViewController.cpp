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

    float SettingsViewController::get_sparkleTest() { return getModConfig().SparkleMultiplier.GetValue(); }
    void SettingsViewController::set_sparkleTest(float value) { getModConfig().SparkleMultiplier.SetValue(value); }
}