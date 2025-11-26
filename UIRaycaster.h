#pragma once
#include <vector>
#include "Object2D.h"
#include "HitInfo.h"

class UIRaycaster {
public:
    // UI ‚ð“o˜^
    void Register(Object2D* ui) {
        elements_.push_back(ui);
    }

    // UI ‚ðíœ
    void Unregister(Object2D* ui) {
        elements_.erase(
            std::remove(elements_.begin(), elements_.end(), ui),
            elements_.end()
        );
    }

    // RaycastiÅ‘O–Ê‚ÌUI‚ð•Ô‚·j
    HitInfo Raycast(float mx, float my) {
        HitInfo best;
        best.type = HitTargetType::NONE;

        int index = 0;
        int bestZ = -99999;

        for (auto* element : elements_) {

            if (!element->IsVisibled()) continue;

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
private:
    std::vector<Object2D*> elements_; // UI—v‘f
};
