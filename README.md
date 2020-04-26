# randombinfile
A random file content generator

linux下载：https://github.com/sffred/randombinfile/releases/download/v0.1/rp-linux-x86_64-0.1.zip

win64下载：https://github.com/sffred/randombinfile/releases/download/v0.1/rp-win64-0.1.zip

这是一个垃圾文件生成器，用于生成测试用的随机文件。采用了尽可能高效的随机算法，以提高文件生成效率（比rand()快一个数量级，可能没那么随机，但是有效）

源码见rp.c，可自行用参数g++ rp.c -o rp -static编译校验，安全无毒没有危险。

用法

rp有4个参数，-o,-n,-s,-d。-o 后跟输出路径，不能带空格，最后需要有斜杠或反斜杠，缺省输出到程序所在目录；-n后跟输出文件数量，缺省为4；-s后跟输出文件大小（以4KiB为单位），缺省为2^18（1GiB），不应小于2048；如果加上-d参数，则输出文件大小会有抖动，否则输出精确的指定大小。


例如PS C:\User\xxx\Downloads> rp -o D:\a\ -n 100 会在D盘a文件夹下生成100个1G大小的随机文件。


如有问题，请联系sffredx@gmail.com
