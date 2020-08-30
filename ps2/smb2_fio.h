#ifndef __SMB2_FIO_H__
#define __SMB2_FIO_H__

/*
 * smb2 driver ops functions prototypes
 */
int SMB2_initdev(void);
int SMB2_dummy(void);
int SMB2_devctl(iop_file_t *f, const char *devname, int cmd, void *arg, unsigned int arglen, void *bufp, unsigned int buflen);


int SMB2_init(iop_device_t *iop_dev);
int SMB2_deinit(iop_device_t *dev);
int SMB2_open(iop_file_t *f, const char *filename, int flags, int mode);
int SMB2_close(iop_file_t *f);
int SMB2_lseek(iop_file_t *f, int pos, int where);
int SMB2_read(iop_file_t *f, void *buf, int size);
int SMB2_write(iop_file_t *f, void *buf, int size);
int SMB2_remove(iop_file_t *f, const char *filename);
int SMB2_mkdir(iop_file_t *f, const char *dirname, int mode);
int SMB2_rmdir(iop_file_t *f, const char *dirname);
int SMB2_dopen(iop_file_t *f, const char *dirname);
int SMB2_dclose(iop_file_t *f);
int SMB2_dread(iop_file_t *f, iox_dirent_t *dirent);
int SMB2_getstat(iop_file_t *f, const char *filename, iox_stat_t *stat);
int SMB2_rename(iop_file_t *f, const char *oldname, const char *newname);
int SMB2_chdir(iop_file_t *f, const char *dirname);
s64 SMB2_lseek64(iop_file_t *f, s64 pos, int where);

#endif
