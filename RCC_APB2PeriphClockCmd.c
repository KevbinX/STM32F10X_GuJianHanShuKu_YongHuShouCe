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
