/**
 * @file game_legend_player.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <multi_game_player.hpp>
#include <interface_defence.hpp>
#include <interface_extra_attack.hpp>

#include <multi_rtti.hpp>

class GameMultiLegendPlayer final : public GameMultiPlayer, public IExtraAttack
{
    MULTI_RTTI_DECL
public:
    virtual ~GameMultiLegendPlayer() {}
    GameMultiLegendPlayer(const GameMultiLegendPlayer &) = delete;
    GameMultiLegendPlayer &operator=(const GameMultiLegendPlayer &) = delete;
    GameMultiLegendPlayer(GameMultiLegendPlayer &&) = default;
    GameMultiLegendPlayer &operator=(GameMultiLegendPlayer &&) = default;

    static const char *GetClassName() { return "GameMultiLegendPlayer"; }
    virtual const char *GetObjectName() const override { return GameMultiLegendPlayer::GetClassName(); }

    QUERYINTERFACE_BEGIN
    QUERYINTERFACE_ADD(ID_Attack, IAttack, GameMultiLegendPlayer)
    QUERYINTERFACE_ADD(ID_Defence, IDefence, GameMultiLegendPlayer)
    QUERYINTERFACE_ADD(ID_ExtraAttack, IExtraAttack, GameMultiLegendPlayer)
    QUERYINTERFACE_END

    void ExtraAttack() override final
    {
        std::cout << GetObjectName() << " ExtraAttack" << std::endl;
    }

    void Attack() override final
    {
        std::cout << GetObjectName() << " Attack" << std::endl;
    }

    void Defence() override final
    {
        std::cout << GetObjectName() << " Defence" << std::endl;
    }

protected:
    friend class GameMultiEntityFactory;
    GameMultiLegendPlayer() = default;
};

MULTI_RTTI_IMPL(GameMultiLegendPlayer, GameMultiPlayer)