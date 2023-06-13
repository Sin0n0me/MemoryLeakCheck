#include <crtdbg.h>
#include <memory>

class HogeHoge {
public:
	~HogeHoge() {
		printf("HogeHoge!\n");
	}
};

class Hoge : HogeHoge {
public:
	~Hoge() {
		printf("Hoge!\n");
	}
};

class Fuga : public Hoge {
private:
	std::unique_ptr<int> intKun;
public:
	Fuga(int* a) : intKun(a) {};
	~Fuga() {
		printf("Fuga\n");
	}
};

int main(void) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// プログラム終了時に自動で _CrtDumpMemoryLeaks();が呼ばれる

	// HogeHogeクラスのデストラクタは呼ばれるが Fuga クラスのデストラクタは呼ばれない
	// つまりstd::unique_ptr<int> intKun;のデストラクタが呼ばれずメモリリークを起こす
	Hoge* hoge = new Fuga(new int);
	delete hoge;

	// 問題なし
	Fuga* fuga = new Fuga(new int);
	delete fuga;

	return 0;
}
