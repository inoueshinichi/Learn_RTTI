/**
 * @file mono_game_entity_factory.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-02-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <memory>
#include <map>
#include <functional>
#include <iostream>
#include <type_traits>

#include <mono_game_entity.hpp>

// Singletonが望ましい
class GameMonoEntityFactory
{
public:
    GameMonoEntityFactory() = default;
    ~GameMonoEntityFactory() = default;
    GameMonoEntityFactory(const GameMonoEntityFactory &) = delete;
    GameMonoEntityFactory &operator=(const GameMonoEntityFactory &) = delete;
    GameMonoEntityFactory(GameMonoEntityFactory &&) = default;
    GameMonoEntityFactory &operator=(GameMonoEntityFactory &&) = default;

    std::shared_ptr<GameEntity> CreateEntity(const std::string &type)
    {
        auto iter = mRegistry.find(type);
        if (iter == mRegistry.end())
        {
            return std::shared_ptr<GameEntity>(); // null. nullはsegmentationfaultになってデバッグしずらい
        }
        return (*iter).second(); // creator() -> std::shared_ptr<Derived>
    }

    // std::is_comvertible_v : >= C++17
    template <typename ENTITY, typename std::enable_if_t<std::is_convertible_v<ENTITY, GameEntity>> * = nullptr>
    void Register(const std::string &type)
    {
        auto iter = mRegistry.find(type);
        if (iter != mRegistry.end())
        {
            return;
        }

        std::cout << "Register creator of " << ENTITY::GetClassName() << std::endl;

        auto deleter = [](ENTITY *ptr) -> void {
            std::cout << "[Delete] " << ENTITY::GetClassName() << std::endl;
            delete ptr;
            ptr = nullptr;
        };

        auto creator = [deleter]() -> std::shared_ptr<GameEntity> {
            std::cout << "[Create] " << ENTITY::GetClassName() << std::endl;
            return std::shared_ptr<ENTITY>(new ENTITY(), deleter);
        };

        mRegistry.emplace(type, creator); // 登録
    }

private :
    typedef std::map<std::string, std::function<std::shared_ptr<GameEntity>()>> CreatorMap;
    CreatorMap mRegistry;
};
