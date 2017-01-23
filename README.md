# jsmpeg-vnc-linux
A semi-complete Linux port of [jsmpeg-vnc](https://github.com/phoboslab/jsmpeg-vnc).

# About
For a project I was working on I needed a way to stream desktop applications to the web browser. I tried creating a video stream using ffmpeg, but I quickly discovered that support of live video streaming was rather poor using only `<video>` tags. For interaction with desktop applications, the latency was too high (after a long battle to get it working at all). I then discovered the project [jsmpeg-vnc](https://github.com/phoboslab/jsmpeg-vnc) which suited my needs very well. By creating a video stream, sending it over a WebSocket, and rendering the video onto a `canvas` element using JavaScript control was given over the screen capturing and rendering. That way, the latency could be minimized and the framerate kept high.

Unfortunately, the jsmpeg-vnc project grabbed screen data using the Windows API. The project I was working on would be run on a Linux-based server. Thus, I ported the software to grab screen data using the X11 library instead.

# Ported
Sharing the whole desktop.

# Not ported
Sharing individual application windows and areas around the cursor.

# Known issues
No windows appear with GNOME/Unity, only the wallpaper is shown. Works with LXDE though.  (http://stackoverflow.com/questions/37972928/xgetimage-captures-wallpaper-but-no-windows-c-x11)
