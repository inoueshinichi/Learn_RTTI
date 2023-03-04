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
#include <multi_game_boss_enemy.hpp>
#include <interface_extra_defence.hpp>

class GameMultiFinalBossEnemy final : public GameMultiBossEnemy, public IExtraDefence
{
    MULTI_RTTI_DECL
public:
    virtual ~GameMultiFinalBossEnemy() {}
    GameMultiFinalBossEnemy(const GameMultiFinalBossEnemy &) = delete;
    GameMultiFinalBossEnemy &operator=(const GameMultiFinalBossEnemy &) = delete;
    GameMultiFinalBossEnemy(GameMultiFinalBossEnemy &&) = default;
    GameMultiFinalBossEnemy &operator=(GameMultiFinalBossEnemy &&) = default;

    static const char *GetClassName() { return "GameMultiFinalBossEnemy"; }
    virtual const char *GetObjectName() const override { return GameMultiFinalBossEnemy::GetClassName(); }

    QUERYINTERFACE_BEGIN
    QUERYINTERFACE_ADD(ID_Attack, IAttack, GameMultiFinalBossEnemy)
    QUERYINTERFACE_ADD(ID_Defence, IDefence, GameMultiFinalBossEnemy)
    QUERYINTERFACE_ADD(ID_ExtraDefence, IExtraDefence, GameMultiFinalBossEnemy)
    QUERYINTERFACE_END

    void Attack() override final
    {
        std::cout << GetObjectName() << " Attack" << std::endl;
    }

    void Defence() override final
    {
        std::cout << GetObjectName() << " Defence" << std::endl;
    }

    void ExtraDefence() override final
    {
        std::cout << GetObjectName() << " ExtraDefence" << std::endl;
    }
protected:
    friend class GameMultiEntityFactory;
    GameMultiFinalBossEnemy() = default;
};

MULTI_RTTI_IMPL(GameMultiFinalBossEnemy, GameMultiBossEnemy)