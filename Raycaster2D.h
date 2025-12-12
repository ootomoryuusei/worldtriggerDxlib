#pragma once  
#include"HitInfo.h"
#include <vector>

class Object2D;

using std::vector;

class Raycaster2D {  
public:  
   vector<Object2D*> elements_; // UI—v‘f  

   // UI ‚ğ“o˜^  
   void Register(Object2D* ui);
   // UI ‚ğíœ  
   void Unregister(Object2D* ui);
   // RaycastiÅ‘O–Ê‚ÌUI‚ğ•Ô‚·j  
   HitInfo Raycast(float mx, float my);
};
