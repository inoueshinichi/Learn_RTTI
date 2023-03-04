/**
 * @file mono_rtti_system.cpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

// Mono RTTI
// #include <mono_rtti.hpp>

// Mono inhereted entities
#include <mono_game_entity.hpp>
#include <mono_game_actor.hpp>
#include <mono_game_player.hpp>
#include <mono_game_legend_player.hpp>
#include <mono_game_enemy.hpp>
#include <mono_game_boss_enemy.hpp>
#include <mono_game_final_boss_enemy.hpp>
#include <mono_game_secret_boss_enemy.hpp>
#include <mono_game_camera.hpp>
#include <mono_game_fps_camera.hpp>

// Factory
#include <mono_game_entity_factory.hpp>

/**
 * @brief 単一継承型RTTIのテスト
 * 
 */


int main(int, char**)
{
    try
    {
        GameMonoEntityFactory factory;

        // Register
        std::cout << "Register" << std::endl;
        factory.Register<GameMonoEntity>(GameMonoEntity::GetClassName());
        factory.Register<GameMonoCamera>(GameMonoCamera::GetClassName());
        factory.Register<GameMonoFpsCamera>(GameMonoFpsCamera::GetClassName());
        factory.Register<GameMonoPlayer>(GameMonoPlayer::GetClassName());
        factory.Register<GameMonoLegendPlayer>(GameMonoLegendPlayer::GetClassName());
        factory.Register<GameMonoActor>(GameMonoActor::GetClassName());
        factory.Register<GameMonoEnemy>(GameMonoEnemy::GetClassName());
        factory.Register<GameMonoBossEnemy>(GameMonoBossEnemy::GetClassName());
        factory.Register<GameMonoFinalBossEnemy>(GameMonoFinalBossEnemy::GetClassName());
        factory.Register<GameMonoSecretBossEnemy>(GameMonoSecretBossEnemy::GetClassName());
        std::cout << std::endl;

        // Create
        std::cout << "Create" << std::endl;
        std::vector<std::shared_ptr<GameMonoEntity>> entities;
        entities.emplace_back(factory.CreateEntity("GameMonoEntity"));
        entities.emplace_back(factory.CreateEntity("GameMonoCamera"));
        entities.emplace_back(factory.CreateEntity("GameMonoFpsCamera"));
        entities.emplace_back(factory.CreateEntity("GameMonoPlayer"));
        entities.emplace_back(factory.CreateEntity("GameMonoLegendPlayer"));
        entities.emplace_back(factory.CreateEntity("GameMonoActor"));
        entities.emplace_back(factory.CreateEntity("GameMonoEnemy"));
        entities.emplace_back(factory.CreateEntity("GameMonoBossEnemy"));
        entities.emplace_back(factory.CreateEntity("GameMonoFinalBossEnemy"));
        entities.emplace_back(factory.CreateEntity("GameMonoSecretBossEnemy"));
        std::cout << std::endl;

        // RTTI
        std::cout << "[Check mono rtti system]" << std::endl;
        for (auto& sp : entities)
        {
            std::printf("%s : rtti address %p, rtti class-name %s\n", sp->GetObjectName(), (void*)&(sp->GetRtti()), sp->GetRtti().GetClassName().c_str());
        } 

        // Check class type with polymorphism
        std::cout << "[Check GameLegendPlayer type with polymorphism]" << std::endl;
        for (auto &sp : entities)
        {
            // sMonoRttiのアドレス直接比較
            if (&(sp->GetRtti()) == &(GameMonoLegendPlayer::sMonoRtti))
            {
                std::cout << sp->GetObjectName() << " : " << GameMonoLegendPlayer::GetClassName() << std::endl;
            }

            // MonoRttiのoperator==でアドレス比較をラッピング
            if (sp->GetRtti() == GameMonoBossEnemy::sMonoRtti)
            {
                std::cout << sp->GetObjectName() << " : " << GameMonoBossEnemy::GetClassName() << std::endl;
            }
        }

        // Check what from is GameSecretBossEnemy derived with polymorphism
        std::cout << "[Check what from is GameSecretBossEnemy derived with polymorphism]" << std::endl;
        std::shared_ptr<GameMonoSecretBossEnemy> spSecretBossEnemy;
        for (auto& sp : entities)
        {
            if (sp->GetRtti() == GameMonoSecretBossEnemy::sMonoRtti)
            {
                spSecretBossEnemy = std::static_pointer_cast<GameMonoSecretBossEnemy>(sp); // share
            }
        }
        for (auto& sp : entities)
        {
            if (spSecretBossEnemy->GetRtti().DerivedFrom(sp->GetRtti()))
            {
                std::cout << spSecretBossEnemy->GetObjectName() << " is derived from " << sp->GetRtti().GetClassName() << std::endl;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}