#ifndef SCENES_H
#define SCENES_H

#include <gui/scene_manager.h>

typedef enum {
    AppSceneWaiting,
    AppSceneResult,
    AppSceneNum,
} AppScene;

extern const SceneManagerHandlers app_scene_event_handlers;

#endif