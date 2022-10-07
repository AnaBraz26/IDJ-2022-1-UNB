#include "GameObject.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Camera.h"
#include "Sprite.h"
#include <stdio.h>
#include <string>

#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

class CameraFollower: public Component{
public:
    CameraFollower(GameObject& go);
    void Update(float dt);
    void Render();
    bool Is(std::string type);

};

#endif