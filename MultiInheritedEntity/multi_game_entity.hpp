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
#include <multi_game_entity_interface.hpp>
#include <iostream>

#include <multi_rtti.hpp>

class GameMultiEntity : public std::enable_shared_from_this<GameMultiEntity>, public GameInterfaceEntity
{
    MULTI_RTTI_DECL_NOPARENT
public:
    virtual ~GameMultiEntity() {}
    GameMultiEntity(const GameMultiEntity &) = delete;
    GameMultiEntity &operator=(const GameMultiEntity &) = delete;
    GameMultiEntity(GameMultiEntity &&) = default;
    GameMultiEntity &operator=(GameMultiEntity &&) = default;

    static const char *GetClassName() { return "GameMultiEntity"; }
    virtual const char *GetObjectName() const override { return GameMultiEntity::GetClassName(); }

    QUERYINTERFACE_BEGIN
    QUERYINTERFACE_END

protected:
    friend class GameMultiEntityFactory;
    GameMultiEntity() = default;
};

MULTI_RTTI_IMPL_NOPARENT(GameMultiEntity)