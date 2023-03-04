/**
 * @file game_enemy.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <mono_game_entity.hpp>

#include <mono_rtti.hpp>

class GameEnemy : public GameEntity
{
    MONO_RTTI_DECL
public:
    virtual ~GameEnemy() {}
    GameEnemy(const GameEnemy &) = delete;
    GameEnemy &operator=(const GameEnemy &) = delete;
    GameEnemy(GameEnemy &&) = default;
    GameEnemy &operator=(GameEnemy &&) = default;

    static const char *GetClassName() { return "GameEnemy"; }
    virtual const char *GetObjectName() const override { return GameEnemy::GetClassName(); }

protected:
    friend class GameMonoEntityFactory;
    GameEnemy() = default;
};

MONO_RTTI_IMPL(GameEnemy, GameEntity)