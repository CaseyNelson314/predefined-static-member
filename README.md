# predefined-static-member

定義済みの静的メンバ変数を作成するマクロ。

## API

-   `CREATE_STATIC_VARIABLE(Ty, Name)`

    静的メンバ変数を作成

    `@param Ty` 変数の型

    `@param Name` 変数名

-   `CREATE_STATIC_ARRAY(Ty, N, Name)`

    静的メンバ配列を作成

    `@param Ty` 要素の型

    `@param N` 要素数

    `@param Name` 配列名

-   `ACCESS_STATIC_VARIABLE(Name)`

    静的メンバ変数にアクセス

    `@param Name` 変数名

## Summary

静的メンバ変数を持つ場合、以下のようにソースファイル内で定義する必要があります。

変数定義のためにソースファイルを追加するのはファイルが増えてイヤ。

```cpp
/// sample.h
class Sample {
public:
	static int value;
};

/// sample.cpp
#include "sample.h"
int Sample::value;  /// 定義
```

しかし関数が静的変数を持つ場合外部での定義は不要なため、静的変数の参照を返すことで静的メンバ変数であるように振る舞うことができます。

```cpp
/// sample.h ✨
class Sample {
public:
	int& value() {
		static int value;
		return value;
	}
	void f() {
		value() = 1234;   /// write
		int a = value();  /// read
	}
};
```

`CREATE_STATIC_VARIABLE`, `CREATE_STATIC_ARRAY` はこのような振る舞いを利用して静的メンバ変数を作成します。

## Example

```cpp
#include <iostream>

#include "PredefinedStaticMember.h"

class MyClass {
	CREATE_STATIC_VARIABLE(int, value)
public:
	MyClass() {
		ACCESS_STATIC_VARIABLE(value)++;
	}
	~MyClass() {
		ACCESS_STATIC_VARIABLE(value)--;
	}
	void print(std::ostream& os) const {
		os << ACCESS_STATIC_VARIABLE(value);
	}
};

int main() {
	MyClass a;

	a.print(std::cout);
	std::cout << std::endl;

	MyClass b;

	a.print(std::cout);
	std::cout << std::endl;
}

/// console
/// 1
/// 2
```

## Attention

型に `,` が含まれる `std::array<Ty, N>` のような場合、関数マクロの仕様上、別々の引数 `std::array<Ty` と `N>` であると解析されるため、以下のようにする必要があります。

```cpp
/// NG
CREATE_STATIC_VARIABLE(std::array<int, 10>, value)

/// OK
using Type = std::array<int, 10>;
CREATE_STATIC_VARIABLE(Type, value)
```
