# Learn_RTTI
C++のRTTI (RunTime Type Information) 実行時型情報

# C++標準のRTTIシステム
1. dynamic_cast演算子
2. typeid演算子
### メリット  
+ 組み込み型なのでどんな型にも適用できる
### デメリット  
+ 実行速度が遅い

デメリットである実行速度が遅い問題をカスタムRTTIで改善することが趣旨.  

# C++標準RTTIシステムの回避方法
1. 文字列を使う : 遅いけどコーディングが楽でデバッグが容易
2. 定数(Enum)を使う : コードが簡潔. デバッグも比較的容易. しかし, 拡張性が低く, 定数を一箇所集中で管理する必要がある.
3. Staticメンバ変数のアドレスを使う : 文字列と定数(Enum)のハイブリッド. クラスID(タグ)をクラス毎に分散化できる点で進歩があるが, 可読性は以前低い. クラスの宣言と実装にRTTI用マクロを追加しなければならない.

### 運用方法
速度を求められるシステム以外でのRTTIはC++標準orクラス文字列による運用で良いと思われる.  

# 単一継承用カスタムRTTIシステム(Static変数アドレス)
+ クラスに付与したRTTIStatic変数(クラス)のアドレスを使う. (クラスのstatic変数のアドレスはクラスに一意)
### メリット
+ 実行速度が速い
### デメリット
+ RTTIStatic変数を持っている独自クラスにしかRTTIの恩恵を受けられない
+ 適用先クラスのHeaderとSourceに独自のマクロを追加することが煩わしい
+ 可読性を下げる

```
#pragma once
#include <string>

class MonoRtti
{
public:
    MonoRtti(const std::string &className);
    MonoRtti(const std::string &className, const MonoRtti &baseRtti);

    const std::string& GetClassName() const;
    bool IsExactly(const RTTI& rtti) { return (this == &rtti); } // アドレス比較なので高速
    bool operator==(const MonoRtti &rtti) { return (this == &rtti); } // アドレス比較
    bool DerivedFrom(const MonoRtti &rtti) const;

private:
    std::string mClassName;
    const MonoRtti *mMonoBaseRtti;

    // コピー系は禁止
    MonoRtti(const MonoRtti&) = delete;
    MonoRtti& operator=(const MonoRtti&) = delete;
};

//////////////////////////
// Headerの適用先クラスに定義
//////////////////////////
#define MONO_RTTI_DECL_NOPARENT        \
public:                                \
    static const MonoRtti sMonoRtti;   \
    virtual const MonoRtti &GetRtti()  \
    {                                  \
        return sMonoRtti;              \
    }

#define MONO_RTTI_DECL                         \
public:                                        \
    static const MonoRtti sMonoRtti;           \
    virtual const MonoRtti &GetRtti() override \
    {                                          \
        return sMonoRtti;                      \
    }

//////////////////////////
// 適用先クラスのSourceに定義
//////////////////////////
// Root用
#define MONO_RTTI_IMPL_NOPARENT(class_name)           \
    const MonoRtti class_name::sMonoRtti(#class_name);

// Rootの子孫用
#define MONO_RTTI_IMPL(class_name, base_name)                               \
    const MonoRtti class_name::sMonoRtti(#class_name, base_name::sMonoRtti);
```


# 多重継承用カスタムRTTIシステム(Static変数アドレス)

