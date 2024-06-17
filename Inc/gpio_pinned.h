/*
 * gpio_pinned.h
 *
 *  Created on: Mar 26, 2024
 *      Author: es-2
 */
#include <stdint.h>

#ifndef INC_GPIO_PINNED_H_
#define INC_GPIO_PINNED_H_

#define RCC_REGS		(0x40021000)
#define GPIO_RCC 		((uint32_t *)(RCC_REGS + 0x4C))
#define GPIO_BASE 		((gpio_t *)(0x48000000u))

#define GPIO_A 			((gpio_t *)(0x48000000u))
#define GPIO_B 			((gpio_t *)(0x48000400u))
#define GPIO_C 			((gpio_t *)(0x48000800u))
#define GPIO_D 			((gpio_t *)(0x48000C00u))
#define GPIO_E 			((gpio_t *)(0x48001000u))
#define GPIO_F 			((gpio_t *)(0x48001400u))
#define GPIO_G 			((gpio_t *)(0x48001800u))
#define GPIO_H 			((gpio_t *)(0x48001C00u))
#define GPIO_I 			((gpio_t *)(0x48002000u))

#define GPIO_A_CLK		(0)
#define GPIO_B_CLK		(1)
#define GPIO_C_CLK		(2)
#define GPIO_D_CLK		(3)
#define GPIO_E_CLK		(4)
#define GPIO_F_CLK		(5)
#define GPIO_G_CLK		(6)
#define GPIO_H_CLK		(7)
#define GPIO_I_CLK		(8)

#define PWR_REGISTER_CR ((uint16_t *)(0x40007000 + 0x04))
#define VDDIO2_MASK		(1<<9)

#define MAX_PIN_NUMBER  (15)
#define MIN_PIN_NUMBER  (0)

#define PIN_SET 		(1)
#define PIN_RESET 		(0)

#define MODE_IN			((uint32_t)(0x00u))
#define MODE_OUT		((uint32_t)(0x01u))
#define MODE_ALT		((uint32_t)(0x02u))
#define MODE_ALT_MASK	((uint32_t)(0x03u))

#define TYPE_PP			((uint32_t)(0x0u))
#define TYPE_OD			((uint32_t)(0x1u))

#define PULL_NO			((uint32_t)(0x00u))
#define PULL_UP			((uint32_t)(0x01u))
#define PULL_DOWN		((uint32_t)(0x02u))

#define SPEED_LOW		((uint32_t)(0x00u))
#define SPEED_MEDIUM	((uint32_t)(0x01u))
#define SPEED_HIGH		((uint32_t)(0x02u))

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
	volatile uint32_t BRR;
	volatile uint32_t ASCR;
} gpio_t;

typedef struct {
	gpio_t * gpio;
	const uint16_t number;
} pin_t;

typedef struct {
	uint8_t mode;
	uint8_t type;
	uint8_t pull;
	uint8_t speed;
} init_t;

void enable_gpio_clock(int index);
void enable_vddio2();

void init_pin(const pin_t* pin, init_t* init);
void write_pin(const pin_t* pin, int state);
int read_pin(const pin_t* pin);

#endif /* INC_GPIO_PINNED_H_ */
