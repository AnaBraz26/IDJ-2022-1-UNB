#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Component.h"
#include "Rect.h"
#include <vector>
#include <stdio.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <memory>
using namespace std;


class Component;

class GameObject {
private:
    vector <unique_ptr<Component>> components;
    bool isDead;
  
public: 
    GameObject();
    ~GameObject();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(string type);
    Rect box;

    //Trabalho 5
    void Start();
    bool started;
    double angleDeg;
};

#endif 