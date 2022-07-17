enum flags {
    running,
    playing,
    flagCount
};


void setGlobalVariable(enum flags, int);
int getGlobalVariable(enum flags);
void initGlobalVariables();
void freeGlobalVariables();
