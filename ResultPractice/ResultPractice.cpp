// ResultPractice.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "Result3.h"

Result<int, std::string> ParseDigit(char c) {
    if (c < '0' || '9' < c) {
        return Error("invalid character");
    }

    return Ok(c - '0');
}

int main()
{
    Result<int, std::string> result_ok = ParseDigit('4');
    if (result_ok.Valid())
    {
        int num = result_ok.Get();
        // 4
    }

    Result<int, std::string> result_err = ParseDigit('g');
    if (!result_err.Valid())
    {
        std::string num = result_err.GetError();
        // "invalid character"
    }











    std::cout << "Hello World!\n";
    auto res = ParseDigit('4');
    std::cout << (res.Valid() ? "Valid" : "Invalid") << std::endl;
    std::cout << res.Get() << std::endl;
    auto res2 = ParseDigit('d');
    std::cout << (res2.Valid() ? "Valid" : "Invalid") << std::endl;
    std::cout << res2.GetError() << std::endl;


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
