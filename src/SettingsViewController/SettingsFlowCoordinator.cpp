#include "main.hpp"
#include "SettingsViewController/SettingsFlowCoordinator.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/Helpers/creation.hpp"
#include "HMUI/ViewController_AnimationDirection.hpp"
#include "HMUI/ViewController_AnimationType.hpp"

DEFINE_TYPE(ParticleTuner, SettingsFlowCoordinator);

namespace ParticleTuner {
    
    void SettingsFlowCoordinator::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (!firstActivation)
            return;
        settingsViewController = BSML::Helpers::CreateViewController<ParticleTuner::SettingsViewController *>();

        showBackButton = true;
        ProvideInitialViewControllers(settingsViewController, nullptr, nullptr, nullptr, nullptr);
        SetTitle("Particle Tuner", HMUI::ViewController::AnimationType::In);
    }

    void SettingsFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController)
    {
        this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
    }
}