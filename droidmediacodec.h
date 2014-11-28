#ifndef DROID_MEDIA_CODEC_H
#define DROID_MEDIA_CODEC_H

#include "droidmedia.h"
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
class DroidMediaCodec;
#else
typedef void DroidMediaCodec;
#endif

typedef enum {
  DROID_MEDIA_CODEC_ENCODER = 0x1,
  DROID_MEDIA_CODEC_SW_ONLY = 0x2,
  DROID_MEDIA_CODEC_HW_ONLY = 0x4,
  DROID_MEDIA_CODEC_STORE_META_DATA_IN_VIDEO_BUFFERS = 0x8,
} DroidMediaCodecFlags;

typedef struct {
  const char *type;
  ssize_t width;
  ssize_t height;
  int32_t fps;
  void *codec_data;
  ssize_t codec_data_size;
} DroidMediaCodecMetaData;

ssize_t droid_media_codec_find_by_type(const char *type, bool encoder);
ssize_t droid_media_codec_find_by_name(const char *name);
size_t droid_media_codec_count();
const char *droid_media_codec_get_name(size_t index);
bool droid_media_codec_is_encoder(size_t index);
bool droid_media_codec_has_quirk(size_t index, const char *quirkName);
char **droid_media_codec_get_supported_types(size_t index, ssize_t *size);
bool droid_media_codec_get_capabilities(size_t index, const char *type,
                                        uint32_t **profiles, uint32_t **levels, ssize_t *profiles_levels_size,
                                        uint32_t **color_formats, ssize_t *color_formats_size);

DroidMediaCodec *droid_media_codec_create(DroidMediaCodecMetaData *meta, DroidMediaCodecFlags flags);
bool droid_media_codec_start(DroidMediaCodec *codec);
void droid_media_codec_stop(DroidMediaCodec *codec);
void droid_media_codec_destroy(DroidMediaCodec *codec);
void droid_media_codec_write(DroidMediaCodec *codec, DroidMediaData *data, DroidMediaBufferCallbacks *cb);

  // TODO:
bool droid_media_codec_read(DroidMediaCodec *codec);

#ifdef __cplusplus
};
#endif

#endif /* DROID_MEDIA_CODEC_H */
