// !!!! DO NOT EDIT !!!, use: make config

#ifndef _CONFIG_H_
#define _CONFIG_H_

#define CONFIG_FREQUENCY 902
#define OPTION_TIME_DISPLAY 1
// CONFIG_METRIC_ONLY is not set
// FIXEDPOINT is not set
#ifndef THIS_DEVICE_ADDRESS
#define THIS_DEVICE_ADDRESS {0xed,0xc0,0xbb,0x25}
#endif // THIS_DEVICE_ADDRESS
// USE_LCD_CHARGE_PUMP is not set
#define USE_WATCHDOG
// DEBUG is not set
#define CONFIG_DAY_OF_WEEK
#define CONFIG_TEST
// CONFIG_EGGTIMER is not set
// CONFIG_PHASE_CLOCK is not set
// CONFIG_ALTITUDE is not set
// CONFIG_VARIO is not set
#define CONFIG_PROUT
// CONFIG_SIDEREAL is not set
// CONFIG_INFOMEM is not set
// CONFIG_ACCEL is not set
// CONFIG_STRENGTH is not set
// CONFIG_ALARM is not set
#define CONFIG_BATTERY
#define CONFIG_CLOCK
#define CONFIG_DATE
#define CONFIG_RFBSL
// CONFIG_STOP_WATCH is not set
// CONFIG_TEMP is not set

#endif // _CONFIG_H_
