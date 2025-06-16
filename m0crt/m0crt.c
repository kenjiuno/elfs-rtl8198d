#include "m0crt.h"

#include <stdarg.h>

extern int main();

// by gpt-4 →

// UART レジスタの定義
#define UART_BASE 0xB8002000
#define UART_THR (UART_BASE + 0x00) // トランスミッタ ホールディング レジスタ
#define UART_LSR (UART_BASE + 0x14) // ライン ステータス レジスタ

#define UART_LSR_THRE 0x20 // トランスミットホールドレジスタ空フラグ

#define REGWB(addr, value)                     \
	do                                         \
	{                                          \
		*(volatile uint8_t *)(addr) = (value); \
	} while (0)

#define REGRB(addr) (*(volatile uint8_t *)(addr))

void uart_putc(char c)
{
	// トランスミッタフィフォが空になるのを待ちます
	while ((REGRB(UART_LSR) & UART_LSR_THRE) == 0)
		;

	// トランスミッタホールディングレジスタに文字を書き込みます
	REGWB(UART_THR, c);
}

// ← by gpt-4

int putchar(int c)
{
	uart_putc(c);
	if (c == '\n')
	{
		uart_putc('\r'); // 改行の後にキャリッジリターンを送信
	}
	return 1;
}

int entry()
{
	return main();
}

// by gpt-4 →

static void print_char(char c)
{
	putchar(c);
}

static void print_string(const char *str)
{
	while (*str)
	{
		print_char(*str++);
	}
}

static const char hexu_digits[] = "0123456789ABCDEF";
static const char hexl_digits[] = "0123456789abcdef";

static void print_number(long num, int base, int minWidth, int padZero, const char *digits)
{
	char buffer[20]; // バッファは長さの十分あるサイズを選択
	int pos = 0;
	int negative = 0;

	if (num < 0 && base == 10)
	{
		negative = 1;
		num = -num;
	}

	do
	{
		int digit = num % base;
		buffer[pos++] = digits[digit];
		num /= base;
	} while (num != 0);

	if (negative)
	{
		buffer[pos++] = '-';
	}

	while (pos < minWidth)
	{
		buffer[pos++] = (padZero) ? '0' : ' ';
	}

	while (--pos >= 0)
	{
		print_char(buffer[pos]);
	}
}

int printf(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++; // '%'の次の文字に進む
			int min_width = 0;
			int pad_zero = 0;

			if (*fmt == '0') // パディング文字がゼロの場合
			{
				pad_zero = 1;
				fmt++;
			}

			// 最小幅指定
			while (*fmt >= '0' && *fmt <= '9')
			{
				min_width = min_width * 10 + (*fmt - '0');
				fmt++;
			}

			switch (*fmt)
			{
			case 'd':
			{
				int val = va_arg(args, int);
				if (val < 0)
				{
					putchar('-');
					val = -val;
				}
				print_number(val, 10, min_width, pad_zero, hexl_digits);
				break;
			}
			case 'u':
				print_number(va_arg(args, unsigned), 10, min_width, pad_zero, hexl_digits);
				break;
			case 'x':
				print_number(va_arg(args, unsigned), 16, min_width, pad_zero, hexl_digits);
				break;
			case 'X':
				print_number(va_arg(args, unsigned), 16, min_width, pad_zero, hexu_digits);
				break;
			case 'p':
				print_string("0x");
				print_number((unsigned long)va_arg(args, void *), 16, min_width, pad_zero, hexl_digits);
				break;
			case 's':
				print_string(va_arg(args, char *));
				break;
			default:
				print_char('%');
				print_char(*fmt); // '%'の後ろの文字
			}
		}
		else
		{
			putchar(*fmt);
		}
		fmt++;
	}

	va_end(args);

	return 1;
}

// ← by gpt-4

int puts(const char *str)
{
	print_string(str);
	print_char('\n');
	return 1;
}
