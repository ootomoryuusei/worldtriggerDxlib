#pragma once
#include <vector>
#include "Object2D.h"
#include "HitInfo.h"

using std::vector;

class Raycaster2D {
public:
    vector<Object2D*> elements_; // UI要素

    // UI を登録
    void Register(Object2D* ui) {
        elements_.push_back(ui);
    }

    // UI を削除
    void Unregister(Object2D* ui) {
        elements_.erase(
            remove(elements_.begin(), elements_.end(), ui),
            elements_.end()
        );
    }

    // Raycast（最前面のUIを返す）
    HitInfo Raycast(float mx, float my) {
        HitInfo best;
        best.type = HitTargetType::NONE;

        int index = 0;
        int bestZ = -99999;

        for (auto* element : elements_) {

            if (!element->IsVisibled()) continue; //非表示ならスキップ

            if (element->IsInMousePoint({ mx, my })) {

                if (!best.IsHit()) {
                    best.type = HitTargetType::UI;
                    best.target = element;
                    best.distance = 0.0f;
                }
            }
            index++;
        }
        return best;
    }
};
