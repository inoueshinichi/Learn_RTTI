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
/*可変引数の個数を数える方法 (Max16)*/
#define INDEX_RSEQ() 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define VA_ARGS_SIZE_IMPL(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, ARG8, ARG9, ARG10, ARG11, ARG12, ARG13, ART14, ARG15, ARG16, N, ...) N
#define VA_ARGS_SIZE_UPD(...) VA_ARGS_SIZE_IMPL(__VA_ARGS__)
#define VA_ARGS_SIZE(...) VA_ARGS_SIZE_UPD(__VA_ARGS__, INDEX_RSEQ())

/*引数の個数毎にsMultiRttiを連結するための再帰展開*/
#define RECURSION_1(a) a## ::sMultiRtti
#define RECURSION_2(a, b) RECURSION_1(a), b## ::sMultiRtti
#define RECURSION_3(a, b, c) RECURSION_2(a, b), c## ::sMultiRtti
#define RECURSION_4(a, b, c, d) RECURSION_3(a, b, c), d## ::sMultiRtti
#define RECURSION_5(a, b, c, d, e) RECURSION_4(a, b, c, d), e## ::sMultiRtti
#define RECURSION_6(a, b, c, d, e, f) RECURSION_5(a, b, c, d, e), f## ::sMultiRtti
#define RECURSION_7(a, b, c, d, e, f, g) RECURSION_6(a, b, c, d, e, f), g## ::sMultiRtti
#define RECURSION_8(a, b, c, d, e, f, g, h) RECURSION_7(a, b, c, d, e, f, g), h## ::sMultiRtti
#define RECURSION_9(a, b, c, d, e, f, g, h, i) RECURSION_8(a, b, c, d, e, f, g, h), i## ::sMultiRtti
#define RECURSION_10(a, b, c, d, e, f, g, h, i, j) RECURSION_9(a, b, c, d, e, f, g, h, i), j## ::sMultiRtti
#define RECURSION_11(a, b, c, d, e, f, g, h, i, j, k) RECURSION_10(a, b, c, d, e, f, g, h, i, j), k## ::sMultiRtti
#define RECURSION_12(a, b, c, d, e, f, g, h, i, j, k, l) RECURSION_11(a, b, c, d, e, f, g, h, i, j, k), l## ::sMultiRtti
#define RECURSION_13(a, b, c, d, e, f, g, h, i, j, k, l, m) RECURSION_12(a, b, c, d, e, f, g, h, i, j, k, l), m## ::sMultiRtti
#define RECURSION_14(a, b, c, d, e, f, g, h, i, j, k, l, m, n) RECURSION_13(a, b, c, d, e, f, g, h, i, j, k, l, m), n## ::sMultiRtti
#define RECURSION_15(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o) RECURSION_14(a, b, c, d, e, f, g, h, i, j, k, l, m, n), o## ::sMultiRtti
#define RECURSION_16(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) RECURSION_15(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o), p## ::sMultiRtti

/*__VA_ARGS__用連結インターフェースマクロ*/
#define CONCATENATE_UPD(x, y) x##y
#define CONCATENATE(x, y) CONCATENATE_UPD(x, y)
#define CONCATENATE_MULTI_RTTI(...) CONCATENATE(RECURSION_, VA_ARGS_SIZE(__VA_ARGS__))(__VA_ARGS__)
```


``

```

