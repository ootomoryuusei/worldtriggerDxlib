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
    SIZE_F_2D graphSizeF_; //アイコンの画像サイズ(float)
    SIZE_2D graphSize_; //アイコンの画像サイズ
    XMFLOAT2 graphPos_; //アイコンの位置
    string fileName_; //ファイル名
    string iconName_; //iconの名前
    bool canVisible_; //iconを表示するかしないか
    bool selecting_; //セレクトされているかどうか
    int num_;
    int createNum_; //作成番号
    VECTOR scale_; //スケール
    int fontHandle_; //フォントのハンドル
    XMFLOAT2 prevMousePos_; 

    XMFLOAT2 center_pos; //画像を回転描画する画像上の中心座標
    float angle; //描画角度
public:
    Icon(GameObject* parent);
    Icon(GameObject* parent,const string& name);
    ~Icon();
    virtual void Update() override;
    virtual void Draw() override;

    void Load(const std::string& _fileName);

    string GetFileName() { return fileName_; }
    SIZE_F_2D GetGraphSizeF_2D() { return graphSizeF_; }
    SIZE_2D GetGraphSize_2D() { return graphSize_; }

    void SetCanVisible(bool _canVisible) { canVisible_ = _canVisible; }
    bool GetCanVisible() { return canVisible_; }

    void SetSelecting(bool _selecting) { selecting_ = _selecting; }
    bool GetSelecting() { return selecting_; }

    void SetNum(int _num) { num_ = _num; }
    int GetNum() { return num_; }

    void SetCreateNum(int _createNum) { createNum_ = _createNum; } 
    int GetCreateNum() { return createNum_; }

    void SetScale(VECTOR _scale) { scale_ = _scale; }
    VECTOR GetScale() { return scale_; }

    void SetIconName(string _iconName) { iconName_ = _iconName; }
    string GetIconName() { return iconName_; }

    void SetFontHandle(int _fontHandle) { fontHandle_ = _fontHandle; }

    /// <summary>
    /// アイコンのエリア内にマウスのポイントがあるかどうか
    /// </summary>
    /// <param name="m_pos"> マウスの位置 </param>
    /// <returns></returns>
    bool IsInMousePoint(XMFLOAT2 m_pos);

   

    XMFLOAT2 GetGraphPos() { return graphPos_; }
private:
};
