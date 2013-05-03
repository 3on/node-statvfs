/*

http://stackoverflow.com/questions/4965355/converting-statvfs-to-percentage-free-correctly

*/

#include <stdio.h>
#include <sys/statvfs.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
    struct statvfs vfs;
    int res = statvfs(argv[1], &vfs);
    
    if(res != 0)
        assert("statvfs failed");

    printf("f_bsize (block size): %lu\n"
       "f_frsize (fragment size): %lu\n"
       "f_blocks (size of fs in f_frsize units): %lu\n"
       "f_bfree (free blocks): %lu\n"
       "f_bavail free blocks for unprivileged users): %lu\n"
       "f_files (inodes): %lu\n"
       "f_ffree (free inodes): %lu\n"
       "f_favail (free inodes for unprivileged users): %lu\n"
       "f_fsid (file system ID): %lu\n"
       "f_flag (mount flags): %lu\n"
       "f_namemax (maximum filename length)%lu\n",
       (long unsigned int) vfs.f_bsize,
       (long unsigned int) vfs.f_frsize,
       (long unsigned int) vfs.f_blocks,
       (long unsigned int) vfs.f_bfree,
       (long unsigned int) vfs.f_bavail,
       (long unsigned int) vfs.f_files,
       (long unsigned int) vfs.f_ffree,
       (long unsigned int) vfs.f_favail,
       (long unsigned int) vfs.f_fsid,
       (long unsigned int) vfs.f_flag,
       (long unsigned int) vfs.f_namemax);

    long unsigned int free_space = vfs.f_bfree * vfs.f_bsize; 
    long unsigned int total_space = vfs.f_blocks * vfs.f_frsize;
    long unsigned int used_space = free_space - total_space;
    
    // fs size in f_frsize
    // (vfs.f_blocks * vfs.f_frsize)

    printf("total: %lu\n", total_space);
    printf("free: %lu\n", free_space);

    return 0;
}

