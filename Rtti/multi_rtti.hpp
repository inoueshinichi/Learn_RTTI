/**
 * @file multi_rtti.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 多重継承対応型RTTIシステム (計算コスト大)
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <iostream>
#include <string>
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
            std::cout << "[Delete] MultiRtti of " << mClassName << " has " << mNumParents << " parents." << std::endl;
            delete[] mRttiParents;
            mRttiParents = nullptr;
            mNumParents = 0;
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


/*Test OK*/
// MULTI_RTTI_IMPL(GameSecretBossEnemy, GameBossEnemy, IExtraAttack, IExtraAttack)