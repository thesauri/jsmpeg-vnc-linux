# jsmpeg-vnc-linux
A semi-complete Linux port of [jsmpeg-vnc](https://github.com/phoboslab/jsmpeg-vnc).

## Compiling on Ubuntu 20.04
Install the following packages:

- build-essential
- libx11-dev
- libx11-dev
- libavutil-dev
- libavcodec-dev
- libswscale-dev
- libxtst-dev
- libssl-dev
- pkg-config
- zlib1g-dev

In addition to this, compile and install [libwebsockets 4.1](https://github.com/warmcat/libwebsockets/tree/v4.1-stable).

Then, run the following commands in the root directory:

```
cmake .
make
```

See the [Dockerfile](Dockerfile) for an example on how to install the dependencies, compile libwebsockets, and compile jsmpeg-vnc-linux (it won't run out-of-the-box in Docker though, as there is nothing to stream).

## Running

```
jsmpeg-vnc [options] <window name>

Options:
  -b bitrate in kilobit/s (default: estimated by output size)
  -s output size as WxH. E.g: -s 640x480 (default: same as window size)
  -f target framerate (default: 60)
  -p port (default: 8080)
  -c crop area in the captured window as X,Y,W,H. E.g.: -c 200,300,640,480
  -i enable/disable remote input. E.g. -i 0 (default: 1)

Use "desktop" as the window name to capture the whole Desktop. Use "cursor"
to capture the window at the current cursor position.

Example:
jsmpeg-vnc -b 2000 -s 640x480 -f 30 -p 9006 "Quake 3: Arena"

To enable mouse lock in the browser (useful for games that require relative
mouse movements, not absolute ones), append "?mouselock" at the target URL
i.e: http://<server-ip>:8080/?mouselock
```
(Copied from the [parent project](https://github.com/phoboslab/jsmpeg-vnc))

## About
For a project I was working on I needed a way to stream desktop applications to the web browser. I tried creating a video stream using ffmpeg, but I quickly discovered that support of live video streaming was rather poor using only `<video>` tags. For interaction with desktop applications, the latency was too high (after a long battle to get it working at all). I then discovered the project [jsmpeg-vnc](https://github.com/phoboslab/jsmpeg-vnc) which suited my needs very well. By creating a video stream, sending it over a WebSocket, and rendering the video onto a `canvas` element using JavaScript control was given over the screen capturing and rendering. That way, the latency could be minimized and the framerate kept high.

Unfortunately, the jsmpeg-vnc project grabbed screen data using the Windows API. The project I was working on would be run on a Linux-based server. Thus, I ported the software to grab screen data using the X11 library instead.

## Ported
Sharing the whole desktop.

## Not ported
Sharing individual application windows and areas around the cursor.

## Known issues
No windows appear with GNOME/Unity, only the wallpaper is shown. Works with LXDE though.  (http://stackoverflow.com/questions/37972928/xgetimage-captures-wallpaper-but-no-windows-c-x11)
