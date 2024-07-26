/*************************************************************************************************
10.2.3 函数GPIO_Init
Table 182. 描述了函数 GPIO_Init
Table 182. 函数 GPIO_Init
函数名 GPIO_Init
函数原形 void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
功能描述 根据 GPIO_InitStruct 中指定的参数初始化外设 GPIOx 寄存器
输入参数 1 GPIOx： x 可以是 A， B， C， D 或者 E，来选择 GPIO 外设
输入参数 2 GPIO_InitStruct：指向结构 GPIO_InitTypeDef 的指针，包含了外设 GPIO 的配置信息
参阅 Section： GPIO_InitTypeDef 查阅更多该参数允许取值范围
输出参数 无
返回值 无
先决条件 无
被调用函数 无
GPIO_InitTypeDef structure
GPIO_InitTypeDef 定义于文件“stm32f10x_gpio.h”：
typedef struct
{
u16 GPIO_Pin;
GPIOSpeed_TypeDef GPIO_Speed;
GPIOMode_TypeDef GPIO_Mode;
} GPIO_InitTypeDef;
GPIO_Pin
该参数选择待设置的 GPIO 管脚，使用操作符“|”可以一次选中多个管脚。可以使用下表中的任意组合。
Table 183. GPIO_Pin 值
GPIO_Pin 描述
GPIO_Pin_None 无管脚被选中
GPIO_Pin_0 选中管脚 0
GPIO_Pin_1 选中管脚 1
GPIO_Pin_2 选中管脚 2
GPIO_Pin_3 选中管脚 3
GPIO_Pin_4 选中管脚 4
GPIO_Pin_5 选中管脚 5
GPIO_Pin_6 选中管脚 6
GPIO_Pin_7 选中管脚 7
GPIO_Pin_8 选中管脚 8
GPIO_Pin_9 选中管脚 9
GPIO_Pin_10 选中管脚 10
GPIO_Pin_11 选中管脚 11
GPIO_Pin_12 选中管脚 12
GPIO_Pin_13 选中管脚 13
GPIO_Pin_14 选中管脚 14
GPIO_Pin_15 选中管脚 15
GPIO_Pin_All 选中全部管脚
GPIO_Speed
GPIO_Speed 用以设置选中管脚的速率。 Table 184. 给出了该参数可取的值GPIO
125/368
译文英文原版为 UM0427 Oct. 2007 Rev 2, 译文仅供参考，与英文版冲突的，以英文版为准
Table 184. GPIO_Speed 值
GPIO_Speed 描述
GPIO_Speed_10MHz 最高输出速率 10MHz
GPIO_Speed_2MHz 最高输出速率 2MHz
GPIO_Speed_50MHz 最高输出速率 50MHz
GPIO_Mode
GPIO_Mode 用以设置选中管脚的工作状态。 Table 185. 给出了该参数可取的值
Table 185. GPIO_Mode 值
GPIO_Speed 描述
GPIO_Mode_AIN 模拟输入
GPIO_Mode_IN_FLOATING 浮空输入
GPIO_Mode_IPD 下拉输入
GPIO_Mode_IPU 上拉输入
GPIO_Mode_Out_OD 开漏输出
GPIO_Mode_Out_PP 推挽输出
GPIO_Mode_AF_OD 复用开漏输出
GPIO_Mode_AF_PP 复用推挽输出
注意：
 当某管脚设置为上拉或者下拉输入模式，使用寄存器 Px_BSRR 和 PxBRR
 GPIO_Mode 允许同时设置 GPIO 方向（输入/输出）和对应的输入/输出设置， ：位[7:4]对应 GPIO 方向，
位[4:0]对应配置。 GPIO 方向有如下索引
- GPIO 输入模式 = 0x00
- GPIO 输出模式 = 0x01
Table 186. 给出了所有 GPIO_Mode 的索引和编码
Table 186. GPIO_Mode 的索引和编码
GPIO方向 索引 模式 设置 模式代码
GPIO_Mode_AIN 0x00 0x00
GPIO_Mode_IN_FLOATING 0x04 0x04
GPIO Input 0x00 GPIO_Mode_IPD 0x08 0x28
GPIO_Mode_IPU 0x08 0x48
GPIO_Mode_Out_OD 0x04 0x14
GPIO_Mode_Out_PP 0x00 0x10
GPIO Output 0x01 GPIO_Mode_AF_OD 0x0C 0x1C
GPIO_Mode_AF_PP 0x08 0x18
例：
/* Configure all the GPIOA in Input Floating mode */
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
GPIO_Init(GPIOA, &GPIO_InitStructure);
*************************************************************************************************\
/**
  * @brief  根据GPIO_InitStruct中指定的参数初始化GPIOx外设。
  * @param  GPIOx: 选择的GPIO外设，x可以是 (A..G)。
  * @param  GPIO_InitStruct: 指向GPIO_InitTypeDef结构的指针，包含指定GPIO外设的配置信息。
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
  uint32_t currentmode = 0x00, currentpin = 0x00, pinpos = 0x00, pos = 0x00; // 定义当前模式、当前引脚、引脚位置和位置索引
  uint32_t tmpreg = 0x00, pinmask = 0x00; // 定义临时寄存器和引脚掩码

  /* 检查输入参数的有效性 */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));                // 确保GPIO外设有效
  assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode)); // 确保GPIO模式有效
  assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));   // 确保GPIO引脚有效

  /*---------------------------- GPIO模式配置 -----------------------*/
  currentmode = ((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x0F); // 获取模式的低四位
  if ((((uint32_t)GPIO_InitStruct->GPIO_Mode) & ((uint32_t)0x10)) != 0x00)
  { 
    /* 检查速度参数 */
    assert_param(IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed)); // 确保GPIO速度有效
    /* 输出模式，设置速度 */
    currentmode |= (uint32_t)GPIO_InitStruct->GPIO_Speed; // 将速度配置合并到模式中
  }

  /*---------------------------- GPIO CRL配置 ------------------------*/
  /* 配置低8个引脚 */
  if (((uint32_t)GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
  {
    tmpreg = GPIOx->CRL; // 读取当前CRL寄存器值
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = ((uint32_t)0x01) << pinpos; // 计算当前引脚位置
      currentpin = (GPIO_InitStruct->GPIO_Pin) & pos; // 获取当前引脚的状态
      if (currentpin == pos) // 如果当前引脚被选中
      {
        pos = pinpos << 2; // 计算寄存器中的位置
        /* 清除对应的低控制寄存器位 */
        pinmask = ((uint32_t)0x0F) << pos; // 生成掩码
        tmpreg &= ~pinmask; // 清除相应位
        /* 在相应位中写入模式配置 */
        tmpreg |= (currentmode << pos); // 设置模式
        /* 重置对应的ODR位 */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << pinpos); // 下拉模式，重置引脚
        }
        else
        {
          /* 设置对应的ODR位 */
          if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
          {
            GPIOx->BSRR = (((uint32_t)0x01) << pinpos); // 上拉模式，设置引脚
          }
        }
      }
    }
    GPIOx->CRL = tmpreg; // 将配置写回CRL寄存器
  }

  /*---------------------------- GPIO CRH配置 ------------------------*/
  /* 配置高8个引脚 */
  if (GPIO_InitStruct->GPIO_Pin > 0x00FF)
  {
    tmpreg = GPIOx->CRH; // 读取当前CRH寄存器值
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
      pos = (((uint32_t)0x01) << (pinpos + 0x08)); // 计算高8位引脚位置
      currentpin = ((GPIO_InitStruct->GPIO_Pin) & pos); // 获取当前引脚的状态
      if (currentpin == pos) // 如果当前引脚被选中
      {
        pos = pinpos << 2; // 计算寄存器中的位置
        /* 清除对应的高控制寄存器位 */
        pinmask = ((uint32_t)0x0F) << pos; // 生成掩码
        tmpreg &= ~pinmask; // 清除相应位
        /* 在相应位中写入模式配置 */
        tmpreg |= (currentmode << pos); // 设置模式
        /* 重置对应的ODR位 */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
        {
          GPIOx->BRR = (((uint32_t)0x01) << (pinpos + 0x08)); // 下拉模式，重置引脚
        }
        /* 设置对应的ODR位 */
        if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
        {
          GPIOx->BSRR = (((uint32_t)0x01) << (pinpos + 0x08)); // 上拉模式，设置引脚
        }
      }
    }
    GPIOx->CRH = tmpreg; // 将配置写回CRH寄存器
  }
}
