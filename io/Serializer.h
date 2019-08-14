#ifndef FINAL_PROJECT_LOADER_H
#define FINAL_PROJECT_LOADER_H

#include "../components/Board.h"
#include "Error.h"

Board* load_from_file(char *path, Error *error);

#endif
