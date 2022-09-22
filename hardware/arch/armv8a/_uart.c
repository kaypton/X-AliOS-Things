#define PL011_BASE_ADDR 0x9000000
#define PL011_BASE_CLK 0x16e3600

#define DR_OFFSET (0x000)

#define FR_OFFSET (0x018)
#define FR_BUSY_BIT (1 << 3)

#define IBRD_OFFSET (0x024)
#define FBRD_OFFSET (0x028)

#define LCR_OFFSET (0x02C)
#define LCR_FEN (1 << 4)
#define LCR_STP2 (1 << 3)

#define CR_OFFSET (0x030)
#define CR_UARTEN (1 << 0)
#define CR_TXEN (1 << 8)

#define IMSC_OFFSET (0x038)
#define DMACR_OFFSET (0x048)

struct pl011 
{
    union
    {
        volatile char data;
        volatile short reserve;
    } dr;
    char reserve1[22];
    volatile unsigned short fr;  /* offset 0x018 */
} __attribute__((packed));

struct pl011 *instance = (struct pl011 *)(PL011_BASE_ADDR);
char *__data = (char *)(PL011_BASE_ADDR);

static void pl011_wait_tx();
void _uart_send_c(char c);

void pl011_putc(char c)
{
    instance->dr.data = c;
    pl011_wait_tx();
}

void pl011_puts(const char *s)
{
    int i;

    for(i = 0; s[i] != '\0'; i++)
    {
        pl011_putc(s[i]);
    }
}

void pl011_reset(void)
{
    unsigned int tmp;

    tmp = *(unsigned short *)(PL011_BASE_ADDR + CR_OFFSET);
    tmp &= ~((unsigned short)CR_UARTEN);
    *(unsigned short *)(PL011_BASE_ADDR + CR_OFFSET) = tmp;

    pl011_wait_tx();

    tmp = *(unsigned int *)(PL011_BASE_ADDR + LCR_OFFSET);
    tmp &= ~((unsigned int)LCR_FEN);
    *(unsigned int *)(PL011_BASE_ADDR + LCR_OFFSET) = tmp;

    *(unsigned int *)(PL011_BASE_ADDR + FBRD_OFFSET) = 832 & 0x3F;
    *(unsigned int *)(PL011_BASE_ADDR + IBRD_OFFSET) = 6 & 0xFFFF;

    tmp = *(unsigned int *)(PL011_BASE_ADDR + LCR_OFFSET);
    tmp &= ~((unsigned int)LCR_STP2);
    tmp |= 0x0060;
    *(unsigned int *)(PL011_BASE_ADDR + LCR_OFFSET) = tmp;

    *(unsigned int *)(PL011_BASE_ADDR + IMSC_OFFSET) = 0x7FF;
    *(unsigned int *)(PL011_BASE_ADDR + DMACR_OFFSET) = 0;

    tmp = *(unsigned int *)(PL011_BASE_ADDR + CR_OFFSET);
    tmp |= (CR_TXEN | CR_UARTEN);
    *(unsigned int *)(PL011_BASE_ADDR + CR_OFFSET) = tmp;

    
}


static void pl011_wait_tx(void)
{
    for(;;)
    {
        if(!(instance->fr & (unsigned short)FR_BUSY_BIT))
            break;
    }
}

