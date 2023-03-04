/**
 * @file game_player.hpp
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
#include <interface_attack.hpp>
#include <interface_defence.hpp>
#include <interface_escape.hpp>

#include <multi_rtti.hpp>

class GameMultiPlayer : public GameMultiEntity, public IAttack, public IDefence, public IEscape
{
    MULTI_RTTI_DECL
public:
    virtual ~GameMultiPlayer() {}
    GameMultiPlayer(const GameMultiPlayer &) = delete;
    GameMultiPlayer &operator=(const GameMultiPlayer &) = delete;
    GameMultiPlayer(GameMultiPlayer &&) = default;
    GameMultiPlayer &operator=(GameMultiPlayer &&) = default;

    static const char *GetClassName() { return "GameMultiPlayer"; }
    virtual const char *GetObjectName() const override { return GameMultiPlayer::GetClassName(); }

    QUERYINTERFACE_BEGIN
    QUERYINTERFACE_ADD(ID_Attack, IAttack, GameMultiPlayer)
    QUERYINTERFACE_ADD(ID_Defence, IDefence, GameMultiPlayer)
    QUERYINTERFACE_ADD(ID_Escape, IEscape, GameMultiPlayer)
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
    GameMultiPlayer() = default;
};

MULTI_RTTI_IMPL(GameMultiPlayer, GameMultiEntity)