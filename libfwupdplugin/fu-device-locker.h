/*
 * Copyright (C) 2017 Richard Hughes <richard@hughsie.com>
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#pragma once

#include <glib-object.h>

#define FU_TYPE_DEVICE_LOCKER (fu_device_locker_get_type ())

G_DECLARE_FINAL_TYPE (FuDeviceLocker, fu_device_locker, FU, DEVICE_LOCKER, GObject)

/**
 * FuDeviceLockerFunc:
 *
 * Callback to use when opening and closing using [ctor@DeviceLocker.new_full].
 **/
typedef gboolean (*FuDeviceLockerFunc)		(GObject		*device,
						 GError			**error);

FuDeviceLocker	*fu_device_locker_new		(gpointer		 device,
						 GError			**error)
						 G_GNUC_WARN_UNUSED_RESULT;
FuDeviceLocker	*fu_device_locker_new_full	(gpointer		 device,
						 FuDeviceLockerFunc	 open_func,
						 FuDeviceLockerFunc	 close_func,
						 GError			**error)
						 G_GNUC_WARN_UNUSED_RESULT;
gboolean	 fu_device_locker_close		(FuDeviceLocker		*self,
						 GError			**error)
						 G_GNUC_WARN_UNUSED_RESULT;
