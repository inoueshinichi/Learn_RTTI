# Learn_RTTI
C++のRTTI (RunTime Type Information) 実行時型情報

# C++標準のRTTIシステム
1. dynamic_cast演算子
2. typeid演算子
メリット  
+ 組み込み型なのでどんな型にも適用できる
デメリット  
+ 実行速度が遅い

# C++標準RTTIシステムの回避方法
1. 文字列を使う
2. 定数を使う
3. Staticメンバ変数のアドレスを使う

# 単一継承用カスタムRTTIシステム(Static変数アドレス)
+ クラスに付与したRTTIStatic変数(クラス)のアドレスを使う. (クラスのstatic変数のアドレスはクラスに一意)
メリット  
+ 実行速度が速い
デメリット  
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

    const char* GetClassName() const;
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
#define MONO_RTTI_DECL                 \
public:                                \
    static const MonoRtti sMonoRtti;   \
    const MonoRtti &GetRtti()          \
    {                                  \
        return sMonoRtti;              \
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


