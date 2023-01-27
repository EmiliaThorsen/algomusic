void writeStr(char **content, int x, int y, char *str);

struct screen *baseScreenBuilder(char *name, int id, char **(*renderer)(int, int, int));
