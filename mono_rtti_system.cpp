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
        factory.Register<GameEntity>(GameEntity::GetClassName());
        factory.Register<GameCamera>(GameCamera::GetClassName());
        factory.Register<GameFpsCamera>(GameFpsCamera::GetClassName());
        factory.Register<GamePlayer>(GamePlayer::GetClassName());
        factory.Register<GameLegendPlayer>(GameLegendPlayer::GetClassName());
        factory.Register<GameActor>(GameActor::GetClassName());
        factory.Register<GameEnemy>(GameEnemy::GetClassName());
        factory.Register<GameBossEnemy>(GameBossEnemy::GetClassName());
        factory.Register<GameFinalBossEnemy>(GameFinalBossEnemy::GetClassName());
        factory.Register<GameSecretBossEnemy>(GameSecretBossEnemy::GetClassName());
        std::cout << std::endl;

        // Create
        std::cout << "Create" << std::endl;
        std::vector<std::shared_ptr<GameEntity>> entities;
        entities.emplace_back(factory.CreateEntity("GameEntity"));
        entities.emplace_back(factory.CreateEntity("GameCamera"));
        entities.emplace_back(factory.CreateEntity("GameFpsCamera"));
        entities.emplace_back(factory.CreateEntity("GamePlayer"));
        entities.emplace_back(factory.CreateEntity("GameLegendPlayer"));
        entities.emplace_back(factory.CreateEntity("GameActor"));
        entities.emplace_back(factory.CreateEntity("GameEnemy"));
        entities.emplace_back(factory.CreateEntity("GameBossEnemy"));
        entities.emplace_back(factory.CreateEntity("GameFinalBossEnemy"));
        entities.emplace_back(factory.CreateEntity("GameSecretBossEnemy"));
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
            if (&(sp->GetRtti()) == &(GameLegendPlayer::sMonoRtti))
            {
                std::cout << sp->GetObjectName() << " : " << GameLegendPlayer::GetClassName() << std::endl;
            }

            // MonoRttiのoperator==でアドレス比較をラッピング
            if (sp->GetRtti() == GameBossEnemy::sMonoRtti)
            {
                std::cout << sp->GetObjectName() << " : " << GameBossEnemy::GetClassName() << std::endl;
            }
        }

        // Check what from is GameSecretBossEnemy derived with polymorphism
        std::cout << "[Check what from is GameSecretBossEnemy derived with polymorphism]" << std::endl;
        std::shared_ptr<GameSecretBossEnemy> spSecretBossEnemy;
        for (auto& sp : entities)
        {
            if (sp->GetRtti() == GameSecretBossEnemy::sMonoRtti)
            {
                spSecretBossEnemy = std::static_pointer_cast<GameSecretBossEnemy>(sp); // share
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