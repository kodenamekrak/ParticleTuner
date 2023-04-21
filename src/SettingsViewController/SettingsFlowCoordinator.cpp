#include "main.hpp"
#include "SettingsViewController/SettingsFlowCoordinator.hpp"

#include "bsml/shared/BSML.hpp"
#include "bsml/shared/Helpers/creation.hpp"
#include "bsml/shared/Helpers/getters.hpp"

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
        SetTitle("ParticleTuner", HMUI::ViewController::AnimationType::In);
    }

    void SettingsFlowCoordinator::BackButtonWasPressed(HMUI::ViewController* topViewController)
    {
        this->parentFlowCoordinator->DismissFlowCoordinator(this, HMUI::ViewController::AnimationDirection::Horizontal, nullptr, false);
    }


    SettingsFlowCoordinator* SettingsFlowCoordinator::settingsFlowCoordinator;

    void SettingsFlowCoordinator::PresentFlow()
    {
        if (!settingsFlowCoordinator || !settingsFlowCoordinator->m_CachedPtr.m_value)
            settingsFlowCoordinator = BSML::Helpers::CreateFlowCoordinator<SettingsFlowCoordinator*>();
                
        auto parentFlow = BSML::Helpers::GetMainFlowCoordinator()->YoungestChildFlowCoordinatorOrSelf();
        parentFlow->PresentFlowCoordinator(settingsFlowCoordinator, nullptr, HMUI::ViewController::AnimationDirection::Horizontal, HMUI::ViewController::AnimationType::Out, false);
    }
}