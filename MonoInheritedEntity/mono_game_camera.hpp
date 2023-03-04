/**
 * @file game_camera.hpp
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

class GameCamera : public GameEntity
{
    MONO_RTTI_DECL
public:
    virtual ~GameCamera() {}
    GameCamera(const GameCamera &) = delete;
    GameCamera &operator=(const GameCamera &) = delete;
    GameCamera(GameCamera &&) = default;
    GameCamera &operator=(GameCamera &&) = default;

    static const char *GetClassName() { return "GameCamera"; }
    virtual const char *GetObjectName() const override { return GameCamera::GetClassName(); }

protected:
    friend class GameMonoEntityFactory;
    GameCamera() = default;
};

MONO_RTTI_IMPL(GameCamera, GameEntity)