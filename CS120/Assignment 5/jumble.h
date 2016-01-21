enum CODE_METHOD {ENCODE, DECODE};

int mystrlen(const unsigned char *string);

void jumble(unsigned char *string, 
            const unsigned char *password, 
            enum CODE_METHOD method, 
            int passes);