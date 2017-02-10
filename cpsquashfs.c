#include <stdio.h>
#include <stdint.h>
#include <endian.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/magic.h>
#include <sys/types.h>
#include <sys/stat.h>

struct squashfs_sb {
  uint32_t       s_magic;
  unsigned int   inodes;
  int            mkfs_time;
  unsigned int   block_size;
  unsigned int   fragments;
  unsigned short compression;
  unsigned short block_log;
  unsigned short flags;
  unsigned short no_ids;
  unsigned short s_major;
  unsigned short s_minor;
  long long      root_inode;
  uint64_t       bytes_used;
  /* ignore the rest */
} __attribute__ ((packed));

#define MIN(a,b) (((a)<(b))?(a):(b))

static inline size_t ALIGN_TO(size_t l, size_t ali) {
  return ((l + ali - 1) & ~(ali - 1));
}

int main(int argc, char **argv) {
  struct squashfs_sb sb;
  struct stat stat;
  int r, in, out;
  uint64_t len;
  ssize_t s;

  if (argc < 3) {
    fprintf(stderr, "Usage: %s <in-file> <out-file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  in = open(argv[1], O_RDONLY);
  if (in < 0) {
    fprintf(stderr, "Error opening %s: %s\n", argv[1], strerror(errno));
    return EXIT_FAILURE;
  }

  r = fstat(in, &stat);
  if (r < 0) {
    fprintf(stderr, "Error reading stats from %s: %s\n", argv[1], strerror(errno));
    return EXIT_FAILURE;
  }

  s = pread(in, &sb, sizeof(sb), 0);
  if ((size_t) s < sizeof(sb)) {
    fprintf(stderr, "Error reading from %s: %s\n", argv[1], strerror(errno));
    return EXIT_FAILURE;
  }

  if (le32toh(sb.s_magic) != SQUASHFS_MAGIC) {
    fprintf(stderr, "No squashfs superblock magic in %s. Exiting.\n", argv[1]);
    return EXIT_FAILURE;
  }

  len = ALIGN_TO(le64toh(sb.bytes_used), 4096);

  out = open(argv[2], O_WRONLY | O_CREAT | O_LARGEFILE | O_TRUNC, stat.st_mode);
  if (out < 0) {
    fprintf(stderr, "Error opening %s: %s\n", argv[2], strerror(errno));
    return EXIT_FAILURE;
  }

  while (len > 0) {
    char buf[64 * 1024];
    size_t l = MIN(len, sizeof(buf));

    s = read(in, buf, l);
    if ((size_t) s < l) {
      fprintf(stderr, "Error reading from %s: %s\n", argv[1], strerror(errno));
      return EXIT_FAILURE;
    }

    s = write(out, buf, l);
    if ((size_t) s < l) {
      fprintf(stderr, "Error writing to %s: %s\n", argv[2], strerror(errno));
      return EXIT_FAILURE;
    }

    len -= l;
  }

  close(in);
  close(out);

  return 0;
}