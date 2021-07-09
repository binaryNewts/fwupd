/*
 * Copyright (C) 2021 Twain Byrnes <binaryNewts@google.com>
 *                    George Popoola <gpopoola@google.com>
 *
 *
 * SPDX-License-Identifier: LGPL-2.1+
 */

#include "config.h"

#include <fwupdplugin.h>

#include <stdio.h>

#include <unistd.h>

void
fu_plugin_init (FuPlugin *plugin)
{
  fu_plugin_set_build_hash (plugin, FU_BUILD_HASH);
}

gboolean
fu_plugin_startup (FuPlugin *plugin, GError **error)
{
        return TRUE;
}

static void
fu_plugin_inhibit_suspend ()
{
        g_autofree gchar *lockdir = NULL;
	g_autofree gchar *inhibitsuspend_path = NULL;

	lockdir = fu_common_get_path (FU_PATH_KIND_LOCKDIR);
	inhibitsuspend_path = g_build_filename (lockdir, "power_override", "fwupd.lock", NULL);
	FILE *inhibit_suspend_file;
	inhibit_suspend_file = fopen (inhibitsuspend_path, "w");
	fprintf (inhibit_suspend_file, "%d", getpid());
	fclose (inhibit_suspend_file);
}

gboolean
fu_plugin_update_prepare (FuPlugin *plugin,
                          FwupdInstallFlags flags,
                          FuDevice *device,
                          GError **error)
{
        fu_plugin_inhibit_suspend ();

        return TRUE;
}

gboolean
fu_plugin_update_cleanup (FuPlugin *plugin,
                          FwupdInstallFlags flags,
                          FuDevice *dev,
                          GError **error)
{
        g_autofree gchar *lockdir = NULL;
        g_autofree gchar *inhibitsuspend_path = NULL;

        lockdir = fu_common_get_path (FU_PATH_KIND_LOCKDIR);
        inhibitsuspend_path = g_build_filename (lockdir, "power_override", "fwupd.lock", NULL);

	return (remove (inhibitsuspend_path) == 0);
}
