// ResultPractice.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
using namespace std;
using namespace std::string_literals;
#include "Result6.hpp"

#include <cassert>

Result<int, std::string> ParseDigit(char c) 
{
    if (c < '0' || '9' < c) 
    {
        return Err(std::string("invalid character"));
    }
    return Ok(c - '0');
}

void ArrayCharTest() 
{
    Result<int, std::string> ret = Err("invalid test"s);
    if (!ret.Valid()) cout << ret.GetError() << endl;
}

class TestClass
{
public:
    int n;
    char sz[32];
};

void StructRetTest()
{
    struct S1
    {
        //S1() = default;
        //S1(S1&&) = delete;
        int n;
        char sz[32];
    };

    struct S2
    {
        std::string str;
        wchar_t wsz[1024];
        unsigned long ul;
    };

    {
        S1 s1 = { 1234, "0123456789012345678901234567890" };
        Result<S1, S2> ret = Ok(s1);

        assert(ret.Valid());
        assert(ret.Get().n == 1234);
        std::string str1 = ret.Get().sz;
        assert(str1.compare("0123456789012345678901234567890") == 0);
    }

    {
        TestClass c1 = { 1234, "0123456789012345678901234567890" };
        Result< TestClass, S1> ret_class = Ok(c1);

        assert(ret_class.Valid());
        assert(ret_class.Get().n == 1234);
        std::string str_class = ret_class.Get().sz;
        assert(str_class.compare("0123456789012345678901234567890") == 0);
    }
}


int main()
{
    auto result_ok = ParseDigit('4');
    if (result_ok.Valid())
    {
        int num = result_ok.Get();
        cout << result_ok.Get() << endl;
        // 4
    }

    Result<int, std::string> result_err = ParseDigit('g');
    if (!result_err.Valid())
    {
        std::string num = result_err.GetError();
        cout << result_err.GetError() << endl;
        // "invalid character"
    }

    ArrayCharTest();
    StructRetTest();

    return 0;
}


// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
