#include <Quickdraw.h>
#include <Dialogs.h>
#include <Fonts.h>
#include <stdbool.h>
#include "types.h"
#include "utils.h"

#ifndef TARGET_API_MAC_CARBON
/* NOTE: this is checking whether the Dialogs.h we use *knows* about Carbon,
             not whether we are actually compiling for Cabon.
             If Dialogs.h is older, we add a define to be able to use the new name
             for NewUserItemUPP, which used to be NewUserItemProc. */

#define NewUserItemUPP NewUserItemProc
#endif

// define position in resource dialog.r (128)
#define MessageBoxOK 1
#define MessageBoxMessage 2
#define MessageBoxCancel 3
#define MessageBoxTitle 4

#define AlertOK 1
#define AlertMessage 2

bool ShowAlert(char *message) {
    DialogItemType type;
    Handle controlHandle;
    Rect box;
    
    DialogPtr adlg = GetNewDialog(129,0,(WindowPtr)-1);
    InitCursor();
    {
        GetDialogItem(adlg, AlertMessage, &type, &controlHandle, &box);
        PString _message = toPascal(message);
        SetDialogItemText(controlHandle, toConstStr255Param(_message));
    }
    ShowWindow(adlg);
    
    short itemHit = NULL;

    while (itemHit != AlertOK) {
        ModalDialog(NULL, &itemHit);
    }
    DisposeDialog(adlg);
    FreeDialog(129);
    return true;
}

bool ShowDialog(char *message, char *title, char *ok, char *cancel) {
    DialogItemType type;
    Handle controlHandle;
    Rect box;

    DialogPtr dlg = GetNewDialog(128,0,(WindowPtr)-1);
    InitCursor();
    
    {
        GetDialogItem(dlg, MessageBoxMessage, &type, &controlHandle, &box);
        PString _message = toPascal(message);
        SetDialogItemText(controlHandle, toConstStr255Param(_message));

        GetDialogItem(dlg, MessageBoxTitle, &type, &controlHandle, &box);
        PString _title = toPascal(title);
        SetDialogItemText(controlHandle, toConstStr255Param(_title));

        GetDialogItem(dlg, MessageBoxOK, &type, &controlHandle, &box);  
        PString _ok = toPascal(ok);
        SetControlTitle(controlHandle, toConstStr255Param(_ok));
        
        GetDialogItem(dlg, MessageBoxCancel, &type, &controlHandle, &box);
        PString _cancel = toPascal(cancel);
        SetControlTitle(controlHandle, toConstStr255Param(_cancel));
    }
    ShowWindow(dlg);
    short itemHit = NULL;

    while (itemHit != MessageBoxOK && itemHit != MessageBoxCancel) {
        ModalDialog(NULL, &itemHit);
    }
    DisposeDialog(dlg);
    return itemHit == MessageBoxOK;
}
