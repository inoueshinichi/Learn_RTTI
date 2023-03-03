# Learn_RTTI
C++のRTTI (RunTime Type Information) 実行時型情報

# C++標準のRTTIシステム
1. dynamic_cast演算子
2. typeid演算子

## dynamic_cast演算子
dynamic_cast演算子はキャスト成功でキャスト先のポインタ型を返す. 失敗でnullptrを返す.
キャストが正しいパターン  
1. 変換する先のポインタ型がオブジェクト自身の型
2. 先祖の型(直接の親でなくてOK, 叔父叔母関係はNG) アップキャスト
3. 変換元ポインタ型の直接子孫の場合 ダウンキャスト
4. 同一子クラスを持つ親クラス同士の場合 クロスキャスト

### 継承図(例)
```
/**
 * @brief Entityの継承図
 * --------------------------------------------------------------------------------------------
 * GameEntity
 * --------------------------------------------------------------------------------------------
 * GameActor  | GamePlayer       | GameEnemy                                | GameCamera
 * --------------------------------------------------------------------------------------------
 *     -      | GameLegendPlayer | GameBossEnemy                            | GameFpsCamera
 * --------------------------------------------------------------------------------------------
 *     -      |         -        | GameFinalBossEnemy | GameSecretBossEnemy |
 * --------------------------------------------------------------------------------------------
 */
```

### 2. 先祖の型(直接の親でなくてOK, 叔父叔母関係はNG) アップキャスト
```
// 正しいポインタ型を返す
GameSecretBossEnemy* pSecretBossEnemy = new GameSecretBossEnemy();
GameBossEnemy* pBossEnemy = dynamic_cast<GameBossEnemy*>(pSecretBossEnemy); // OK
GameEnemy* pEnemy = dynamic_cast<GameEnemy*>(pSecretBossEnemy); // OK
GameEntity* pEntity = dynamic_cast<GameEntity*>(pSecretBossEnemy); // OK

// 全てnullptrを返す
GameActor* pActor = dynamic_cast<GameActor*>(pSecretBossEnemy); // NG
GamePlayer* pPlayer = dynamic_cast<GamePlayer*>(pSecretBossEnemy); // NG
GameFpsCamera* pFpsCamera = dynamic_cast<GameFpsCamera*>(pSecretBossEnemy); // NG
```

### 3. 変換元ポインタ型の直接子孫の場合 ダウンキャスト
```
GameEntity* pEntity = new GamePlayer();

// 正しいポインタ型を返す
GamePlayer* pPlayer = dynamic_cast<GamePlayer*>(pEntity); // OK

// 全てnullptrを返す
GameLegendPlayer* pLegendPlayer = dynamic_cast<GameLegendPlayer*>(pEntity); // NG
GameActor* pActor = dynamic_cast<GameActor*>(pEntity); // NG? (要調査)
```

### 4. 同一子クラスを持つ親クラス同士の場合 クロスキャスト
```
/**
 * @brief Interfaceを含めたGameSecretBossEnemyの多重継承
 * --------------------------------------------------------------------------------------------
 *     -      | GameBossEnemy | IExtraAttack | IExtraDefence |                
 * --------------------------------------------------------------------------------------------
 *     -      | GameSecretBossEnemy                          |
 * --------------------------------------------------------------------------------------------
 */
```
上記のInterfaceを利用した多重継承を行っている時, GameSecretBossEnemyの親クラス同士のキャストは可能.
```
// 上へ
GameSecretBossEnemy* pSecretBossEnemy = new GameSecretBossEnemy();
GameBossEnemy* pBossEnemy = dynamic_cast<BossEnemy*>(pSecretBossEnemy); // OK
IExtraAttack* pIExtraAttack = dynamic_cast<IExtraAttack*>(pSecretBossEnemy); // OK
IExtraDefence* pIExtraDefence = dynamic_cast<IExtraDefence*>(pSecretBossEnemy); // OK

// 下へ
GameBossEnemy* pBossEnemy = new GameSecretBossEnemy();
GameSecretBossEnemy* pSecretBossEnemy = dynamic_cast<GameSecretBossEnemy*>(pBossEnemy); // OK

// クロスキャスト
IExtraAttack* pIExtraAttack = new GameSecretBossEnemy();
IExtraDefence* pIExtraDefence = dynamic_cast<IExtraDefence*>(pIExtraAttack); // OK
GameBossEnemy* pBossEnemy = dynamic_cast<GameBossEnemy*>(pIExtraAttack); // OK(要確認)

// これはダメ(要確認)
IExtraAttack* pIExtraAttack = new IExtraAttack();
IExtraDefence* pIExtraDefence = dynamic_cast<IExtraDefence*>(pIExtraAttack);
```