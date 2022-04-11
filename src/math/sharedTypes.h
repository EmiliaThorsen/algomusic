typedef struct {
    int type;
    union {
        float *f;
        float _Complex *cf;
    };
} mixBuff;


typedef struct {
    int type;
    union {
    int ID;
    mixBuff data;
    };
} instruction;
