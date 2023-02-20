#include "main.hpp"
#include "ModConfig.hpp"
#include "SettingsViewController/UIManager.hpp"
#include "Dust.hpp"

#include "GlobalNamespace/NoteCutParticlesEffect.hpp"
#include "GlobalNamespace/BombExplosionEffect.hpp"
#include "GlobalNamespace/SaberClashEffect.hpp"

#include "UnityEngine/Color32.hpp"
#include "UnityEngine/ParticleSystem.hpp"
#include "UnityEngine/ParticleSystem_MainModule.hpp"

#include "sombrero/shared/FastColor.hpp"

#include <iostream>
#include <cstdlib>
#include <random>

static ModInfo modInfo;

UnityEngine::Color32 RandomColorGen()
{
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    float hue = dis(gen);
    float saturation = 1.0f;
    float value = 1.0f;

    Sombrero::FastColor color = Sombrero::FastColor::HSVToRGB(hue, saturation, value);
    return UnityEngine::Color32(color.r * 255, color.g * 255, color.b * 255);
}

MAKE_HOOK_MATCH(SceneManager_SetActiveScene, &UnityEngine::SceneManagement::SceneManager::SetActiveScene, bool, UnityEngine::SceneManagement::Scene newActiveScene)
{
    bool result = SceneManager_SetActiveScene(newActiveScene);

    std::string sceneName = newActiveScene.get_name();

    if((sceneName == "MainMenu" || sceneName == "GameCore" ) && getModConfig().ReducedDustParticles.GetValue())
    {
        
    }
    
    return result;
}

MAKE_HOOK_MATCH(BombExplosionEffect_SpawnExplosion, &GlobalNamespace::BombExplosionEffect::SpawnExplosion, void, GlobalNamespace::BombExplosionEffect* self, UnityEngine::Vector3 pos)
{
    if(getModConfig().ReducedBombCutEffects.GetValue())
    {
        self->debrisCount = 0;
        self->explosionParticlesCount = 0;
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

        auto sparkleMain = self->sparklesPS->get_main();
        sparkleMain.set_maxParticles(sparkleParticlesCount);

        auto explosionMain = self->explosionPS->get_main();
        explosionMain.set_maxParticles(explosionParticlesCount);
        explosionMain.set_startLifetime(getModConfig().ExplosionsLifetimeMultiplier.GetValue() * 0.6f);

        if(getModConfig().RainbowParticles.GetValue())
        {
            color = RandomColorGen();
        }
        float newOpacity = 255.0f * getModConfig().ParticleOpacity.GetValue();
        color.a = static_cast<uint8_t>(std::clamp(newOpacity, 0.0f, 255.0f));
    }

    NoteCutParticlesEffect_SpawnParticles(self, cutPoint, cutNormal, saberDir, saberSpeed, noteMovementVec, color, sparkleParticlesCount, explosionParticlesCount, lifetimeMultiplier);
}

MAKE_HOOK_MATCH(SaberClashEffect_Start, &GlobalNamespace::SaberClashEffect::Start, void, GlobalNamespace::SaberClashEffect *self)
{
    if(getModConfig().ReducedClashEffects.GetValue())
    {
        self->sparkleParticleSystem->get_gameObject()->SetActive(false);
        self->glowParticleSystem->get_gameObject()->SetActive(false);
    }
    SaberClashEffect_Start(self); 
}

Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load();
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getModConfig().Init(modInfo);
    BSML::Init();
    ParticleTuner::manager.Init();


    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), NoteCutParticlesEffect_SpawnParticles);
    INSTALL_HOOK(getLogger(), BombExplosionEffect_SpawnExplosion);
    INSTALL_HOOK(getLogger(), SceneManager_SetActiveScene);
    INSTALL_HOOK(getLogger(), SaberClashEffect_Start);
    getLogger().info("Installed all hooks!");
}