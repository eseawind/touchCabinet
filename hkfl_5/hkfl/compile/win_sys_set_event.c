/*
 * This file is automatically generated by func_gen.c,don't edit
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lincon.h"
#include "linconhmi.h"
#include "userfunc.h"

#ifndef HMI_GEN_FUNC_FILE
static void widget_button_11_click(void);
static void widget_button_10_click(void);
static void widget_button_9_click(void);
static void widget_button_6_click(void);

hmi_widget_func_t hmi_window_77696E5F7379735F736574_event_funcs[]={
{"button_11_click",(void *)widget_button_11_click},
{"button_10_click",(void *)widget_button_10_click},
{"button_9_click",(void *)widget_button_9_click},
{"button_6_click",(void *)widget_button_6_click},
{NULL,NULL}
};

static void widget_button_11_click(void)
{
	{
#line 1 "�ؼ�:button_11,�¼�:click"
hmi_window_show("win_sys_reset");
	}
{
}
}

static void widget_button_10_click(void)
{
	{
#line 1 "�ؼ�:button_10,�¼�:click"
hmi_window_show("win_sys_set_time");
	}
{
}
}

static void widget_button_9_click(void)
{
	{
#line 1 "�ؼ�:button_9,�¼�:click"
hmi_window_show("win_change_admin_psd");

	}
{
}
}

static void widget_button_6_click(void)
{
	{
#line 1 "�ؼ�:button_6,�¼�:click"
hmi_window_hide("win_sys_set");

	}
{
}
}

#endif