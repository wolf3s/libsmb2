/* -*-  mode:c; tab-width:8; c-basic-offset:8; indent-tabs-mode:nil;  -*- */
#include "types.h"
#include "defs.h"
#include "irx.h"
#include "intrman.h"
#include "iomanX.h"
#include "io_common.h"
#include "sifman.h"
#include "stdio.h"
#include "sysclib.h"
#include "thbase.h"
#include "thsemap.h"
#include "errno.h"
#include "ps2smb.h"

#include "smb2_fio.h"

#include "compat.h"
#include "smb2.h"
#include "libsmb2.h"

int smb2man_io_sema;

static iop_device_ops_t smb2man_ops = {
	&SMB2_init,
	&SMB2_deinit,
	(void*)&SMB2_dummy,
	(void*)&SMB2_dummy,//&smb_open,
	(void*)&SMB2_dummy,//&smb_close,
	(void*)&SMB2_dummy,//&smb_read,
	(void*)&SMB2_dummy,//&smb_write,
	(void*)&SMB2_dummy,//&smb_lseek,
	(void*)&SMB2_dummy,
	(void*)&SMB2_dummy,//&smb_remove,
	(void*)&SMB2_dummy,//&smb_mkdir,
	(void*)&SMB2_dummy,//&smb_rmdir,
	(void*)&SMB2_dummy,//&smb_dopen,
	(void*)&SMB2_dummy,//&smb_dclose,
	(void*)&SMB2_dummy,//&smb_dread,
	(void*)&SMB2_dummy,//&smb_getstat,
	(void*)&SMB2_dummy,
	(void*)&SMB2_dummy,//&smb_rename,
	(void*)&SMB2_dummy,//&smb_chdir,
	(void*)&SMB2_dummy,
	(void*)&SMB2_dummy,
	(void*)&SMB2_dummy,
	(void*)&SMB2_dummy,//&smb_lseek64,
	(void*)&SMB2_dummy,//&smb_devctl,
	(void*)&SMB2_dummy,
	(void*)&SMB2_dummy,
	(void*)&SMB2_dummy
};

static iop_device_t smb2dev = {
	"smb2",
	IOP_DT_FS  | IOP_DT_FSEXT,
	1,
	"SMB2",
	&smb2man_ops
};

#define SMB_NAME_MAX	256

typedef struct {
	iop_file_t 	*f;
	struct smb2_fh  *fh;
	s64		filesize;
	s64		position;
	u32		mode;
	char		name[SMB_NAME_MAX];
} FHANDLE;

#define MAX_FDHANDLES		32
FHANDLE smb2man_fdhandles[MAX_FDHANDLES];

int SMB2_initdev(void)
{
	int i;
	FHANDLE *fh;

	DelDrv(smb2dev.name);
	if (AddDrv((iop_device_t *)&smb2dev))
		return 1;

	for (i=0; i<MAX_FDHANDLES; i++) {
		fh = (FHANDLE *)&smb2man_fdhandles[i];
		fh->f = NULL;
		fh->filesize = 0;
		fh->position = 0;
		fh->mode = 0;
	}

	return 0;
}

int SMB2_init(iop_device_t *dev)
{
	smb2man_io_sema = CreateMutex(IOP_MUTEX_UNLOCKED);

	return 0;
}

int SMB2_deinit(iop_device_t *dev)
{
	DeleteSema(smb2man_io_sema);

	return 0;
}

int SMB2_dummy(void)
{
	return -EIO;
}
