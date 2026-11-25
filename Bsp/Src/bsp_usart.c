#include "bsp_usart.h"
#include "oled.h"
#include "font.h"

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == USART3) {
	
	}
}
