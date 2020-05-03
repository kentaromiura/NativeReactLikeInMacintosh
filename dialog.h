#ifndef DIALOG_H
#define DIALOG_H
#include <stdbool.h>

bool ShowAlert(char *message);
bool ShowDialog(char *message, char *title, char *ok, char *cancel);

#endif