### 可変長マクロ引数をループして処理するプリプロセッサを準備
+ `CONCATENATE_MULTI_RTTI(...)`に渡される可変長マクロ引数を個別分解して, `arg(i)::sMultiRtti` と末尾に`::sMultiRtti`を連結する
```
// preprocessor_magic.hpp

#pragma once

/**
 * @brief 可変長マクロのループ処理
 * @url https://in-neuro.hatenablog.com/entry/2020/10/21/155651
 * @note 可変長引数の上限があること前提として, マクロの再帰展開を使う.
 *
 */

/*可変引数の個数を数える方法 (Max16)*/
#define INDEX_RSEQ() 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define VA_ARGS_SIZE_IMPL(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9, ARG10, ARG11, ARG12, ARG13, ART14, ARG15, ARG16, N, ...) N
#define VA_ARGS_SIZE_UPD(...) VA_ARGS_SIZE_IMPL(__VA_ARGS__)
#define VA_ARGS_SIZE(...) VA_ARGS_SIZE_UPD(__VA_ARGS__, INDEX_RSEQ())

/*引数の個数毎にsMultiRttiを連結するための再帰展開*/
// トークン連結演算子の罠 参考: https://tkuro.hatenadiary.org/entry/20081124/1227539454
#define RECURSION_1(a) a::sMultiRtti
#define RECURSION_2(a, b) RECURSION_1(a), b::sMultiRtti
#define RECURSION_3(a, b, c) RECURSION_2(a, b), c::sMultiRtti
#define RECURSION_4(a, b, c, d) RECURSION_3(a, b, c), d::sMultiRtti
#define RECURSION_5(a, b, c, d, e) RECURSION_4(a, b, c, d), e::sMultiRtti
#define RECURSION_6(a, b, c, d, e, f) RECURSION_5(a, b, c, d, e), f::sMultiRtti
#define RECURSION_7(a, b, c, d, e, f, g) RECURSION_6(a, b, c, d, e, f), g::sMultiRtti
#define RECURSION_8(a, b, c, d, e, f, g, h) RECURSION_7(a, b, c, d, e, f, g), h::sMultiRtti
#define RECURSION_9(a, b, c, d, e, f, g, h, i) RECURSION_8(a, b, c, d, e, f, g, h), i::sMultiRtti
#define RECURSION_10(a, b, c, d, e, f, g, h, i, j) RECURSION_9(a, b, c, d, e, f, g, h, i), j::sMultiRtti
#define RECURSION_11(a, b, c, d, e, f, g, h, i, j, k) RECURSION_10(a, b, c, d, e, f, g, h, i, j), k::sMultiRtti
#define RECURSION_12(a, b, c, d, e, f, g, h, i, j, k, l) RECURSION_11(a, b, c, d, e, f, g, h, i, j, k), l::sMultiRtti
#define RECURSION_13(a, b, c, d, e, f, g, h, i, j, k, l, m) RECURSION_12(a, b, c, d, e, f, g, h, i, j, k, l), m::sMultiRtti
#define RECURSION_14(a, b, c, d, e, f, g, h, i, j, k, l, m, n) RECURSION_13(a, b, c, d, e, f, g, h, i, j, k, l, m), n::sMultiRtti
#define RECURSION_15(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o) RECURSION_14(a, b, c, d, e, f, g, h, i, j, k, l, m, n), o::sMultiRtti
#define RECURSION_16(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) RECURSION_15(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o), p::sMultiRtti

/*__VA_ARGS__用連結インターフェースマクロ*/
#define CONCATENATE_UPD(x, y) x##y
#define CONCATENATE(x, y) CONCATENATE_UPD(x, y)
#define CONCATENATE_MULTI_RTTI(...) CONCATENATE(RECURSION_, VA_ARGS_SIZE(__VA_ARGS__))(__VA_ARGS__)

```


```
// multi_rtti.hpp

#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <preprocessor_magic.hpp>

class MultiRtti
{
    void GetPackedParamsAddressImpl(const MultiRtti **pp, int numParents)
    {
        // nothing
    }

    template <typename FirstRtti, typename... RestRttis>
    void GetPackedParamsAddressImpl(const MultiRtti **pp, int numParents,
                                    const FirstRtti &first, const RestRttis &...rest)
    {
        int restSize = sizeof...(RestRttis);
        int index = numParents - restSize - 1;
        mRttiParents[index] = &first; // 親クラスが所有する静的Rttiクラスのポインタ

        if (sizeof...(rest) > 0)
        {
            GetPackedParamsAddressImpl(pp, numParents, rest...);
        }
        else
        {
            GetPackedParamsAddressImpl(pp, numParents);
        }
    }

    template <typename... BaseRttis>
    void GetPackedParamsAddress(const MultiRtti  **pp, int numParents, const BaseRttis &...baseRttis)
    {
        GetPackedParamsAddressImpl(pp, numParents, baseRttis...);
    }

public:
    

    // ... BaseRttisの展開例, [GameMultiEnemy::sMultiRtti, GameMultiEntity::sMultiRtti, ...]
    // #include <preprocessor_magic.hpp>の可変長マクロループ展開マクロで各スコープをつけてsMultiRttiが展開される.
    template <typename... BaseRttis> // Derived
    MultiRtti(const std::string &className, const BaseRttis &...parents)
        : mClassName(className), mNumParents(sizeof...(parents))
    {
        mRttiParents = new const MultiRtti *[mNumParents];

        GetPackedParamsAddress(mRttiParents, mNumParents, parents...);
    }

    // Root
    MultiRtti(const std::string &className)
        : mClassName(className), mNumParents(0), mRttiParents(nullptr)
    {
    }

    ~MultiRtti()
    {
        if (mNumParents > 0)
        {
            delete[] mRttiParents;
            mRttiParents = nullptr;
            mNumParents = 0;
            std::cout << "[Delete] MultiRtti of " << mClassName << std::endl;
        }
    }

    const std::string &GetClassName() const { return mClassName; }
    bool IsExactly(const MultiRtti &rtti) const { return (this == &rtti); }
    bool operator==(const MultiRtti &rtti) const { return IsExactly(rtti); }

    bool DerivedFrom(const MultiRtti &rtti) const
    {
        if (&rtti == this)
        {
            return true;
        }

        for (int i = 0; i < mNumParents; ++i)
        {
            if (mRttiParents[i]->DerivedFrom(rtti))
            {
                return true;
            }
        }

        return false;
    }

    MultiRtti(const MultiRtti &) = delete;
    MultiRtti &operator=(const MultiRtti &) = delete;

private:
    std::string mClassName;
    int mNumParents;
    const MultiRtti **mRttiParents; // 親クラスが所有する静的Rttiクラスのポインタ配列
};

///////////////////////////
// Headerの適用先クラスに定義
///////////////////////////
#define MULTI_RTTI_DECL                         \
public:                                         \
    static const MultiRtti sMultiRtti;          \
    virtual const MultiRtti &GetRtti() override \
    {                                           \
        return sMultiRtti;                      \
    }

// Root用
#define MULTI_RTTI_DECL_NOPARENT                \
public:                                         \
    static const MultiRtti sMultiRtti;          \
    virtual const MultiRtti &GetRtti()          \
    {                                           \
        return sMultiRtti;                      \
    }

//////////////////////////
// 適用先クラスのSourceに定義
//////////////////////////
// Root用
#define MULTI_RTTI_IMPL_NOPARENT(class_name)             \
    const MultiRtti class_name::sMultiRtti(#class_name);

// 可変長マクロの処理方法
// #define LOG(fmt, ...) printf(fmt, __VA_ARGS__)を作ると, 
// 通常は, 可変部分は1個以上値を渡さなければならない.
// LOG("FOOBAR\n"); // コンパイルエラー
// しかし、GCCの場合... ##__VA_ARGS__を使えば、0個の場合でも受け取れる.
// #define LOG(fmt, ...) printf(fmt, ##__VA_ARGS__); // OK
// MSVCの場合... 空の場合, コンパイラがprintf(fmt, __VA_ARGS__)の`,`を気を利かせて消してくれるが...
// Visual StudioのバージョンとC++17以前とC++20以降で動作が異なるので要注意.

#if defined(_MSC_VER) && (__cplusplus <= 201703L) // <= C++17
#   define IS_EXPAND(...) __VA__ARGS__
#else
#   define IS_VA_ARGS(...) , ##__VA_ARGS__
#endif

// // Rootの子孫用
#if __cplusplus <= 201703L // <= C++17
#   if defined(_MSC_VER) // `, IS_EXPAND`で可変長マクロを処理
        // _MSVC_TRADITIONAL 従来:1, 準拠:0
#       if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL // 従来型のプリプロセッサ: __VA__ARGSが空の場合, __VA_ARGS__の前にある`,`は自動消去可能

#           define MULTI_RTTI_IMPL(class_name, ...) \
                const MultiRtti class_name::sMultiRtti(#class_name, IS_EXPAND(CONCATENATE_MULTI_RTTI(__VA_ARGS__)));

#       else // 新しいプリプロセッサ: __VA__ARGSが空のでも, __VA_ARGS__の前にある`,`は自動消去されない. ##__VA_ARGS__ が必要.

#           define MULTI_RTTI_IMPL(class_name, ...) \
                const MultiRtti class_name::sMultiRtti(#class_name IS_VA_ARGS(CONCATENATE_MULTI_RTTI(__VA_ARGS__)));

#       endif
#   else // GNU, Clang or AppleClang `, ##__VA_ARGS__'(GNU拡張)で処理

