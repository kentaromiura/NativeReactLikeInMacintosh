// This file is almost the same used for windows 3.1 (save for LPCStrings and minor things)
#include "dukbridge.h"
#include "dialog.h"

void populateCtx(duk_context *ctx) {
    duk_get_global_string(ctx, "React"); //0
    duk_get_prop_string(ctx, -1, "duktape"); //1
    duk_push_c_lightfunc(ctx, DUK_DIALOG, 4,4,0); //2
    duk_put_prop_string(ctx, -2, "showDialog");

    duk_push_c_lightfunc(ctx, DUK_MessageBox, 1,1,0);
    duk_put_prop_string(ctx, -2, "showMessageBox");
}

void emptyStack(duk_context *ctx) {
    duk_idx_t idx_top;
    do {
        idx_top = duk_get_top_index(ctx);
        if (idx_top != DUK_INVALID_INDEX) duk_pop(ctx);
    } while(idx_top != DUK_INVALID_INDEX);
}

duk_ret_t DUK_DIALOG(duk_context *ctx) {
    
    duk_idx_t top = duk_get_top(ctx);
    char* title = duk_safe_to_string(ctx, 0);
    char* message = duk_safe_to_string(ctx, 1);

    int ok = ShowDialog(message, title, "Yes", "No");
    if (ok) {
        duk_dup(ctx, 2);
    } else {
        duk_dup(ctx, 3);
    }
    duk_call(ctx, 0);
    duk_pop_n(ctx, 5);
    return 0;
}

duk_ret_t DUK_MessageBox(duk_context *ctx) {
    const char* message = duk_safe_to_string(ctx, 0);
    ShowAlert(message);
    duk_pop(ctx);
    return 0;
}
