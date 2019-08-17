#ifndef _CANVASCONTEXT_IMAGE_H_
#define _CANVASCONTEXT_IMAGE_H_

#include <string>
#include <thread>

#include <v8.h>
#include <node.h>
#include <nan.h>

#include <defines.h>
#include <canvas/include/Context.h>
#include <canvas/include/Image.h>
#include <canvas/include/ImageData.h>
#include <canvas/include/Resources.h>
#include <SkData.h>
#include <SkImage.h>
#include <nanosvg.h>
#include <nanosvgrast.h>
#include <windowsystem.h>
#include <threadpool.h>

using namespace v8;
using namespace node;

class Image : public ObjectWrap {
public:
  static Local<Object> Initialize(Isolate *isolate);
  unsigned int GetWidth();
  unsigned int GetHeight();
  unsigned int GetNumChannels();
  // unsigned char *GetData();
  void Load(Local<ArrayBuffer> arrayBuffer, size_t byteOffset, size_t byteLength, Local<Function> cbFn);
  // void Set(canvas::Image *image);

protected:
  static NAN_METHOD(New);
  static NAN_GETTER(WidthGetter);
  static NAN_GETTER(HeightGetter);
  static NAN_GETTER(DataGetter);
  static NAN_METHOD(Load);

  Image();
  ~Image();

private:
  sk_sp<SkImage> image;
  Nan::Persistent<Uint8ClampedArray> dataArray;

  Nan::Persistent<Function> cbFn;
  bool loading;
  bool hasCbFn;
  std::string error;
  uv_sem_t sem;

  friend class CanvasRenderingContext2D;
  friend class ImageData;
  friend class ImageBitmap;
};

#include "canvas-context.h"

#endif
