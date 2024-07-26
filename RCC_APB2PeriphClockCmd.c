/******************************************************************************************************
15.2.22 函数RCC_APB2PeriphClockCmd
Table 372. 描述了函数RCC_APB2PeriphClockCmd
Table 372. 函数 RCC_APB2PeriphClockCmd
函数名 RCC_APB2PeriphClockCmd
函数原形 void RCC_APB2PeriphClockCmd(u32 RCC_APB2Periph,
FunctionalState NewState)
功能描述 使能或者失能 APB2 外设时钟
输入参数 1 RCC_APB2Periph: 门控 APB2 外设时钟
参阅 Section： RCC_APB2Periph 查阅更多该参数允许取值范围
输入参数 2 NewState：指定外设时钟的新状态
这个参数可以取： ENABLE 或者 DISABLE
输出参数 无
返回值 无
先决条件 无
被调用函数 无
RCC_APB2Periph
该参数被门控的APB2外设时钟，可以取下表的一个或者多个取值的组合作为该参数的值。RCC
208/368
译文英文原版为 UM0427 Oct. 2007 Rev 2, 译文仅供参考，与英文版冲突的，以英文版为准
Table 373. RCC_AHB2Periph 值
RCC_AHB2Periph 描述
RCC_APB2Periph_AFIO 功能复用 IO 时钟
RCC_APB2Periph_GPIOA GPIOA 时钟
RCC_APB2Periph_GPIOB GPIOB 时钟
RCC_APB2Periph_GPIOC GPIOC 时钟
RCC_APB2Periph_GPIOD GPIOD 时钟
RCC_APB2Periph_GPIOE GPIOE 时钟
RCC_APB2Periph_ADC1 ADC1 时钟
RCC_APB2Periph_ADC2 ADC2 时钟
RCC_APB2Periph_TIM1 TIM1 时钟
RCC_APB2Periph_SPI1 SPI1 时钟
RCC_APB2Periph_USART1 USART1 时钟
RCC_APB2Periph_ALL 全部 APB2 外设时钟
例：
/* Enable GPIOA, GPIOB and SPI1 clocks */
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
RCC_APB2Periph_SPI1, ENABLE);
*****************************************************************************************************\
/**
  * @brief  启用或禁用高速APB (APB2) 外设时钟。
  * @param  RCC_APB2Periph: 指定要控制时钟的APB2外设。
  *   此参数可以是以下值的任意组合：
  *     @arg RCC_APB2Periph_AFIO, RCC_APB2Periph_GPIOA, RCC_APB2Periph_GPIOB,
  *          RCC_APB2Periph_GPIOC, RCC_APB2Periph_GPIOD, RCC_APB2Periph_GPIOE,
  *          RCC_APB2Periph_GPIOF, RCC_APB2Periph_GPIOG, RCC_APB2Periph_ADC1,
  *          RCC_APB2Periph_ADC2, RCC_APB2Periph_TIM1, RCC_APB2Periph_SPI1,
  *          RCC_APB2Periph_TIM8, RCC_APB2Periph_USART1, RCC_APB2Periph_ADC3,
  *          RCC_APB2Periph_TIM15, RCC_APB2Periph_TIM16, RCC_APB2Periph_TIM17,
  *          RCC_APB2Periph_TIM9, RCC_APB2Periph_TIM10, RCC_APB2Periph_TIM11     
  * @param  NewState: 指定外设时钟的新状态。
  *   此参数可以是：ENABLE 或 DISABLE。
  * @retval None
  */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
  /* 检查输入参数的有效性 */
  assert_param(IS_RCC_APB2_PERIPH(RCC_APB2Periph));  // 确保外设参数有效
  assert_param(IS_FUNCTIONAL_STATE(NewState));        // 确保状态参数有效
  
  if (NewState != DISABLE)  // 如果要启用时钟
  {
    RCC->APB2ENR |= RCC_APB2Periph;  // 设置对应位以启用外设时钟
  }
  else  // 如果要禁用时钟
  {
    RCC->APB2ENR &= ~RCC_APB2Periph;  // 清除对应位以禁用外设时钟
  }
}
