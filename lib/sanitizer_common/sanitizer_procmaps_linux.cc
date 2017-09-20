//===-- sanitizer_procmaps_linux.cc ---------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Information about the process mappings (Linux-specific parts).
//===----------------------------------------------------------------------===//

#include "sanitizer_platform.h"
#if SANITIZER_LINUX
#include "sanitizer_common.h"
#include "sanitizer_procmaps.h"
#include "sanitizer_linux.h"

namespace __sanitizer {

<<<<<<< HEAD
  struct ProcSelfMapsBuff {
    char *data;
    uptr mmaped_size;
    uptr len;
  };

  struct MemoryMappingLayoutData {
    ProcSelfMapsBuff proc_self_maps;
    const char *current;
    // Static mappings cache.
    static ProcSelfMapsBuff cached_proc_self_maps;
    static StaticSpinMutex cache_lock;  // protects cached_proc_self_maps_.
  };
=======

>>>>>>> 169007b9587e002f2f16c5ae1c9518a1db17c3ca
void ReadProcMaps(ProcSelfMapsBuff *proc_maps) {
  ReadFileToBuffer("/proc/self/maps", &proc_maps->data, &proc_maps->mmaped_size,
                   &proc_maps->len);
}

static bool IsOneOf(char c, char c1, char c2) {
  return c == c1 || c == c2;
}

bool MemoryMappingLayout::Next(MemoryMappedSegment *segment) {
  char *last = data_->proc_self_maps.data + data_->proc_self_maps.len;
<<<<<<< HEAD
  if (data_->current_ >= last) return false;
  char *next_line =
  (char*)internal_memchr(data_->current_, '\n', last - data_->current_);
  if (next_line == 0)
    next_line = last;
  // Example: 08048000-08056000 r-xp 00000000 03:0c 64593   /foo/bar
  segment->start = ParseHex(&data_->current_);
  CHECK_EQ(*data_->current_++, '-');
  segment->end = ParseHex(&data_->current_);
  CHECK_EQ(*data_->current_++, ' ');
  CHECK(IsOneOf(*data_->current_, '-', 'r'));
  segment->protection = 0;
  if (*data_->current_++ == 'r') segment->protection |= kProtectionRead;
  CHECK(IsOneOf(*data_->current_, '-', 'w'));
  if (*data_->current_++ == 'w') segment->protection |= kProtectionWrite;
  CHECK(IsOneOf(*data_->current_, '-', 'x'));
  if (*data_->current_++ == 'x') segment->protection |= kProtectionExecute;
  CHECK(IsOneOf(*data_->current_, 's', 'p'));
  if (*data_->current_++ == 's') segment->protection |= kProtectionShared;
  CHECK_EQ(*data_->current_++, ' ');
  segment->offset = ParseHex(&data_->current_);
  CHECK_EQ(*data_->current_++, ' ');
  ParseHex(&data_->current_);
  CHECK_EQ(*data_->current_++, ':');
  ParseHex(&data_->current_);
  CHECK_EQ(*data_->current_++, ' ');
  while (IsDecimal(*data_->current_))
    data_->current_++;
  // Qemu may lack the trailing space.
  // https://github.com/google/sanitizers/issues/160
  // CHECK_EQ(*data_->current_++, ' ');
  // Skip spaces.
  while (data_->current_ < next_line && *data_->current_ == ' ')
    data_->current_++;
  // Fill in the filename.
  if (segment->filename) {
    uptr len =
    Min((uptr)(next_line - data_->current_), segment->filename_size - 1);
    internal_strncpy(segment->filename, data_->current_, len);
    segment->filename[len] = 0;
  }

  data_->current_ = next_line + 1;
=======
  if (data_->current >= last) return false;
  char *next_line =
  (char*)internal_memchr(data_->current, '\n', last - data_->current);
  if (next_line == 0)
    next_line = last;
  // Example: 08048000-08056000 r-xp 00000000 03:0c 64593   /foo/bar
  segment->start = ParseHex(&data_->current);
  CHECK_EQ(*data_->current++, '-');
  segment->end = ParseHex(&data_->current);
  CHECK_EQ(*data_->current++, ' ');
  CHECK(IsOneOf(*data_->current, '-', 'r'));
  segment->protection = 0;
  if (*data_->current++ == 'r') segment->protection |= kProtectionRead;
  CHECK(IsOneOf(*data_->current, '-', 'w'));
  if (*data_->current++ == 'w') segment->protection |= kProtectionWrite;
  CHECK(IsOneOf(*data_->current, '-', 'x'));
  if (*data_->current++ == 'x') segment->protection |= kProtectionExecute;
  CHECK(IsOneOf(*data_->current, 's', 'p'));
  if (*data_->current++ == 's') segment->protection |= kProtectionShared;
  CHECK_EQ(*data_->current++, ' ');
  segment->offset = ParseHex(&data_->current);
  CHECK_EQ(*data_->current++, ' ');
  ParseHex(&data_->current);
  CHECK_EQ(*data_->current++, ':');
  ParseHex(&data_->current);
  CHECK_EQ(*data_->current++, ' ');
  while (IsDecimal(*data_->current))
    data_->current++;
  // Qemu may lack the trailing space.
  // https://github.com/google/sanitizers/issues/160
  // CHECK_EQ(*data_->current++, ' ');
  // Skip spaces.
  while (data_->current < next_line && *data_->current == ' ')
    data_->current++;
  // Fill in the filename.
  if (segment->filename) {
    uptr len =
    Min((uptr)(next_line - data_->current), segment->filename_size - 1);
    internal_strncpy(segment->filename, data_->current, len);
    segment->filename[len] = 0;
  }

  data_->current = next_line + 1;
>>>>>>> 169007b9587e002f2f16c5ae1c9518a1db17c3ca
  return true;
}

}  // namespace __sanitizer

#endif  // SANITIZER_LINUX
