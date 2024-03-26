import wave


def unhide(input, step, output):
    # 打开藏有其它文件的歌曲文件，读取数据
    with wave.open(input, 'rb') as f:
        wav_data = f.readframes(-1)

    # 提取wav_data中的特殊位置数据
    extract_data = bytearray()
    for index in range(0, len(wav_data), step):
        extract_data += (wav_data[index]).to_bytes(1, byteorder='little')

    # 得到被隐藏的文件的大小
    file_len = int.from_bytes(extract_data[0:4], 'little')

    # 重新生成被隐藏的文件
    with open(output, 'wb') as f:
        f.write(extract_data[4: file_len+4])


def hide(input, file, step, output):
    with open(file, 'rb') as f:
        txt_data = f.read()
        file_len = len(txt_data)
        txt_data = file_len.to_bytes(4, byteorder='little') + txt_data

    # 打开wav格式的歌曲文件，读取数据
    with wave.open(input, "rb") as f:
        attrib = f.getparams()    # 获取音频属性
        wav_data = bytearray(f.readframes(-1))

    # 隐藏txt_data中的数据到wav_data中
    for index in range(len(txt_data)):
        wav_data[index * step] = txt_data[index]

    # 生成新的歌曲文件
    with wave.open(output, "wb") as f:
        f.setparams(attrib)     # 设置音频属性
        f.writeframes(wav_data)  # 写入数据


def v(input, step, output):#调整音乐速度
    # 打开wav格式的歌曲文件，读取数据
    with wave.open(input, "rb") as f:
        attrib = f.getparams()    # 获取音频属性
        rate = f.getframerate()
        wav_data = bytearray(f.readframes(-1))

    # 生成新的歌曲文件
    with wave.open(output, "wb") as f:
        f.setparams(attrib)     # 设置音频属性
        f.setframerate(rate*step)
        f.writeframes(wav_data)  # 写入数据


# hide('1.wav', 's.txt', 2, '114514.wav')
v('1.wav', 0.6, '1919810.wav')
# unhide('114514.wav', 1, '1.txt')
