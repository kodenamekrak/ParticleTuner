#include "main.hpp"
#include "ModConfig.hpp"
#include "SettingsViewController/UIManager.hpp"

#include "GlobalNamespace/NoteCutParticlesEffect.hpp"

#include "UnityEngine/Color32.hpp"
#include "UnityEngine/Color.hpp"
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

MAKE_HOOK_MATCH(NoteCutParticlesEffect_SpawnParticles, &GlobalNamespace::NoteCutParticlesEffect::SpawnParticles, void, GlobalNamespace::NoteCutParticlesEffect* self, UnityEngine::Vector3 cutPoint, UnityEngine::Vector3 cutNormal, UnityEngine::Vector3 saberDir, float saberSpeed, UnityEngine::Vector3 noteMovementVec, UnityEngine::Color32 color, int sparkleParticlesCount, int explosionParticlesCount, float lifetimeMultiplier)
{
    if(getModConfig().Enabled.GetValue())
    {

        getLogger().info("----PREHOOK----");
        getLogger().info("sparkleParticlesCount: %i", sparkleParticlesCount);
        getLogger().info("explosionParticlesCount: %i", explosionParticlesCount);
        getLogger().info("lifetimeMultiplier: %f", lifetimeMultiplier);
        getLogger().info("sparkleMaxParticles: %i", self->sparklesPS->get_main().get_maxParticles());
        getLogger().info("explosionMaxParticles: %i", self->explosionPS->get_main().get_maxParticles());

        sparkleParticlesCount = static_cast<int>(static_cast<float>(getModConfig().SparkleMultiplier.GetValue()) * sparkleParticlesCount);
        explosionParticlesCount = static_cast<int>(static_cast<float>(getModConfig().ExplosionMultiplier.GetValue()) * explosionParticlesCount);
        lifetimeMultiplier = getModConfig().SparkleLifetimeMultiplier.GetValue();

        auto sparkleMain = self->sparklesPS->get_main();
        sparkleMain.set_maxParticles(sparkleParticlesCount);

        auto explosionMain = self->explosionPS->get_main();
        explosionMain.set_maxParticles(explosionParticlesCount);
        explosionMain.set_startLifetime(getModConfig().ExplosionLifetimeMultiplier.GetValue() * 0.6f);

        if(getModConfig().RainbowParticles.GetValue())
        {
            color = RandomColorGen();
        }
        float newOpacity = 255.0f * getModConfig().ParticleOpacity.GetValue();
        color.a = static_cast<uint8_t>(std::clamp(newOpacity, 0.0f, 255.0f));

        getLogger().info("----POSTHOOK----");
        getLogger().info("sparkleParticlesCount: %i", sparkleParticlesCount);
        getLogger().info("explosionParticlesCount: %i", explosionParticlesCount);
        getLogger().info("lifetimeMultiplier: %f", lifetimeMultiplier);
        getLogger().info("maxParticles: %i", self->sparklesPS->get_main().get_maxParticles());
        getLogger().info("explosionMaxParticles: %i", self->explosionPS->get_main().get_maxParticles());
    }

    NoteCutParticlesEffect_SpawnParticles(self, cutPoint, cutNormal, saberDir, saberSpeed, noteMovementVec, color, sparkleParticlesCount, explosionParticlesCount, lifetimeMultiplier);
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
    getLogger().info("Installed all hooks!");
}