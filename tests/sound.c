#include "drivers/gfx.h"
#include "arm11/console.h"
#include "arm11/drivers/csnd.h"
#include "arm11/fmt.h"
#include "arm11/drivers/hid.h"
#include "arm11/drivers/timer.h"
#include "arm11/drivers/codec.h"
#include "arm11/power.h"



int main(void)
{
	GFX_init(GFX_BGR8, GFX_BGR565, GFX_TOP_2D);
	GFX_setLcdLuminance(80);
	consoleInit(GFX_LCD_BOT, NULL);
	CSND_init();

	ee_puts("Sound test");
	u16 freq = 500;
	bool freqChanged = true;
	CSND_setupCh(8, CSND_PSG_FREQ(freq), CSND_calcVol(1.f, 0.f), NULL, NULL, 0, CSND_CH_FMT_PSG_NOISE | CSND_CH_DUTY(3));
	CSND_setChState(8, true); // Unpause
	while(1)
	{
		hidScanInput();

		const u32 kHeld = hidKeysHeld();
		if(kHeld & KEY_DUP) {freq++; freqChanged = true;}
		else if(kHeld & KEY_DDOWN) {freq--; freqChanged = true;}
		if(hidGetExtraKeys(0) & (KEY_POWER_HELD | KEY_POWER)) break;

		if(freqChanged)
		{
			freqChanged = false;

			CSND_setSrFreq(8, CSND_PSG_FREQ(freq));
			ee_printf("\rFreq: %05" PRId16, freq);
		}

		TIMER_sleepMs(60);
	}
	CSND_stopCh(8);

	CODEC_deinit();
	GFX_deinit();

	power_off();

	return 0;
}