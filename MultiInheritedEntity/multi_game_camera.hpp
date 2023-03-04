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
#include <multi_game_entity.hpp>
#include <interface_view.hpp>

#include <multi_rtti.hpp>

class GameMultiCamera : public GameMultiEntity, public IView
{
    MULTI_RTTI_DECL
public:
    virtual ~GameMultiCamera() {}
    GameMultiCamera(const GameMultiCamera &) = delete;
    GameMultiCamera &operator=(const GameMultiCamera &) = delete;
    GameMultiCamera(GameMultiCamera &&) = default;
    GameMultiCamera &operator=(GameMultiCamera &&) = default;

    static const char *GetClassName() { return "GameMultiCamera"; }
    virtual const char *GetObjectName() const override { return GameMultiCamera::GetClassName(); }

    QUERYINTERFACE_BEGIN
    QUERYINTERFACE_ADD(ID_View, IView, GameMultiCamera)
    QUERYINTERFACE_END

    virtual void View() override
    {
        std::cout << GetObjectName() << " View" << std::endl;
    }

protected:
    friend class GameMultiEntityFactory;
    GameMultiCamera() = default;
};

MULTI_RTTI_IMPL(GameMultiCamera, GameMultiEntity)