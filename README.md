# Qt_final
qimage and qvideo for end of term.

# 一、软件设计任务概述（应用背景、任务、开发环境搭建）
应用背景：
能对视频做一定程度的处理，并且能对视频的每一帧做一定程度的处理，并且能将视频的某一帧截下来放入图片编辑器处理。

任务：
写出图像编辑器和视频编辑器。

开发环境搭建：
Win :    Qt creator + LAV Filter(解码器,用于播放QMediaPlayer)
Ubuntu:  Qt creator + ffmpeg   (解码器,用于播放QMediaPlayer)

# 二、可行性研究、需求分析及分工
可行性研究：
可行，很有意义。

需求分析：
要实现对图片每个像素点的处理，要实现对视频每一帧的处理。

分工：
分别写图像编辑器和视频编辑器，并实现图像编辑器和视频编辑器之间的交互（比如将视频截图放入图片编辑器进行更复杂的操作）。

# 三、软件设计的基本原理和采用的主要方法(算法)与技术
图片： QLabel里显示QImage
视频：在QVideoSurface里播放，取出QVideoSurface里的帧(QVideoFrame)，将QVideoFrame转码为QImage，然后就可以在QLabel上一帧一帧的显示了。
灰度化：每个点的rgb值都设为原rgb值的和/3。
二值化：给定一个阈值，如果该点灰度值比规定的阈值小就设为黑，否则设为白。
均值滤波：3*3均值滤波，将周围包括自己九个格子里的rgb值取和/9，然后分别赋给当前像素点的rgb。
边缘检测：简易版candy算法(在理解了candy算法的原理自己写了一个边缘检测算法)
伽马滤波：解决图片某处过暗，人眼对其很难区分的问题，通过幂函数使图片对比度增强。

# 四、实现的过程与步骤
![image](https://github.com/zholofmeister/Qt_final/assets/49775592/13e9e709-a148-438d-ac9b-d3c94f166a45)

# 五、遇到的困难与获得的主要成果
做图片处理时基本没遇到什么困难，就是多选图片放到图片编辑器，删除某张图片带来显示索引的变化，有些边界情况会导致索引显示异常，调了一会就解决了。图像操作都是之前平时作业做过的，所以没遇到什么问题。
做视频处理学到的东西还是蛮多的。一开始先看了QGraphicsView显示视频，但在我的电脑上会有bug，有一半的可能开的出来视频，一半的可能开不出来，就不用这个方法了。然后听某位大佬说qt+vlc真香，但自己试了一下并不是很香，首先配置好vlc还是蛮麻烦的，其次我认为qt里取出vlc里每帧的过程很繁琐，先要调用回调函数balabala....，而且都是给你封装好的函数，可操作性空间很小，遂不用这个方法。最后了解到qt内有QVideoSurface这个类，可以在这个类里播放视频，在播放的时候可以取出QVideoFrame并把他转化为QImage，并且转化效率并不差，然后就可以在label里显示了，我觉得这种方法最好，代码很简洁，并且可操作的东西很多。
最后学了一下QMediaPlayer的基本操作，首先要下一个解码器才能让QMediaPlayer在qt内播放视频，windows下用的是LAV Filter，ubuntu下用的是ffmpeg，然后用QMediaPlayer发出的播放信号让QSlider接收，并且QSilder发出的移动信号让QMediaPlayer接收，实现进度条拖动和音量拖动功能。然后写了一点在视频播放过程中的图形处理，最后加了个截图功能，即把当前视频帧的图形截下来，并放到图片编辑器中进行更多的操作。

# 六、测试与运行记录
![水平对称](https://github.com/zholofmeister/Qt_final/assets/49775592/4f91496e-35aa-4292-bc19-1e5831696d6a)
![竖直对称](https://github.com/zholofmeister/Qt_final/assets/49775592/e19a7a06-7b3c-47fb-957f-e4263c1ba42e)
![逆时针旋转90度](https://github.com/zholofmeister/Qt_final/assets/49775592/240e1c35-a58f-4110-a241-0c642503c85f)
![顺时针旋转90度](https://github.com/zholofmeister/Qt_final/assets/49775592/69fadaef-66a8-49d0-87bd-0359315d609b)
![渐红](https://github.com/zholofmeister/Qt_final/assets/49775592/db1275ea-1a90-4c01-9ea2-fa0820486025)
![渐绿](https://github.com/zholofmeister/Qt_final/assets/49775592/bd713700-ce25-4ee4-b0b7-ae00ab32c0b6)
![渐蓝](https://github.com/zholofmeister/Qt_final/assets/49775592/ec3789d1-a4d5-4245-aee5-0a8e1a056100)
![灰度化](https://github.com/zholofmeister/Qt_final/assets/49775592/f2d8fa54-128c-4730-9870-06772a9b206c)
![伽马变换](https://github.com/zholofmeister/Qt_final/assets/49775592/49c0fad9-1a54-4fdc-bc73-7fe5885d143a)
![边缘检测](https://github.com/zholofmeister/Qt_final/assets/49775592/db1d32a8-de2f-4bce-93c8-5e2f2bda276f)
![正常播放](https://github.com/zholofmeister/Qt_final/assets/49775592/9f24d21a-1897-48ff-b8d1-5c818541be94)
![放大](https://github.com/zholofmeister/Qt_final/assets/49775592/d14813bc-2a6d-4167-a534-9e9124db64eb)
![缩小](https://github.com/zholofmeister/Qt_final/assets/49775592/aac5121f-f30f-4a57-9e16-e99604a135da)
![二值化播放](https://github.com/zholofmeister/Qt_final/assets/49775592/f1a42a56-d890-41c4-9390-8da40229726b)
![灰度化播放](https://github.com/zholofmeister/Qt_final/assets/49775592/855bc023-5c87-476f-8c91-8b3c1740ca9f)
![马赛克](https://github.com/zholofmeister/Qt_final/assets/49775592/eb215654-6d0e-4a90-ae1f-99bb33f44108)
![截图处理](https://github.com/zholofmeister/Qt_final/assets/49775592/26df0ecf-8fc7-444e-ac98-4d6040cf6d8c)

# 七、结果分析与小结
复习了之前的图像处理，学习了如何在qt内利用QVideoSurface和QMediaPlayer播放视频，并且可以将画面转化为QImage并进行图像处理.




