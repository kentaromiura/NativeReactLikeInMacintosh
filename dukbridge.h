#ifndef DUKBRIDGE_H
#define DUKBRIDGE_H
#include "duktape.h"
duk_ret_t DUK_DIALOG(duk_context *ctx);
duk_ret_t DUK_MessageBox(duk_context *ctx);

void emptyStack(duk_context *ctx);
void populateCtx(duk_context *ctx);
#endif