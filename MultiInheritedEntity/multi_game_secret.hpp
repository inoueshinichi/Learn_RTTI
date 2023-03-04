/**
 * @file multi_game_secret.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-03-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <multi_game_hidden.hpp>
#include <multi_game_special.hpp>

#include <multi_rtti.hpp>

class GameMultiSecret : public GameMultiHidden, public GameMultiSpecial
{
    MULTI_RTTI_DECL
public:
    virtual ~GameMultiSecret() {}
    GameMultiSecret(const GameMultiSecret &) = delete;
    GameMultiSecret &operator=(const GameMultiSecret &) = delete;
    GameMultiSecret(GameMultiSecret &&) = default;
    GameMultiSecret &operator=(GameMultiSecret &&) = default;

    static const char *GetClassName() { return "GameMultiSecret"; }
    virtual const char *GetObjectName() const override { return GameMultiSecret::GetClassName(); }
protected:
    friend class GameMultiEntityFactory;
    GameMultiSecret() = default;
};

// ポイント
MULTI_RTTI_IMPL(GameMultiSecret, GameMultiHidden, GameMultiSpecial)