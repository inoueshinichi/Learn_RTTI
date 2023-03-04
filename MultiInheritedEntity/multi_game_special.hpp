/**
 * @file multi_game_special.hpp
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

class GameMultiSpecial
{
    MULTI_RTTI_DECL_NOPARENT
public:
    virtual ~GameMultiSpecial() {}
    GameMultiSpecial(const GameMultiSpecial &) = delete;
    GameMultiSpecial &operator=(const GameMultiSpecial &) = delete;
    GameMultiSpecial(GameMultiSpecial &&) = default;
    GameMultiSpecial &operator=(GameMultiSpecial &&) = default;

    static const char *GetClassName() { return "GameMultiSpecial"; }
    virtual const char *GetObjectName() const { return GameMultiSpecial::GetClassName(); }

protected:
    friend class GameMultiEntityFactory;
    GameMultiSpecial() = default;
};

MULTI_RTTI_IMPL_NOPARENT(GameMultiSpecial)