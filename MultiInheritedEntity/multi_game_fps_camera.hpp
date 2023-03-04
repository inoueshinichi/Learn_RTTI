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
#include <multi_game_camera.hpp>
#include <interface_fps_view.hpp>

#include <multi_rtti.hpp>

class GameMultiFpsCamera final : public GameMultiCamera, public IFpsView
{
    MULTI_RTTI_DECL
public:
    virtual ~GameMultiFpsCamera() {}
    GameMultiFpsCamera(const GameMultiFpsCamera &) = delete;
    GameMultiFpsCamera &operator=(const GameMultiFpsCamera &) = delete;
    GameMultiFpsCamera(GameMultiFpsCamera &&) = default;
    GameMultiFpsCamera &operator=(GameMultiFpsCamera &&) = default;

    static const char *GetClassName() { return "GameMultiFpsCamera"; }
    virtual const char *GetObjectName() const override { return GameMultiFpsCamera::GetClassName(); }

    QUERYINTERFACE_BEGIN
    QUERYINTERFACE_ADD(ID_View, IView, GameMultiFpsCamera)
    QUERYINTERFACE_ADD(ID_FpsView, IFpsView, GameMultiFpsCamera)
    QUERYINTERFACE_END

    void View() override final
    {
        std::cout << GetObjectName() << " View" << std::endl;
    }

    void FpsView() override final
    {
        std::cout << GetObjectName() << " FpsView" << std::endl;
    }

protected:
    friend class GameMultiEntityFactory;
    GameMultiFpsCamera() = default;
};

MULTI_RTTI_IMPL(GameMultiFpsCamera, GameMultiCamera)