extern uint8_t outputBuf[128];
extern uint16_t VCP_DataTx (uint8_t* Buf, uint32_t Len);
#define printf(x, ...) do {                           \
        sprintf(outputBuf, x, ##__VA_ARGS__);                       \
        VCP_DataTx (outputBuf, strlen(outputBuf));    \
    } while(0)                                      \
