/*
 * Copyright (C) 2011 Michitaka Ohno <elpeo@mars.dti.ne.jp>
 * You can redistribute it and/or modify it under GPL2.
 */

#include <ruby.h>
#include <usb.h>
#include <stdio.h>

extern usb_dev_handle* pcsensor_open();
extern void pcsensor_close(usb_dev_handle* lvr_winusb);
extern float pcsensor_get_temperature(usb_dev_handle* lvr_winusb);

static VALUE rb_temperature(VALUE self){
	usb_dev_handle* lvr_winusb = pcsensor_open();
	if(!lvr_winusb) return Qnil;
	float tempc = pcsensor_get_temperature(lvr_winusb);
	pcsensor_close(lvr_winusb);
	return rb_float_new(tempc);
}

Init_temper(void){
	VALUE mTemper;
	mTemper = rb_define_module("Temper");
	rb_define_module_function(mTemper, "temperature", rb_temperature, 0);
}
