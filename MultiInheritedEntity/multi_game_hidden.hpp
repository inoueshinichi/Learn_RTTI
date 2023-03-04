/**
 * @file multi_game_hidden.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <multi_rtti.hpp>

class GameMultiHidden
{
    MULTI_RTTI_DECL_NOPARENT
public:
    virtual ~GameMultiHidden() {}
    GameMultiHidden(const GameMultiHidden &) = delete;
    GameMultiHidden &operator=(const GameMultiHidden &) = delete;
    GameMultiHidden(GameMultiHidden &&) = default;
    GameMultiHidden &operator=(GameMultiHidden &&) = default;

    static const char *GetClassName() { return "GameMultiHidden"; }
    virtual const char *GetObjectName() const { return GameMultiHidden::GetClassName(); }

protected:
    friend class GameMultiEntityFactory;
    GameMultiHidden() = default;
};

MULTI_RTTI_IMPL_NOPARENT(GameMultiHidden)