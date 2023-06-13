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

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// �v���O�����I�����Ɏ����� _CrtDumpMemoryLeaks();���Ă΂��

	// HogeHoge�N���X�̃f�X�g���N�^�͌Ă΂�邪 Fuga �N���X�̃f�X�g���N�^�͌Ă΂�Ȃ�
	// �܂�std::unique_ptr<int> intKun;�̃f�X�g���N�^���Ă΂ꂸ���������[�N���N����
	Hoge* hoge = new Fuga(new int);
	delete hoge;

	// ���Ȃ�
	Fuga* fuga = new Fuga(new int);
	delete fuga;

	return 0;
}
