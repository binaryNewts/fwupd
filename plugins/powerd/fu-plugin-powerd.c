/*
 * Copyright (C) 2021 Twain Byrnes <binarynewts@google.com>
 * Copyright (C) 2021 George Popoola <gpopoola@google.com>
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
<<<<<<< HEAD
=======
}

static void
fu_plugin_inhibit_suspend ()
{
        g_autofree gchar *lockfilename = fu_common_get_path (FU_PATH_KIND_LOCKFILE);
        FILE *inhibit_suspend_file;
        inhibit_suspend_file = fopen (lockfilename, "w");
        fprintf (inhibit_suspend_file, "%d", getpid());
        fclose (inhibit_suspend_file);
>>>>>>> 608f1be3 (CHROMIUM: inhibit system suspend during update)
}

gboolean
fu_plugin_update_prepare (FuPlugin *plugin,
                          FwupdInstallFlags flags,
                          FuDevice *device,
                          GError **error)
{
<<<<<<< HEAD
        return TRUE;
=======
        fu_plugin_inhibit_suspend ();

        return TRUE;
}

gboolean
fu_plugin_update_cleanup (FuPlugin *plugin,
                          FwupdInstallFlags flags,
                          FuDevice *dev,
                          GError **error)
{
        g_autofree gchar *lockfilename = fu_common_get_path (FU_PATH_KIND_LOCKFILE);
        return (remove (lockfilename) == 0);
>>>>>>> 608f1be3 (CHROMIUM: inhibit system suspend during update)
}
