#ifndef RPI_PERIPHS_H
#define RPI_PERIPHS_H

#include "type/rpi_type.h"

// レジスタやメモリマップドIOのアドレス定義のためのファイル

#ifdef RPI2
#define PHY_PERI_ADDR(x) (0x3f000000 + (x))
#else
#define PHY_PERI_ADDR(x) (0x20000000 + (x))
#endif
// GPIO Peripheral
#define GPIO_BASE	(0x00200000)
#define GPIO_FSEL0		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x00))
#define GPIO_FSEL1		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x04))
#define GPIO_FSEL2		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x08))
#define GPIO_FSEL3		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x0c))
#define GPIO_FSEL4		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x10))
#define GPIO_FSEL5		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x14))

#define GPIO_SET0		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x1c))
#define GPIO_SET1		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x20))
#define GPIO_CLR0		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x28))
#define GPIO_CLR1		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x2c))
#define GPIO_LEV0		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x34))
#define GPIO_LEV1		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x38))
// for GPFSEL mask
// use AND mask
#define GPIO_FSEL_MASK_IN(n)	(~(vu32_t)(0x07 << ((n % 10) * 3)))
// use OR mask
#define GPIO_FSEL_MASK_OUT(n)	(0x01 << ((n % 10) * 3))
#define GPIO_FSEL_MASK_ALT0(n)	(0x04 << ((n % 10) * 3))
#define GPIO_FSEL_MASK_ALT1(n)	(0x05 << ((n % 10) * 3))
#define GPIO_FSEL_MASK_ALT2(n)	(0x06 << ((n % 10) * 3))
#define GPIO_FSEL_MASK_ALT3(n)	(0x07 << ((n % 10) * 3))
#define GPIO_FSEL_MASK_ALT4(n)	(0x03 << ((n % 10) * 3))
#define GPIO_FSEL_MASK_ALT5(n)	(0x02 << ((n % 10) * 3))
// GPIO PULLUP/DOWN
#define GPIO_PUD 		((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x94))
#define GPIO_PUDCLK0	((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x98))
#define GPIO_PUDCLK1	((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x9C))

#define GPIO_EDS0 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x40))
#define GPIO_EDS1 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x44))
#define GPIO_REN0 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x4c))
#define GPIO_REN1 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x50))
#define GPIO_FEN0 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x58))
#define GPIO_FEN1 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x5c))
#define GPIO_HEN0 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x64))
#define GPIO_HEN1 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x68))
#define GPIO_LEN0 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x70))
#define GPIO_LEN1 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x74))
#define GPIO_AREN0 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x7c))
#define GPIO_AREN1 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x80))
#define GPIO_AFEN0 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x88))
#define GPIO_AFEN1 ((vu32_t *)PHY_PERI_ADDR(GPIO_BASE + 0x8c))


// SystemTimer Peripheral
#define SYST_BASE	(0x00003000)
#define SYST_CS		((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x00))
#define SYST_CLO	((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x04))
#define SYST_CHI	((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x08))
#define SYST_C0		((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x0c))
#define SYST_C1		((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x10))
#define SYST_C2		((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x14))
#define SYST_C3		((vu32_t *)PHY_PERI_ADDR(SYST_BASE + 0x18))


// UART peripheral
#define UART0_BASE		0x00201000
#define UART0_DR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x00))
#define UART0_RSRECR	((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x04))
#define UART0_FR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x18))
// #define UART0_ILPR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x20)) // not use
#define UART0_IBRD		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x24))
#define UART0_FBRD		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x28))
#define UART0_LCRH		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x2c))
#define UART0_CR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x30))
#define UART0_IFLS		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x34))
#define UART0_IMSC		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x38))
#define UART0_RIS		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x3c))
#define UART0_MIS		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x40))
#define UART0_ICR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x44))
#define UART0_DMACR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x48))
#define UART0_ITCR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x80))
#define UART0_ITIP		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x84))
#define UART0_ITOP		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x88))
#define UART0_TDR		((vu32_t *)PHY_PERI_ADDR(UART0_BASE + 0x8c))


// SPI0 peripheral
#define SPI0_BASE		(0x00204000)
#define SPI0_CS			((vu32_t *)PHY_PERI_ADDR(SPI0_BASE + 0x00))
#define SPI0_FIFO		((vu32_t *)PHY_PERI_ADDR(SPI0_BASE + 0x04))
#define SPI0_CLK		((vu32_t *)PHY_PERI_ADDR(SPI0_BASE + 0x08))
#define SPI0_DLEN		((vu32_t *)PHY_PERI_ADDR(SPI0_BASE + 0x0C))
#define SPI0_LTOH		((vu32_t *)PHY_PERI_ADDR(SPI0_BASE + 0x10))
#define SPI0_DC			((vu32_t *)PHY_PERI_ADDR(SPI0_BASE + 0x14))

