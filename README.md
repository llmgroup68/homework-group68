# homework-group68
Project1: implement the naïve birthday attack of reduced SM3


实现方式：CPP  


成员：李丽敏 202100460130（仅一人一组）


实验概述；


主要包括以下部分：（只展示部分关键代码）


1：定义了一些辅助宏和函数，如左循环移位、反转四字节整型字节序等。


<img width="471" alt="image" src="https://github.com/llmgroup68/homework-group68/assets/138642474/b31cfa90-c62d-4611-878c-3abe86993262">

2：定义了SM3算法中用到的常量和函数，如T函数、FF函数、GG函数和P0、P1函数等。
<img width="419" alt="image" src="https://github.com/llmgroup68/homework-group68/assets/138642474/b3f54cb9-cdc9-47c3-8bfe-8f8ad730fe3d">

3：实现了SM3算法的初始化函数SM3Init和消息处理函数SM3ProcessMessageBlock。
<img width="586" alt="image" src="https://github.com/llmgroup68/homework-group68/assets/138642474/b4a78f3d-1a4a-41bb-8de2-551fe9bdc26a">

4：主函数中生成了一个随机字符串并计算其哈希值，并存储在output数组中。使用一个循环不断生成新的随机字符串并计算其哈希值，直到找到与output相同的哈希值。


<img width="352" alt="image" src="https://github.com/llmgroup68/homework-group68/assets/138642474/fa5db40e-1dd7-4cf5-9b7b-8f6794b6e4be">

运行截图：


<img width="620" alt="image" src="https://github.com/llmgroup68/homework-group68/assets/138642474/acac9449-3b74-4673-bfa3-8466bcb0d18d">
