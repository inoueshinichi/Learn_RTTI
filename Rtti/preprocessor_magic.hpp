/**
 * @file preprocessor_magic.hpp
 * @author Shinichi Inoue (inoue.shinichi.1800@gmail.com)
 * @brief 可変長マクロを捏ねくり回す
 * @version 0.1
 * @date 2023-03-04
 *
 * @copyright Copyright (c) 2023
 *
 */
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

// // e.g OK
// VA_ARGS_SIZE(A, B, C, D, E, F, G, H, I, J)
// CONCATENATE_MULTI_RTTI(A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P)

// RECURSION_1(GameMultiPlayer)