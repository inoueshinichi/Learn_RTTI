/**
 * @file game_final_boss_enemy.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <mono_game_boss_enemy.hpp>

#include <mono_rtti.hpp>

class GameFinalBossEnemy final : public GameBossEnemy
{
    MONO_RTTI_DECL
public:
    virtual ~GameFinalBossEnemy() {}
    GameFinalBossEnemy(const GameFinalBossEnemy &) = delete;
    GameFinalBossEnemy &operator=(const GameFinalBossEnemy &) = delete;
    GameFinalBossEnemy(GameFinalBossEnemy &&) = default;
    GameFinalBossEnemy &operator=(GameFinalBossEnemy &&) = default;

    static const char *GetClassName() { return "GameFinalBossEnemy"; }
    virtual const char *GetObjectName() const override { return GameFinalBossEnemy::GetClassName(); }

protected:
    friend class GameMonoEntityFactory;
    GameFinalBossEnemy() = default;
};

MONO_RTTI_IMPL(GameFinalBossEnemy, GameBossEnemy)