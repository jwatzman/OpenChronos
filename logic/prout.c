/*
   Vario function for ez430 chronos watch.
   Copyright (C) 2010 Marc Poulhiès <dkm@kataplop.net>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// *************************************************************************************************
//
//	Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
//	 
//	 
//	  Redistribution and use in source and binary forms, with or without 
//	  modification, are permitted provided that the following conditions 
//	  are met:
//	
//	    Redistributions of source code must retain the above copyright 
//	    notice, this list of conditions and the following disclaimer.
//	 
//	    Redistributions in binary form must reproduce the above copyright
//	    notice, this list of conditions and the following disclaimer in the 
//	    documentation and/or other materials provided with the   
//	    distribution.
//	 
//	    Neither the name of Texas Instruments Incorporated nor the names of
//	    its contributors may be used to endorse or promote products derived
//	    from this software without specific prior written permission.
//	
//	  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//	  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//	  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//	  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//	  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//	  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//	  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//	  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//	  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//	  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//	  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include "project.h"

#ifdef CONFIG_PROUT

// driver
#include "altitude.h"
#include "display.h"
#include "vti_ps.h"
#include "ports.h"
#include "timer.h"

#include "stopwatch.h"

// logic
#include "user.h"
#include "prout.h"

#include "menu.h"

struct prouttimer sprouttimer;

#define NUM_STRS 5

#define POUET_STR_1 " BETHANY 1S AWESOMME 1 LOVE YOU BETHA"
#define POUET_STR_2 " BETHANY YOU ARE BEAUT1FUL BETHA"
#define POUET_STR_3 " BETHANY DOES NOT PREFER CHEESE BETHA"
#define POUET_STR_4 " BETHANY BADGER MUSHROOM BETHA"
#define POUET_STR_5 " BETHANY MAKES ME SO HAPPY BETHA"

static u8 *strs[NUM_STRS] = {POUET_STR_1, POUET_STR_2, POUET_STR_3,
	POUET_STR_4, POUET_STR_5};
static u8 lens[NUM_STRS] = {sizeof(POUET_STR_1), sizeof(POUET_STR_2),
	sizeof(POUET_STR_3), sizeof(POUET_STR_4), sizeof(POUET_STR_5)};

void prout_tick()
{
	sprouttimer.pos = (sprouttimer.pos+1) % (lens[sprouttimer.message_idx]-7);
	display_prout(0, 0);
}

u8 is_prout(void)
{
	return (sprouttimer.state == PROUT_RUN &&  (ptrMenu_L2 == &menu_L2_Prout));
}

void update_prout_timer()
{
}

void start_prout()
{
	sprouttimer.state = PROUT_RUN;
	//sprouttimer.message_idx = sDate.day % NUM_STRS;
	display_symbol(LCD_ICON_RECORD, SEG_ON);
}

void stop_prout()
{
	sprouttimer.pos = 0;
	sprouttimer.state = PROUT_STOP;
	sprouttimer.message_idx = (sprouttimer.message_idx + 1) % NUM_STRS;

	display_symbol(LCD_ICON_RECORD, SEG_OFF);

	// Call draw routine immediately
	display_prout(LINE2, DISPLAY_LINE_UPDATE_FULL);
}

void sx_prout(u8 line)
{
	if (button.flag.down)
	{
		if (sprouttimer.state == PROUT_STOP){
			start_prout();
		} else {
			stop_prout();
		}
	}
}

void mx_prout(u8 line)
{
}

void display_prout(u8 line, u8 update)
{
	u8 cur[7];
	memcpy(cur, strs[sprouttimer.message_idx] + sprouttimer.pos, 6);
	cur[6] = 0;

	display_chars(LCD_SEG_L2_5_0, cur, SEG_ON);
	//display_chars(LCD_SEG_L1_3_0, "JOSH", SEG_ON);
}

void reset_prout(void)
{
	sprouttimer.pos = 0;
	sprouttimer.state = PROUT_STOP;
	sprouttimer.message_idx = 0;
}

#endif /* CONFIG_PROUT */
