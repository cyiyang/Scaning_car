# 二维码例程
#
# 这个例子展示了OpenMV Cam使用镜头校正来检测QR码的功能（请参阅qrcodes_with_lens_corr.py脚本以获得更高的性能）。
import sensor, image, time
 
sensor.reset()                       # 重置感光元件，重置摄像机
sensor.set_pixformat(sensor.RGB565)  # 设置颜色格式为RGB565，彩色，每个像素16bit
sensor.set_framesize(sensor.QVGA)    # 图像大小为QVGA
sensor.skip_frames(time = 2000)      # 跳过n张照片，在更改设置后，跳过一些帧，等待感光元件变稳定。
sensor.set_auto_gain(False)          # 必须关闭此功能，以防止图像冲洗…
clock = time.clock()
 
while(True):
    clock.tick()
    img = sensor.snapshot()          # 截取感光元件中的一张图片
    #采用软件畸变矫正，因为OpenMV标配自带的镜头是2.8mm聚焦的鱼眼镜头，会存在桶形畸变，也就是鱼眼效果，会影响识别二维码
    #畸变矫正运算量比较大，可能会影响帧率。对帧率有要求，可购买无畸变镜头，就无需软件畸变矫正
    img.lens_corr(1.8)               # 1.8的强度参数对于2.8mm镜头来说是不错的。
    for code in img.find_qrcodes():  # 进行二维码检测
        img.draw_rectangle(code.rect(), color = (255, 0, 0))
        #print(code)                  # 输出二维码内容
        message = code.payload()
        if message == 'OpenMV':
            print('ok',message)
        else:
            print('非目标二维码') #检测到非目标二维码打印
    #print(clock.fps())