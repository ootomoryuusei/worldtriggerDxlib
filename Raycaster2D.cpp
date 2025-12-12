#include "Raycaster2D.h"
#include"Object2D.h"
#include <algorithm>

using std::remove;

void Raycaster2D::Register(Object2D* ui)
{
    elements_.push_back(ui);
}

void Raycaster2D::Unregister(Object2D* ui)
{
    elements_.erase(
        remove(elements_.begin(), elements_.end(), ui),
        elements_.end()
    );
}

HitInfo Raycaster2D::Raycast(float mx, float my)
{
    HitInfo best;
    best.type = HitTargetType::NONE;

    int index = 0;
    int bestZ = -99999;

    for (auto* element : elements_) {

        if (!element->IsVisibled()) continue; //非表示ならスキップ  

        if (element->IsInMousePoint({ mx, my })) {

            if (!best.IsHit()) {
                best.type = HitTargetType::UI;
                best.target = (GameObject*)element;
                best.distance = 0.0f;
            }
        }
        index++;
    }
    return best;
}
