/**
 * @file game_entity.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <memory>
#include <interface_unknown.hpp>

class GameInterfaceEntity
{
public:
    virtual ~GameInterfaceEntity() {}  
    virtual std::shared_ptr<IUnknown> QueryInterface(IID iid) = 0;

    static const char *GetClassName() { return "GameInterfaceEntity"; }
    virtual const char*GetObjectName() const { return GameInterfaceEntity::GetClassName(); }
};

/**
 * @brief Entityの継承図 (GameInterfaceEntity is interface for abstruct virtual func QueryInterface )
 * ----------------------------------------------------------------------------------------------------------------------
 * | GameMultiEntity                                                                                                    |
 * ----------------------------------------------------------------------------------------------------------------------
 * | GameMultiActor  | GameMultiPlayer       | GameMultiEnemy                                     | GameMultiCamera     |
 * ----------------------------------------------------------------------------------------------------------------------
 * |     -           | GameMultiLegendPlayer | GameMultiBossEnemy                                 | GameMultiFpsCamera  |
 * ----------------------------------------------------------------------------------------------------------------------
 * |     -           |         -             | GameMultiFinalBossEnemy | GameMultiSecretBossEnemy |                     |
 * ----------------------------------------------------------------------------------------------------------------------
 */

/**
 * @brief GameMultiSecretBossEnemyの別ルートの継承図 (Interfaceを除いて, GameMultiSecretBossEnemyが唯一の多重継承クラス)
 * --------------------------------------
 * | GameMultiSpecial | GameMultiHidden | 
 * --------------------------------------
 * | GameMultiSecret                    | 
 * --------------------------------------
 * | GameMultiSecretBossEnemy           |
 * --------------------------------------
 */