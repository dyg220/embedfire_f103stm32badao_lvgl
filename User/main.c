/**
 ******************************************************************************
 * @file    main.c
 * @author  fire
 * @version V1.0
 * @date    2013-xx-xx
 * @brief   触摸画板实验
 ******************************************************************************
 * @attention
 *
 * 实验平台:野火 F103-霸道 STM32 开发板
 * 论坛    :http://www.firebbs.cn
 * 淘宝    :https://fire-stm32.taobao.com
 *
 ******************************************************************************
 */

#include "./Systick/bsp_SysTick.h"
#include "./flash/bsp_spi_flash.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./lcd/bsp_xpt2046_lcd.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_usart.h"
#include "lv_apps\demo\demo.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "lv_tests\lv_test_theme\lv_test_theme_1.h"
#include "lv_tests\lv_test_theme\lv_test_theme_2.h"
#include "lvgl.h"
#include "palette.h"
#include "stm32f10x.h"
#include <string.h>

int main(void) {
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  SysTick_Init();
  ILI9341_Init();
  XPT2046_Init();
  Calibrate_or_Get_TouchParaWithFlash(
      3, 0); // 从FLASH里获取校正参数，若FLASH无参数，则使用模式3进行校正
  USART_Config();
  LED_GPIO_Config();
  printf("\r\n ********** 触摸画板程序 *********** \r\n");
  printf("\r\n "
         "若汉字显示不正常，请阅读工程中的readme.txt文件说明，根据要求给FLASH重"
         "刷字模数据\r\n");
  // 其中0、3、5、6 模式适合从左至右显示文字，
  // 不推荐使用其它模式显示文字	其它模式显示文字会有镜像效果
  // 其中 6 模式为大部分液晶例程的默认显示方向
  ILI9341_GramScan(5);
  lv_init();
  lv_port_disp_init();  // lvgl 显示接口初始化,放在 lv_init()的后面
  lv_port_indev_init(); // lvgl 输入接口初始化,放在 lv_init()的后面
  demo_create();
  //  lv_test_theme_1(lv_theme_night_init(210, NULL));
  //  lv_test_theme_2();

  // lv_obj_t *parent = lv_obj_create(lv_scr_act());
  // lv_obj_set_size(parent, 800, 480);

  while (1) {
    lv_task_handler();
  }
}

/* ------------------------------------------end of
 * file---------------------------------------- */
