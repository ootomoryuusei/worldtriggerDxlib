#include "gameObject.h"
#include <assert.h>
#include "global.h"

//�R���X�g���N�^�i�e�����O���Ȃ��j
GameObject::GameObject(void) :
	GameObject(nullptr, "")
{

}

//�R���X�g���N�^�i���O�Ȃ��j
GameObject::GameObject(GameObject * parent) :
	GameObject(parent, "")
{
}

//�R���X�g���N�^�i�W���j
GameObject::GameObject(GameObject * parent, const std::string& name)
	: pParent_(parent),



	objectName_(name)
{
	childList_.clear();
	state_ = { 0, 1, 1, 0 };

	if(parent)
		transform_.pParent_ = &parent->transform_;

}

//�f�X�g���N�^
GameObject::~GameObject()
{
}

// �폜���邩�ǂ���
bool GameObject::IsDead()
{
	return (state_.dead != 0);
}

// �������폜����
void GameObject::KillMe()
{
	state_.dead = 1;
}

// Update������
void GameObject::Enter()
{
	state_.entered = 1;
}

// Update������
void GameObject::Leave()
{
	state_.entered = 0;
}

// Draw������
void GameObject::Visible()
{
	state_.visible = 1;
}

// Draw������
void GameObject::Invisible()
{
	state_.visible = 0;
}

// �������ς݂��ǂ���
bool GameObject::IsInitialized()
{
	return (state_.initialized != 0);
}

// �������ς݂ɂ���
void GameObject::SetInitialized()
{
	state_.initialized = 1;
}

// Update���s���Ă�����
bool GameObject::IsEntered()
{
	return (state_.entered != 0);
}

// Draw���s���Ă�����
bool GameObject::IsVisibled()
{
	return (state_.visible != 0);
}

//�q�I�u�W�F�N�g���X�g���擾
std::list<GameObject*>* GameObject::GetChildList()
{
	return &childList_;
}

//�e�I�u�W�F�N�g���擾
GameObject * GameObject::GetParent(void)
{
	return pParent_;
}

//���O�ŃI�u�W�F�N�g�������i�Ώۂ͎����̎q���ȉ��j
GameObject * GameObject::FindChildObject(const std::string & name)
{
	//�q�������Ȃ��Ȃ�I���
	if (childList_.empty())
		return nullptr;

	//�C�e���[�^
	auto it = childList_.begin();	//�擪
	auto end = childList_.end();	//����

	//�q�I�u�W�F�N�g����T��
	while (it != end) {
		//�������O�̃I�u�W�F�N�g���������炻���Ԃ�
		if ((*it)->GetObjectName() == name)
			return *it;

		//���̎q���i���j�ȍ~�ɂ��Ȃ����T��
		GameObject* obj = (*it)->FindChildObject(name);
		if (obj != nullptr)
		{
			return obj;
		}

		//���̎q��
		it++;
	}

	//������Ȃ�����
	return nullptr;
}

//�I�u�W�F�N�g�̖��O���擾
const std::string& GameObject::GetObjectName(void) const
{
	return objectName_;
}

//�q�I�u�W�F�N�g��ǉ��i���X�g�̍Ō�ցj
void GameObject::PushBackChild(GameObject * obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_back(obj);
}

//�q�I�u�W�F�N�g��ǉ��i���X�g�̐擪�ցj
void GameObject::PushFrontChild(GameObject * obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_front(obj);
}

//�q�I�u�W�F�N�g��S�č폜
void GameObject::KillAllChildren(void)
{
	//�q�������Ȃ��Ȃ�I���
	if (childList_.empty())
		return;

	//�C�e���[�^
	auto it = childList_.begin();	//�擪
	auto end = childList_.end();	//����

	//�q�I�u�W�F�N�g��1���폜
	while (it != end)
	{
		KillObjectSub(*it);
		delete *it;
		it = childList_.erase(it);
	}

	//���X�g���N���A
	childList_.clear();
}

//�I�u�W�F�N�g�폜�i�ċA�j
void GameObject::KillObjectSub(GameObject * obj)
{
	if (!childList_.empty())
	{
		auto list = obj->GetChildList();
		auto it = list->begin();
		auto end = list->end();
		while (it != end)
		{
			KillObjectSub(*it);
			delete *it;
			it = list->erase(it);
		}
		list->clear();
	}
	obj->Release();
}


//RootJob���擾
GameObject * GameObject::GetRootJob()
{
	if (GetParent() == nullptr)
	{
		return this;
	}
	else return GetParent()->GetRootJob();
}




void GameObject::UpdateSub()
{
	if (IsEntered()) {
		Update();
	}
	Transform();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->UpdateSub();
	}

	for (auto it = childList_.begin(); it != childList_.end();)
	{
		if ((*it)->IsDead() == true)
		{
			(*it)->ReleaseSub();
			SAFE_DELETE(*it);
			it = childList_.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void GameObject::DrawSub()
{
	if (IsVisibled()) {
		Draw();
	}

	//���̎q�I�u�W�F�N�g�̕`�揈��
	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->ReleaseSub();
		SAFE_DELETE(*it);
	}

	Release();
}

////���[�J���s��̎擾�i���̃I�u�W�F�N�g�̍s��j
//XMMATRIX GameObject::GetLocalMatrix(void)
//{
//	return transform_.GetWorldMatrix();
//}

//���[���h�s��̎擾�i�e�̉e�����󂯂��ŏI�I�ȍs��j
XMMATRIX GameObject::GetWorldMatrix(void)
{
	return transform_.GetWorldMatrix();
}


bool GameObject::PointInBox(XMFLOAT2 _point, XMFLOAT2 _LeftUp, XMFLOAT2 _distance)
{
	VECTOR P1P2, P2P3, P3P4, P4P1;
	VECTOR P1P, P2P, P3P, P4P;
	XMFLOAT2 P1, P2, P3, P4;

	P1 = { _LeftUp.x,  _LeftUp.y }; //����
	P2 = { _LeftUp.x + _distance.x,  _LeftUp.y }; //�E��
	P3 = { _LeftUp.x + _distance.x,  _LeftUp.y + _distance.y }; //�E��
	P4 = { _LeftUp.x,  _LeftUp.y + _distance.y }; //����

	P1P2 = { P2.x - P1.x, P2.y - P1.y };
	P2P3 = { P3.x - P2.x, P3.y - P2.y };
	P3P4 = { P4.x - P3.x, P4.y - P3.y };
	P4P1 = { P1.x - P4.x, P1.y - P4.y };

	P1P = { _point.x - P1.x,_point.y - P1.y };
	P2P = { _point.x - P2.x,_point.y - P2.y };
	P3P = { _point.x - P3.x,_point.y - P3.y };
	P4P = { _point.x - P4.x,_point.y - P4.y };

	if (VCross(P1P2, P1P).z >= 0 && VCross(P2P3, P2P).z >= 0 && VCross(P3P4, P3P).z >= 0 && VCross(P4P1, P4P).z >= 0)
	{
		return true;
	}
	return false;
}
