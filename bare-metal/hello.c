#define UART0_BASE 0xE0000000U
#define UART_CR (*(volatile unsigned int *)(UART0_BASE + 0x00))
#define UART_MODE (*(volatile unsigned int *)(UART0_BASE + 0x04))
#define UART_BAUDGEN (*(volatile unsigned int *)(UART0_BASE + 0x18))
#define UART_BAUDDIV (*(volatile unsigned int *)(UART0_BASE + 0x34))
#define UART_SR (*(volatile unsigned int *)(UART0_BASE + 0x2C))
#define UART_FIFO (*(volatile unsigned int *)(UART0_BASE + 0x30))

#define UART_TXFULL (1 << 4)
#define UART_RXEMPTY (1 << 1)

static void uart_init(void)
{
    UART_CR = 0x00000000;   // Disable TX/RX before setup
    UART_MODE = 0x00000000; // Normal mode
    UART_BAUDGEN = 0x7C;    // Divisor for 115200 baud @ 50 MHz UART ref clk
    UART_BAUDDIV = 0x06;
    UART_CR = (1 << 4) | (1 << 2); // Enable TX & RX
}

static void uart_send(char c)
{
    while (UART_SR & UART_TXFULL)
        ; // wait until TX FIFO not full
    UART_FIFO = c;
}

static void print(const char *s)
{
    while (*s)
        uart_send(*s++);
}

int _custom_main(void)
{
    uart_init();
    print("Hello from UART0 bare-metal on Zynq-7000!\r\n");
     print("aaaa\r\n");
    while (1)
        ;
}