#       define MULTI_RTTI_IMPL(class_name, ...) \
            const MultiRtti class_name::sMultiRtti(#class_name IS_VA_ARGS(CONCATENATE_MULTI_RTTI(__VA_ARGS__)));

#   endif
#else // (>= C++20)
#   if  defined(_MSC_VER)
        // Visual Studio 2019 version 16.5.1 & コンパイラオプション(C++準拠モードを有効) /Zc:preprocessor
        // 可変長マクロ引数が空でも、`,`の自動消去は行われない. GCCと同じ, ##__VA_ARGS__で消える.
        // マクロ内で別のマクロに可変長マクロ引数を渡しても、以前と異なり、パラメータアンパックされる.
        // Visual Studio 2019 version 16.5.1のC++20では__VA_OPT__(,)も使える.
        // コンパイラオプション(C++準拠モードを有効) /Zc:preprocessor
#       if _MSC_VER >= 1925 // >= Visual Studio 2019 16.5.1

#           define MULTI_RTTI_IMPL(class_name, ...) \
                const MultiRtti class_name::sMultiRtti(#class_name __VA_OPT__(, ) CONCATENATE_MULTI_RTTI(__VA_ARGS__));

#       else // < Visual Studio 2019 16.5.1
            // _MSVC_TRADITIONAL 従来:1, 準拠:0
#           if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL // 従来型プリプロセッサ

#               define MULTI_RTTI_IMPL(class_name, ...) \
                    const MultiRtti class_name::sMultiRtti(#class_name IS_EXPAND(CONCATENATE_MULTI_RTTI(__VA_ARGS__)));

#           else // 新型プリプロセッサ
#               define MULTI_RTTI_IMPL(class_name, ...) \
                    const MultiRtti class_name::sMultiRtti(#class_name, IS_VA_ARGS(CONCATENATE_MULTI_RTTI(__VA_ARGS__)));
#           endif
#       endif // #if _MSC_VER >= 1925
#   else // GNU, Clang or AppleClang

#   define MULTI_RTTI_IMPL(class_name, ...) \
        const MultiRtti class_name::sMultiRtti(#class_name __VA_OPT__(, ) CONCATENATE_MULTI_RTTI(__VA_ARGS__));

#   endif // #ifdef _MSC_VER
#endif // #if __cplusplus < 201703L

```

