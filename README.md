# Introduction
zkcv is short for zk computer vision.
This is a simple computer vision library for myself.
This library is written in C.
This library is created in 2018.

# Basic

## bmp file support

##Image derivative

## raw_bmp file format support
  
### 简介
raw_bmp 是一种文件格式，是bmp文件的扩展，既包含bmp图像数据也包含原始raw数据。
  
### 动机
做图像处理经常要查看二维map，然而这些二维的map不一定是8bit灰度图，而是各种各样的格式，例如disparity map用uint16\_t或者uint32\_t，甚至是float类型。
一般情况下，我们会给这些map加入假彩色，用于可视化分析。
我们经常有这样的需求：希望能够有一个工具，能直接打开这些map，然后点击某个点，显示关于这个点的信息，例如坐标、值，或者拖框，查看map的max、min、average。
但是一旦把这些map转换成bmp之后，是无法完成这样的功能的，因为缺少原始数据。
如果不转换成bmp文件，那么在文件管理器里，数据文件都是没有办法预览的，在数据很多的情况下，很不快捷。
这就会导致我们在分析的时候需要两个文件，一个是bmp文件，用于在Windows Explorer里预览，另一个是原始文件，用于自己构建的工具进行更细致的预览和分析。
两个文件需要两个读写接口，而且bmp文件和raw文件的位置不一定很近，在这两个文件之间切换比较费事。
raw\_bmp就是为了解决这个问题而设计的，raw\_bmp除了包含转换成假彩色的bmp文件内容外，还在bmp文件末尾加入了map的原始数据，相当于把这两种数据合在一起。
这样设计，存下来的文件，乍一看仍然是bmp文件，各种文件管理器都能预览，然后也可以通过右键自定义程序打开，满足细致分析的需求。

### 设计

#### map数据类型
bmp格式中的file header包中的reverved用来表示当前map的数据类型，自建程序可以通过这个值来确当当前map的数据类型，定义如下表格。

| 值   | 0         | 1    | 2     | 3     | 4      | 5     | 6      | 7     | 8      |
| 类型 | 非raw_bmp | int8 | uint8 | int16 | uint16 | int32 | uint32 | float | double |

#### 文件协议

| File Header | Info Header | bmp data (rgb) | cmapN | cmap min | cmap max | raw data |
| 14 B        | 40 B        |                | 4 B   | 8 B      | 8 B      |          |

File Header: 文件头，固定14字节，除了上节说的reservered 1，其他值和标准bmp保持一致。
Info Header: 信息头，固定40字节，和标准bmp一致。
bmp data: bmp图像数据，rgb三通道，每通道用uint8表示，长度不固定。
cmapN: color map的 bin 个数，int32类型，color map是一个 大小为cmapN*3的表格，[0,cmapN-1]对应着cmapN种颜色。
cmap min: color map转换的数据最小值，double类型。
cmap max: color map转换的数据最大值，double类型，在转换假彩色的时候，把原始数据的[min, max] 部分映射到 color map的[0, cmapN-1]区间。
raw data: 原始数据，长宽和Info header里保持一致。

### 完成情况
目前只支持int16类型的数据，其他数据需要新增。

## Middle

### Harris corner


## Advanced
