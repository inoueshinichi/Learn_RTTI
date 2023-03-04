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
#include <multi_game_entity.hpp>
#include <interface_escape.hpp>
#include <interface_defence.hpp>

#include <multi_rtti.hpp>

class GameMultiEnemy : public GameMultiEntity, public IEscape, public IDefence
{
    MULTI_RTTI_DECL
public:
    virtual ~GameMultiEnemy() {}
    GameMultiEnemy(const GameMultiEnemy &) = delete;
    GameMultiEnemy &operator=(const GameMultiEnemy &) = delete;
    GameMultiEnemy(GameMultiEnemy &&) = default;
    GameMultiEnemy &operator=(GameMultiEnemy &&) = default;

    static const char *GetClassName() { return "GameMultiEnemy"; }
    virtual const char *GetObjectName() const override { return GameMultiEnemy::GetClassName(); }

    QUERYINTERFACE_BEGIN
    QUERYINTERFACE_ADD(ID_Escape, IEscape, GameMultiEnemy)
    QUERYINTERFACE_ADD(ID_Defence, IDefence, GameMultiEnemy)
    QUERYINTERFACE_END

    /*virutal*/ void Escape() override /*final*/
    {
        std::cout << GetObjectName() << " Escape" << std::endl;
    }

    /*virtual*/ void Defence() override
    {
        std::cout << GetObjectName() << " Defence" << std::endl;
    }

protected:
    friend class GameMultiEntityFactory;
    GameMultiEnemy() = default;
};

MULTI_RTTI_IMPL(GameMultiEnemy, GameMultiEntity)