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
#include <multi_game_enemy.hpp>
#include <interface_attack.hpp>
#include <interface_escape.hpp>

#include <multi_rtti.hpp>

class GameMultiBossEnemy : public GameMultiEnemy, public IAttack
{
    MULTI_RTTI_DECL
public:
    virtual ~GameMultiBossEnemy() {}
    GameMultiBossEnemy(const GameMultiBossEnemy &) = delete;
    GameMultiBossEnemy &operator=(const GameMultiBossEnemy &) = delete;
    GameMultiBossEnemy(GameMultiBossEnemy &&) = default;
    GameMultiBossEnemy &operator=(GameMultiBossEnemy &&) = default;

    static const char *GetClassName() { return "GameMultiBossEnemy"; }
    virtual const char *GetObjectName() const override { return GameMultiBossEnemy::GetClassName(); }

    QUERYINTERFACE_BEGIN
    QUERYINTERFACE_ADD(ID_Attack, IAttack, GameMultiBossEnemy)
    QUERYINTERFACE_ADD(ID_Defence, IDefence, GameMultiBossEnemy)
    QUERYINTERFACE_ADD(ID_Escape, IEscape, GameMultiBossEnemy)
    QUERYINTERFACE_END

    virtual void Attack() override
    {
        std::cout << GetObjectName() << " Attack" << std::endl;
    }

    virtual void Defence() override
    {
        std::cout << GetObjectName() << " Defence" << std::endl;
    }

    /*virtual*/ void Escape() override final
    {
        std::cout << GetObjectName() << " Escape" << std::endl;
    }

protected:
    friend class GameMultiEntityFactory;
    GameMultiBossEnemy() = default;
};

MULTI_RTTI_IMPL(GameMultiBossEnemy, GameMultiEnemy)