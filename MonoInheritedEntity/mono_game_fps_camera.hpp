/**
 * @file game_fps_camera.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <mono_game_camera.hpp>

#include <mono_rtti.hpp>

class GameFpsCamera final : public GameCamera
{
    MONO_RTTI_DECL
public:
    virtual ~GameFpsCamera() {}
    GameFpsCamera(const GameFpsCamera &) = delete;
    GameFpsCamera &operator=(const GameFpsCamera &) = delete;
    GameFpsCamera(GameFpsCamera &&) = default;
    GameFpsCamera &operator=(GameFpsCamera &&) = default;

    static const char *GetClassName() { return "GameFpsCamera"; }
    virtual const char *GetObjectName() const override { return GameFpsCamera::GetClassName(); }

protected:
    friend class GameMonoEntityFactory;
    GameFpsCamera() = default;
};

MONO_RTTI_IMPL(GameFpsCamera, GameCamera)