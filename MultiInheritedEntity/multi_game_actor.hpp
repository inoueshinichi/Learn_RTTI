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
#include <multi_game_entity.hpp>
#include <interface_escape.hpp>

#include <multi_rtti.hpp>

class GameMultiActor : public GameMultiEntity, public IEscape
{
    MULTI_RTTI_DECL
public:
    virtual ~GameMultiActor() {}
    GameMultiActor(const GameMultiActor &) = delete;
    GameMultiActor &operator=(const GameMultiActor &) = delete;
    GameMultiActor(GameMultiActor &&) = default;
    GameMultiActor &operator=(GameMultiActor &&) = default;

    static const char *GetClassName() { return "GameMultiActor"; }
    virtual const char *GetObjectName() const override { return GameMultiActor::GetClassName(); }

    QUERYINTERFACE_BEGIN
    QUERYINTERFACE_ADD(ID_Escape, IEscape, GameMultiActor)
    QUERYINTERFACE_END

    void Escape() override final
    {
        std::cout << GetObjectName() << " Escape" << std::endl;
    }

protected:
    friend class GameMultiEntityFactory;
    GameMultiActor() = default;
};

MULTI_RTTI_IMPL(GameMultiActor, GameMultiEntity)