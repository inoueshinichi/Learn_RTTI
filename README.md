# Learn_RTTI
C++のRTTI (RunTime Type Information) 実行時型情報

# C++標準のRTTIシステム
1. dynamic_cast演算子
2. typeid演算子


## typeid演算子
適用先のオブジェクトの型についての情報を返す. 重要な情報は下記の2つ
1. ユーザーが読めるクラス名 (MSVCは直接ユーザーが見てわかるが, MSVC以外のGNUやClang系はデマングルが必要)
2. C++Versionのクラス名

```
GameSecretBossEnemy* pSecretBossEnemy = new GameSecretBossEnemy();
GameEnemy* pEnemy = dynamic_cast<GameEnemy*>(pSecretBossEnemy);

// type_info
const type_info& info = typeid(*pEnemy);
std::cout << type_info.name() << std::cout; // ClassName: GameSecretBossEnemy

// クラス型の比較
const type_info& info1 = typeid(*pObj1);
const type_info& info2 = typeid(*pObj2);
if (info1 == info2)
    // この2つは同じ型. 何らかの処理


// 型名の比較に使える
if (typeid(*pEntity) == typeid(GameSecretBossEnemy))
    // オブジェクト *pEntityの実態クラスはGameSecretBossEnemy.

```

## Unix系のデマングル
+ デマングル用関数は, libstdc++ライブラリに含まれる.
+ #include/<cxxabi.h/>ヘッダが必要
```
 #if __has_include(<cxxabi.h>)
            #include <cxxabi.h>
            #define DEMANGLE_LOG(message, singleton)                                                         \
            std::string class_name;                                                                          \
            const std::type_info &type_id = typeid(singleton); /* RTTI */                                    \
            int stat{-1};                                                                                    \
            char *name = abi::__cxa_demangle(type_id.name(), 0, 0, &stat); /* デマングル */                    \
            if (name != nullptr)                                                                             \
            {                                                                                                \
                if (stat == 0) /* success: stat == 0 */                                                      \
                {                                                                                            \
                    class_name = name;                                                                       \
                    std::cout << "[" << #message << "] a class name `" << class_name << "`" << std::endl;    \
                    ::free(name);                                                                            \
                }                                                                                            \
            }                                                                                                \
            if (stat != 0)                                                                                   \
            {                                                                                                \
                std::cout << "[" << #message << "] a singleton `" <<                                         \
                    typeid(SINGLETON).name() << "`" << std::endl;                                            \
            }
#endif
```