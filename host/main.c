#include <stdio.h>
#include <string.h>

/* 
   M1_A_L PC15
   M1_B_L PC14
   M1_C_L PC13
   M2_A_L PD2
   M2_B_L PC11
   M2_C_L PC12
   M3_A_L PC10
   M3_B_L PB2
   M3_C_L PB13
   M4_A_L PB15
   M4_B_L PB12
   M4_C_L PB14
*/
const char motor_channel_l[4][3][5] = {
    "PC15",
    "PC14",
    "PC13",
    "PD2",
    "PC11",
    "PC12",
    "PC10",
    "PB2",
    "PB13",
    "PB15",
    "PB12",
    "PB14"
};
 
/* 
   M1_A_H PB8
   M1_B_H PB9
   M1_C_H PB7
   M2_A_H PB4
   M2_B_H PB6
   M2_C_H PB5
   M3_A_H PC6
   M3_B_H PC7
   M3_C_H PC8
   M4_A_H PA10
   M4_B_H PC9
   M4_C_H PA8
*/
const char motor_channel_h[4][3][5] = {
    "PB8",
    "PB9",
    "PB7",
    "PB4",
    "PB6",
    "PB5",
    "PC6",
    "PC7",
    "PC8",
    "PA10",
    "PC9",
    "PA8"
};

    

int port_offset(const char str[5])
{
    return 0x400 * (str[1] - 'A');
}
int pin_offset(const char str[5]) 
{
    int i;
    sscanf(&(str[2]), "%d", &i);
    return i;
}

void print_define_l_off()
{
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            printf("#define M%d_%c_L_OFF\t((uint32_t *)(0x42000000 + ((0x2001A + 0x%x) << 5) + (%2d << 2)))\n", 
                   i + 1, j + 'A', port_offset(motor_channel_l[i][j]), pin_offset(motor_channel_l[i][j]));
        }
    }
}

void print_define_l_on()
{
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            printf("#define M%d_%c_L_ON\t((uint32_t *)(0x42000000 + ((0x20018 + 0x%x) << 5) + (%2d << 2)))\n", 
                   i + 1, j + 'A', port_offset(motor_channel_l[i][j]), pin_offset(motor_channel_l[i][j]));
        }
    }
}

void print_define_pwm_ctrl()
{
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            printf("#define M%d_%c_PWM_CTRL_0\t((uint32_t *)(0x42000000 + ((0x20000 + 0x%x) << 5) + (%2d << 2)))\n", 
                   i + 1, j + 'A', port_offset(motor_channel_h[i][j]), 2 * pin_offset(motor_channel_h[i][j]));
            printf("#define M%d_%c_PWM_CTRL_1\t((uint32_t *)(0x42000000 + ((0x20000 + 0x%x) << 5) + (%2d << 2)))\n", 
                   i + 1, j + 'A', port_offset(motor_channel_h[i][j]), 1 + 2 * pin_offset(motor_channel_h[i][j]));
        }
    }
}

void print_define_motor()
{
}

void print_define() 
{
    

}

void main(void) 
{
    print_define_l_on();
    print_define_l_off();
    print_define_pwm_ctrl();
}