// I2C(BSC1) peripheral
#define BSC1_BASE	(0x00804000)
#define BSC1_C		((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x00))
#define BSC1_S		((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x04))
#define BSC1_DLEN	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x08))
#define BSC1_A		((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x0C))
#define BSC1_FIFO	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x10))
#define BSC1_DIV	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x14))
#define BSC1_DEL	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x18))
#define BSC1_CLKT	((vu32_t *)PHY_PERI_ADDR(BSC1_BASE + 0x1C))


// Timer(ARM side) peripheral
#define TIMER_BASE			(0x0000B000)
#define TIMER_LOAD			((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x400))
#define TIMER_VALUE			((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x404))
#define TIMER_CONTROL		((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x408))
#define TIMER_IRQ_CLR		((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x40C))
#define TIMER_RAWIRQ		((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x410))
#define TIMER_MASKEDIRQ		((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x414))
#define TIMER_RELOAD		((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x418))
#define TIMER_PREDIVIDER	((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x41C))
#define TIMER_FREECOUNTER	((vu32_t *)PHY_PERI_ADDR(TIMER_BASE + 0x420))


// Interrupt
#define INTERRUPT_BASE					(0x0000B000)
#define INTERRUPT_IRQ_BASIC_PENDING		((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x200))
#define INTERRUPT_IRQ_PENDING1			((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x204))
#define INTERRUPT_IRQ_PENDING2			((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x208))
#define INTERRUPT_FIQ_CTRL				((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x20C))
#define INTERRUPT_ENABLE_IRQS1			((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x210))
#define INTERRUPT_ENABLE_IRQS2			((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x214))
#define INTERRUPT_ENABLE_BASIC_IRQS		((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x218))
#define INTERRUPT_DISABLE_IRQS1			((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x21C))
#define INTERRUPT_DISABLE_IRQS2			((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x220))
#define INTERRUPT_DISABLE_BASIC_IRQS	((vu32_t *)PHY_PERI_ADDR(INTERRUPT_BASE + 0x224))

// PWM Peripheral
#define PWM_BASE (0x20C000)
#define PWM_CTL ((vu32_t *)PHY_PERI_ADDR(PWM_BASE + 0x00))
#define PWM_STA ((vu32_t *)PHY_PERI_ADDR(PWM_BASE + 0x04))
#define PWM_DMAC ((vu32_t *)PHY_PERI_ADDR(PWM_BASE + 0x08))
#define PWM_RNG1 ((vu32_t *)PHY_PERI_ADDR(PWM_BASE + 0x10))
#define PWM_DAT1 ((vu32_t *)PHY_PERI_ADDR(PWM_BASE + 0x14))
#define PWM_FIF1 ((vu32_t *)PHY_PERI_ADDR(PWM_BASE + 0x18))
#define PWM_RNG2 ((vu32_t *)PHY_PERI_ADDR(PWM_BASE + 0x20))
#define PWM_DAT2 ((vu32_t *)PHY_PERI_ADDR(PWM_BASE + 0x24))

// DMA Peripheral
#define DMA_BASE (0x007000)
#define DMA0_CS ((vu32_t *)PHY_PERI_ADDR(DMA_BASE + 0x000))
#define DMA0_CONBLK_AD ((vu32_t *)PHY_PERI_ADDR(DMA_BASE + 0x004))
#define DMA0_DEBUG ((vu32_t *)PHY_PERI_ADDR(DMA_BASE + 0x020))
#define DMA0_NEXTCONBLOCK ((vu32_t *)PHY_PERI_ADDR(DMA_BASE + 0x01c))

#define DMA_INT_STATUS ((vu32_t *)PHY_PERI_ADDR(DMA_BASE + 0xfe0))
#define DMA_ENABLE ((vu32_t *)PHY_PERI_ADDR(DMA_BASE + 0xff0))

// Clock Manager
#define CM_BASE (0x101000)
#define CM_PWMCTL ((vu32_t *)PHY_PERI_ADDR(CM_BASE + 0xa0))
#define CM_PWMDIV ((vu32_t *)PHY_PERI_ADDR(CM_BASE + 0xa4))

#endif /* end of include guard: RPI_PERIPHS_H */
