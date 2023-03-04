/**
 * @file game_entity.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <iostream>

#include <mono_rtti.hpp>

class GameEntity : public std::enable_shared_from_this<GameEntity>
{
    MONO_RTTI_NO_PARENT_DECL
public:
    virtual ~GameEntity() {}
    GameEntity(const GameEntity &) = delete;
    GameEntity &operator=(const GameEntity &) = delete;
    GameEntity(GameEntity &&) = default;
    GameEntity &operator=(GameEntity &&) = default;

    static const char *GetClassName() { return "GameEntity"; }
    virtual const char*GetObjectName() const { return GameEntity::GetClassName(); }

protected:
    friend class GameMonoEntityFactory;
    GameEntity() = default;
};

MONO_RTTI_IMPL_NOPARENT(GameEntity)
