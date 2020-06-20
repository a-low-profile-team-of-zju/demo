# flowchart小型流程图绘制程序
### 项目背景：

c大程大作业题目要求：**小型算法流程图绘制工具**

题目描述：基于libgraphics，实现简单流程图的输入、编辑功能，提供文件保存和读取功能。可选：参考结合编译原理抽象语法树有关知识，对简单C语言代码能够绘制程序流程。

---------

### 更新日志：

2020/6/20前 我忘了: P

2020/6/20 添加README

-------

### 编译：

编译环境：Visual Studio 17/19

编译方法：新建项目或使用老师所给的sln解决方案文件，配置按要求完成即可，将源代码添加进项目中，编译即可。

注意，需要的库文件请使用本仓库中提供的库文件，因为做过修改与改善。

**若编译出现问题无法解决可使用已编译好的exe可执行文件打开即可使用。*

-----

### 使用说明：

#### 写在前面：

由于提供的库（graphics，imgui）的运行效率实在不敢恭维，亲测不同的计算机运行时的效果不尽相同，如在使用时出现难以忍受的卡顿请尝试在电池选项中选择最佳性能，一般来说能解决英文界面下的卡顿情况，中文界面相较英文界面会更为卡顿，需要看你的计算机的具体情况，亲测部分计算机会卡顿，部分计算机无明显卡顿。考虑到这种情况，我们并不觉得这是一个值得修复的“特性”。

#### 界面介绍：

![Image text](https://github.com/a-low-profile-team-of-zju/demo/blob/master/image/2020-06-20.png)

#### menu菜单栏：

##### 	File/文件:

###### 		New/新建：

​			重新打开应用程序，如画布上已有图形则先提示是否保存。

###### 		Open/打开：

​			打开一个保存过的文件，后缀名为txt。

###### 		Save/保存：

​			如果已保存过则将改动保存至已保存的文件。

###### 		Save as/另存为：

​			保存为新的文件。

###### 		Close/关闭：

​			关闭应用程序前先提示是否保存。

###### 		Exit/退出：

​			直接关闭应用程序。

##### 	Edit/编辑：

​		略，因为均为各位熟悉的操作。

##### 	Draw/绘图：

​		包含了矩形、圆角矩形等9种图形。

​		**注意，并不推荐使用menu里的Draw/绘图来绘制图形，极力推荐使用侧边栏的绘图工具绘图，不要问为什么，用了你就知道了。*🤣

##### 	Fill Colors/填充颜色：

​		包含了14种颜色，其中黑色为默认颜色，White(!)/白色(!)表示慎用白色，否则会与背景白色混为一体，可能无法分辨。

##### 	Font Colors/文本颜色：

​		同Fill Colors/填充颜色。

##### 	Pen Size/画笔大小：

​		提供了5种画笔大小，默认为3号线。

##### 	Help/帮助：

###### 		About us/关于我们：

​			介绍了队名。

###### 		More Info/更多信息：

​			想必不用多说。

###### 		Switch language/切换语言：

​			顾名思义……

#### sideButton侧边栏：

​			均为menu中的常用功能，极力推荐使用此侧边栏中的按钮，而非menu中的按钮。

#### bottomBar底部状态栏：

##### 	左下状态：

​		显示当前操作。

##### 	文本输入框：

​		浅灰色区域为文本输入框，可在此输入文本，已支持中文输入。

#### 操作：

​	选中使用鼠标左键点击图形，选中后图形周围会有windows蓝色的选中框，选中后可以进行修改颜色，大小，修改文字的操作。

​	取消选中需在图形外点击鼠标右键，即可取消选中。

​	鼠标滚轮可控制图形的缩放。

​	拖动图形只需在图形内按下鼠标左键拖动鼠标即可实现。

### 最后：

​	希望看到这里的朋友不要通过我的contributor来揣测我们组的任何成员，本仓库不透露任何成员信息，因此并不破坏匿名互评的规则。

