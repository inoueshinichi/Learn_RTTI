/**
 * @file game_boss_enemy.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <mono_game_enemy.hpp>

#include <mono_rtti.hpp>

class GameBossEnemy : public GameEnemy
{
    MONO_RTTI_DECL
public:
    virtual ~GameBossEnemy() {}
    GameBossEnemy(const GameBossEnemy &) = delete;
    GameBossEnemy &operator=(const GameBossEnemy &) = delete;
    GameBossEnemy(GameBossEnemy &&) = default;
    GameBossEnemy &operator=(GameBossEnemy &&) = default;

    static const char *GetClassName() { return "GameBossEnemy"; }
    virtual const char *GetObjectName() const override { return GameBossEnemy::GetClassName(); }

protected:
    friend class GameMonoEntityFactory;
    GameBossEnemy() = default;
};

MONO_RTTI_IMPL(GameBossEnemy, GameEnemy)