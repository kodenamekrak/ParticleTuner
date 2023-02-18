#include "main.hpp"
#include "SettingsViewController/SettingsFlowCoordinator.hpp"

#include "bsml/shared/BSML.hpp"

DEFINE_TYPE(ParticleTuner, SettingsFlowCoordinator);

namespace ParticleTuner {
    SettingsViewController* settingsViewController;

    void SettingsFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {}

    void SettingsFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController)
    {}
}