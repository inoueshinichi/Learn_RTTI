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
#include <mono_game_player.hpp>

#include <mono_rtti.hpp>

class GameLegendPlayer final : public GamePlayer
{
    MONO_RTTI_DECL
public:
    virtual ~GameLegendPlayer() {}
    GameLegendPlayer(const GameLegendPlayer &) = delete;
    GameLegendPlayer &operator=(const GameLegendPlayer &) = delete;
    GameLegendPlayer(GameLegendPlayer &&) = default;
    GameLegendPlayer &operator=(GameLegendPlayer &&) = default;

    static const char *GetClassName() { return "GameLegendPlayer"; }
    virtual const char *GetObjectName() const override { return GameLegendPlayer::GetClassName(); }

protected:
    friend class GameMonoEntityFactory;
    GameLegendPlayer() = default;
};

MONO_RTTI_IMPL(GameLegendPlayer, GamePlayer)