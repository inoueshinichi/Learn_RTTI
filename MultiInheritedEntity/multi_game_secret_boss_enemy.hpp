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
#include <multi_game_boss_enemy.hpp>
#include <multi_game_secret.hpp>
#include <interface_extra_attack.hpp>
#include <interface_extra_defence.hpp>

#include <multi_rtti.hpp>

class GameMultiSecretBossEnemy final : public GameMultiBossEnemy, public GameMultiSecret, public IExtraAttack, public IExtraDefence
{
    MULTI_RTTI_DECL
public:
    virtual ~GameMultiSecretBossEnemy() {}
    GameMultiSecretBossEnemy(const GameMultiSecretBossEnemy &) = delete;
    GameMultiSecretBossEnemy &operator=(const GameMultiSecretBossEnemy &) = delete;
    GameMultiSecretBossEnemy(GameMultiSecretBossEnemy &&) = default;
    GameMultiSecretBossEnemy &operator=(GameMultiSecretBossEnemy &&) = default;

    static const char *GetClassName() { return "GameMultiSecretBossEnemy"; }
    virtual const char *GetObjectName() const override { return GameMultiSecretBossEnemy::GetClassName(); }

    QUERYINTERFACE_BEGIN
    QUERYINTERFACE_ADD(ID_Attack, IAttack, GameMultiSecretBossEnemy)
    QUERYINTERFACE_ADD(ID_Defence, IDefence, GameMultiSecretBossEnemy)
    QUERYINTERFACE_ADD(ID_ExtraAttack, IExtraAttack, GameMultiSecretBossEnemy)
    QUERYINTERFACE_ADD(ID_ExtraDefence, IExtraDefence, GameMultiSecretBossEnemy)
    QUERYINTERFACE_END

    void Attack() override final
    {
        std::cout << GetObjectName() << " Attack" << std::endl;
    }

    void Defence() override final
    {
        std::cout << GetObjectName() << " Defence" << std::endl;
    }

    void ExtraAttack() override final
    {
        std::cout << GetObjectName() << " ExtraAttack" << std::endl;
    }

    void ExtraDefence() override final
    {
        std::cout << GetObjectName() << " ExtraDefence" << std::endl;
    }

protected:
    friend class GameMultiEntityFactory;
    GameMultiSecretBossEnemy() = default;
};

// ポイント
MULTI_RTTI_IMPL(GameMultiSecretBossEnemy, GameMultiBossEnemy, GameMultiSecret)