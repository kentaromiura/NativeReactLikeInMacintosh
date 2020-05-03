#include <Quickdraw.h>
#include <Dialogs.h>
#include <Fonts.h>
#include <stdbool.h>
#include <Resources.h>

// This is probably not needed to save space, 
// in case you encounter any issues aliasing builtins remove this.
#define DUK_USE_LIGHTFUNC_BUILTINS

#include "duktape.h"
#include "dukbridge.h"
#include "dialog.h"

void Initialize();
void MainLoop();
void Terminate();

int main()
{
    Initialize();
    MainLoop();
    Terminate();
    return 0;
}

void Initialize()
{
#if !TARGET_API_MAC_CARBON
    InitGraf(&qd.thePort);
    InitFonts();
    InitWindows();
    InitMenus();
    TEInit();
    InitDialogs(NULL);
#endif
}

char * readFromResource(int resourceId) {
    Handle hnd = GetResource('TEXT', resourceId); 
    long size = GetResourceSizeOnDisk(hnd);
    char * out = malloc(size + 1);    
    ReadPartialResource(hnd, 0, out, size);
    out[size] = '\0';
    return out;
}

void MainLoop()
{
    char * fakeReact = readFromResource(129); // app/fakeReact.js
    
    duk_context *ctx = duk_create_heap_default();
    duk_eval_string(ctx, fakeReact);
    free(fakeReact);
    emptyStack(ctx);

    populateCtx(ctx);
    emptyStack(ctx);  

    char * source = readFromResource(128); // app/index.js
    duk_eval_string(ctx, source);
    free(source);
    emptyStack(ctx);

    duk_eval_string(ctx, "React.mount(main())");
    emptyStack(ctx); 
}

void Terminate()
{
    ExitToShell();
}
