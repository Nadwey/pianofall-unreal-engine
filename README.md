# Pianofall Unreal Engine

[Pianofall](https://github.com/ste-art/Pianofall) but in Unreal Engine...

![Pianofall Unreal Engine - title screen](https://github.com/Nadwey/pianofall-unreal-engine/assets/81181783/b60998cc-6fd7-4cb8-8ae7-3932132751cf)

![A lot of notes](https://github.com/Nadwey/pianofall-unreal-engine/assets/81181783/c5c791cc-4c02-4e68-a0fb-e73df1e3e715)

![A lot of colorful notes](https://github.com/Nadwey/pianofall-unreal-engine/assets/81181783/578b6f71-f076-4434-9f36-e9153cd856f3)

[Showcase](https://www.youtube.com/watch?v=H7Ljd3_qltU)

## Merge frames using FFmpeg

To merge the frames you need to execute this command in the directory where the frames are located (Frame000001.png, Frame000002.png, Frame000003.png, etc...):

```batch
ffmpeg -i audio.mp3 -framerate 60 -i Frame%06d.png output.mp4
```
