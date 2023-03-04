/**
 * @file multi_rtti_system.cpp
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

// Multi inhereted entities
#include <multi_game_entity.hpp>
#include <multi_game_actor.hpp>
#include <multi_game_player.hpp>
#include <multi_game_legend_player.hpp>
#include <multi_game_enemy.hpp>
#include <multi_game_boss_enemy.hpp>
#include <multi_game_final_boss_enemy.hpp>
#include <multi_game_secret_boss_enemy.hpp>
#include <multi_game_camera.hpp>
#include <multi_game_fps_camera.hpp>

// Factory
#include <multi_game_entity_factory.hpp>

/**
 * @brief 多重継承型RTTIのテスト
 *
 */

int main(int, char**)
{
    try
    {
        GameMultiEntityFactory factory;

        // Register
        std::cout << "Register" << std::endl;
        factory.Register<GameMultiEntity>(GameMultiEntity::GetClassName());
        factory.Register<GameMultiCamera>(GameMultiCamera::GetClassName());
        factory.Register<GameMultiFpsCamera>(GameMultiFpsCamera::GetClassName());
        factory.Register<GameMultiPlayer>(GameMultiPlayer::GetClassName());
        factory.Register<GameMultiLegendPlayer>(GameMultiLegendPlayer::GetClassName());
        factory.Register<GameMultiActor>(GameMultiActor::GetClassName());
        factory.Register<GameMultiEnemy>(GameMultiEnemy::GetClassName());
        factory.Register<GameMultiBossEnemy>(GameMultiBossEnemy::GetClassName());
        factory.Register<GameMultiFinalBossEnemy>(GameMultiFinalBossEnemy::GetClassName());
        factory.Register<GameMultiSecretBossEnemy>(GameMultiSecretBossEnemy::GetClassName());
        // GameMultiEntityをRootに持たないクラス
        // factory.Register<GameMultiSecret>(GameMultiSecret::GetClassName());
        // factory.Register<GameMultiSpecial>(GameMultiSpecial::GetClassName());
        // factory.Register<GameMultiHidden>(GameMultiHidden::GetClassName());
        std::cout << std::endl;

        // Create
        std::cout << "Create" << std::endl;
        std::vector<std::shared_ptr<GameMultiEntity>> entities;
        entities.emplace_back(factory.CreateEntity("GameMultiEntity"));
        entities.emplace_back(factory.CreateEntity("GameMultiCamera"));
        entities.emplace_back(factory.CreateEntity("GameMultiFpsCamera"));
        entities.emplace_back(factory.CreateEntity("GameMultiPlayer"));
        entities.emplace_back(factory.CreateEntity("GameMultiLegendPlayer"));
        entities.emplace_back(factory.CreateEntity("GameMultiActor"));
        entities.emplace_back(factory.CreateEntity("GameMultiEnemy"));
        entities.emplace_back(factory.CreateEntity("GameMultiBossEnemy"));
        entities.emplace_back(factory.CreateEntity("GameMultiFinalBossEnemy"));
        entities.emplace_back(factory.CreateEntity("GameMultiSecretBossEnemy"));
        std::cout << std::endl;

        // RTTI
        std::cout << "[Check multi rtti system]" << std::endl;
        for (auto &sp : entities)
        {
            std::printf("%s : rtti address %p, rtti class-name %s\n", sp->GetObjectName(), (void *)&(sp->GetRtti()), sp->GetRtti().GetClassName().c_str());
        }

        std::cout << "[Check what is class derived from GameMultiHidden with polymorphism?]" << std::endl;
        for (auto &sp : entities)
        {
            if (sp->GetRtti().DerivedFrom(GameMultiHidden::sMultiRtti))
            {
                std::cout << sp->GetObjectName() << std::endl; 
            }
        }

        std::cout << "[Check what is class derived from GameMultiSpecial with polymorphism?]" << std::endl;
        for (auto &sp : entities)
        {
            if (sp->GetRtti().DerivedFrom(GameMultiSpecial::sMultiRtti))
            {
                std::cout << sp->GetObjectName() << std::endl;
            }
        }

        std::cout << "[Check what is class derived from GameMultiBossEnemy with polymorphism?]" << std::endl;
        for (auto &sp : entities)
        {
            if (sp->GetRtti().DerivedFrom(GameMultiBossEnemy::sMultiRtti))
            {
                std::cout << sp->GetObjectName() << std::endl;
            }
        }

        std::cout << "[Check what is class derived from GameMultiEntity with polymorphism?]" << std::endl;
        for (auto &sp : entities)
        {
            if (sp->GetRtti().DerivedFrom(GameMultiEntity::sMultiRtti))
            {
                std::cout << sp->GetObjectName() << std::endl;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}