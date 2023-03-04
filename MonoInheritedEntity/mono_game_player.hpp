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
#include <mono_game_entity.hpp>

#include <mono_rtti.hpp>

class GamePlayer : public GameEntity
{
    MONO_RTTI_DECL
public:
    virtual ~GamePlayer() {}
    GamePlayer(const GamePlayer &) = delete;
    GamePlayer &operator=(const GamePlayer &) = delete;
    GamePlayer(GamePlayer &&) = default;
    GamePlayer &operator=(GamePlayer &&) = default;

    static const char *GetClassName() { return "GamePlayer"; }
    virtual const char *GetObjectName() const override { return GamePlayer::GetClassName(); }

protected:
    friend class GameMonoEntityFactory;
    GamePlayer() = default;
};

MONO_RTTI_IMPL(GamePlayer, GameEntity)