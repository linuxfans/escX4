#include "stdlib.h"
#include "string.h"
#include "global_includes.h"
#include "motor.h"
#include "shell.h"

extern uint16_t VCP_DataTx (uint8_t* Buf, uint32_t Len);
#define KEY_BACKSPACE 127
uint8_t shellBuf[128];
uint32_t shellBufCnt;

typedef struct 
{
    void (*cmdFunc) (uint8_t *param);
    uint8_t *name;
    const uint8_t *info;
} shellCmd_t;
uint8_t outputBuf[128];

#define DEFINE_CMD(name) \
    {                    \
        cmdFunc##name, #name, info##name        \
            }                                   


const uint8_t infoHelp[] = "Test\r\n";

void cmdFuncHelp(char *param) 
{
    printf("Hello, I'm help function %s\r\n", ":)");
}

const uint8_t infoStart[] = "Start\r\n";

void cmdFuncStart(char *param) 
{
//    printf("Hello, I'm help function %s\r\n", ":)");
    motor_start(&(motor[M2_IDX]));
}
const uint8_t infoPwm[] = "Start\r\n";

void cmdFuncPwm(char *param) 
{
//    printf("Hello, I'm help function %s\r\n", ":)");
    int i;
    MOTOR* p;
    p = &(motor[M2_IDX]);
    
    sscanf(param, "%d", &i);
    if (i < 400) i = 400;
    if (i > 3999) i = 3999;
    
    *(p->phase_a_pwm) = i;
    *(p->phase_b_pwm) = i;
    *(p->phase_c_pwm) = i;
}

const uint8_t infoZCP[] = "Start\r\n";
extern volatile uint32_t zcp;
void cmdFuncZCP(char *param) 
{
//    printf("Hello, I'm help function %s\r\n", ":)");
    int i;
    MOTOR* p;
    p = &(motor[M2_IDX]);
    
    sscanf(param, "%d", &i);
    zcp = i;
    
}

    
const shellCmd_t shellCmdTable[] = 
{
    DEFINE_CMD(Help),
    DEFINE_CMD(Start),
    DEFINE_CMD(Pwm),
    DEFINE_CMD(ZCP),
};
    

#define CMD_NUM (sizeof shellCmdTable / sizeof shellCmdTable[0])
    
void shellPrintCR() 
{
    printf("\r\n");
}
void shellPrintR() 
{
    printf("\r");
}
void shellPrintPrompt() 
{
    printf("\r$ ");
}

void shellInit() 
{
    shellPrintCR();
    shellPrintPrompt();
    shellBufCnt == 0;
}

shellCmd_t* shellFindCmd(uint8_t *str) 
{
    int i;
    
    for (i = 0; i < CMD_NUM; i++) {
        if (strncmpi(str, shellCmdTable[i].name, strlen(shellCmdTable[i].name)) == 0 &&
            (str[strlen(shellCmdTable[i].name)] == ' ' ||
             str[strlen(shellCmdTable[i].name)] == '\r' ||
             str[strlen(shellCmdTable[i].name)] == '\n') ) {
            return &(shellCmdTable[i]);
        }
    }
    return NULL;
}

void shellReadChar(uint8_t ch)
{
    shellCmd_t* cmd;

    if (ch == '\n' || ch == '\r') {
        if (shellBufCnt != 0) {
            shellBuf[shellBufCnt++] = ch;
            cmd = shellFindCmd(shellBuf);
            shellPrintCR();
            if (cmd != NULL){
                cmd->cmdFunc(&(shellBuf[strlen(cmd->name)]));
            } else {
                printf("Unknown command\r\n");
            }
        }
        shellBufCnt = 0;
        shellPrintCR();
        shellPrintPrompt();
    } else if (ch == KEY_BACKSPACE) {
        if (shellBufCnt > 0) {
            shellBuf[--shellBufCnt] = ' ';
            shellPrintPrompt();        
            VCP_DataTx (shellBuf, shellBufCnt + 1);
            shellPrintPrompt();        
            VCP_DataTx (shellBuf, shellBufCnt);
        }
        else {
            shellPrintR();        
            shellPrintPrompt();        
        }
    } else if (ch < 32 || ch > 126) {
        
    } else {
        shellBuf[shellBufCnt++] = ch;
        VCP_DataTx (&ch, 1);
    }
}

