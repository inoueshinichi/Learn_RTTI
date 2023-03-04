/**
 * @file game_secret_boss_enemy.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <mono_game_boss_enemy.hpp>

#include <mono_rtti.hpp>

class GameSecretBossEnemy : public GameBossEnemy
{
    MONO_RTTI_DECL
public:
    virtual ~GameSecretBossEnemy() {}
    GameSecretBossEnemy(const GameSecretBossEnemy &) = delete;
    GameSecretBossEnemy &operator=(const GameSecretBossEnemy &) = delete;
    GameSecretBossEnemy(GameSecretBossEnemy &&) = default;
    GameSecretBossEnemy &operator=(GameSecretBossEnemy &&) = default;

    static const char *GetClassName() { return "GameSecretBossEnemy"; }
    virtual const char *GetObjectName() const override { return GameSecretBossEnemy::GetClassName(); }

protected:
    friend class GameMonoEntityFactory;
    GameSecretBossEnemy() = default;
};

MONO_RTTI_IMPL(GameSecretBossEnemy, GameBossEnemy)