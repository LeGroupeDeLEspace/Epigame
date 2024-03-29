//
// Created by Iannis on 18/07/2022.
//

#ifndef JEUDELESPACE_SCENE_HPP
#define JEUDELESPACE_SCENE_HPP

#include <GLFW/glfw3.h>
#include "Graphics.hpp"

class Scene {
public:
// Called when scene initially created. Called once.
    virtual void OnCreate() = 0;
// Called when scene destroyed. Called at most once (if a scene
// is not removed from the game, this will never be called).
    virtual void OnDestroy() = 0;
// Called whenever a scene is transitioned into. Can be
// called many times in a typical game cycle.
    virtual void OnActivate() {};
// Called whenever a transition out of a scene occurs.
// Can be called many times in a typical game cycle.
    virtual void OnDeactivate() {};
// The below functions can be overridden as necessary in our scenes.
    virtual void ProcessInput() {};
    virtual void Update(float deltaTime) {};
    virtual void LateUpdate(float deltaTime) {};
    virtual void Draw(gr::Graphics& graphics) {};
};


#endif //JEUDELESPACE_SCENE_HPP
