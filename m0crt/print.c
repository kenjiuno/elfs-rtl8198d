#include "m0crt.h"

int main()
{
	// テスト用の文字列を出力
	printf("Hello, World!\n");

	// 数値の出力
	printf("Number: %d\n", 42);

	// 16進数の出力
	printf("Hex: %x\n", 0x2A);

	// 最小幅指定の出力
	printf("Padded Number: %5d\n", 7);

	// パディング文字の指定
	printf("Zero Padded: %05d\n", 7);

	// 改行
	printf("\n");
	return 0;
}
