#include "main.hpp"
#include "ModConfig.hpp"
#include "SettingsViewController.hpp"

#include "GlobalNamespace/NoteCutParticlesEffect.hpp"
#include "GlobalNamespace/BombExplosionEffect.hpp"
#include "GlobalNamespace/SaberClashEffect.hpp"
#include "GlobalNamespace/SaberBurnMarkSparkles.hpp"
#include "GlobalNamespace/ObstacleSaberSparkleEffect.hpp"

#include "UnityEngine/Color32.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"
#include "UnityEngine/ParticleSystem.hpp"
#include "UnityEngine/Resources.hpp"

#include "sombrero/shared/FastColor.hpp"

#include "bsml/shared/BSML.hpp"

#include <random>

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

#define MAX_PARTICLES 2147483647

void SetDustActive(bool value)
{
    for(auto particle : UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::ParticleSystem*>())
    {
        if(particle->get_name() == "DustPS")
        {
            particle->get_emission().set_enabled(value);
        }
    }
}

UnityEngine::Color32 RandomColorGen()
{
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    float hue = dis(gen);
    float saturation = 1.0f;
    float value = 1.0f;

    Sombrero::FastColor color = Sombrero::FastColor::HSVToRGB(hue, saturation, value);
    return UnityEngine::Color32(0, color.r * 255, color.g * 255, color.b * 255, 0);
}

MAKE_HOOK_MATCH(SceneManager_SetActiveScene, &UnityEngine::SceneManagement::SceneManager::SetActiveScene, bool, UnityEngine::SceneManagement::Scene newActiveScene)
{
    bool result = SceneManager_SetActiveScene(newActiveScene);

    StringW sceneName = newActiveScene.name;
    if((sceneName == "MainMenu" || sceneName == "GameCore" ) && getModConfig().ReducedDustParticles.GetValue())
    {
        SetDustActive(false);
    }
    return result;
}

MAKE_HOOK_MATCH(BombExplosionEffect_SpawnExplosion, &GlobalNamespace::BombExplosionEffect::SpawnExplosion, void, GlobalNamespace::BombExplosionEffect* self, UnityEngine::Vector3 pos)
{
    if(getModConfig().ReducedBombCutEffects.GetValue())
    {
        self->_debrisCount = 0;
        self->_explosionParticlesCount = 0;
    }

    BombExplosionEffect_SpawnExplosion(self, pos);
}

MAKE_HOOK_MATCH(NoteCutParticlesEffect_SpawnParticles, &GlobalNamespace::NoteCutParticlesEffect::SpawnParticles, void, GlobalNamespace::NoteCutParticlesEffect* self, UnityEngine::Vector3 cutPoint, UnityEngine::Vector3 cutNormal, UnityEngine::Vector3 saberDir, float saberSpeed, UnityEngine::Vector3 noteMovementVec, UnityEngine::Color32 color, int sparkleParticlesCount, int explosionParticlesCount, float lifetimeMultiplier)
{
    if(getModConfig().ReducedNoteParticles.GetValue())
    {
        sparkleParticlesCount = 0;
        explosionParticlesCount = 0;
    }
    else
    {
        sparkleParticlesCount = static_cast<int>(static_cast<float>(getModConfig().SparklesMultiplier.GetValue()) * sparkleParticlesCount);
        explosionParticlesCount = static_cast<int>(static_cast<float>(getModConfig().ExplosionsMultiplier.GetValue()) * explosionParticlesCount);
        lifetimeMultiplier = getModConfig().SparklesLifetimeMultiplier.GetValue() * 0.5f;

        auto sparkleMain = self->_sparklesPS->get_main();
        sparkleMain.set_maxParticles(MAX_PARTICLES);

        auto explosionMain = self->_explosionPS->get_main();
        explosionMain.set_maxParticles(MAX_PARTICLES);
        explosionMain.set_startLifetime(UnityEngine::ParticleSystem::MinMaxCurve::op_Implicit___UnityEngine____ParticleSystem__MinMaxCurve(getModConfig().ExplosionsLifetimeMultiplier.GetValue() * 0.6f));

        if(getModConfig().RainbowParticles.GetValue())
        {
            color = RandomColorGen();
        }

        // Limit at 128 because the colour is just mostly white as you go higher
        float newOpacity = 128.0f * getModConfig().ParticleOpacity.GetValue();
        color.a = static_cast<uint8_t>(std::clamp(newOpacity, 0.0f, 128.0f));
    }

    NoteCutParticlesEffect_SpawnParticles(self, cutPoint, cutNormal, saberDir, saberSpeed, noteMovementVec, color, sparkleParticlesCount, explosionParticlesCount, lifetimeMultiplier);
}

MAKE_HOOK_MATCH(SaberClashEffect_Start, &GlobalNamespace::SaberClashEffect::Start, void, GlobalNamespace::SaberClashEffect *self)
{
    SaberClashEffect_Start(self);
    if(getModConfig().ReducedClashEffects.GetValue())
    {
        self->_sparkleParticleSystem->get_main().set_maxParticles(0);
        self->_glowParticleSystem->get_main().set_maxParticles(0);
    }
}

MAKE_HOOK_MATCH(SaberBurnMarkSparkles_Start, &GlobalNamespace::SaberBurnMarkSparkles::Start, void, GlobalNamespace::SaberBurnMarkSparkles *self)
{
    SaberBurnMarkSparkles_Start(self);
    if(getModConfig().ReducedClashEffects.GetValue())
    {
        self->_sparklesPS->get_main().set_maxParticles(0);

        for(auto ps : self->_burnMarksPS)
            ps->get_main().set_maxParticles(0);
    }
}

MAKE_HOOK_MATCH(ObstacleSaberSparkleEffect_Awake, &GlobalNamespace::ObstacleSaberSparkleEffect::Awake, void, GlobalNamespace::ObstacleSaberSparkleEffect *self)
{
    ObstacleSaberSparkleEffect_Awake(self);
    if(getModConfig().ReducedClashEffects.GetValue())
    {
        self->_sparkleParticleSystem->get_main().set_maxParticles(0);
        self->_burnParticleSystem->get_main().set_maxParticles(0);
    }
}

void setup(CModInfo* info) {
    *info = modInfo.to_c();

    INFO("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getModConfig().Init(modInfo);
    BSML::Init();
    BSML::Register::RegisterMainMenu<ParticleTuner::SettingsViewController*>("ParticleTuner", "ParticleTuner", "ParticleTuner mod settings");


    INFO("Installing hooks...");
    INSTALL_HOOK(Logger, NoteCutParticlesEffect_SpawnParticles);
    INSTALL_HOOK(Logger, BombExplosionEffect_SpawnExplosion);
    INSTALL_HOOK(Logger, SceneManager_SetActiveScene);
    INSTALL_HOOK(Logger, SaberClashEffect_Start);
    INSTALL_HOOK(Logger, SaberBurnMarkSparkles_Start);
    INSTALL_HOOK(Logger, ObstacleSaberSparkleEffect_Awake);
    INFO("Installed all hooks!");
}