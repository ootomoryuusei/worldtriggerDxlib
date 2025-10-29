#pragma once
#include "Object3D.h"
#include<vector>

using std::vector;
using std::string;

struct MOVEMENT {
    VECTOR movement;
    string movename;
};

class Icon :
    public Object3D
{
protected:
    SIZE_F_2D graphSizeF_; //�A�C�R���̉摜�T�C�Y(float)
    SIZE_2D graphSize_; //�A�C�R���̉摜�T�C�Y
    XMFLOAT2 graphPos_; //�A�C�R���̈ʒu
    string fileName_; //�t�@�C����
    string iconName_; //icon�̖��O
    bool selecting_; //�Z���N�g����Ă��邩�ǂ���
    int createNum_; //�쐬�ԍ�
    VECTOR scale_; //�X�P�[��
    int fontHandle_; //�t�H���g�̃n���h��
    XMFLOAT2 prevMousePos_; 

    XMFLOAT2 center_pos; //�摜����]�`�悷��摜��̒��S���W
    float angle; //�`��p�x
public:
    Icon(GameObject* parent);
    Icon(GameObject* parent,const string& name);
    ~Icon();
    virtual void Update() override;
    virtual void Draw() override;

    ////�N���b�N�n
    //virtual void OnClick() = 0;
    //virtual void OnDoubleClick() = 0;
    //virtual void OnDrag() = 0;

    /// <summary>
    /// �摜�̃��[�h
    /// </summary>
    /// <param name="_fileName">�t�@�C���̃p�X</param>
    void Load(const std::string& _fileName);

    string GetFileName() { return fileName_; }
    SIZE_F_2D GetGraphSizeF_2D() { return graphSizeF_; }
    SIZE_2D GetGraphSize_2D() { return graphSize_; }

    void SetSelecting(bool _selecting) { selecting_ = _selecting; }
    bool GetSelecting() { return selecting_; }

    void SetCreateNum(int _createNum) { createNum_ = _createNum; } 
    int GetCreateNum() { return createNum_; }

    void SetScale(VECTOR _scale) { scale_ = _scale; }
    VECTOR GetScale() { return scale_; }

    void SetIconName(string _iconName) { iconName_ = _iconName; }
    string GetIconName() { return iconName_; }

    void SetFontHandle(int _fontHandle) { fontHandle_ = _fontHandle; }

    /// <summary>
    /// �A�C�R���̃G���A(�摜�͈�)���Ƀ}�E�X�̃|�C���g�����邩�ǂ���
    /// </summary>
    /// <param name="m_pos"> �}�E�X�̈ʒu </param>
    /// <returns></returns>
    bool IsInMousePoint(XMFLOAT2 m_pos);

    XMFLOAT2 GetGraphPos() { return graphPos_; }
private:
};
