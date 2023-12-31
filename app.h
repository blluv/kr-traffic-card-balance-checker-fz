#ifndef APP_H
#define APP_H

#include <gui/gui.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/widget.h>
#include <gui/modules/dialog_ex.h>

#include <lib/nfc/nfc.h>
#include <lib/nfc/protocols/iso14443_4a/iso14443_4a_poller.h>

typedef enum { AppViewWaitingText, AppViewDialog } AppView;
typedef enum { BalanceReadEvent } AppEvent;

typedef struct App {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;
    Widget* widget;

    Nfc* nfc;
    NfcPoller* poller;

    BitBuffer* tx;
    BitBuffer* rx;

    DialogEx* dialog;

    char text[100];
    int32_t balance;
} App;

App* app_alloc();
void app_free(App* app);
bool app_custom_callback(void* context, uint32_t custom_event);
bool app_back_event_callback(void* context);

#endif