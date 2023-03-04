/**
 * @file game_actor.hpp
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

class GameActor : public GameEntity
{
    MONO_RTTI_DECL
public:
    virtual ~GameActor() {}
    GameActor(const GameActor &) = delete;
    GameActor &operator=(const GameActor &) = delete;
    GameActor(GameActor &&) = default;
    GameActor &operator=(GameActor &&) = default;

    static const char *GetClassName() { return "GameActor"; }
    virtual const char *GetObjectName() const override { return GameActor::GetClassName(); }

protected:
    friend class GameMonoEntityFactory;
    GameActor() = default;
};

MONO_RTTI_IMPL(GameActor, GameEntity)