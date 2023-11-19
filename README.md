# Pianofall Unreal Engine

[Pianofall](https://github.com/ste-art/Pianofall) but in Unreal Engine...

> [!WARNING]
> Chaos can crash on larger midis, I'm trying to fix this.

![Pianofall Unreal Engine - Main Menu](https://github.com/Nadwey/pianofall-unreal-engine/assets/81181783/2f5fce7c-23c8-4f1a-a072-a09f64f553f4)

![A lot of notes](https://github.com/Nadwey/pianofall-unreal-engine/assets/81181783/c5c791cc-4c02-4e68-a0fb-e73df1e3e715)

![A lot of colorful notes](https://github.com/Nadwey/pianofall-unreal-engine/assets/81181783/578b6f71-f076-4434-9f36-e9153cd856f3)

[![](https://github.com/Nadwey/pianofall-unreal-engine/assets/81181783/27ce0f90-640e-4560-809f-bd2c3bc42b02)](https://www.youtube.com/watch?v=TOIqd2r_3cE)

## Merge frames using FFmpeg

To merge the frames you need to execute this command in the directory where the frames are located (Frame000001.png, Frame000002.png, Frame000003.png, etc...):

```batch
ffmpeg -i audio.mp3 -framerate 60 -i Frame%06d.png output.mp4
```
