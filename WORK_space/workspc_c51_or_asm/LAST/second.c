/* K1控制EEPROM的写，K2控制EEPROM的读，读取上次写进的数据
   下载完成程序后要拔掉BOOT1，再重启就可以 */


#include "public.h"
#include "iic.h"
#include "lcd1602.h"

// 键盘矩阵的行和列对应的GPIO引脚
#define ROW_PINS GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15
#define COL_PINS GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11

// 键盘矩阵的映射
const uint8_t keymap[4][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
};

u8 num[]="0123456789+-*/()=";
u8 show[100];
unsigned char count = 0;
u8 oper_val = 0 , oper_status = 0;

u8 nums_val = 0, nums_status = 0; 

void nums_show()
{
    if(nums_status == 1)
    {
        nums_status = 0 ;
        show[count] =num[ nums_val ];
        
        lcdwrd(show[count]);
		count ++ ;
    }
}

void GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIOB的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // 初始化列引脚为输出
    GPIO_InitStructure.GPIO_Pin = COL_PINS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 初始化行引脚为输入带上拉
    GPIO_InitStructure.GPIO_Pin = ROW_PINS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t read_key(void) {
    for (int col = 0; col < 4; col++) {
        // 设置当前列为低电平，其他列为高电平
        GPIO_WriteBit(GPIOB, (1 << (col + 8)), Bit_RESET);
        for (int row = 0; row < 4; row++) {
            // 检测行是否有低电平
            if (GPIO_ReadInputDataBit(GPIOB, (1 << (row + 12))) == Bit_RESET) {
                // 按键被按下，返回键值
                return keymap[row][col];
            }
        }
        // 恢复当前列为高电平
        GPIO_WriteBit(GPIOB, (1 << (col + 8)), Bit_SET);
    }
    // 没有按键被按下
    return 0;
}

int main(void) {
    SystemInit(); // 初始化系统时钟
    GPIO_Init();  // 初始化GPIO
	uint8_t key 
    while (1) {
        key= read_key();
        if (key != 0) {
             lcdwrd(num[key]);
        }
    }
}
