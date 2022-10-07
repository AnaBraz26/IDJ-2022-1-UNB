#include "../include/Component.h"
#include <stdio.h>
#include <string>

Component :: Component(GameObject &associated): associated(associated){

}
Component :: ~Component(){

}

void  Component :: Update(float dt){

}

void  Component :: Render(){

}

bool  Component :: Is(std :: string type){

}