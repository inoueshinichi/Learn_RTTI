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

#include <multi_game_entity.hpp>

// Singletonが望ましい
class GameMultiEntityFactory
{
public:
    GameMultiEntityFactory() = default;
    ~GameMultiEntityFactory() = default;
    GameMultiEntityFactory(const GameMultiEntityFactory &) = delete;
    GameMultiEntityFactory &operator=(const GameMultiEntityFactory &) = delete;
    GameMultiEntityFactory(GameMultiEntityFactory &&) = default;
    GameMultiEntityFactory &operator=(GameMultiEntityFactory &&) = default;

    std::shared_ptr<GameMultiEntity> CreateEntity(const std::string &type)
    {
        auto iter = mRegistry.find(type);
        if (iter == mRegistry.end())
        {
            return std::shared_ptr<GameMultiEntity>(); // null. nullはsegmentationfaultになってデバッグしずらい
        }
        return (*iter).second(); // creator() -> std::shared_ptr<Derived>
    }

    // std::is_comvertible_v : >= C++17
    template <typename ENTITY, typename std::enable_if_t<std::is_convertible_v<ENTITY, GameMultiEntity>> * = nullptr>
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

        auto creator = [deleter]() -> std::shared_ptr<GameMultiEntity> {
            std::cout << "[Create] " << ENTITY::GetClassName() << std::endl;
            return std::shared_ptr<ENTITY>(new ENTITY(), deleter);
        };

        mRegistry.emplace(type, creator); // 登録
    }

private :
    typedef std::map<std::string, std::function<std::shared_ptr<GameMultiEntity>()>> CreatorMap;
    CreatorMap mRegistry;
};
