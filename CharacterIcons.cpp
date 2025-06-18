#include "CharacterIcons.h"
#include"Mouse.h"

CharacterIcons::CharacterIcons(GameObject* parent) : Icon(parent)
{
	csv_ = new CsvReader();
	csv_->Load("Assets//Character//CharacterStatus.csv");
	FN2DLine = 0;
	DLC = "Assets//Image//CharacterIcon//selectCIcon//";
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "FileName2D") {
			FN2DLine = x;
		}
	}
	for (int y = 1; y < csv_->GetHeight(); y++) {
		std::string graphName;
		graphName = csv_->GetString(FN2DLine, y);
		std::string flPath;
		flPath = DLC + graphName;
		CharacterIcon* pCIcon = Instantiate<CharacterIcon>(this);
		pCIcon->Load(flPath);
		SIZE_F_2D IconSize = pCIcon->GetGraphSizeF_2D();
		VECTOR graphPos = { 0,300 + IconSize.y * (y - 1) ,0 };
		pCIcon->SetInitialPosition(graphPos);
		pCIcon->Set3DPosition(graphPos);
		pCIcon->SetNum(y);
		pCIcon->SetIconName(csv_->GetString(0, y));
		pCIcons_.push_back(pCIcon);
	}
}

CharacterIcons::~CharacterIcons()
{
}

void CharacterIcons::Update()
{
	Mouse* pMouse = GetParent()->GetParent()->FindGameObject<Mouse>();
	XMFLOAT2 mousePos = pMouse->GetMousePos();

	if (canVisible_) {
		// �S�A�C�R�����������i�\��ON�E�I�������j
		for (auto& itr : pCIcons_) {
			if (!itr->GetCanVisible()) {
				itr->SetCanVisible(true);
			}
			itr->SetSelecting(false); // �܂��S�Ĕ�I���ɂ���
		}

		// 1�����I������
		for (auto& itr : pCIcons_) {
			XMFLOAT2 leftUp = { itr->Get3DPosition().x,itr->Get3DPosition().y };
			XMFLOAT2 distance = { itr->GetGraphSizeF_2D().x,itr->GetGraphSizeF_2D().y };
			if (PointInBox(mousePos, leftUp, distance)) {
				itr->SetSelecting(true); // �ŏ��Ɍ�����1�����I��
				break; // ���̉~�ʂ͖����i�����I��h�~�j
			}
		}
	}
	else {
		for (auto& itr : pCIcons_) {
			itr->SetCanVisible(false);
		}
	}
}

void CharacterIcons::Draw()
{
}
